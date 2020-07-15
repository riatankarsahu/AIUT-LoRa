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

#ifndef INCLUDED_AIUT_LORA_DEMODULATOR_IMPL_H
#define INCLUDED_AIUT_LORA_DEMODULATOR_IMPL_H

#include <AIUT/Lora_Demodulator.h>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <queue>
#include <complex>
#include <fstream>
#include <gnuradio/fft/fft.h>
#include <gnuradio/fft/window.h>
#include <volk/volk.h>

using namespace std;
using namespace pmt;

namespace gr 
{
  namespace AIUT 
  {
    class Lora_Demodulator_impl : public Lora_Demodulator
    {
     private:
      pmt_t d_out_port;
      demodulator_state_t d_state;

     public:
      Lora_Demodulator_impl(int spreading_factor, bool low_data_rate, float beta, int fft_factor);
      ~Lora_Demodulator_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };

  } // namespace AIUT
} // namespace gr

#endif /* INCLUDED_AIUT_LORA_DEMODULATOR_IMPL_H */

