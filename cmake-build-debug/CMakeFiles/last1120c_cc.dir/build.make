# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = "/Users/alexbrachet/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/191.6707.69/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/alexbrachet/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/191.6707.69/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/alexbrachet/Developer/last1120c-cc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/alexbrachet/Developer/last1120c-cc/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/last1120c_cc.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/last1120c_cc.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/last1120c_cc.dir/flags.make

CMakeFiles/last1120c_cc.dir/src/ScanFile.cc.o: CMakeFiles/last1120c_cc.dir/flags.make
CMakeFiles/last1120c_cc.dir/src/ScanFile.cc.o: ../src/ScanFile.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alexbrachet/Developer/last1120c-cc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/last1120c_cc.dir/src/ScanFile.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/last1120c_cc.dir/src/ScanFile.cc.o -c /Users/alexbrachet/Developer/last1120c-cc/src/ScanFile.cc

CMakeFiles/last1120c_cc.dir/src/ScanFile.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/last1120c_cc.dir/src/ScanFile.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alexbrachet/Developer/last1120c-cc/src/ScanFile.cc > CMakeFiles/last1120c_cc.dir/src/ScanFile.cc.i

CMakeFiles/last1120c_cc.dir/src/ScanFile.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/last1120c_cc.dir/src/ScanFile.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alexbrachet/Developer/last1120c-cc/src/ScanFile.cc -o CMakeFiles/last1120c_cc.dir/src/ScanFile.cc.s

CMakeFiles/last1120c_cc.dir/tests/ScanFileTest.cc.o: CMakeFiles/last1120c_cc.dir/flags.make
CMakeFiles/last1120c_cc.dir/tests/ScanFileTest.cc.o: ../tests/ScanFileTest.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alexbrachet/Developer/last1120c-cc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/last1120c_cc.dir/tests/ScanFileTest.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/last1120c_cc.dir/tests/ScanFileTest.cc.o -c /Users/alexbrachet/Developer/last1120c-cc/tests/ScanFileTest.cc

CMakeFiles/last1120c_cc.dir/tests/ScanFileTest.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/last1120c_cc.dir/tests/ScanFileTest.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alexbrachet/Developer/last1120c-cc/tests/ScanFileTest.cc > CMakeFiles/last1120c_cc.dir/tests/ScanFileTest.cc.i

CMakeFiles/last1120c_cc.dir/tests/ScanFileTest.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/last1120c_cc.dir/tests/ScanFileTest.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alexbrachet/Developer/last1120c-cc/tests/ScanFileTest.cc -o CMakeFiles/last1120c_cc.dir/tests/ScanFileTest.cc.s

CMakeFiles/last1120c_cc.dir/tests/ScannerTest.cc.o: CMakeFiles/last1120c_cc.dir/flags.make
CMakeFiles/last1120c_cc.dir/tests/ScannerTest.cc.o: ../tests/ScannerTest.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alexbrachet/Developer/last1120c-cc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/last1120c_cc.dir/tests/ScannerTest.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/last1120c_cc.dir/tests/ScannerTest.cc.o -c /Users/alexbrachet/Developer/last1120c-cc/tests/ScannerTest.cc

CMakeFiles/last1120c_cc.dir/tests/ScannerTest.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/last1120c_cc.dir/tests/ScannerTest.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alexbrachet/Developer/last1120c-cc/tests/ScannerTest.cc > CMakeFiles/last1120c_cc.dir/tests/ScannerTest.cc.i

CMakeFiles/last1120c_cc.dir/tests/ScannerTest.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/last1120c_cc.dir/tests/ScannerTest.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alexbrachet/Developer/last1120c-cc/tests/ScannerTest.cc -o CMakeFiles/last1120c_cc.dir/tests/ScannerTest.cc.s

CMakeFiles/last1120c_cc.dir/tests/TokenizedFileTest.cc.o: CMakeFiles/last1120c_cc.dir/flags.make
CMakeFiles/last1120c_cc.dir/tests/TokenizedFileTest.cc.o: ../tests/TokenizedFileTest.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alexbrachet/Developer/last1120c-cc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/last1120c_cc.dir/tests/TokenizedFileTest.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/last1120c_cc.dir/tests/TokenizedFileTest.cc.o -c /Users/alexbrachet/Developer/last1120c-cc/tests/TokenizedFileTest.cc

CMakeFiles/last1120c_cc.dir/tests/TokenizedFileTest.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/last1120c_cc.dir/tests/TokenizedFileTest.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alexbrachet/Developer/last1120c-cc/tests/TokenizedFileTest.cc > CMakeFiles/last1120c_cc.dir/tests/TokenizedFileTest.cc.i

