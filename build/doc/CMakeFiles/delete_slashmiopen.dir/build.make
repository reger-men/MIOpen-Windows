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

# Utility rule file for delete_slashmiopen.

# Include the progress variables for this target.
include doc/CMakeFiles/delete_slashmiopen.dir/progress.make

doc/CMakeFiles/delete_slashmiopen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Removing MIOPEN_EXPORT from latex document. C:/Users/Adil/Desktop/MLOpen-1-1.5.x/doc/pdf/miopen.tex"
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\doc && sed -e s/sret{MIOPEN\/sret{/ -i C:/Users/Adil/Desktop/MLOpen-1-1.5.x/doc/pdf/miopen.tex

delete_slashmiopen: doc/CMakeFiles/delete_slashmiopen
delete_slashmiopen: doc/CMakeFiles/delete_slashmiopen.dir/build.make

.PHONY : delete_slashmiopen

# Rule to build all files generated by this target.
doc/CMakeFiles/delete_slashmiopen.dir/build: delete_slashmiopen

.PHONY : doc/CMakeFiles/delete_slashmiopen.dir/build

doc/CMakeFiles/delete_slashmiopen.dir/clean:
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\doc && $(CMAKE_COMMAND) -P CMakeFiles\delete_slashmiopen.dir\cmake_clean.cmake
.PHONY : doc/CMakeFiles/delete_slashmiopen.dir/clean

doc/CMakeFiles/delete_slashmiopen.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Adil\Desktop\MLOpen-1-1.5.x C:\Users\Adil\Desktop\MLOpen-1-1.5.x\doc C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\doc C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\doc\CMakeFiles\delete_slashmiopen.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : doc/CMakeFiles/delete_slashmiopen.dir/depend

