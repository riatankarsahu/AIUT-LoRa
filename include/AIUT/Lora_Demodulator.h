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


#ifndef INCLUDED_AIUT_LORA_DEMODULATOR_H
#define INCLUDED_AIUT_LORA_DEMODULATOR_H

#include <AIUT/api.h>
#include <gnuradio/block.h>

#define DEMODULATOR_HISTORY_DEPTH 3
#define REQUIRED_PREAMBLE_CHIRPS 4
#define REQUIRED_SFD-CHIRPS 2
#define LORA_SFD_TOLERANCE 1
#define LORA_PREAMBLE_TOLERANCE 1
#define DEMODULATOR_SYNC_RECOVERY_COUNT (8 - REQUIRED_PREAMBLE_CHIRPS) + (2 - REQUIRED_SFD_CHIRPS) + 4

namespace gr 
{
  namespace AIUT 
  {
    enum demodulator_state_t
    {
      S_RESET,
      S_PREFILL,
      S_DETECT_PREAMBLE,
      S_SFD_SYNC,
      S_READ_HEADER,
      S_READ_PAYLOAD,
      S_OUT
    };

    /*!
     * \brief <+description of block+>
     * \ingroup AIUT     *
     */

    class AIUT_API Lora_Demodulator : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<Lora_Demodulator> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of AIUT::Lora_Demodulator.
       *
       * To avoid accidental use of raw pointers, AIUT::Lora_Demodulator's
       * constructor is in a private implementation
       * class. AIUT::Lora_Demodulator::make is the public interface for
       * creating new instances.
       */
      static sptr make(int spreading_factor, bool low_data_rate, float beta, int fft_factor);
    };

  } // namespace AIUT
} // namespace gr

#endif /* INCLUDED_AIUT_LORA_DEMODULATOR_H */
