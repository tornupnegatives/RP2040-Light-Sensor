##############################################################################
# @file         Makefile
# @brief        Makefile for Raspberry Pi Pico projects
#               
##############################################################################
# @attention
#
# Authors: Joseph Bellahcen <joe@josephbellahcen.com>
#
##############################################################################

# Fetch current version of Raspberry Pi Pico SDK and initialize submodules
update-sdk: 
	git submodule sync
	git submodule update --init
	git submodule foreach git submodule update --init
.PHONY: update-sdk

# Fetch latest version of Raspberry Pi Pico SDK and initialize submodules
upgrade-sdk: 
	git submodule sync
	git submodule update --remote --merge
	git submodule foreach git submodule update --init
.PHONY: upgrade-sdk

# Build current project via CMake
build:
	# Create build directory and prepare CMakeFiles
	cmake -S . -B build
	# Build  project
	cd build && $(MAKE) -j
.PHONY: build

# Remove build artifacts
clean:
	rm -rf build
.PHONY: clean