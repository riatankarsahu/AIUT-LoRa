/* -*- c++ -*- */
/* 
 * Copyright 2020 AIUT sp. z o. o
 * Author - Ritankar Sahu
 * Inspiration - Matt Knight (Bastille Threat Research Team)
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "Lora_Decoder_impl.h"

using namespace std;
using namespace pmt;

#define MAXIMUM_RDD 4

#define HAMMING_P1_BITMASK 0xAA  // 0b10101010
#define HAMMING_P2_BITMASK 0x66  // 0b01100110
#define HAMMING_P4_BITMASK 0x1E  // 0b00011110
#define HAMMING_P8_BITMASK 0xFE  // 0b11111110

#define INTERLEAVER_BLOCK_SIZE 12

#define DEBUG_OUTPUT 0

namespace gr {
  namespace AIUT {

    Lora_Decoder::sptr
    Lora_Decoder::make(int spreading_factor, int code_rate, bool low_data_rate, bool header)
    {
      return gnuradio::get_initial_sptr
        (new Lora_Decoder_impl(spreading_factor, code_rate, low_data_rate, header));
    }

    /*
     * The private constructor
     */
    Lora_Decoder_impl::Lora_Decoder_impl(int spreading_factor, int code_rate, bool low_data_rate, bool header)
      : gr::block("Lora_Decoder",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        d_sf(spreading_factor), d_cr(code_rate),
        d_ldr(low_data_rate), d_header(header)
    {
      assert((d_sf > 5) && (d_sf < 13));
      assert((d_cr > 0) && (d_cr < 5));
      if (d_sf == 6) assert(!header);

      d_in_port = pmt::mp("in");
      d_out_port = pmt::mp("out");

      message_port_register_in(d_in_port);
      message_port_register_out(d_out_port);

      set_msg_handler(d_in_port, boost::bind(&Lora_Decoder_impl::decode, this, _1));

      switch(d_sf)
      {
        case 6:
          if (d_ldr) d_whitening_sequence = whitening_sequence_sf6_ldr_implicit;    // implicit header, LDR on
          else       d_whitening_sequence = whitening_sequence_sf6_implicit;        // implicit header, LDR on
          break;
        case 7:
          if (d_ldr) d_whitening_sequence = whitening_sequence_sf7_ldr_implicit;    // implicit header, LDR on
          else       d_whitening_sequence = whitening_sequence_sf7_implicit;        // implicit header, LDR on
          break;
        case 8:
          if (d_ldr) d_whitening_sequence = whitening_sequence_sf8_ldr_implicit;    // implicit header, LDR on
          else       d_whitening_sequence = whitening_sequence_sf8_implicit;        // implicit header, LDR on
          break;
        case 9:
          if (d_ldr) d_whitening_sequence = whitening_sequence_sf9_ldr_implicit;    // implicit header, LDR on
          else       d_whitening_sequence = whitening_sequence_sf9_implicit;        // implicit header, LDR on
          break;
        case 10:
          if (d_ldr) d_whitening_sequence = whitening_sequence_sf10_ldr_implicit;    // implicit header, LDR on
          else       d_whitening_sequence = whitening_sequence_sf10_implicit;        // implicit header, LDR on
          break;
        case 11:
          if (d_ldr) d_whitening_sequence = whitening_sequence_sf11_ldr_implicit;    // implicit header, LDR on
          else       d_whitening_sequence = whitening_sequence_sf11_implicit;        // implicit header, LDR on
          break;
        case 12:
          if (d_ldr) d_whitening_sequence = whitening_sequence_sf12_ldr_implicit;    // implicit header, LDR on
          else       d_whitening_sequence = whitening_sequence_sf12_implicit;        // implicit header, LDR on
          break;
        default:
          cerr << "Invalid spreading factor -- this state should never occur." << endl;
          d_whitening_sequence = whitening_sequence_sf8_implicit;   // TODO actually handle this
          break;
      }

      if (d_header)
      {
        cout << "Warning: Explicit header mode is not yet supported." << endl;
        cout << "         Using an implicit whitening sequence: demodulation will work correctly; decoding will not." << endl;
      }

      d_interleaver_size = d_sf;

      d_fft_size = (1 << spreading_factor);
    }

    /*
     * Our virtual destructor.
     */
    Lora_Decoder_impl::~Lora_Decoder_impl()
    {
    }
    void
    Lora_Decoder_impl::to_gray(vector<unsigned short> &symbols)
    {
      for (int i = 0; i < symbols.size(); i++)
      {
        symbols[i] = (symbols[i] >> 1) ^ symbols[i];
      }
    }

    void
    Lora_Decoder_impl::from_gray(vector<unsigned short> &symbols)
    {
      for (int i = 0; i < symbols.size(); i++)
      {
        symbols[i] = symbols[i] ^ (symbols[i] >> 16);
        symbols[i] = symbols[i] ^ (symbols[i] >>  8);
        symbols[i] = symbols[i] ^ (symbols[i] >>  4);
        symbols[i] = symbols[i] ^ (symbols[i] >>  2);
        symbols[i] = symbols[i] ^ (symbols[i] >>  1);
      }
    }

    void
    Lora_Decoder_impl::whiten(vector<unsigned short> &symbols)
    {
      for (int i = 0; (i < symbols.size()) && (i < whitening_sequence_length); i++)
      {
        symbols[i] = (symbols[i] ^ d_whitening_sequence[i]);
      }
    }

     // Forward interleaver dimensions:
    //  PPM   == number of bits per symbol OUT of interleaver        AND number of codewords IN to interleaver
    //  RDD+4 == number of bits per codeword IN to interleaver       AND number of interleaved codewords OUT of interleaver
    //
    // bit width in:  (4+rdd)   block length: ppm
    // bit width out: ppm       block length: (4+rdd)

    // Reverse interleaver (de-interleaver) dimensions:
    //  PPM   == number of bits per symbol IN to deinterleaver       AND number of codewords OUT of deinterleaver
    //  RDD+4 == number of bits per codeword OUT of deinterleaver    AND number of interleaved codewords IN to deinterleaver
    //
    // bit width in:  ppm       block length: (4+rdd)
    // bit width out: (4+rdd)   block length: ppm

    void
    Lora_Decoder_impl::deinterleave(vector <unsigned short> &symbols, vector <unsigned char> &codewords, unsigned char ppm, unsigned char rdd)
    {
      int symbol_offset = 0;
      int bit_offset    = 0;
      int bit_idx       = 0;
      unsigned char block[INTERLEAVER_BLOCK_SIZE];    // maximum bit-width is 8, should RDD==4

      // Swap MSBs of each symbol within buffer (one of LoRa's quirks)
      for (int symbol_idx = 0; symbol_idx < symbols.size(); symbol_idx++)
      {
        symbols[symbol_idx] = ( (symbols[symbol_idx] &  (0x1 << (ppm-1))) >> 1 |
                                (symbols[symbol_idx] &  (0x1 << (ppm-2))) << 1 |
                                (symbols[symbol_idx] & ((0x1 << (ppm-2)) - 1))
                              );
      }

      // Block interleaver: de-interleave RDD+4 symbols at a time into PPM codewords
      for (int block_count = 0; block_count < symbols.size()/(4+rdd); block_count++)
      {
        memset(block, 0, INTERLEAVER_BLOCK_SIZE*sizeof(unsigned char));
        bit_idx = 0;
        bit_offset = 0;

        // Iterate through each bit in the interleaver block
        for (int bitcount = 0; bitcount < ppm*(4+rdd); bitcount++)
        {
              // Symbol indexing                                     // Diagonal pattern mask
          if (symbols[(bitcount % (4+rdd)) + (4+rdd)*block_count] & ((0x1 << (ppm-1)) >> ((bit_idx + bit_offset) % ppm)))
          {
            block[bitcount / (4+rdd)] |= 0x1 << (bitcount % (4+rdd));   // integer divison in C++ is defined to floor
          }

          // bit_idx walks through diagonal interleaving pattern, bit_offset adjusts offset starting point for each codeword
          if (bitcount % (4+rdd) == (4+rdd-1))
          {
            bit_idx = 0;
            bit_offset++;
          }
          else
          {
            bit_idx++;
          }
        }

        // Post-process de-interleaved codewords
        for (int cw_idx = 0; cw_idx < ppm; cw_idx++)
        {
          // Put bits into traditional Hamming order
          switch (rdd)
          {
            case 4:
              block[cw_idx] = (block[cw_idx] & 128) | (block[cw_idx] & 64) | (block[cw_idx] & 32) >> 5 | (block[cw_idx] & 16) | (block[cw_idx] & 8) << 2 | (block[cw_idx] & 4) << 1 | (block[cw_idx] & 2) << 1 | (block[cw_idx] & 1) << 1;
              break;

            case 3:
              block[cw_idx] = (block[cw_idx] & 64) | (block[cw_idx] & 32) | (block[cw_idx] & 16) >> 1 | (block[cw_idx] & 8) << 1 | (block[cw_idx] & 4) | (block[cw_idx] & 2) | (block[cw_idx] & 1);
              break;

            default:
              break;
          }

          // Mask
          block[cw_idx] = block[cw_idx] & ((1 << (4+rdd)) - 1);
        }
        
        // Append deinterleaved codewords to codeword buffer, rearranging into proper order
        if (ppm == 8)
        {
          codewords.push_back(block[6]);
          codewords.push_back(block[7]);
          codewords.push_back(block[4]);
          codewords.push_back(block[5]);
        }
        else if (ppm == 7)
        {
          codewords.push_back(block[6]);
          codewords.push_back(block[4]);
          codewords.push_back(block[5]);
        }
        else if (ppm == 6)
        {
          codewords.push_back(block[4]);
          codewords.push_back(block[5]);
        }
        else if (ppm == 5)
        {
          codewords.push_back(block[4]);
        }
        codewords.push_back(block[2]);
        codewords.push_back(block[3]);
        codewords.push_back(block[0]);
        codewords.push_back(block[1]);
      }
    }

    void
    Lora_Decoder_impl::hamming_decode(vector<unsigned char> &codewords, vector<unsigned char> &bytes, unsigned char rdd)
    {
      unsigned char p1, p2, p4, p8;
      unsigned char mask;
      unsigned int num_set_bits;
      unsigned int num_set_flags;
      int error_pos = 0;

      for (int i = 0; i < codewords.size(); i++)
      {
        switch (rdd) {
          case 4:
            p8 = parity(codewords[i], mask = (unsigned char)HAMMING_P8_BITMASK);
          case 3:
            p4 = parity(codewords[i], mask = (unsigned char)HAMMING_P4_BITMASK >> (4 - rdd));
          case 2:
            p2 = parity(codewords[i], mask = (unsigned char)HAMMING_P2_BITMASK >> (4 - rdd));
          case 1:
            p1 = parity(codewords[i], mask = (unsigned char)HAMMING_P1_BITMASK >> (4 - rdd));
            break;
        }

        error_pos = -1;
        if (p1 != 0) error_pos += 1;
        if (p2 != 0) error_pos += 2;
        if (p4 != 0) error_pos += 4;

        num_set_flags = p1 + p2 + p4;

        // Hamming(4+rdd,4) is only corrective if rdd >= 3
        if (rdd > 2)
        {
          num_set_bits = 0;
          for (int bit_idx = 0; bit_idx < 8; bit_idx++)
          {
            if (codewords[i] & (0x01 << bit_idx))
            {
              num_set_bits++;
            }
          }

          if (error_pos >= 0 && num_set_bits < 6 && num_set_bits > 2)
          {
            codewords[i] ^= (0x80 >> (4-rdd)) >> error_pos;
          } 

          num_set_bits = 0;
          for (int bit_idx = 0; bit_idx < 8; bit_idx++)
          {
            if (codewords[i] & (0x01 << bit_idx))
            {
              num_set_bits++;
            }
          }

          // if (rdd == 4)
          // {
          //   if (num_set_bits < 3)
          //   {
          //     codewords[i] = 0;
          //   }
          //   else if (num_set_bits > 5)
          //   {
          //     codewords[i] = 0xFF;
          //   }
          // }
        }

        switch (rdd)
        {
          case 1:
          case 2:
            codewords[i] = codewords[i] & 0x0F;
            break;
          case 3:
            codewords[i] = (((codewords[i] & 0x10) >> 1) | \
                            ((codewords[i] & 0x04))      | \
                            ((codewords[i] & 0x02))      | \
                            ((codewords[i] & 0x01))) & 0x0F;
            break;
          case 4:
            codewords[i] = (((codewords[i] & 0x20) >> 2) | \
                            ((codewords[i] & 0x08) >> 1) | \
                            ((codewords[i] & 0x04) >> 1) | \
                            ((codewords[i] & 0x02) >> 1)) & 0x0F;
            break;
        }

        bytes.push_back(codewords[i] & 0x0F);
      }
    }

    unsigned char
    Lora_Decoder_impl::parity(unsigned char c, unsigned char bitmask)
    {
      unsigned char parity = 0;
      unsigned char shiftme = c & bitmask;

      for (int i = 0; i < 8; i++)
      {
        if (shiftme & 0x1) parity++;
        shiftme = shiftme >> 1;
      }

      return parity % 2;
    }

    void
    Lora_Decoder_impl::print_payload(vector<unsigned char> &payload)
    {
      cout << "Received LoRa packet (hex): ";
        for (int i = 0; i < payload.size(); i++)
        {
          cout << hex << (unsigned int)payload[i] << " ";
        }
        cout << endl;
    }

    void
    Lora_Decoder_impl::print_bitwise_u8(vector<unsigned char> &buffer)
    {
      for (int i = 0; i < buffer.size(); i++)
      {
        cout << i << "\t" << bitset<8>(buffer[i] & 0xFF) << "\t";
        cout << hex << (buffer[i] & 0xFF) << endl;
      }
    }

    void
    Lora_Decoder_impl::print_bitwise_u16(vector<unsigned char> &buffer)
    {
      for (int i = 0; i < buffer.size(); i++)
      {
        cout << i << "\t" << bitset<16>(buffer[i] & 0xFFFF) << "\t";
        cout << hex << (buffer[i] & 0xFFFF) << endl;
      }
    }

    void
    Lora_Decoder_impl::decode(pmt_t msg)
    {
      pmt_t symbols(cdr(msg));

      size_t pkt_len(0);
      const uint16_t* symbols_v = u16vector_elements(symbols, pkt_len);

      vector<unsigned short> symbols_in;
      vector<unsigned short> header_symbols_in;
      vector<unsigned short> payload_symbols_in;
      vector<unsigned char> header_codewords;
      vector<unsigned char> payload_codewords;
      vector<unsigned char> header_bytes;
      vector<unsigned char> payload_bytes;
      vector<unsigned char> combined_bytes;

      symbols_in.clear();
      for (int i = 0; i < pkt_len; i++) symbols_in.push_back(symbols_v[i]);

      to_gray(symbols_in);
#if 1 // Disable this #if to derive the whitening sequence
      whiten(symbols_in);

      for (int i = 0; (i < symbols_in.size()) && (i < 8); i++) header_symbols_in.push_back(symbols_in[i]);
      for (int i = 8;  i < symbols_in.size()            ; i++) payload_symbols_in.push_back(symbols_in[i]);

      #if DEBUG_OUTPUT
        cout << "header syms len " << header_symbols_in.size() << endl;
        cout << "payload syms len " << payload_symbols_in.size() << endl;

        cout << "header dewhitened symbols" << endl;
        print_bitwise_u16(header_symbols_in);
        cout << "payload dewhitened symbols" << endl;
        print_bitwise_u16(payload_symbols_in);
      #endif

      // Decode header
      // First 8 symbols are always sent at ppm=d_sf-2, rdd=4 (code rate 4/8), regardless of header mode
      deinterleave(header_symbols_in, header_codewords, d_sf-2, 4);
      #if DEBUG_OUTPUT
        cout << "deinterleaved header" << endl;
        print_bitwise_u8(header_codewords);
      #endif

      hamming_decode(header_codewords, header_bytes, 4);

      // Decode payload
      // Remaining symbols are at ppm=d_sf, unless sent at the low data rate, in which case ppm=d_sf-2
      deinterleave(payload_symbols_in, payload_codewords, d_ldr ? (d_sf-2) : d_sf, d_cr);
      #if DEBUG_OUTPUT
        cout << "deinterleaved payload" << endl;
        print_bitwise_u8(payload_codewords);
      #endif

      hamming_decode(payload_codewords, payload_bytes, d_cr);
      #if DEBUG_OUTPUT
        cout << "payload data" << endl;
        print_bitwise_u8(payload_bytes);
      #endif

      // Combine header and payload vectors by interleaving data nybbles
      header_bytes.insert(header_bytes.end(), payload_bytes.begin(), payload_bytes.end());
      unsigned int i = 0;
      for (i = 0; i < header_bytes.size(); i++)
      {
        if (i%2 == 0)
        {
          combined_bytes.push_back((header_bytes[i] << 4) & 0xF0);
        }
        else
        {
          combined_bytes[i/2] |= header_bytes[i] & 0x0F;
        }
      }

      pmt_t output = init_u8vector(combined_bytes.size(), combined_bytes);

#else // Whitening sequence derivation
      for (int i = 0; i < symbols_in.size(); i++)
      {
        cout << ", " << bitset<16>(symbols_in[i]);
      }
      cout << endl;
      cout << "Length of above: " << symbols_in.size() << endl;
      pmt_t output = init_u16vector(symbols_in.size(), symbols_in);
#endif

      pmt_t msg_pair = cons(make_dict(), output);
      message_port_pub(d_out_port, msg_pair);
    }
  } /* namespace AIUT */
} /* namespace gr */
