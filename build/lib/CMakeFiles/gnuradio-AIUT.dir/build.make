# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ritankar/gr-AIUT

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ritankar/gr-AIUT/build

# Include any dependencies generated for this target.
include lib/CMakeFiles/gnuradio-AIUT.dir/depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/gnuradio-AIUT.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/gnuradio-AIUT.dir/flags.make

lib/CMakeFiles/gnuradio-AIUT.dir/Lora_Decoder_impl.cc.o: lib/CMakeFiles/gnuradio-AIUT.dir/flags.make
lib/CMakeFiles/gnuradio-AIUT.dir/Lora_Decoder_impl.cc.o: ../lib/Lora_Decoder_impl.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ritankar/gr-AIUT/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/CMakeFiles/gnuradio-AIUT.dir/Lora_Decoder_impl.cc.o"
	cd /home/ritankar/gr-AIUT/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gnuradio-AIUT.dir/Lora_Decoder_impl.cc.o -c /home/ritankar/gr-AIUT/lib/Lora_Decoder_impl.cc

lib/CMakeFiles/gnuradio-AIUT.dir/Lora_Decoder_impl.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gnuradio-AIUT.dir/Lora_Decoder_impl.cc.i"
	cd /home/ritankar/gr-AIUT/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ritankar/gr-AIUT/lib/Lora_Decoder_impl.cc > CMakeFiles/gnuradio-AIUT.dir/Lora_Decoder_impl.cc.i

lib/CMakeFiles/gnuradio-AIUT.dir/Lora_Decoder_impl.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gnuradio-AIUT.dir/Lora_Decoder_impl.cc.s"
	cd /home/ritankar/gr-AIUT/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ritankar/gr-AIUT/lib/Lora_Decoder_impl.cc -o CMakeFiles/gnuradio-AIUT.dir/Lora_Decoder_impl.cc.s

lib/CMakeFiles/gnuradio-AIUT.dir/Lora_Demodulator_impl.cc.o: lib/CMakeFiles/gnuradio-AIUT.dir/flags.make
lib/CMakeFiles/gnuradio-AIUT.dir/Lora_Demodulator_impl.cc.o: ../lib/Lora_Demodulator_impl.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ritankar/gr-AIUT/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lib/CMakeFiles/gnuradio-AIUT.dir/Lora_Demodulator_impl.cc.o"
	cd /home/ritankar/gr-AIUT/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gnuradio-AIUT.dir/Lora_Demodulator_impl.cc.o -c /home/ritankar/gr-AIUT/lib/Lora_Demodulator_impl.cc

lib/CMakeFiles/gnuradio-AIUT.dir/Lora_Demodulator_impl.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gnuradio-AIUT.dir/Lora_Demodulator_impl.cc.i"
	cd /home/ritankar/gr-AIUT/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ritankar/gr-AIUT/lib/Lora_Demodulator_impl.cc > CMakeFiles/gnuradio-AIUT.dir/Lora_Demodulator_impl.cc.i

lib/CMakeFiles/gnuradio-AIUT.dir/Lora_Demodulator_impl.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gnuradio-AIUT.dir/Lora_Demodulator_impl.cc.s"
	cd /home/ritankar/gr-AIUT/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ritankar/gr-AIUT/lib/Lora_Demodulator_impl.cc -o CMakeFiles/gnuradio-AIUT.dir/Lora_Demodulator_impl.cc.s

# Object files for target gnuradio-AIUT
gnuradio__AIUT_OBJECTS = \
"CMakeFiles/gnuradio-AIUT.dir/Lora_Decoder_impl.cc.o" \
"CMakeFiles/gnuradio-AIUT.dir/Lora_Demodulator_impl.cc.o"

# External object files for target gnuradio-AIUT
gnuradio__AIUT_EXTERNAL_OBJECTS =

lib/libgnuradio-AIUT-1.0.0git.so.0.0.0: lib/CMakeFiles/gnuradio-AIUT.dir/Lora_Decoder_impl.cc.o
lib/libgnuradio-AIUT-1.0.0git.so.0.0.0: lib/CMakeFiles/gnuradio-AIUT.dir/Lora_Demodulator_impl.cc.o
lib/libgnuradio-AIUT-1.0.0git.so.0.0.0: lib/CMakeFiles/gnuradio-AIUT.dir/build.make
lib/libgnuradio-AIUT-1.0.0git.so.0.0.0: //usr/lib/x86_64-linux-gnu/libboost_filesystem.so
lib/libgnuradio-AIUT-1.0.0git.so.0.0.0: //usr/lib/x86_64-linux-gnu/libboost_system.so
lib/libgnuradio-AIUT-1.0.0git.so.0.0.0: /usr/lib/x86_64-linux-gnu/libgnuradio-runtime.so
lib/libgnuradio-AIUT-1.0.0git.so.0.0.0: /usr/lib/x86_64-linux-gnu/libgnuradio-pmt.so
lib/libgnuradio-AIUT-1.0.0git.so.0.0.0: lib/CMakeFiles/gnuradio-AIUT.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ritankar/gr-AIUT/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared library libgnuradio-AIUT-1.0.0git.so"
	cd /home/ritankar/gr-AIUT/build/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gnuradio-AIUT.dir/link.txt --verbose=$(VERBOSE)
	cd /home/ritankar/gr-AIUT/build/lib && $(CMAKE_COMMAND) -E cmake_symlink_library libgnuradio-AIUT-1.0.0git.so.0.0.0 libgnuradio-AIUT-1.0.0git.so.0.0.0 libgnuradio-AIUT-1.0.0git.so
	cd /home/ritankar/gr-AIUT/build/lib && /usr/bin/cmake -E create_symlink libgnuradio-AIUT-1.0.0git.so.0.0.0 /home/ritankar/gr-AIUT/build/lib/libgnuradio-AIUT.so
	cd /home/ritankar/gr-AIUT/build/lib && /usr/bin/cmake -E create_symlink libgnuradio-AIUT-1.0.0git.so.0.0.0 /home/ritankar/gr-AIUT/build/lib/libgnuradio-AIUT-1.0.0git.so.0
	cd /home/ritankar/gr-AIUT/build/lib && /usr/bin/cmake -E touch libgnuradio-AIUT-1.0.0git.so.0.0.0

lib/libgnuradio-AIUT-1.0.0git.so: lib/libgnuradio-AIUT-1.0.0git.so.0.0.0
	@$(CMAKE_COMMAND) -E touch_nocreate lib/libgnuradio-AIUT-1.0.0git.so

# Rule to build all files generated by this target.
lib/CMakeFiles/gnuradio-AIUT.dir/build: lib/libgnuradio-AIUT-1.0.0git.so

.PHONY : lib/CMakeFiles/gnuradio-AIUT.dir/build

lib/CMakeFiles/gnuradio-AIUT.dir/clean:
	cd /home/ritankar/gr-AIUT/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/gnuradio-AIUT.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/gnuradio-AIUT.dir/clean

lib/CMakeFiles/gnuradio-AIUT.dir/depend:
	cd /home/ritankar/gr-AIUT/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ritankar/gr-AIUT /home/ritankar/gr-AIUT/lib /home/ritankar/gr-AIUT/build /home/ritankar/gr-AIUT/build/lib /home/ritankar/gr-AIUT/build/lib/CMakeFiles/gnuradio-AIUT.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/gnuradio-AIUT.dir/depend
