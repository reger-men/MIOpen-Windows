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
include addkernels/CMakeFiles/addkernels.dir/depend.make

# Include the progress variables for this target.
include addkernels/CMakeFiles/addkernels.dir/progress.make

# Include the compile flags for this target's objects.
include addkernels/CMakeFiles/addkernels.dir/flags.make

addkernels/CMakeFiles/addkernels.dir/include_inliner.cpp.obj: addkernels/CMakeFiles/addkernels.dir/flags.make
addkernels/CMakeFiles/addkernels.dir/include_inliner.cpp.obj: ../addkernels/include_inliner.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object addkernels/CMakeFiles/addkernels.dir/include_inliner.cpp.obj"
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\addkernels && C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\addkernels.dir\include_inliner.cpp.obj -c C:\Users\Adil\Desktop\MLOpen-1-1.5.x\addkernels\include_inliner.cpp

addkernels/CMakeFiles/addkernels.dir/include_inliner.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/addkernels.dir/include_inliner.cpp.i"
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\addkernels && C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Adil\Desktop\MLOpen-1-1.5.x\addkernels\include_inliner.cpp > CMakeFiles\addkernels.dir\include_inliner.cpp.i

addkernels/CMakeFiles/addkernels.dir/include_inliner.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/addkernels.dir/include_inliner.cpp.s"
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\addkernels && C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Adil\Desktop\MLOpen-1-1.5.x\addkernels\include_inliner.cpp -o CMakeFiles\addkernels.dir\include_inliner.cpp.s

addkernels/CMakeFiles/addkernels.dir/addkernels.cpp.obj: addkernels/CMakeFiles/addkernels.dir/flags.make
addkernels/CMakeFiles/addkernels.dir/addkernels.cpp.obj: ../addkernels/addkernels.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object addkernels/CMakeFiles/addkernels.dir/addkernels.cpp.obj"
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\addkernels && C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\addkernels.dir\addkernels.cpp.obj -c C:\Users\Adil\Desktop\MLOpen-1-1.5.x\addkernels\addkernels.cpp

addkernels/CMakeFiles/addkernels.dir/addkernels.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/addkernels.dir/addkernels.cpp.i"
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\addkernels && C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Adil\Desktop\MLOpen-1-1.5.x\addkernels\addkernels.cpp > CMakeFiles\addkernels.dir\addkernels.cpp.i

addkernels/CMakeFiles/addkernels.dir/addkernels.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/addkernels.dir/addkernels.cpp.s"
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\addkernels && C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Adil\Desktop\MLOpen-1-1.5.x\addkernels\addkernels.cpp -o CMakeFiles\addkernels.dir\addkernels.cpp.s

# Object files for target addkernels
addkernels_OBJECTS = \
"CMakeFiles/addkernels.dir/include_inliner.cpp.obj" \
"CMakeFiles/addkernels.dir/addkernels.cpp.obj"

# External object files for target addkernels
addkernels_EXTERNAL_OBJECTS =

bin/addkernels.exe: addkernels/CMakeFiles/addkernels.dir/include_inliner.cpp.obj
bin/addkernels.exe: addkernels/CMakeFiles/addkernels.dir/addkernels.cpp.obj
bin/addkernels.exe: addkernels/CMakeFiles/addkernels.dir/build.make
bin/addkernels.exe: addkernels/CMakeFiles/addkernels.dir/linklibs.rsp
bin/addkernels.exe: addkernels/CMakeFiles/addkernels.dir/objects1.rsp
bin/addkernels.exe: addkernels/CMakeFiles/addkernels.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ..\bin\addkernels.exe"
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\addkernels && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\addkernels.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
addkernels/CMakeFiles/addkernels.dir/build: bin/addkernels.exe

.PHONY : addkernels/CMakeFiles/addkernels.dir/build

addkernels/CMakeFiles/addkernels.dir/clean:
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\addkernels && $(CMAKE_COMMAND) -P CMakeFiles\addkernels.dir\cmake_clean.cmake
.PHONY : addkernels/CMakeFiles/addkernels.dir/clean

addkernels/CMakeFiles/addkernels.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Adil\Desktop\MLOpen-1-1.5.x C:\Users\Adil\Desktop\MLOpen-1-1.5.x\addkernels C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\addkernels C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\addkernels\CMakeFiles\addkernels.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : addkernels/CMakeFiles/addkernels.dir/depend
