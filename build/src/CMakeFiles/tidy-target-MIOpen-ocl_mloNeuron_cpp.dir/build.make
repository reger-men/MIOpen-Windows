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

# Utility rule file for tidy-target-MIOpen-ocl_mloNeuron_cpp.

# Include the progress variables for this target.
include src/CMakeFiles/tidy-target-MIOpen-ocl_mloNeuron_cpp.dir/progress.make

src/CMakeFiles/tidy-target-MIOpen-ocl_mloNeuron_cpp:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "clang-tidy: Running clang-tidy on target ocl/mloNeuron.cpp..."
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\src && CLANG_TIDY_EXE-NOTFOUND -p C:/Users/Adil/Desktop/MLOpen-1-1.5.x/build -checks='*,-cert-env33-c,-android-cloexec-fopen,-cert-msc30-c,-cert-msc50-cpp,-clang-analyzer-alpha.core.CastToStruct,-clang-analyzer-optin.performance.Padding,-clang-diagnostic-deprecated-declarations,-clang-diagnostic-extern-c-compat,-clang-diagnostic-unused-command-line-argument,-cppcoreguidelines-pro-bounds-array-to-pointer-decay,-cppcoreguidelines-pro-bounds-constant-array-index,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-pro-type-member-init,-cppcoreguidelines-pro-type-reinterpret-cast,-cppcoreguidelines-pro-type-union-access,-cppcoreguidelines-pro-type-vararg,-cppcoreguidelines-special-member-functions,-fuchsia-*,-google-explicit-constructor,-google-readability-braces-around-statements,-google-readability-todo,-google-runtime-int,-google-runtime-references,-hicpp-braces-around-statements,-hicpp-explicit-conversions,-hicpp-no-array-decay,-hicpp-signed-bitwise,-hicpp-special-member-functions,-hicpp-use-equals-default,-hicpp-use-override,-llvm-header-guard,-llvm-include-order,-misc-misplaced-const,-modernize-pass-by-value,-modernize-use-default-member-init,-modernize-use-equals-default,-modernize-use-transparent-functors,-performance-unnecessary-value-param,-readability-braces-around-statements,-readability-else-after-return,-readability-named-parameter,-hicpp-use-auto,-modernize-use-auto' -extra-arg=-DMIOPEN_USE_CLANG_TIDY -analyze-temporary-dtors -header-filter='.*hpp' ocl/mloNeuron.cpp -export-fixes=C:/Users/Adil/Desktop/MLOpen-1-1.5.x/build/fixits/MIOpen-ocl_mloNeuron_cpp.yaml

tidy-target-MIOpen-ocl_mloNeuron_cpp: src/CMakeFiles/tidy-target-MIOpen-ocl_mloNeuron_cpp
tidy-target-MIOpen-ocl_mloNeuron_cpp: src/CMakeFiles/tidy-target-MIOpen-ocl_mloNeuron_cpp.dir/build.make

.PHONY : tidy-target-MIOpen-ocl_mloNeuron_cpp

# Rule to build all files generated by this target.
src/CMakeFiles/tidy-target-MIOpen-ocl_mloNeuron_cpp.dir/build: tidy-target-MIOpen-ocl_mloNeuron_cpp

.PHONY : src/CMakeFiles/tidy-target-MIOpen-ocl_mloNeuron_cpp.dir/build

src/CMakeFiles/tidy-target-MIOpen-ocl_mloNeuron_cpp.dir/clean:
	cd /d C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\src && $(CMAKE_COMMAND) -P CMakeFiles\tidy-target-MIOpen-ocl_mloNeuron_cpp.dir\cmake_clean.cmake
.PHONY : src/CMakeFiles/tidy-target-MIOpen-ocl_mloNeuron_cpp.dir/clean

src/CMakeFiles/tidy-target-MIOpen-ocl_mloNeuron_cpp.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Adil\Desktop\MLOpen-1-1.5.x C:\Users\Adil\Desktop\MLOpen-1-1.5.x\src C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\src C:\Users\Adil\Desktop\MLOpen-1-1.5.x\build\src\CMakeFiles\tidy-target-MIOpen-ocl_mloNeuron_cpp.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/tidy-target-MIOpen-ocl_mloNeuron_cpp.dir/depend
