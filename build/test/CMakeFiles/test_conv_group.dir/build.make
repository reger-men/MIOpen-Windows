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

# Utility rule file for test_conv_group.

# Include the progress variables for this target.
include test/CMakeFiles/test_conv_group.dir/progress.make

test/CMakeFiles/test_conv_group:
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 16 128 56 56 --weights 256 4 3 3 --filter 1 1 1 1, --group-count 32
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 16 256 56 56 --weights 512 8 3 3 --filter 1 1 2 2, --group-count 32
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 16 256 28 28 --weights 512 8 3 3 --filter 1 1 1 1, --group-count 32
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 16 512 28 28 --weights 1024 16 3 3 --filter 1 1 2 2, --group-count 32
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 16 512 14 14 --weights 1024 16 3 3 --filter 1 1 1 1, --group-count 32
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 16 1024 14 14 --weights 2048 32 3 3 --filter 1 1 2 2, --group-count 32
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 16 1024 7 7 --weights 2048 32 3 3 --filter 1 1 1 1, --group-count 32
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 32 128 56 56 --weights 256 4 3 3 --filter 1 1 1 1, --group-count 32
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 32 256 56 56 --weights 512 8 3 3 --filter 1 1 2 2, --group-count 32
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 32 256 28 28 --weights 512 8 3 3 --filter 1 1 1 1, --group-count 32
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 32 512 28 28 --weights 1024 16 3 3 --filter 1 1 2 2, --group-count 32
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 32 512 14 14 --weights 1024 16 3 3 --filter 1 1 1 1, --group-count 32
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 32 1024 14 14 --weights 2048 32 3 3 --filter 1 1 2 2, --group-count 32
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 32 1024 7 7 --weights 2048 32 3 3 --filter 1 1 1 1, --group-count 32
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 4 4 161 700 --weights 32 1 5 20 --filter 0 0 2 2, --cmode dw
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 8 2 161 700 --weights 32 1 5 20 --filter 0 0 2 2, --cmode dw
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 16 4 161 700 --weights 32 1 5 20 --filter 0 0 2 2, --cmode dw
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 32 2 161 700 --weights 32 1 5 20 --filter 0 0 2 2, --cmode dw
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 4 32 79 341 --weights 32 16 5 10 --filter 0 0 2 2, --group-count 2
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 8 32 79 341 --weights 32 16 5 10 --filter 0 0 2 2, --group-count 2
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 16 32 79 341 --weights 32 16 5 10 --filter 0 0 2 2, --group-count 2
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 32 32 79 341 --weights 32 16 5 10 --filter 0 0 2 2, --group-count 2
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 16 4 48 480 --weights 16 1 3 3 --filter 1 1 1 1, --cmode dw
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 16 16 24 240 --weights 32 1 3 3 --filter 1 1 1 1, --cmode dw
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 16 32 12 120 --weights 64 8 3 3 --filter 1 1 1 1, --group-count 4
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 16 64 6 60 --weights 128 16 3 3 --filter 1 1 1 1, --group-count 4
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 8 3 108 108 --weights 63 1 3 3 --filter 1 1 2 2, --group-count 3
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 8 64 54 54 --weights 64 8 3 3 --filter 1 1 1 1, --group-count 8
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 8 128 27 27 --weights 128 16 3 3 --filter 1 1 1 1, --group-count 8
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 8 3 224 224 --weights 63 1 3 3 --filter 1 1 1 1, --group-count 3
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 8 64 112 112 --weights 128 32 3 3 --filter 1 1 1 1, --group-count 2
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 16 9 224 224 --weights 63 3 3 3 --filter 1 1 1 1, --group-count 3
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 16 64 112 112 --weights 128 16 3 3 --filter 1 1 1 1, --group-count 4
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 16 3 224 224 --weights 63 1 7 7 --filter 3 3 2 2, --group-count 3
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 16 192 28 28 --weights 32 12 5 5 --filter 2 2 1 1, --group-count 16
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 16 832 7 7 --weights 128 52 5 5 --filter 2 2 1 1, --group-count 16
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 16 192 28 28 --weights 32 24 1 1 --filter 0 0 1 1, --group-count 8
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 16 832 7 7 --weights 128 104 1 1 --filter 0 0 1 1, --group-count 8
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && ..\bin\test_conv.exe --verbose --input 11 23 161 700 --weights 46 1 7 7 --filter 1 1 2 2, --cmode dw

test_conv_group: test/CMakeFiles/test_conv_group
test_conv_group: test/CMakeFiles/test_conv_group.dir/build.make

.PHONY : test_conv_group

# Rule to build all files generated by this target.
test/CMakeFiles/test_conv_group.dir/build: test_conv_group

.PHONY : test/CMakeFiles/test_conv_group.dir/build

test/CMakeFiles/test_conv_group.dir/clean:
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test && $(CMAKE_COMMAND) -P CMakeFiles\test_conv_group.dir\cmake_clean.cmake
.PHONY : test/CMakeFiles/test_conv_group.dir/clean

test/CMakeFiles/test_conv_group.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Adil\Desktop\MLOpen-1-1.5.x C:\Users\Adil\Desktop\MLOpen-1-1.5.x\test C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\test\CMakeFiles\test_conv_group.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/test_conv_group.dir/depend
