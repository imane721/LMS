# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.22.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.22.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/emy/CS6013/IL_malloc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/emy/CS6013/IL_malloc

# Include any dependencies generated for this target.
include CMakeFiles/IL_malloc.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/IL_malloc.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/IL_malloc.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/IL_malloc.dir/flags.make

CMakeFiles/IL_malloc.dir/myMalloc.cpp.o: CMakeFiles/IL_malloc.dir/flags.make
CMakeFiles/IL_malloc.dir/myMalloc.cpp.o: myMalloc.cpp
CMakeFiles/IL_malloc.dir/myMalloc.cpp.o: CMakeFiles/IL_malloc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/emy/CS6013/IL_malloc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/IL_malloc.dir/myMalloc.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/IL_malloc.dir/myMalloc.cpp.o -MF CMakeFiles/IL_malloc.dir/myMalloc.cpp.o.d -o CMakeFiles/IL_malloc.dir/myMalloc.cpp.o -c /Users/emy/CS6013/IL_malloc/myMalloc.cpp

CMakeFiles/IL_malloc.dir/myMalloc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IL_malloc.dir/myMalloc.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/emy/CS6013/IL_malloc/myMalloc.cpp > CMakeFiles/IL_malloc.dir/myMalloc.cpp.i

CMakeFiles/IL_malloc.dir/myMalloc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IL_malloc.dir/myMalloc.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/emy/CS6013/IL_malloc/myMalloc.cpp -o CMakeFiles/IL_malloc.dir/myMalloc.cpp.s

CMakeFiles/IL_malloc.dir/MyHashTable.cpp.o: CMakeFiles/IL_malloc.dir/flags.make
CMakeFiles/IL_malloc.dir/MyHashTable.cpp.o: MyHashTable.cpp
CMakeFiles/IL_malloc.dir/MyHashTable.cpp.o: CMakeFiles/IL_malloc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/emy/CS6013/IL_malloc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/IL_malloc.dir/MyHashTable.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/IL_malloc.dir/MyHashTable.cpp.o -MF CMakeFiles/IL_malloc.dir/MyHashTable.cpp.o.d -o CMakeFiles/IL_malloc.dir/MyHashTable.cpp.o -c /Users/emy/CS6013/IL_malloc/MyHashTable.cpp

CMakeFiles/IL_malloc.dir/MyHashTable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IL_malloc.dir/MyHashTable.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/emy/CS6013/IL_malloc/MyHashTable.cpp > CMakeFiles/IL_malloc.dir/MyHashTable.cpp.i

CMakeFiles/IL_malloc.dir/MyHashTable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IL_malloc.dir/MyHashTable.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/emy/CS6013/IL_malloc/MyHashTable.cpp -o CMakeFiles/IL_malloc.dir/MyHashTable.cpp.s

CMakeFiles/IL_malloc.dir/Tester.cpp.o: CMakeFiles/IL_malloc.dir/flags.make
CMakeFiles/IL_malloc.dir/Tester.cpp.o: Tester.cpp
CMakeFiles/IL_malloc.dir/Tester.cpp.o: CMakeFiles/IL_malloc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/emy/CS6013/IL_malloc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/IL_malloc.dir/Tester.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/IL_malloc.dir/Tester.cpp.o -MF CMakeFiles/IL_malloc.dir/Tester.cpp.o.d -o CMakeFiles/IL_malloc.dir/Tester.cpp.o -c /Users/emy/CS6013/IL_malloc/Tester.cpp

CMakeFiles/IL_malloc.dir/Tester.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IL_malloc.dir/Tester.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/emy/CS6013/IL_malloc/Tester.cpp > CMakeFiles/IL_malloc.dir/Tester.cpp.i

CMakeFiles/IL_malloc.dir/Tester.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IL_malloc.dir/Tester.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/emy/CS6013/IL_malloc/Tester.cpp -o CMakeFiles/IL_malloc.dir/Tester.cpp.s

# Object files for target IL_malloc
IL_malloc_OBJECTS = \
"CMakeFiles/IL_malloc.dir/myMalloc.cpp.o" \
"CMakeFiles/IL_malloc.dir/MyHashTable.cpp.o" \
"CMakeFiles/IL_malloc.dir/Tester.cpp.o"

# External object files for target IL_malloc
IL_malloc_EXTERNAL_OBJECTS =

IL_malloc: CMakeFiles/IL_malloc.dir/myMalloc.cpp.o
IL_malloc: CMakeFiles/IL_malloc.dir/MyHashTable.cpp.o
IL_malloc: CMakeFiles/IL_malloc.dir/Tester.cpp.o
IL_malloc: CMakeFiles/IL_malloc.dir/build.make
IL_malloc: CMakeFiles/IL_malloc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/emy/CS6013/IL_malloc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable IL_malloc"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/IL_malloc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/IL_malloc.dir/build: IL_malloc
.PHONY : CMakeFiles/IL_malloc.dir/build

CMakeFiles/IL_malloc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/IL_malloc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/IL_malloc.dir/clean

CMakeFiles/IL_malloc.dir/depend:
	cd /Users/emy/CS6013/IL_malloc && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/emy/CS6013/IL_malloc /Users/emy/CS6013/IL_malloc /Users/emy/CS6013/IL_malloc /Users/emy/CS6013/IL_malloc /Users/emy/CS6013/IL_malloc/CMakeFiles/IL_malloc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/IL_malloc.dir/depend

