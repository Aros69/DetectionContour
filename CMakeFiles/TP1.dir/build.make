# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /home/robin/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/192.5728.100/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/robin/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/192.5728.100/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/robin/Master/AI/TP1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/robin/Master/AI/TP1

# Include any dependencies generated for this target.
include CMakeFiles/TP1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TP1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TP1.dir/flags.make

CMakeFiles/TP1.dir/main.cpp.o: CMakeFiles/TP1.dir/flags.make
CMakeFiles/TP1.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/robin/Master/AI/TP1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TP1.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TP1.dir/main.cpp.o -c /home/robin/Master/AI/TP1/main.cpp

CMakeFiles/TP1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP1.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robin/Master/AI/TP1/main.cpp > CMakeFiles/TP1.dir/main.cpp.i

CMakeFiles/TP1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP1.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robin/Master/AI/TP1/main.cpp -o CMakeFiles/TP1.dir/main.cpp.s

CMakeFiles/TP1.dir/src/utils/MatrixFilter.cpp.o: CMakeFiles/TP1.dir/flags.make
CMakeFiles/TP1.dir/src/utils/MatrixFilter.cpp.o: src/utils/MatrixFilter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/robin/Master/AI/TP1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/TP1.dir/src/utils/MatrixFilter.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TP1.dir/src/utils/MatrixFilter.cpp.o -c /home/robin/Master/AI/TP1/src/utils/MatrixFilter.cpp

CMakeFiles/TP1.dir/src/utils/MatrixFilter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP1.dir/src/utils/MatrixFilter.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robin/Master/AI/TP1/src/utils/MatrixFilter.cpp > CMakeFiles/TP1.dir/src/utils/MatrixFilter.cpp.i

CMakeFiles/TP1.dir/src/utils/MatrixFilter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP1.dir/src/utils/MatrixFilter.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robin/Master/AI/TP1/src/utils/MatrixFilter.cpp -o CMakeFiles/TP1.dir/src/utils/MatrixFilter.cpp.s

CMakeFiles/TP1.dir/src/Computations.cpp.o: CMakeFiles/TP1.dir/flags.make
CMakeFiles/TP1.dir/src/Computations.cpp.o: src/Computations.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/robin/Master/AI/TP1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/TP1.dir/src/Computations.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TP1.dir/src/Computations.cpp.o -c /home/robin/Master/AI/TP1/src/Computations.cpp

CMakeFiles/TP1.dir/src/Computations.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP1.dir/src/Computations.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robin/Master/AI/TP1/src/Computations.cpp > CMakeFiles/TP1.dir/src/Computations.cpp.i

CMakeFiles/TP1.dir/src/Computations.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP1.dir/src/Computations.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robin/Master/AI/TP1/src/Computations.cpp -o CMakeFiles/TP1.dir/src/Computations.cpp.s

CMakeFiles/TP1.dir/src/utils/Matrix.cpp.o: CMakeFiles/TP1.dir/flags.make
CMakeFiles/TP1.dir/src/utils/Matrix.cpp.o: src/utils/Matrix.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/robin/Master/AI/TP1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/TP1.dir/src/utils/Matrix.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TP1.dir/src/utils/Matrix.cpp.o -c /home/robin/Master/AI/TP1/src/utils/Matrix.cpp

CMakeFiles/TP1.dir/src/utils/Matrix.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP1.dir/src/utils/Matrix.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robin/Master/AI/TP1/src/utils/Matrix.cpp > CMakeFiles/TP1.dir/src/utils/Matrix.cpp.i

CMakeFiles/TP1.dir/src/utils/Matrix.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP1.dir/src/utils/Matrix.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robin/Master/AI/TP1/src/utils/Matrix.cpp -o CMakeFiles/TP1.dir/src/utils/Matrix.cpp.s

# Object files for target TP1
TP1_OBJECTS = \
"CMakeFiles/TP1.dir/main.cpp.o" \
"CMakeFiles/TP1.dir/src/utils/MatrixFilter.cpp.o" \
"CMakeFiles/TP1.dir/src/Computations.cpp.o" \
"CMakeFiles/TP1.dir/src/utils/Matrix.cpp.o"

# External object files for target TP1
TP1_EXTERNAL_OBJECTS =

bin/TP1: CMakeFiles/TP1.dir/main.cpp.o
bin/TP1: CMakeFiles/TP1.dir/src/utils/MatrixFilter.cpp.o
bin/TP1: CMakeFiles/TP1.dir/src/Computations.cpp.o
bin/TP1: CMakeFiles/TP1.dir/src/utils/Matrix.cpp.o
bin/TP1: CMakeFiles/TP1.dir/build.make
bin/TP1: /usr/local/lib/libopencv_dnn.so.4.1.0
bin/TP1: /usr/local/lib/libopencv_gapi.so.4.1.0
bin/TP1: /usr/local/lib/libopencv_ml.so.4.1.0
bin/TP1: /usr/local/lib/libopencv_objdetect.so.4.1.0
bin/TP1: /usr/local/lib/libopencv_photo.so.4.1.0
bin/TP1: /usr/local/lib/libopencv_stitching.so.4.1.0
bin/TP1: /usr/local/lib/libopencv_video.so.4.1.0
bin/TP1: /usr/local/lib/libopencv_calib3d.so.4.1.0
bin/TP1: /usr/local/lib/libopencv_features2d.so.4.1.0
bin/TP1: /usr/local/lib/libopencv_flann.so.4.1.0
bin/TP1: /usr/local/lib/libopencv_highgui.so.4.1.0
bin/TP1: /usr/local/lib/libopencv_videoio.so.4.1.0
bin/TP1: /usr/local/lib/libopencv_imgcodecs.so.4.1.0
bin/TP1: /usr/local/lib/libopencv_imgproc.so.4.1.0
bin/TP1: /usr/local/lib/libopencv_core.so.4.1.0
bin/TP1: CMakeFiles/TP1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/robin/Master/AI/TP1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable bin/TP1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TP1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TP1.dir/build: bin/TP1

.PHONY : CMakeFiles/TP1.dir/build

CMakeFiles/TP1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TP1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TP1.dir/clean

CMakeFiles/TP1.dir/depend:
	cd /home/robin/Master/AI/TP1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/robin/Master/AI/TP1 /home/robin/Master/AI/TP1 /home/robin/Master/AI/TP1 /home/robin/Master/AI/TP1 /home/robin/Master/AI/TP1/CMakeFiles/TP1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TP1.dir/depend
