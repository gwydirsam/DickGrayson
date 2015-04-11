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

TEST_BINS := $(wildcard $(BUILD_DIR)/test/*-test)

.DEFAULT:	all

.PHONY:	all help helpall compile release build debug \
				check test clean clean-all clean-release clean-build clean-debug \
				update update-makeall reconfig clean-build-dirs $(TEST_BINS) test-all

all::
	@echo ======================================
	@echo Starting $(PROJECT_NAME) Build
	@echo ""

reconfig build release compile::
	@echo ======================================
	@echo Rebuilding CMake Cache
	@echo ======================================
	@$(MAKE) -C $(BUILD_DIR) rebuild_cache

reconfig debug::
	@echo ======================================
	@echo Rebuilding CMake Cache
	@echo ======================================
	@$(MAKE) -C $(DEBUG_DIR) rebuild_cache

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

all release build debug compile test::
	@mkdir -p $(BUILD_DIR) $(DEBUG_DIR)

all release build debug compile test::
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

check test::
	@echo ======================================
	@echo Starting Tests
	@echo ======================================
check test:: $(TEST_BINS)
$(TEST_BINS)::
	@$@ --gtest_color=yes
check test::
	@echo ======================================
	@echo Finished Tests
	@echo ======================================

all::
	@echo ""
	@echo Finished $(PROJECT_NAME) Build
	@echo ======================================

clean-all clean clean-release clean-build::
	$(MAKE) -C $(BUILD_DIR) clean

clean-all clean-debug::
	$(MAKE) -C $(DEBUG_DIR) clean

clean-build-dirs::
	rm -rf $(DEBUG_DIR) $(BUILD_DIR)

help help-all::
	$(info )
	$(info $(PROJECT_NAME) Help)
	$(info ================)
	$(info make help                   - show brief help)
	$(info make help-all               - show extended help)
	$(info )
	$(info Build and Check)
	$(info ===============)
	$(info make                        - defaults to make build)
	$(info make all                    - build all targets (debug and release), tests and all documentation)
	$(info make build                  - build release build of all targets)
	$(info make debug                  - build debug build of all targets)
help-all::
	$(info make rsa-crypt              - build only rsa-crypt)
	$(info make rsa-attack             - build only rsa-attack)
	$(info make stego-crypt            - build only stego-crypt)
	$(info make stego-attack           - build only stego-attack)
help help-all::
	$(info )
	$(info Testing)
	$(info ===============)
	$(info make test                   - run test suite on release build)
help-all::
	$(info make test-build             - run test suite on release build)
	$(info make test-debug             - run test suite on debug build)
	$(info make test-rsa-crypt         - run rsa-crypt test)
	$(info make test-rsa-attack        - run rsa-attack test)
	$(info make test-stego-crypt       - run stego-crypt test)
	$(info make test-stego-attack      - run stego-attack test)
help help-all::
	$(info )
	$(info Cleaning)
	$(info ========)
	$(info make clean                  - remove compiled files in both build/ and debug/)
help-all::
	$(info make clean-all              - same as clean)
	$(info make clean-build            - remove compiled files in build/)
	$(info make clean-debug            - remove compiled files in debug/)
	$(info make clean-build-dirs       - remove debug and build completely)
	$(info )
	$(info Configuration Check)
	$(info ===================)
	$(info make reconfig               - rebuild cmake configuration)
help help-all::
	$(info )
	$(info Documentation)
	$(info =============)
	$(info make doc                    - build all documentation)
help-all::
	$(info make man                    - build man documentation)
	$(info make info                   - build Info documentation)
help help-all::
	$(info )
	$(info Convenience)
	$(info ===========)
	$(info make update                 - stash, then pull from upstream and build)
help help-all::
	@echo ""
