# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = "C:/Program Files/CMake/bin/cmake.exe"

# The command to remove a file.
RM = "C:/Program Files/CMake/bin/cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "D:/Assignment/4th Sem/Theory of automata/RegXplorer"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:/Assignment/4th Sem/Theory of automata/RegXplorer/build"

# Include any dependencies generated for this target.
include CMakeFiles/RegexSearchEngine.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/RegexSearchEngine.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/RegexSearchEngine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RegexSearchEngine.dir/flags.make

CMakeFiles/RegexSearchEngine.dir/src/main.cpp.obj: CMakeFiles/RegexSearchEngine.dir/flags.make
CMakeFiles/RegexSearchEngine.dir/src/main.cpp.obj: CMakeFiles/RegexSearchEngine.dir/includes_CXX.rsp
CMakeFiles/RegexSearchEngine.dir/src/main.cpp.obj: D:/Assignment/4th\ Sem/Theory\ of\ automata/RegXplorer/src/main.cpp
CMakeFiles/RegexSearchEngine.dir/src/main.cpp.obj: CMakeFiles/RegexSearchEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:/Assignment/4th Sem/Theory of automata/RegXplorer/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/RegexSearchEngine.dir/src/main.cpp.obj"
	C:/msys64/mingw64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/RegexSearchEngine.dir/src/main.cpp.obj -MF CMakeFiles/RegexSearchEngine.dir/src/main.cpp.obj.d -o CMakeFiles/RegexSearchEngine.dir/src/main.cpp.obj -c "D:/Assignment/4th Sem/Theory of automata/RegXplorer/src/main.cpp"

CMakeFiles/RegexSearchEngine.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RegexSearchEngine.dir/src/main.cpp.i"
	C:/msys64/mingw64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:/Assignment/4th Sem/Theory of automata/RegXplorer/src/main.cpp" > CMakeFiles/RegexSearchEngine.dir/src/main.cpp.i

CMakeFiles/RegexSearchEngine.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RegexSearchEngine.dir/src/main.cpp.s"
	C:/msys64/mingw64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:/Assignment/4th Sem/Theory of automata/RegXplorer/src/main.cpp" -o CMakeFiles/RegexSearchEngine.dir/src/main.cpp.s

# Object files for target RegexSearchEngine
RegexSearchEngine_OBJECTS = \
"CMakeFiles/RegexSearchEngine.dir/src/main.cpp.obj"

# External object files for target RegexSearchEngine
RegexSearchEngine_EXTERNAL_OBJECTS =

D:/Assignment/4th\ Sem/Theory\ of\ automata/RegXplorer/bin/RegexSearchEngine.exe: CMakeFiles/RegexSearchEngine.dir/src/main.cpp.obj
D:/Assignment/4th\ Sem/Theory\ of\ automata/RegXplorer/bin/RegexSearchEngine.exe: CMakeFiles/RegexSearchEngine.dir/build.make
D:/Assignment/4th\ Sem/Theory\ of\ automata/RegXplorer/bin/RegexSearchEngine.exe: CMakeFiles/RegexSearchEngine.dir/linkLibs.rsp
D:/Assignment/4th\ Sem/Theory\ of\ automata/RegXplorer/bin/RegexSearchEngine.exe: CMakeFiles/RegexSearchEngine.dir/objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:/Assignment/4th Sem/Theory of automata/RegXplorer/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable \"D:/Assignment/4th Sem/Theory of automata/RegXplorer/bin/RegexSearchEngine.exe\""
	"C:/Program Files/CMake/bin/cmake.exe" -E rm -f CMakeFiles/RegexSearchEngine.dir/objects.a
	C:/msys64/mingw64/bin/ar.exe qc CMakeFiles/RegexSearchEngine.dir/objects.a @CMakeFiles/RegexSearchEngine.dir/objects1.rsp
	C:/msys64/mingw64/bin/g++.exe -g -Wl,--whole-archive CMakeFiles/RegexSearchEngine.dir/objects.a -Wl,--no-whole-archive -o "D:/Assignment/4th Sem/Theory of automata/RegXplorer/bin/RegexSearchEngine.exe" -Wl,--out-implib,libRegexSearchEngine.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/RegexSearchEngine.dir/linkLibs.rsp

# Rule to build all files generated by this target.
CMakeFiles/RegexSearchEngine.dir/build: D:/Assignment/4th\ Sem/Theory\ of\ automata/RegXplorer/bin/RegexSearchEngine.exe
.PHONY : CMakeFiles/RegexSearchEngine.dir/build

CMakeFiles/RegexSearchEngine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/RegexSearchEngine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/RegexSearchEngine.dir/clean

CMakeFiles/RegexSearchEngine.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "D:/Assignment/4th Sem/Theory of automata/RegXplorer" "D:/Assignment/4th Sem/Theory of automata/RegXplorer" "D:/Assignment/4th Sem/Theory of automata/RegXplorer/build" "D:/Assignment/4th Sem/Theory of automata/RegXplorer/build" "D:/Assignment/4th Sem/Theory of automata/RegXplorer/build/CMakeFiles/RegexSearchEngine.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/RegexSearchEngine.dir/depend

