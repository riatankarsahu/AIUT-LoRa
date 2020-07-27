#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/ritankar/gr-AIUT/lib
export PATH=/home/ritankar/gr-AIUT/build/lib:$PATH
export LD_LIBRARY_PATH=/home/ritankar/gr-AIUT/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH
test-AIUT 
