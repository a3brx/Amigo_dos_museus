# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.2.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.2.1\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = Z:\Amigo_dos_museus

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = Z:\Amigo_dos_museus\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/amigo_dos_museus.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/amigo_dos_museus.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/amigo_dos_museus.dir/flags.make

CMakeFiles/amigo_dos_museus.dir/main.cpp.obj: CMakeFiles/amigo_dos_museus.dir/flags.make
CMakeFiles/amigo_dos_museus.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=Z:\Amigo_dos_museus\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/amigo_dos_museus.dir/main.cpp.obj"
	C:\Programs\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\amigo_dos_museus.dir\main.cpp.obj -c Z:\Amigo_dos_museus\main.cpp

CMakeFiles/amigo_dos_museus.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/amigo_dos_museus.dir/main.cpp.i"
	C:\Programs\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E Z:\Amigo_dos_museus\main.cpp > CMakeFiles\amigo_dos_museus.dir\main.cpp.i

CMakeFiles/amigo_dos_museus.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/amigo_dos_museus.dir/main.cpp.s"
	C:\Programs\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S Z:\Amigo_dos_museus\main.cpp -o CMakeFiles\amigo_dos_museus.dir\main.cpp.s

CMakeFiles/amigo_dos_museus.dir/Date.cpp.obj: CMakeFiles/amigo_dos_museus.dir/flags.make
CMakeFiles/amigo_dos_museus.dir/Date.cpp.obj: ../Date.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=Z:\Amigo_dos_museus\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/amigo_dos_museus.dir/Date.cpp.obj"
	C:\Programs\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\amigo_dos_museus.dir\Date.cpp.obj -c Z:\Amigo_dos_museus\Date.cpp

CMakeFiles/amigo_dos_museus.dir/Date.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/amigo_dos_museus.dir/Date.cpp.i"
	C:\Programs\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E Z:\Amigo_dos_museus\Date.cpp > CMakeFiles\amigo_dos_museus.dir\Date.cpp.i

CMakeFiles/amigo_dos_museus.dir/Date.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/amigo_dos_museus.dir/Date.cpp.s"
	C:\Programs\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S Z:\Amigo_dos_museus\Date.cpp -o CMakeFiles\amigo_dos_museus.dir\Date.cpp.s

# Object files for target amigo_dos_museus
amigo_dos_museus_OBJECTS = \
"CMakeFiles/amigo_dos_museus.dir/main.cpp.obj" \
"CMakeFiles/amigo_dos_museus.dir/Date.cpp.obj"

# External object files for target amigo_dos_museus
amigo_dos_museus_EXTERNAL_OBJECTS =

amigo_dos_museus.exe: CMakeFiles/amigo_dos_museus.dir/main.cpp.obj
amigo_dos_museus.exe: CMakeFiles/amigo_dos_museus.dir/Date.cpp.obj
amigo_dos_museus.exe: CMakeFiles/amigo_dos_museus.dir/build.make
amigo_dos_museus.exe: CMakeFiles/amigo_dos_museus.dir/linklibs.rsp
amigo_dos_museus.exe: CMakeFiles/amigo_dos_museus.dir/objects1.rsp
amigo_dos_museus.exe: CMakeFiles/amigo_dos_museus.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=Z:\Amigo_dos_museus\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable amigo_dos_museus.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\amigo_dos_museus.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/amigo_dos_museus.dir/build: amigo_dos_museus.exe

.PHONY : CMakeFiles/amigo_dos_museus.dir/build

CMakeFiles/amigo_dos_museus.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\amigo_dos_museus.dir\cmake_clean.cmake
.PHONY : CMakeFiles/amigo_dos_museus.dir/clean

CMakeFiles/amigo_dos_museus.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" Z:\Amigo_dos_museus Z:\Amigo_dos_museus Z:\Amigo_dos_museus\cmake-build-debug Z:\Amigo_dos_museus\cmake-build-debug Z:\Amigo_dos_museus\cmake-build-debug\CMakeFiles\amigo_dos_museus.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/amigo_dos_museus.dir/depend

