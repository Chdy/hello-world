# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/dengyan/ClionProjects/Linux

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/dengyan/ClionProjects/Linux/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Linux.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Linux.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Linux.dir/flags.make

CMakeFiles/Linux.dir/test.c.o: CMakeFiles/Linux.dir/flags.make
CMakeFiles/Linux.dir/test.c.o: ../test.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dengyan/ClionProjects/Linux/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Linux.dir/test.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Linux.dir/test.c.o   -c /Users/dengyan/ClionProjects/Linux/test.c

CMakeFiles/Linux.dir/test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Linux.dir/test.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/dengyan/ClionProjects/Linux/test.c > CMakeFiles/Linux.dir/test.c.i

CMakeFiles/Linux.dir/test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Linux.dir/test.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/dengyan/ClionProjects/Linux/test.c -o CMakeFiles/Linux.dir/test.c.s

CMakeFiles/Linux.dir/test.c.o.requires:

.PHONY : CMakeFiles/Linux.dir/test.c.o.requires

CMakeFiles/Linux.dir/test.c.o.provides: CMakeFiles/Linux.dir/test.c.o.requires
	$(MAKE) -f CMakeFiles/Linux.dir/build.make CMakeFiles/Linux.dir/test.c.o.provides.build
.PHONY : CMakeFiles/Linux.dir/test.c.o.provides

CMakeFiles/Linux.dir/test.c.o.provides.build: CMakeFiles/Linux.dir/test.c.o


# Object files for target Linux
Linux_OBJECTS = \
"CMakeFiles/Linux.dir/test.c.o"

# External object files for target Linux
Linux_EXTERNAL_OBJECTS =

Linux: CMakeFiles/Linux.dir/test.c.o
Linux: CMakeFiles/Linux.dir/build.make
Linux: CMakeFiles/Linux.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/dengyan/ClionProjects/Linux/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Linux"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Linux.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Linux.dir/build: Linux

.PHONY : CMakeFiles/Linux.dir/build

CMakeFiles/Linux.dir/requires: CMakeFiles/Linux.dir/test.c.o.requires

.PHONY : CMakeFiles/Linux.dir/requires

CMakeFiles/Linux.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Linux.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Linux.dir/clean

CMakeFiles/Linux.dir/depend:
	cd /Users/dengyan/ClionProjects/Linux/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/dengyan/ClionProjects/Linux /Users/dengyan/ClionProjects/Linux /Users/dengyan/ClionProjects/Linux/cmake-build-debug /Users/dengyan/ClionProjects/Linux/cmake-build-debug /Users/dengyan/ClionProjects/Linux/cmake-build-debug/CMakeFiles/Linux.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Linux.dir/depend

