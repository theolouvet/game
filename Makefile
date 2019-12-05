# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/thep/Documents/game

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/thep/Documents/game

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/thep/Documents/game/CMakeFiles /home/thep/Documents/game/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/thep/Documents/game/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named pgm

# Build rule for target.
pgm: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 pgm
.PHONY : pgm

# fast build rule for target.
pgm/fast:
	$(MAKE) -f CMakeFiles/pgm.dir/build.make CMakeFiles/pgm.dir/build
.PHONY : pgm/fast

projet/src/camera.o: projet/src/camera.cpp.o

.PHONY : projet/src/camera.o

# target to build an object file
projet/src/camera.cpp.o:
	$(MAKE) -f CMakeFiles/pgm.dir/build.make CMakeFiles/pgm.dir/projet/src/camera.cpp.o
.PHONY : projet/src/camera.cpp.o

projet/src/camera.i: projet/src/camera.cpp.i

.PHONY : projet/src/camera.i

# target to preprocess a source file
projet/src/camera.cpp.i:
	$(MAKE) -f CMakeFiles/pgm.dir/build.make CMakeFiles/pgm.dir/projet/src/camera.cpp.i
.PHONY : projet/src/camera.cpp.i

projet/src/camera.s: projet/src/camera.cpp.s

.PHONY : projet/src/camera.s

# target to generate assembly for a file
projet/src/camera.cpp.s:
	$(MAKE) -f CMakeFiles/pgm.dir/build.make CMakeFiles/pgm.dir/projet/src/camera.cpp.s
.PHONY : projet/src/camera.cpp.s

projet/src/heros.o: projet/src/heros.cpp.o

.PHONY : projet/src/heros.o

# target to build an object file
projet/src/heros.cpp.o:
	$(MAKE) -f CMakeFiles/pgm.dir/build.make CMakeFiles/pgm.dir/projet/src/heros.cpp.o
.PHONY : projet/src/heros.cpp.o

projet/src/heros.i: projet/src/heros.cpp.i

.PHONY : projet/src/heros.i

# target to preprocess a source file
projet/src/heros.cpp.i:
	$(MAKE) -f CMakeFiles/pgm.dir/build.make CMakeFiles/pgm.dir/projet/src/heros.cpp.i
.PHONY : projet/src/heros.cpp.i

projet/src/heros.s: projet/src/heros.cpp.s

.PHONY : projet/src/heros.s

# target to generate assembly for a file
projet/src/heros.cpp.s:
	$(MAKE) -f CMakeFiles/pgm.dir/build.make CMakeFiles/pgm.dir/projet/src/heros.cpp.s
.PHONY : projet/src/heros.cpp.s

projet/src/main.o: projet/src/main.cpp.o

.PHONY : projet/src/main.o

# target to build an object file
projet/src/main.cpp.o:
	$(MAKE) -f CMakeFiles/pgm.dir/build.make CMakeFiles/pgm.dir/projet/src/main.cpp.o
.PHONY : projet/src/main.cpp.o

projet/src/main.i: projet/src/main.cpp.i

.PHONY : projet/src/main.i

# target to preprocess a source file
projet/src/main.cpp.i:
	$(MAKE) -f CMakeFiles/pgm.dir/build.make CMakeFiles/pgm.dir/projet/src/main.cpp.i
.PHONY : projet/src/main.cpp.i

projet/src/main.s: projet/src/main.cpp.s

.PHONY : projet/src/main.s

# target to generate assembly for a file
projet/src/main.cpp.s:
	$(MAKE) -f CMakeFiles/pgm.dir/build.make CMakeFiles/pgm.dir/projet/src/main.cpp.s
.PHONY : projet/src/main.cpp.s

projet/src/map/myterrain.o: projet/src/map/myterrain.cpp.o

.PHONY : projet/src/map/myterrain.o

# target to build an object file
projet/src/map/myterrain.cpp.o:
	$(MAKE) -f CMakeFiles/pgm.dir/build.make CMakeFiles/pgm.dir/projet/src/map/myterrain.cpp.o
.PHONY : projet/src/map/myterrain.cpp.o

projet/src/map/myterrain.i: projet/src/map/myterrain.cpp.i

.PHONY : projet/src/map/myterrain.i

# target to preprocess a source file
projet/src/map/myterrain.cpp.i:
	$(MAKE) -f CMakeFiles/pgm.dir/build.make CMakeFiles/pgm.dir/projet/src/map/myterrain.cpp.i
