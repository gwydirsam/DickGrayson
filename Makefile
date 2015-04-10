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

.DEFAULT: all

.PHONY: all help helpall build debug test clean
all:: release debug test

update update-makeall::
	git stash save "stashed by make update $(DATETIME)"
	git remote update
	git pull

update-makeall::
	$(MAKE) all

release build debug configure::
	mkdir -p $(BUILD_DIR) $(DEBUG_DIR)

release build::
	$(CMAKE) -E chdir $(BUILD_DIR) $(CMAKE) -Dtest=ON -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) ..
	$(MAKE) -C $(BUILD_DIR) -j $(NUM_CORES)

debug:: BUILD_TYPE = Debug
	$(CMAKE) -E chdir $(DEBUG_DIR) $(CMAKE) -Dtest=ON -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) ..
	$(MAKE) -C $(BUILD_DIR) -j $(NUM_CORES)

check test::
	sh build/test/dickgrayson-test

clean:

help helpall::
	$(info )
	$(info $(PROJECT_NAME) Help)
	$(info ====================)
	$(info make help           - show brief help)
	$(info make targets        - ditto)
	$(info make helpall        - show extended help)
	$(info )
	$(info Build and Check)
	$(info ===============)
	$(info make                - build Org ELisp and all documentation)
	$(info make all            - ditto)
	$(info make compile        - build Org ELisp files)
	$(info make single         - build Org ELisp files, single Emacs per source)
	$(info make autoloads      - create org-loaddefs.el to load Org in-place)
	$(info make test           - build Org ELisp files and run test suite)
helpall::
	$(info make test-dirty     - check without building first)
	$(info make compile-dirty  - build only stale Org ELisp files)
	$(info )
	$(info Compatibility)
	$(info =============)
	$(info make oldorg         - what the old make did: compile autoloads info)
	$(info )
	$(info Cleaning)
	$(info ========)
	$(info make clean          - remove built Org ELisp files and documentation)
	$(info make cleanall       - remove everything that can be built and all remnants)
	$(info make clean-install  - remove previous Org installation)
	$(info )
	$(info Configuration Check)
	$(info ===================)
help helpall::
	$(info make config         - check main configuration)
helpall::
	$(info make config-version - check Org version)
	$(info make config-test    - check test configuration)
	$(info make config-exe     - check executables configuration)
	$(info make config-cmd     - check command configuration)
	$(info make config-all     - check all configuration)
	$(info )
	$(info Documentation)
	$(info =============)
help helpall::
	$(info make doc            - build all documentation)
helpall::
	$(info make docs           - ditto)
help helpall::
	$(info make info           - build Info documentation)
helpall::
	$(info make html           - build HTML documentation)
	$(info make pdf            - build PDF documentation)
	$(info make card           - build reference cards)
	$(info make refcard        - ditto)
help helpall::
	$(info )
	$(info Installation)
	$(info ============)
	$(info make install        - build and install Org)
helpall::
	$(info make install-etc    - build and install files in /etc)
	$(info make install-lisp   - build and install Org Elisp files)
	$(info make install-info   - build and install Info documentation)
	$(info )
	$(info Convenience)
	$(info ===========)
	$(info make up0            - pull from upstream)
	$(info make up1            - pull from upstream, build and check)
	$(info make up2            - pull from upstream, build, check and install)
	$(info make update         - pull from upstream and build)
	$(info make update2        - pull from upstream, build and install)
	$(info make uncompiled     - combine cleanlisp and autoloads)
	$(info make local.mk       - create new local.mk as template for adaptation)
help helpall::
	$(info )
	$(info Full documentation on Worg)
	$(info ==========================)
	$(info http://orgmode.org/worg/dev/org-build-system.html)
	@echo ""

