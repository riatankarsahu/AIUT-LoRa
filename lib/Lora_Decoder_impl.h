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

#ifndef INCLUDED_AIUT_LORA_DECODER_IMPL_H
#define INCLUDED_AIUT_LORA_DECODER_IMPL_H

#include <AIUT/Lora_Decoder.h>
#include <iostream>
#include <bitset>

using namespace std;
using namespace pmt;

namespace gr 
{
  namespace AIUT 
  {
    class Lora_Decoder_impl : public Lora_Decoder
    {
     private:
      pmt_t d_in_port;
      pmt_t d_out_port;

      const unsigned short *d_whitening_sequence;

      unsigned char d_sf;
      unsigned char d_cr;
      bool d_ldr;
      bool d_header;

      unsigned short d_fft_size;
      unsigned char d_interleaver_size;

      vector<unsigned short> d_symbols;
      vector<unsigned char> d_codewards;
      vector<unsigned char> d_bytes;

     public:
      Lora_Decoder_impl(int spreading_factor, int code_rate, bool low_data_rate, bool header);
      ~Lora_Decoder_impl();

      void to_gray(vector<unsigned short> &symbols);
      void from_gray(vector<unsigned short> &symbols);
      void whiten(vector<unsigned short> &symbols);
      void deinterleave(vector<unsigned short> &symbols, vector<unsigned char> &codewords, unsigned char ppm, unsigned char rdd);
      void hamming_decode(vector<unsigned char> &codewords, vector<unsigned char> &bytes, unsigned char rdd);
      unsigned char parity(unsigned char c, unsigned char bitmask);
      void print_payload(vector<unsigned char> &payload);

      void print_bitwise_u8(vector<unsigned char> &buffer);
      void print_bitwise_u16(vector<unsigned char> &buffer);

      void decode(pmt_t msg);     
    };

  } // namespace AIUT
} // namespace gr

#endif /* INCLUDED_AIUT_LORA_DECODER_IMPL_H */
