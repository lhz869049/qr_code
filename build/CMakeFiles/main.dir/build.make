# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lhz/aero/qrcode_scan

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lhz/aero/qrcode_scan/build

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/src/main.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lhz/aero/qrcode_scan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/src/main.cpp.o -c /home/lhz/aero/qrcode_scan/src/main.cpp

CMakeFiles/main.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lhz/aero/qrcode_scan/src/main.cpp > CMakeFiles/main.dir/src/main.cpp.i

CMakeFiles/main.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lhz/aero/qrcode_scan/src/main.cpp -o CMakeFiles/main.dir/src/main.cpp.s

CMakeFiles/main.dir/src/detect_qrcode.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/detect_qrcode.cpp.o: ../src/detect_qrcode.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lhz/aero/qrcode_scan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main.dir/src/detect_qrcode.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/src/detect_qrcode.cpp.o -c /home/lhz/aero/qrcode_scan/src/detect_qrcode.cpp

CMakeFiles/main.dir/src/detect_qrcode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/detect_qrcode.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lhz/aero/qrcode_scan/src/detect_qrcode.cpp > CMakeFiles/main.dir/src/detect_qrcode.cpp.i

CMakeFiles/main.dir/src/detect_qrcode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/detect_qrcode.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lhz/aero/qrcode_scan/src/detect_qrcode.cpp -o CMakeFiles/main.dir/src/detect_qrcode.cpp.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/src/main.cpp.o" \
"CMakeFiles/main.dir/src/detect_qrcode.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: CMakeFiles/main.dir/src/main.cpp.o
main: CMakeFiles/main.dir/src/detect_qrcode.cpp.o
main: CMakeFiles/main.dir/build.make
main: /usr/local/lib/libopencv_calib3d.a
main: /usr/local/lib/libopencv_core.a
main: /usr/local/lib/libopencv_dnn.a
main: /usr/local/lib/libopencv_features2d.a
main: /usr/local/lib/libopencv_flann.a
main: /usr/local/lib/libopencv_highgui.a
main: /usr/local/lib/libopencv_imgcodecs.a
main: /usr/local/lib/libopencv_imgproc.a
main: /usr/local/lib/libopencv_ml.a
main: /usr/local/lib/libopencv_objdetect.a
main: /usr/local/lib/libopencv_photo.a
main: /usr/local/lib/libopencv_shape.a
main: /usr/local/lib/libopencv_stitching.a
main: /usr/local/lib/libopencv_superres.a
main: /usr/local/lib/libopencv_video.a
main: /usr/local/lib/libopencv_videoio.a
main: /usr/local/lib/libopencv_videostab.a
main: /usr/local/lib/libopencv_viz.a
main: /usr/local/lib/libopencv_aruco.a
main: /usr/local/lib/libopencv_bgsegm.a
main: /usr/local/lib/libopencv_bioinspired.a
main: /usr/local/lib/libopencv_ccalib.a
main: /usr/local/lib/libopencv_datasets.a
main: /usr/local/lib/libopencv_dnn_objdetect.a
main: /usr/local/lib/libopencv_dpm.a
main: /usr/local/lib/libopencv_face.a
main: /usr/local/lib/libopencv_freetype.a
main: /usr/local/lib/libopencv_fuzzy.a
main: /usr/local/lib/libopencv_hdf.a
main: /usr/local/lib/libopencv_hfs.a
main: /usr/local/lib/libopencv_img_hash.a
main: /usr/local/lib/libopencv_line_descriptor.a
main: /usr/local/lib/libopencv_optflow.a
main: /usr/local/lib/libopencv_phase_unwrapping.a
main: /usr/local/lib/libopencv_plot.a
main: /usr/local/lib/libopencv_reg.a
main: /usr/local/lib/libopencv_rgbd.a
main: /usr/local/lib/libopencv_saliency.a
main: /usr/local/lib/libopencv_stereo.a
main: /usr/local/lib/libopencv_structured_light.a
main: /usr/local/lib/libopencv_surface_matching.a
main: /usr/local/lib/libopencv_text.a
main: /usr/local/lib/libopencv_tracking.a
main: /usr/local/lib/libopencv_xfeatures2d.a
main: /usr/local/lib/libopencv_ximgproc.a
main: /usr/local/lib/libopencv_xobjdetect.a
main: /usr/local/lib/libopencv_xphoto.a
main: /usr/local/lib/libopencv_shape.a
main: /usr/local/lib/libopencv_photo.a
main: /usr/lib/x86_64-linux-gnu/hdf5/serial/libhdf5.so
main: /usr/lib/x86_64-linux-gnu/libpthread.so
main: /usr/lib/x86_64-linux-gnu/libsz.so
main: /usr/lib/x86_64-linux-gnu/libdl.so
main: /usr/lib/x86_64-linux-gnu/libm.so
main: /usr/local/lib/libopencv_calib3d.a
main: /usr/local/lib/libopencv_viz.a
main: /usr/lib/x86_64-linux-gnu/libfreetype.so
main: /usr/lib/x86_64-linux-gnu/libgl2ps.so
main: /usr/local/lib/libopencv_phase_unwrapping.a
main: /usr/local/lib/libopencv_video.a
main: /usr/local/lib/libopencv_datasets.a
main: /usr/local/lib/libopencv_plot.a
main: /usr/local/lib/libopencv_text.a
main: /usr/local/lib/libopencv_dnn.a
main: /usr/local/share/OpenCV/3rdparty/lib/liblibprotobuf.a
main: /usr/local/lib/libopencv_features2d.a
main: /usr/local/lib/libopencv_flann.a
main: /usr/local/lib/libopencv_highgui.a
main: /usr/local/lib/libopencv_ml.a
main: /usr/local/lib/libopencv_videoio.a
main: /usr/local/lib/libopencv_imgcodecs.a
main: /usr/lib/x86_64-linux-gnu/libwebp.so
main: /usr/lib/x86_64-linux-gnu/libjasper.so
main: /usr/lib/x86_64-linux-gnu/libjpeg.so
main: /usr/lib/x86_64-linux-gnu/libpng.so
main: /usr/lib/x86_64-linux-gnu/libtiff.so
main: /usr/lib/x86_64-linux-gnu/libImath.so
main: /usr/lib/x86_64-linux-gnu/libIlmImf.so
main: /usr/lib/x86_64-linux-gnu/libIex.so
main: /usr/lib/x86_64-linux-gnu/libHalf.so
main: /usr/lib/x86_64-linux-gnu/libIlmThread.so
main: /usr/local/lib/libopencv_objdetect.a
main: /usr/local/lib/libopencv_imgproc.a
main: /usr/local/lib/libopencv_core.a
main: /usr/lib/x86_64-linux-gnu/libz.so
main: /usr/local/share/OpenCV/3rdparty/lib/libittnotify.a
main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lhz/aero/qrcode_scan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main

.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /home/lhz/aero/qrcode_scan/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lhz/aero/qrcode_scan /home/lhz/aero/qrcode_scan /home/lhz/aero/qrcode_scan/build /home/lhz/aero/qrcode_scan/build /home/lhz/aero/qrcode_scan/build/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend

