# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_SOURCE_DIR = /home/coderish/src/repos/OHLCService

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/coderish/src/repos/OHLCService/cmake

# Include any dependencies generated for this target.
include CMakeFiles/protobufs.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/protobufs.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/protobufs.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/protobufs.dir/flags.make

ohlc.pb.h: /home/coderish/src/repos/OHLCService/protobufs/ohlc.proto
ohlc.pb.h: /usr/bin/protoc
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/coderish/src/repos/OHLCService/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Running cpp protocol buffer compiler on protobufs/ohlc.proto"
	/usr/bin/protoc --cpp_out /home/coderish/src/repos/OHLCService/cmake -I /home/coderish/src/repos/OHLCService/protobufs /home/coderish/src/repos/OHLCService/protobufs/ohlc.proto

ohlc.pb.cc: ohlc.pb.h
	@$(CMAKE_COMMAND) -E touch_nocreate ohlc.pb.cc

CMakeFiles/protobufs.dir/ohlc.pb.cc.o: CMakeFiles/protobufs.dir/flags.make
CMakeFiles/protobufs.dir/ohlc.pb.cc.o: ohlc.pb.cc
CMakeFiles/protobufs.dir/ohlc.pb.cc.o: CMakeFiles/protobufs.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/coderish/src/repos/OHLCService/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/protobufs.dir/ohlc.pb.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/protobufs.dir/ohlc.pb.cc.o -MF CMakeFiles/protobufs.dir/ohlc.pb.cc.o.d -o CMakeFiles/protobufs.dir/ohlc.pb.cc.o -c /home/coderish/src/repos/OHLCService/cmake/ohlc.pb.cc

CMakeFiles/protobufs.dir/ohlc.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/protobufs.dir/ohlc.pb.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/coderish/src/repos/OHLCService/cmake/ohlc.pb.cc > CMakeFiles/protobufs.dir/ohlc.pb.cc.i

CMakeFiles/protobufs.dir/ohlc.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/protobufs.dir/ohlc.pb.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/coderish/src/repos/OHLCService/cmake/ohlc.pb.cc -o CMakeFiles/protobufs.dir/ohlc.pb.cc.s

# Object files for target protobufs
protobufs_OBJECTS = \
"CMakeFiles/protobufs.dir/ohlc.pb.cc.o"

# External object files for target protobufs
protobufs_EXTERNAL_OBJECTS =

libprotobufs.a: CMakeFiles/protobufs.dir/ohlc.pb.cc.o
libprotobufs.a: CMakeFiles/protobufs.dir/build.make
libprotobufs.a: CMakeFiles/protobufs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/coderish/src/repos/OHLCService/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libprotobufs.a"
	$(CMAKE_COMMAND) -P CMakeFiles/protobufs.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/protobufs.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/protobufs.dir/build: libprotobufs.a
.PHONY : CMakeFiles/protobufs.dir/build

CMakeFiles/protobufs.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/protobufs.dir/cmake_clean.cmake
.PHONY : CMakeFiles/protobufs.dir/clean

CMakeFiles/protobufs.dir/depend: ohlc.pb.cc
CMakeFiles/protobufs.dir/depend: ohlc.pb.h
	cd /home/coderish/src/repos/OHLCService/cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/coderish/src/repos/OHLCService /home/coderish/src/repos/OHLCService /home/coderish/src/repos/OHLCService/cmake /home/coderish/src/repos/OHLCService/cmake /home/coderish/src/repos/OHLCService/cmake/CMakeFiles/protobufs.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/protobufs.dir/depend