.PHONY : projet/src/map/myterrain.cpp.i

projet/src/map/myterrain.s: projet/src/map/myterrain.cpp.s

.PHONY : projet/src/map/myterrain.s

# target to generate assembly for a file
projet/src/map/myterrain.cpp.s:
	$(MAKE) -f CMakeFiles/pgm.dir/build.make CMakeFiles/pgm.dir/projet/src/map/myterrain.cpp.s
.PHONY : projet/src/map/myterrain.cpp.s

projet/src/map/qmap.o: projet/src/map/qmap.cpp.o

.PHONY : projet/src/map/qmap.o

# target to build an object file
projet/src/map/qmap.cpp.o:
	$(MAKE) -f CMakeFiles/pgm.dir/build.make CMakeFiles/pgm.dir/projet/src/map/qmap.cpp.o
.PHONY : projet/src/map/qmap.cpp.o

projet/src/map/qmap.i: projet/src/map/qmap.cpp.i

.PHONY : projet/src/map/qmap.i

# target to preprocess a source file
projet/src/map/qmap.cpp.i:
	$(MAKE) -f CMakeFiles/pgm.dir/build.make CMakeFiles/pgm.dir/projet/src/map/qmap.cpp.i
.PHONY : projet/src/map/qmap.cpp.i

projet/src/map/qmap.s: projet/src/map/qmap.cpp.s

.PHONY : projet/src/map/qmap.s

# target to generate assembly for a file
projet/src/map/qmap.cpp.s:
	$(MAKE) -f CMakeFiles/pgm.dir/build.make CMakeFiles/pgm.dir/projet/src/map/qmap.cpp.s
.PHONY : projet/src/map/qmap.cpp.s

projet/src/map/waterquad.o: projet/src/map/waterquad.cpp.o

.PHONY : projet/src/map/waterquad.o

# target to build an object file
projet/src/map/waterquad.cpp.o:
	$(MAKE) -f CMakeFiles/pgm.dir/build.make CMakeFiles/pgm.dir/projet/src/map/waterquad.cpp.o
.PHONY : projet/src/map/waterquad.cpp.o

projet/src/map/waterquad.i: projet/src/map/waterquad.cpp.i

.PHONY : projet/src/map/waterquad.i

# target to preprocess a source file
projet/src/map/waterquad.cpp.i:
	$(MAKE) -f CMakeFiles/pgm.dir/build.make CMakeFiles/pgm.dir/projet/src/map/waterquad.cpp.i
.PHONY : projet/src/map/waterquad.cpp.i

projet/src/map/waterquad.s: projet/src/map/waterquad.cpp.s

.PHONY : projet/src/map/waterquad.s

# target to generate assembly for a file
projet/src/map/waterquad.cpp.s:
	$(MAKE) -f CMakeFiles/pgm.dir/build.make CMakeFiles/pgm.dir/projet/src/map/waterquad.cpp.s
.PHONY : projet/src/map/waterquad.cpp.s

projet/src/mascene.o: projet/src/mascene.cpp.o

.PHONY : projet/src/mascene.o

# target to build an object file
projet/src/mascene.cpp.o:
	$(MAKE) -f CMakeFiles/pgm.dir/build.make CMakeFiles/pgm.dir/projet/src/mascene.cpp.o
.PHONY : projet/src/mascene.cpp.o

projet/src/mascene.i: projet/src/mascene.cpp.i

.PHONY : projet/src/mascene.i

# target to preprocess a source file
projet/src/mascene.cpp.i:
	$(MAKE) -f CMakeFiles/pgm.dir/build.make CMakeFiles/pgm.dir/projet/src/mascene.cpp.i
.PHONY : projet/src/mascene.cpp.i

projet/src/mascene.s: projet/src/mascene.cpp.s

.PHONY : projet/src/mascene.s

# target to generate assembly for a file
projet/src/mascene.cpp.s:
	$(MAKE) -f CMakeFiles/pgm.dir/build.make CMakeFiles/pgm.dir/projet/src/mascene.cpp.s
.PHONY : projet/src/mascene.cpp.s

projet/src/myeventreceiver.o: projet/src/myeventreceiver.cpp.o

.PHONY : projet/src/myeventreceiver.o

# target to build an object file
projet/src/myeventreceiver.cpp.o:
	$(MAKE) -f CMakeFiles/pgm.dir/build.make CMakeFiles/pgm.dir/projet/src/myeventreceiver.cpp.o
.PHONY : projet/src/myeventreceiver.cpp.o

