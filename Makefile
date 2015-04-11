PROJECT_NAME := DickGrayson

UNAME := $(shell uname)
HOSTNAME := $(shell hostname)

# set cores correctly
ifeq ($(UNAME), 'Linux')
		ifeq ($(HOSTNAME), 'build')
		NUM_CORES = 8
	endif
else
	NUM_CORES = 8
endif

ifeq ($(UNAME), 'Darwin')
	ifeq ($(HOSTNAME), 'Tron.local')
		NUM_CORES = 4
	endif
else
	NUM_CORES = 4
endif

CMAKE := $(shell which cmake)
CMAKE_GENERATOR ?= "Unix Makefiles"
#CMAKE_GENERATOR ?= Ninja

PROJECT_DIR := $(CURDIR)
BUILD_DIR := $(PROJECT_DIR)/build
DEBUG_DIR := $(PROJECT_DIR)/debug
TEST_DIR := $(PROJECT_DIR)/test
# respect $TMPDIR if set in environment
TMPDIR ?= /tmp

PROJECT_MAKE_DOC = #man info html pdf

CLEANDIRS = $(BUILD_DIR) $(DEBUG_DIR)

DATETIME = $(shell date +%Y-%m-%d-%H:%M)

BUILD_TYPE = Release

RELEASE_TEST_BINS := $(wildcard $(BUILD_DIR)/test/*-test)
DEBUG_TEST_BINS := $(wildcard $(DEBUG_DIR)/test/*-test)

.DEFAULT:	all

.PHONY:	all help helpall compile release build debug \
				check test clean clean-all clean-release clean-build clean-debug \
				update update-makeall reconfig clean-build-dirs $(RELEASE_TEST_BINS) \
				test-all test-build test-debug $(DEBUG_TEST_BINS)

all::
	@echo ======================================
	@echo Starting $(PROJECT_NAME) Build
	@echo ""

install-cmake::
	@echo ======================================
	@echo Start Installing CMake
	@echo ======================================
	@(cd share/scripts; sh install-cmake.sh)
	@echo ======================================
	@echo Done Installing CMake
	@echo ======================================

install-better-defaults::
	@echo ======================================
	@echo Start Installing Better Defaults
	@echo ======================================
	@(cd share/scripts; sh better-defaults.sh)
	@echo ======================================
	@echo Done Installing Better Defaults
	@echo ======================================

reconfig build release compile::
	@echo ======================================
	@echo Rebuilding CMake Cache
	@echo ======================================
ifeq ($(CMAKE_GENERATOR), Ninja)
	@ninja -C $(BUILD_DIR) rebuild_cache
else
	@$(MAKE) -C $(BUILD_DIR) rebuild_cache
endif

reconfig debug::
	@echo ======================================
	@echo Rebuilding CMake Cache
	@echo ======================================
ifeq ($(CMAKE_GENERATOR), Ninja)
	@ninja -C $(DEBUG_DIR) rebuild_cache
else
	@$(MAKE) -C $(DEBUG_DIR) rebuild_cache
endif

update update-makeall::
	@echo ======================================
	@echo Stashing Unsaved Changes and Pulling
	@echo ======================================
	git stash save "stashed by make update $(DATETIME)"
	git remote update
	git pull
update-makeall::
	-$(MAKE) all
	@echo ======================================
	@echo Remember to apply your stashed changes
	@echo ======================================
	@echo ""

all release build debug compile::
	@mkdir -p $(BUILD_DIR) $(DEBUG_DIR)

all release build compile::
	@echo ======================================
	@echo Starting Release Build
	@echo ======================================
	@$(CMAKE) -E chdir $(BUILD_DIR) $(CMAKE) -G $(CMAKE_GENERATOR) -DBUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Release ..
ifeq ($(CMAKE_GENERATOR), Ninja)
	@ninja -C $(BUILD_DIR) gtest && ninja -C $(BUILD_DIR) all
else
	@$(MAKE) -C $(BUILD_DIR) -j $(NUM_CORES)
endif
	@echo ======================================
	@echo Release Build Finished
	@echo ======================================

all debug::
	@echo ======================================
	@echo Starting Debug Build
	@echo ======================================
	@$(CMAKE) -E chdir $(DEBUG_DIR) $(CMAKE) -G $(CMAKE_GENERATOR) -DBUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Debug ..
ifeq ($(CMAKE_GENERATOR), Ninja)
	@ninja -C $(DEBUG_DIR) gtest && ninja -C $(DEBUG_DIR) all
else
	@$(MAKE) -C $(DEBUG_DIR) -j $(NUM_CORES)
endif
	@echo ======================================
	@echo Debug Build Finished
	@echo ======================================

test-all check test test-build:: build
	@echo ======================================
	@echo Starting Release Tests
	@echo ======================================
test-all check test test-build:: $(RELEASE_TEST_BINS)
$(RELEASE_TEST_BINS)::
	@$@ --gtest_color=yes
test-all check test test-build::
	@echo ======================================
	@echo Finished Release Tests
	@echo ======================================

test-all test-debug:: debug
	@echo ======================================
	@echo Starting Debug Tests
	@echo ======================================
test-all test-debug:: $(DEBUG_TEST_BINS)
$(DEBUG_TEST_BINS)::
	@$@ --gtest_color=yes
test-all test-debug::
	@echo ======================================
	@echo Finished Debug Tests
	@echo ======================================

all::
	@echo ""
	@echo Finished $(PROJECT_NAME) Build
	@echo ======================================

clean-all clean clean-release clean-build::
ifeq ($(CMAKE_GENERATOR), Ninja)
	@ninja -C $(BUILD_DIR) clean
else
	@$(MAKE) -C $(BUILD_DIR) clean
endif

clean-all clean-debug::
ifeq ($(CMAKE_GENERATOR), Ninja)
	@ninja -C $(DEBUG_DIR) clean
else
	@$(MAKE) -C $(DEBUG_DIR) clean
endif

clean-build-dirs::
	rm -rf $(DEBUG_DIR) $(BUILD_DIR)

help help-all::
	$(info )
	$(info $(PROJECT_NAME) Help)
	$(info ================)
	$(info make help                    - show brief help)
	$(info make help-all                - show extended help)
	$(info )
	$(info Build and Check)
	$(info ===============)
	$(info make                         - defaults to make build)
	$(info make all                     - build all targets (debug and release), tests and all docs)
	$(info make build                   - build release build of all targets)
	$(info make debug                   - build debug build of all targets)
help-all::
	$(info make rsa-crypt               - build only rsa-crypt)
	$(info make rsa-attack              - build only rsa-attack)
	$(info make stego-crypt             - build only stego-crypt)
	$(info make stego-attack            - build only stego-attack)
help help-all::
	$(info )
	$(info Testing)
	$(info ===============)
	$(info make test                    - run test suite on release build)
help-all::
	$(info make test-build              - run test suite on release build)
	$(info make test-debug              - run test suite on debug build)
	$(info make test-rsa-crypt          - run rsa-crypt test)
	$(info make test-rsa-attack         - run rsa-attack test)
	$(info make test-stego-crypt        - run stego-crypt test)
	$(info make test-stego-attack       - run stego-attack test)
help help-all::
	$(info )
	$(info Cleaning)
	$(info ========)
	$(info make clean                   - remove compiled files in both build/ and debug/)
help-all::
	$(info make clean-all               - same as clean)
	$(info make clean-build             - remove compiled files in build/)
	$(info make clean-debug             - remove compiled files in debug/)
	$(info make clean-build-dirs        - remove debug and build completely)
	$(info )
	$(info Configuration Check)
	$(info ===================)
	$(info make reconfig                - rebuild cmake configuration)
help help-all::
	$(info )
	$(info Documentation)
	$(info =============)
	$(info make doc                     - build all documentation)
help-all::
	$(info make man                     - build man documentation)
	$(info make info                    - build Info documentation)
help help-all::
	$(info )
	$(info Convenience)
	$(info ===========)
	$(info make update                  - stash, then pull from upstream and build)
help-all::
	$(info make install-cmake           - install cmake)
	$(info make install-better-defaults - install better defaults)
help help-all::
	@echo ""
