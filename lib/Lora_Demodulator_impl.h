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
      unsigned short d_sf;
      bool d_ldr;

      unsigned short d_num_symbols;
      unsigned short d_fft_size_factor;
      unsigned short d_fft_size;
      unsigned short d_overlaps;
      unsigned short d_offset;

      float d_power;
      float d_threshold;
      bool d_squelched;

      unsigned short d_preamble_idx;
      unsigned short d_sfd_idx;
      
      vector<unsigned short> d_argmax_history;
      vector<unsigned short> d_sfd_history;
      unsigned short d_sync_recovery_counter;

      fft::fft_complex *d_fft;
      vector<float> d_window;
      float d_beta;

      vector<gr_complex> d_upchirp;
      vector<gr_complex> d_downchirp;

      vector<unsigned short> d_symbols;

      ofstream f_raw, f_up_windowless, f_up, f_down;

     public:
      Lora_Demodulator_impl(int spreading_factor, bool low_data_rate, float beta, int fft_factor);
      ~Lora_Demodulator_impl();

      unsigned short argmax(gr_complex *fft_result, bool update_squelch);

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