projet/src/myeventreceiver.i: projet/src/myeventreceiver.cpp.i

.PHONY : projet/src/myeventreceiver.i

# target to preprocess a source file
projet/src/myeventreceiver.cpp.i:
	$(MAKE) -f CMakeFiles/pgm.dir/build.make CMakeFiles/pgm.dir/projet/src/myeventreceiver.cpp.i
.PHONY : projet/src/myeventreceiver.cpp.i

projet/src/myeventreceiver.s: projet/src/myeventreceiver.cpp.s

.PHONY : projet/src/myeventreceiver.s

# target to generate assembly for a file
projet/src/myeventreceiver.cpp.s:
	$(MAKE) -f CMakeFiles/pgm.dir/build.make CMakeFiles/pgm.dir/projet/src/myeventreceiver.cpp.s
.PHONY : projet/src/myeventreceiver.cpp.s

projet/src/personnages.o: projet/src/personnages.cpp.o

.PHONY : projet/src/personnages.o

# target to build an object file
projet/src/personnages.cpp.o:
	$(MAKE) -f CMakeFiles/pgm.dir/build.make CMakeFiles/pgm.dir/projet/src/personnages.cpp.o
.PHONY : projet/src/personnages.cpp.o

projet/src/personnages.i: projet/src/personnages.cpp.i

.PHONY : projet/src/personnages.i

# target to preprocess a source file
projet/src/personnages.cpp.i:
	$(MAKE) -f CMakeFiles/pgm.dir/build.make CMakeFiles/pgm.dir/projet/src/personnages.cpp.i
.PHONY : projet/src/personnages.cpp.i

projet/src/personnages.s: projet/src/personnages.cpp.s

.PHONY : projet/src/personnages.s

# target to generate assembly for a file
projet/src/personnages.cpp.s:
	$(MAKE) -f CMakeFiles/pgm.dir/build.make CMakeFiles/pgm.dir/projet/src/personnages.cpp.s
.PHONY : projet/src/personnages.cpp.s

projet/src/quake.o: projet/src/quake.cpp.o

.PHONY : projet/src/quake.o

# target to build an object file
projet/src/quake.cpp.o:
	$(MAKE) -f CMakeFiles/pgm.dir/build.make CMakeFiles/pgm.dir/projet/src/quake.cpp.o
.PHONY : projet/src/quake.cpp.o

projet/src/quake.i: projet/src/quake.cpp.i

.PHONY : projet/src/quake.i

# target to preprocess a source file
projet/src/quake.cpp.i:
	$(MAKE) -f CMakeFiles/pgm.dir/build.make CMakeFiles/pgm.dir/projet/src/quake.cpp.i
.PHONY : projet/src/quake.cpp.i

projet/src/quake.s: projet/src/quake.cpp.s

.PHONY : projet/src/quake.s

# target to generate assembly for a file
projet/src/quake.cpp.s:
	$(MAKE) -f CMakeFiles/pgm.dir/build.make CMakeFiles/pgm.dir/projet/src/quake.cpp.s
.PHONY : projet/src/quake.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... pgm"
	@echo "... edit_cache"
	@echo "... projet/src/camera.o"
	@echo "... projet/src/camera.i"
	@echo "... projet/src/camera.s"
	@echo "... projet/src/heros.o"
	@echo "... projet/src/heros.i"
	@echo "... projet/src/heros.s"
	@echo "... projet/src/main.o"
	@echo "... projet/src/main.i"
	@echo "... projet/src/main.s"
	@echo "... projet/src/map/myterrain.o"
	@echo "... projet/src/map/myterrain.i"
	@echo "... projet/src/map/myterrain.s"
	@echo "... projet/src/map/qmap.o"
	@echo "... projet/src/map/qmap.i"
	@echo "... projet/src/map/qmap.s"
	@echo "... projet/src/map/waterquad.o"
	@echo "... projet/src/map/waterquad.i"
	@echo "... projet/src/map/waterquad.s"
	@echo "... projet/src/mascene.o"
	@echo "... projet/src/mascene.i"
	@echo "... projet/src/mascene.s"
	@echo "... projet/src/myeventreceiver.o"
	@echo "... projet/src/myeventreceiver.i"
	@echo "... projet/src/myeventreceiver.s"
	@echo "... projet/src/personnages.o"
	@echo "... projet/src/personnages.i"
	@echo "... projet/src/personnages.s"
	@echo "... projet/src/quake.o"
	@echo "... projet/src/quake.i"
	@echo "... projet/src/quake.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

