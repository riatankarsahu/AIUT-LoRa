/* -*- c++ -*- */

#define AIUT_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "AIUT_swig_doc.i"

%{
#include "AIUT/Lora_Decoder.h"
#include "AIUT/Lora_Demodulator.h"
%}


%include "AIUT/Lora_Decoder.h"
GR_SWIG_BLOCK_MAGIC2(AIUT, Lora_Decoder);
%include "AIUT/Lora_Demodulator.h"
GR_SWIG_BLOCK_MAGIC2(AIUT, Lora_Demodulator);
