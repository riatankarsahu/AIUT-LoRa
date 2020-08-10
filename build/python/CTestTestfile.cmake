# CMake generated Testfile for 
# Source directory: /home/ritankar/gr-AIUT/python
# Build directory: /home/ritankar/gr-AIUT/build/python
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(qa_Lora_Decoder "/bin/sh" "/home/ritankar/gr-AIUT/build/python/qa_Lora_Decoder_test.sh")
set_tests_properties(qa_Lora_Decoder PROPERTIES  _BACKTRACE_TRIPLES "/home/ritankar/gr-AIUT/cmake/Modules/GrTest.cmake;114;add_test;/home/ritankar/gr-AIUT/python/CMakeLists.txt;44;GR_ADD_TEST;/home/ritankar/gr-AIUT/python/CMakeLists.txt;0;")
add_test(qa_Lora_Demodulator "/bin/sh" "/home/ritankar/gr-AIUT/build/python/qa_Lora_Demodulator_test.sh")
set_tests_properties(qa_Lora_Demodulator PROPERTIES  _BACKTRACE_TRIPLES "/home/ritankar/gr-AIUT/cmake/Modules/GrTest.cmake;114;add_test;/home/ritankar/gr-AIUT/python/CMakeLists.txt;45;GR_ADD_TEST;/home/ritankar/gr-AIUT/python/CMakeLists.txt;0;")
