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
          std::cerr << "Invalid spreading factor -- this state should never occur." << std::endl;
          d_whitening_sequence = whitening_sequence_sf8_implicit;   // TODO actually handle this
          break;
      }

      if (d_header)
      {
        std::cout << "Warning: Explicit header mode is not yet supported." << std::endl;
        std::cout << "         Using an implicit whitening sequence: demodulation will work correctly; decoding will not." << std::endl;
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
    Lora_Decoder_impl::to_gray(std::vector<unsigned short> &symbols)
    {
      for (int i = 0; i < symbols.size(); i++)
      {
        symbols[i] = (symbols[i] >> 1) ^ symbols[i];
      }
    }

    void
    Lora_Decoder_impl::from_gray(std::vector<unsigned short> &symbols)
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

    int
    Lora_Decoder_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const <+ITYPE+> *in = (const <+ITYPE+> *) input_items[0];
      <+OTYPE+> *out = (<+OTYPE+> *) output_items[0];

      // Do <+signal processing+>
      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace AIUT */
} /* namespace gr */