CMakeFiles/last1120c_cc.dir/tests/TokenizedFileTest.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/last1120c_cc.dir/tests/TokenizedFileTest.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alexbrachet/Developer/last1120c-cc/tests/TokenizedFileTest.cc -o CMakeFiles/last1120c_cc.dir/tests/TokenizedFileTest.cc.s

CMakeFiles/last1120c_cc.dir/tests/TokenListTest.cc.o: CMakeFiles/last1120c_cc.dir/flags.make
CMakeFiles/last1120c_cc.dir/tests/TokenListTest.cc.o: ../tests/TokenListTest.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alexbrachet/Developer/last1120c-cc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/last1120c_cc.dir/tests/TokenListTest.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/last1120c_cc.dir/tests/TokenListTest.cc.o -c /Users/alexbrachet/Developer/last1120c-cc/tests/TokenListTest.cc

CMakeFiles/last1120c_cc.dir/tests/TokenListTest.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/last1120c_cc.dir/tests/TokenListTest.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alexbrachet/Developer/last1120c-cc/tests/TokenListTest.cc > CMakeFiles/last1120c_cc.dir/tests/TokenListTest.cc.i

CMakeFiles/last1120c_cc.dir/tests/TokenListTest.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/last1120c_cc.dir/tests/TokenListTest.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alexbrachet/Developer/last1120c-cc/tests/TokenListTest.cc -o CMakeFiles/last1120c_cc.dir/tests/TokenListTest.cc.s

CMakeFiles/last1120c_cc.dir/tests/TokenTest.cc.o: CMakeFiles/last1120c_cc.dir/flags.make
CMakeFiles/last1120c_cc.dir/tests/TokenTest.cc.o: ../tests/TokenTest.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alexbrachet/Developer/last1120c-cc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/last1120c_cc.dir/tests/TokenTest.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/last1120c_cc.dir/tests/TokenTest.cc.o -c /Users/alexbrachet/Developer/last1120c-cc/tests/TokenTest.cc

CMakeFiles/last1120c_cc.dir/tests/TokenTest.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/last1120c_cc.dir/tests/TokenTest.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alexbrachet/Developer/last1120c-cc/tests/TokenTest.cc > CMakeFiles/last1120c_cc.dir/tests/TokenTest.cc.i

CMakeFiles/last1120c_cc.dir/tests/TokenTest.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/last1120c_cc.dir/tests/TokenTest.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alexbrachet/Developer/last1120c-cc/tests/TokenTest.cc -o CMakeFiles/last1120c_cc.dir/tests/TokenTest.cc.s

# Object files for target last1120c_cc
last1120c_cc_OBJECTS = \
"CMakeFiles/last1120c_cc.dir/src/ScanFile.cc.o" \
"CMakeFiles/last1120c_cc.dir/tests/ScanFileTest.cc.o" \
"CMakeFiles/last1120c_cc.dir/tests/ScannerTest.cc.o" \
"CMakeFiles/last1120c_cc.dir/tests/TokenizedFileTest.cc.o" \
"CMakeFiles/last1120c_cc.dir/tests/TokenListTest.cc.o" \
"CMakeFiles/last1120c_cc.dir/tests/TokenTest.cc.o"

# External object files for target last1120c_cc
last1120c_cc_EXTERNAL_OBJECTS =

last1120c_cc: CMakeFiles/last1120c_cc.dir/src/ScanFile.cc.o
last1120c_cc: CMakeFiles/last1120c_cc.dir/tests/ScanFileTest.cc.o
last1120c_cc: CMakeFiles/last1120c_cc.dir/tests/ScannerTest.cc.o
last1120c_cc: CMakeFiles/last1120c_cc.dir/tests/TokenizedFileTest.cc.o
last1120c_cc: CMakeFiles/last1120c_cc.dir/tests/TokenListTest.cc.o
last1120c_cc: CMakeFiles/last1120c_cc.dir/tests/TokenTest.cc.o
last1120c_cc: CMakeFiles/last1120c_cc.dir/build.make
last1120c_cc: CMakeFiles/last1120c_cc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/alexbrachet/Developer/last1120c-cc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable last1120c_cc"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/last1120c_cc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/last1120c_cc.dir/build: last1120c_cc

.PHONY : CMakeFiles/last1120c_cc.dir/build

CMakeFiles/last1120c_cc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/last1120c_cc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/last1120c_cc.dir/clean

CMakeFiles/last1120c_cc.dir/depend:
	cd /Users/alexbrachet/Developer/last1120c-cc/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/alexbrachet/Developer/last1120c-cc /Users/alexbrachet/Developer/last1120c-cc /Users/alexbrachet/Developer/last1120c-cc/cmake-build-debug /Users/alexbrachet/Developer/last1120c-cc/cmake-build-debug /Users/alexbrachet/Developer/last1120c-cc/cmake-build-debug/CMakeFiles/last1120c_cc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/last1120c_cc.dir/depend

