# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /homes/a/m/amatikya/home/enee408m/monday/team3/final

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /homes/a/m/amatikya/home/enee408m/monday/team3/final

# Include any dependencies generated for this target.
include test/test02/CMakeFiles/driver2.exe.dir/depend.make

# Include the progress variables for this target.
include test/test02/CMakeFiles/driver2.exe.dir/progress.make

# Include the compile flags for this target's objects.
include test/test02/CMakeFiles/driver2.exe.dir/flags.make

test/test02/CMakeFiles/driver2.exe.dir/driver2.cpp.o: test/test02/CMakeFiles/driver2.exe.dir/flags.make
test/test02/CMakeFiles/driver2.exe.dir/driver2.cpp.o: test/test02/driver2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/a/m/amatikya/home/enee408m/monday/team3/final/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/test02/CMakeFiles/driver2.exe.dir/driver2.cpp.o"
	cd /homes/a/m/amatikya/home/enee408m/monday/team3/final/test/test02 && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/driver2.exe.dir/driver2.cpp.o -c /homes/a/m/amatikya/home/enee408m/monday/team3/final/test/test02/driver2.cpp

test/test02/CMakeFiles/driver2.exe.dir/driver2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/driver2.exe.dir/driver2.cpp.i"
	cd /homes/a/m/amatikya/home/enee408m/monday/team3/final/test/test02 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /homes/a/m/amatikya/home/enee408m/monday/team3/final/test/test02/driver2.cpp > CMakeFiles/driver2.exe.dir/driver2.cpp.i

test/test02/CMakeFiles/driver2.exe.dir/driver2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/driver2.exe.dir/driver2.cpp.s"
	cd /homes/a/m/amatikya/home/enee408m/monday/team3/final/test/test02 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /homes/a/m/amatikya/home/enee408m/monday/team3/final/test/test02/driver2.cpp -o CMakeFiles/driver2.exe.dir/driver2.cpp.s

# Object files for target driver2.exe
driver2_exe_OBJECTS = \
"CMakeFiles/driver2.exe.dir/driver2.cpp.o"

# External object files for target driver2.exe
driver2_exe_EXTERNAL_OBJECTS =

test/test02/driver2.exe: test/test02/CMakeFiles/driver2.exe.dir/driver2.cpp.o
test/test02/driver2.exe: test/test02/CMakeFiles/driver2.exe.dir/build.make
test/test02/driver2.exe: src/libclassifier.a
test/test02/driver2.exe: test/test02/CMakeFiles/driver2.exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/homes/a/m/amatikya/home/enee408m/monday/team3/final/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable driver2.exe"
	cd /homes/a/m/amatikya/home/enee408m/monday/team3/final/test/test02 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/driver2.exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/test02/CMakeFiles/driver2.exe.dir/build: test/test02/driver2.exe

.PHONY : test/test02/CMakeFiles/driver2.exe.dir/build

test/test02/CMakeFiles/driver2.exe.dir/clean:
	cd /homes/a/m/amatikya/home/enee408m/monday/team3/final/test/test02 && $(CMAKE_COMMAND) -P CMakeFiles/driver2.exe.dir/cmake_clean.cmake
.PHONY : test/test02/CMakeFiles/driver2.exe.dir/clean

test/test02/CMakeFiles/driver2.exe.dir/depend:
	cd /homes/a/m/amatikya/home/enee408m/monday/team3/final && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /homes/a/m/amatikya/home/enee408m/monday/team3/final /homes/a/m/amatikya/home/enee408m/monday/team3/final/test/test02 /homes/a/m/amatikya/home/enee408m/monday/team3/final /homes/a/m/amatikya/home/enee408m/monday/team3/final/test/test02 /homes/a/m/amatikya/home/enee408m/monday/team3/final/test/test02/CMakeFiles/driver2.exe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/test02/CMakeFiles/driver2.exe.dir/depend

