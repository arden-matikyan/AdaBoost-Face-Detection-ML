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
CMAKE_SOURCE_DIR = /homes/a/m/amatikya/home/enee408m/friday/team3/final

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /homes/a/m/amatikya/home/enee408m/friday/team3/final

# Include any dependencies generated for this target.
include demo/CMakeFiles/driver.exe.dir/depend.make

# Include the progress variables for this target.
include demo/CMakeFiles/driver.exe.dir/progress.make

# Include the compile flags for this target's objects.
include demo/CMakeFiles/driver.exe.dir/flags.make

demo/CMakeFiles/driver.exe.dir/driver.cpp.o: demo/CMakeFiles/driver.exe.dir/flags.make
demo/CMakeFiles/driver.exe.dir/driver.cpp.o: demo/driver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/a/m/amatikya/home/enee408m/friday/team3/final/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object demo/CMakeFiles/driver.exe.dir/driver.cpp.o"
	cd /homes/a/m/amatikya/home/enee408m/friday/team3/final/demo && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/driver.exe.dir/driver.cpp.o -c /homes/a/m/amatikya/home/enee408m/friday/team3/final/demo/driver.cpp

demo/CMakeFiles/driver.exe.dir/driver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/driver.exe.dir/driver.cpp.i"
	cd /homes/a/m/amatikya/home/enee408m/friday/team3/final/demo && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /homes/a/m/amatikya/home/enee408m/friday/team3/final/demo/driver.cpp > CMakeFiles/driver.exe.dir/driver.cpp.i

demo/CMakeFiles/driver.exe.dir/driver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/driver.exe.dir/driver.cpp.s"
	cd /homes/a/m/amatikya/home/enee408m/friday/team3/final/demo && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /homes/a/m/amatikya/home/enee408m/friday/team3/final/demo/driver.cpp -o CMakeFiles/driver.exe.dir/driver.cpp.s

# Object files for target driver.exe
driver_exe_OBJECTS = \
"CMakeFiles/driver.exe.dir/driver.cpp.o"

# External object files for target driver.exe
driver_exe_EXTERNAL_OBJECTS =

demo/driver.exe: demo/CMakeFiles/driver.exe.dir/driver.cpp.o
demo/driver.exe: demo/CMakeFiles/driver.exe.dir/build.make
demo/driver.exe: src/libclassifier.a
demo/driver.exe: demo/CMakeFiles/driver.exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/homes/a/m/amatikya/home/enee408m/friday/team3/final/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable driver.exe"
	cd /homes/a/m/amatikya/home/enee408m/friday/team3/final/demo && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/driver.exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
demo/CMakeFiles/driver.exe.dir/build: demo/driver.exe

.PHONY : demo/CMakeFiles/driver.exe.dir/build

demo/CMakeFiles/driver.exe.dir/clean:
	cd /homes/a/m/amatikya/home/enee408m/friday/team3/final/demo && $(CMAKE_COMMAND) -P CMakeFiles/driver.exe.dir/cmake_clean.cmake
.PHONY : demo/CMakeFiles/driver.exe.dir/clean

demo/CMakeFiles/driver.exe.dir/depend:
	cd /homes/a/m/amatikya/home/enee408m/friday/team3/final && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /homes/a/m/amatikya/home/enee408m/friday/team3/final /homes/a/m/amatikya/home/enee408m/friday/team3/final/demo /homes/a/m/amatikya/home/enee408m/friday/team3/final /homes/a/m/amatikya/home/enee408m/friday/team3/final/demo /homes/a/m/amatikya/home/enee408m/friday/team3/final/demo/CMakeFiles/driver.exe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : demo/CMakeFiles/driver.exe.dir/depend

