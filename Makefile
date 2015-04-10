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

#all: munchkincrypt munchkinsteg toto dorothy

.DEFAULT:	all

.PHONY:	all help helpall compile release build debug \
				check test clean clean-all clean-release clean-build clean-debug \
				update update-makeall reconfig

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
	@$(CMAKE) -E chdir $(BUILD_DIR) $(CMAKE) -DBUILD_TESTS=ON -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) ..
	@$(MAKE) -C $(BUILD_DIR) -j $(NUM_CORES)
	@echo ======================================
	@echo Release Build Finished
	@echo ======================================

all debug::
	@echo ======================================
	@echo Starting Debug Build
	@echo ======================================
	@$(CMAKE) -E chdir $(DEBUG_DIR) $(CMAKE) -DBUILD_TESTS=ON -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) ..
	@$(MAKE) -C $(BUILD_DIR) -j $(NUM_CORES)
	@echo ======================================
	@echo Debug Build Finished
	@echo ======================================

check test::
	@echo ======================================
	@echo Starting Tests
	@echo ======================================
	-@build/test/dickgrayson-test
	@echo ======================================
	@echo Tests Finished
	@echo ======================================

clean-all clean clean-release clean-build::
	$(MAKE) -C $(BUILD_DIR) clean

clean-all clean-debug::
	$(MAKE) -C $(DEBUG_DIR) clean

help help-all::
	$(info )
	$(info $(PROJECT_NAME) Help)
	$(info ================)
	$(info make help                   - show brief help)
	$(info make help-all               - show extended help)
	$(info )
	$(info Build and Check)
	$(info ===============)
	$(info make                        - defaults to make all)
	$(info make all                    - build all targets, tests and all documentation)
	$(info make build                  - build release build of all targets)
	$(info make debug                  - build debug build of all targets)
help-all::
	$(info make dorothy                - build only dorothy)
	$(info make toto                   - build only toto)
	$(info make munchkincrypt          - build only munchkincrypt)
	$(info make munchkinsteg           - build only munchkinsteg)
help help-all::
	$(info )
	$(info Testing)
	$(info ===============)
	$(info make test                   - run test suite on release build)
help-all::
	$(info make test-build             - run test suite on release build)
	$(info make test-debug             - run test suite on debug build)
	$(info make test-dorothy           - run test suite)
	$(info make test-toto              - run test suite)
	$(info make test-munchkincrypt     - run test suite)
	$(info make test-toto              - run test suite)
help help-all::
	$(info )
	$(info Cleaning)
	$(info ========)
	$(info make clean                  - remove compiled files in both build/ and debug/)
help-all::
	$(info make clean-all              - same as clean)
	$(info make clean-build            - remove compiled files in build/)
	$(info make clean-debug            - remove compiled files in debug/)
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
