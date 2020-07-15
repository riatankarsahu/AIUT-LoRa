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


#ifndef INCLUDED_AIUT_LORA_DECODER_H
#define INCLUDED_AIUT_LORA_DECODER_H

#include <AIUT/api.h>
#include <gnuradio/block.h>
#include <AIUT/lora.h>

#define SYMBOL_TIMEOUT_COUNT 256

namespace gr {
  namespace AIUT {

    /*!
     * \brief <+description of block+>
     * \ingroup AIUT
     *
     */
    class AIUT_API Lora_Decoder : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<Lora_Decoder> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of AIUT::Lora_Decoder.
       *
       * To avoid accidental use of raw pointers, AIUT::Lora_Decoder's
       * constructor is in a private implementation
       * class. AIUT::Lora_Decoder::make is the public interface for
       * creating new instances.
       */
      static sptr make(int spreading_factor, int code_rate, bool low_data_rate, bool header);
    };

  } // namespace AIUT
} // namespace gr

#endif /* INCLUDED_AIUT_LORA_DECODER_H */
