# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.12

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Adil\Desktop\MLOpen-1-1.5.x

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build

# Include any dependencies generated for this target.
include test/CMakeFiles/test_na_inference.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/test_na_inference.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/test_na_inference.dir/flags.make

test/CMakeFiles/test_na_inference.dir/na_inference.cpp.obj: test/CMakeFiles/test_na_inference.dir/flags.make
test/CMakeFiles/test_na_inference.dir/na_inference.cpp.obj: test/CMakeFiles/test_na_inference.dir/includes_CXX.rsp
test/CMakeFiles/test_na_inference.dir/na_inference.cpp.obj: ../test/na_inference.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/test_na_inference.dir/na_inference.cpp.obj"
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\test_na_inference.dir\na_inference.cpp.obj -c C:\Users\Adil\Desktop\MLOpen-1-1.5.x\test\na_inference.cpp

test/CMakeFiles/test_na_inference.dir/na_inference.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_na_inference.dir/na_inference.cpp.i"
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Adil\Desktop\MLOpen-1-1.5.x\test\na_inference.cpp > CMakeFiles\test_na_inference.dir\na_inference.cpp.i

test/CMakeFiles/test_na_inference.dir/na_inference.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_na_inference.dir/na_inference.cpp.s"
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Adil\Desktop\MLOpen-1-1.5.x\test\na_inference.cpp -o CMakeFiles\test_na_inference.dir\na_inference.cpp.s

# Object files for target test_na_inference
test_na_inference_OBJECTS = \
"CMakeFiles/test_na_inference.dir/na_inference.cpp.obj"

# External object files for target test_na_inference
test_na_inference_EXTERNAL_OBJECTS =

bin/test_na_inference.exe: test/CMakeFiles/test_na_inference.dir/na_inference.cpp.obj
bin/test_na_inference.exe: test/CMakeFiles/test_na_inference.dir/build.make
bin/test_na_inference.exe: lib/libMIOpen.dll.a
bin/test_na_inference.exe: C:/Program\ Files\ (x86)/AMD\ APP\ SDK/3.0/lib/x86_64/libOpenCL.a
bin/test_na_inference.exe: C:/MinGW/lib/libboost_filesystem.a
bin/test_na_inference.exe: C:/MinGW/lib/libboost_system.a
bin/test_na_inference.exe: test/CMakeFiles/test_na_inference.dir/linklibs.rsp
bin/test_na_inference.exe: test/CMakeFiles/test_na_inference.dir/objects1.rsp
bin/test_na_inference.exe: test/CMakeFiles/test_na_inference.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ..\bin\test_na_inference.exe"
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\test_na_inference.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/test_na_inference.dir/build: bin/test_na_inference.exe

.PHONY : test/CMakeFiles/test_na_inference.dir/build

test/CMakeFiles/test_na_inference.dir/clean:
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && $(CMAKE_COMMAND) -P CMakeFiles\test_na_inference.dir\cmake_clean.cmake
.PHONY : test/CMakeFiles/test_na_inference.dir/clean

test/CMakeFiles/test_na_inference.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Adil\Desktop\MLOpen-1-1.5.x C:\Users\Adil\Desktop\MLOpen-1-1.5.x\test C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test\CMakeFiles\test_na_inference.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/test_na_inference.dir/depend

