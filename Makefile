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
				test-all test-build test-debug $(DEBUG_TEST_BINS) \
				install-better-defaults install-cmake install-gmp xcode xcode-all \
				xcode-debug xcode-build ninja ninja-all ninja-debug ninja-build

all::
	@echo ======================================
	@echo Starting $(PROJECT_NAME) Build
	@echo ""

xcode-all xcode xcode-build::
	@mkdir -p xcode-build
	@export CC=/usr/bin/clang
	@export CXX=/usr/bin/clang++
	@$(CMAKE) -E chdir xcode-build $(CMAKE) -GXcode -DBUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Release ..

xcode-all xcode-debug::
	@export CC=/usr/bin/clang
	@export CXX=/usr/bin/clang++
	@mkdir -p xcode-debug
	@$(CMAKE) -E chdir xcode-debug $(CMAKE) -GXcode -DBUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Debug ..

ninja-all ninja ninja-build::
	@mkdir -p ninja-build
	@$(CMAKE) -E chdir ninja-build $(CMAKE) -GNinja -DBUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Release ..

ninja-all ninja-debug::
	@mkdir -p ninja-debug
	@$(CMAKE) -E chdir ninja-debug $(CMAKE) -GNinja -DBUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Debug ..


install-better-defaults::
	@echo ======================================
	@echo Start Installing Better Defaults
	@echo ======================================
	@(cd share/scripts; bash better-defaults.sh)
	@echo ======================================
	@echo Done Installing Better Defaults
	@echo ======================================

install-deps::
	@echo ======================================
	@echo Start Installing Dependencies
	@echo ======================================

install-deps install-cmake::
	@echo ======================================
	@echo Start Installing CMake
	@echo ======================================
	@(cd share/scripts; bash install-cmake.sh)
	@echo ======================================
	@echo Done Installing CMake
	@echo ======================================


install-deps install-gmp::
	@echo ======================================
	@echo Start Installing GNU MP
	@echo ======================================
	@(cd share/scripts; bash install-gmp.sh)
	@echo ======================================
	@echo Done Installing GNUMP
	@echo ======================================

install-deps::
	@echo ======================================
	@echo Finished Installing Dependencies
	@echo ======================================

reconfig::
	@echo ======================================
	@echo Rebuilding CMake Cache
	@echo ======================================
ifeq ($(CMAKE_GENERATOR), Ninja)
	@ninja -C $(BUILD_DIR) rebuild_cache
else
	@$(MAKE) -C $(BUILD_DIR) rebuild_cache
endif

reconfig::
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

test-all test test-build:: build
	@echo ======================================
	@echo Starting Release Tests
	@echo ======================================

test-all test test-build test-rsa-crypt::
	$(BUILD_DIR)/test/rsa-crypt-test --gtest_color=yes
test-all test test-build test-rsa-attack::
	$(BUILD_DIR)/test/rsa-attack-test --gtest_color=yes
test-all test test-build test-stego-crypt::
	$(BUILD_DIR)/test/stego-crypt-test --gtest_color=yes
test-all test test-build test-stego-attack::
	$(BUILD_DIR)/test/stego-attack-test --gtest_color=yes
test-all test test-build test-dgcrypto::
	$(BUILD_DIR)/test/dgcrypto-test --gtest_color=yes
test-all test test-build test-dgtype::
	$(BUILD_DIR)/test/dgtype-test --gtest_color=yes
test-all test test-build test-dgimg::
	$(BUILD_DIR)/test/dgimg-test --gtest_color=yes

test-all test test-build::
	@echo ======================================
	@echo Finished Release Tests
	@echo ======================================

test-all test-debug:: debug
	@echo ======================================
	@echo Starting Debug Tests
	@echo ======================================

test-all test-debug test-rsa-crypt::
	$(DEBUG_DIR)/test/rsa-crypt-test --gtest_color=yes
test-all test-debug test-rsa-attack::
	$(DEBUG_DIR)/test/rsa-attack-test --gtest_color=yes
test-all test-debug test-stego-crypt::
	$(DEBUG_DIR)/test/stego-crypt-test --gtest_color=yes
test-all test-debug test-stego-attack::
	$(DEBUG_DIR)/test/stego-attack-test --gtest_color=yes
test-all test-debug test-dgcrypto::
	$(DEBUG_DIR)/test/dgcrypto-test --gtest_color=yes
test-all test-debug test-dgtype::
	$(DEBUG_DIR)/test/dgtype-test --gtest_color=yes
test-all test-debug test-dgimg::
	$(DEBUG_DIR)/test/dgimg-test --gtest_color=yes

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
	$(info Build and Test)
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
	$(info make test-dgcrypto           - run dgcrypto test)
	$(info make test-dgtype             - run dgtype test)
	$(info make test-dgimg              - run dgimg test)
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
	$(info make install-deps            - install cmake and GNU MP library)
help-all::
	$(info make install-cmake           - install cmake)
	$(info make install-gmp             - install GNU MP library)
	$(info make install-better-defaults - install bash and git configurations)
help help-all::
	@echo ""
