# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/john/Desktop/Git/Tetris/Tetris_SDL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/john/Desktop/Git/Tetris/Tetris_SDL/Build

# Include any dependencies generated for this target.
include CMakeFiles/Tetris.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Tetris.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Tetris.dir/flags.make

CMakeFiles/Tetris.dir/run.cpp.o: CMakeFiles/Tetris.dir/flags.make
CMakeFiles/Tetris.dir/run.cpp.o: ../run.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/john/Desktop/Git/Tetris/Tetris_SDL/Build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Tetris.dir/run.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Tetris.dir/run.cpp.o -c /home/john/Desktop/Git/Tetris/Tetris_SDL/run.cpp

CMakeFiles/Tetris.dir/run.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tetris.dir/run.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/john/Desktop/Git/Tetris/Tetris_SDL/run.cpp > CMakeFiles/Tetris.dir/run.cpp.i

CMakeFiles/Tetris.dir/run.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tetris.dir/run.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/john/Desktop/Git/Tetris/Tetris_SDL/run.cpp -o CMakeFiles/Tetris.dir/run.cpp.s

CMakeFiles/Tetris.dir/run.cpp.o.requires:
.PHONY : CMakeFiles/Tetris.dir/run.cpp.o.requires

CMakeFiles/Tetris.dir/run.cpp.o.provides: CMakeFiles/Tetris.dir/run.cpp.o.requires
	$(MAKE) -f CMakeFiles/Tetris.dir/build.make CMakeFiles/Tetris.dir/run.cpp.o.provides.build
.PHONY : CMakeFiles/Tetris.dir/run.cpp.o.provides

CMakeFiles/Tetris.dir/run.cpp.o.provides.build: CMakeFiles/Tetris.dir/run.cpp.o

# Object files for target Tetris
Tetris_OBJECTS = \
"CMakeFiles/Tetris.dir/run.cpp.o"

# External object files for target Tetris
Tetris_EXTERNAL_OBJECTS =

Tetris: CMakeFiles/Tetris.dir/run.cpp.o
Tetris: CMakeFiles/Tetris.dir/build.make
Tetris: CMakeFiles/Tetris.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable Tetris"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Tetris.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Tetris.dir/build: Tetris
.PHONY : CMakeFiles/Tetris.dir/build

CMakeFiles/Tetris.dir/requires: CMakeFiles/Tetris.dir/run.cpp.o.requires
.PHONY : CMakeFiles/Tetris.dir/requires

CMakeFiles/Tetris.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Tetris.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Tetris.dir/clean

CMakeFiles/Tetris.dir/depend:
	cd /home/john/Desktop/Git/Tetris/Tetris_SDL/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/john/Desktop/Git/Tetris/Tetris_SDL /home/john/Desktop/Git/Tetris/Tetris_SDL /home/john/Desktop/Git/Tetris/Tetris_SDL/Build /home/john/Desktop/Git/Tetris/Tetris_SDL/Build /home/john/Desktop/Git/Tetris/Tetris_SDL/Build/CMakeFiles/Tetris.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Tetris.dir/depend

