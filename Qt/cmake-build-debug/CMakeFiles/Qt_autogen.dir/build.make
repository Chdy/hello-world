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
CMAKE_SOURCE_DIR = /Users/dengyan/ClionProjects/Qt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/dengyan/ClionProjects/Qt/cmake-build-debug

# Utility rule file for Qt_autogen.

# Include the progress variables for this target.
include CMakeFiles/Qt_autogen.dir/progress.make

CMakeFiles/Qt_autogen: ../doc-open.png
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/dengyan/ClionProjects/Qt/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC, UIC and RCC for target Qt"
	/Applications/CLion.app/Contents/bin/cmake/bin/cmake -E cmake_autogen /Users/dengyan/ClionProjects/Qt/cmake-build-debug/CMakeFiles/Qt_autogen.dir Debug

Qt_autogen: CMakeFiles/Qt_autogen
Qt_autogen: CMakeFiles/Qt_autogen.dir/build.make

.PHONY : Qt_autogen

# Rule to build all files generated by this target.
CMakeFiles/Qt_autogen.dir/build: Qt_autogen

.PHONY : CMakeFiles/Qt_autogen.dir/build

CMakeFiles/Qt_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Qt_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Qt_autogen.dir/clean

CMakeFiles/Qt_autogen.dir/depend:
	cd /Users/dengyan/ClionProjects/Qt/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/dengyan/ClionProjects/Qt /Users/dengyan/ClionProjects/Qt /Users/dengyan/ClionProjects/Qt/cmake-build-debug /Users/dengyan/ClionProjects/Qt/cmake-build-debug /Users/dengyan/ClionProjects/Qt/cmake-build-debug/CMakeFiles/Qt_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Qt_autogen.dir/depend
