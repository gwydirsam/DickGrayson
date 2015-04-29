PROJECT_NAME := DickGrayson

UNAME := $(shell uname)
HOSTNAME := $(shell hostname)

# set cores correctly
ifeq ($(UNAME), 'Linux')
		ifeq ($(HOSTNAME), 'build')
		NUM_CORES = 8
	else
		NUM_CORES = 2
	endif
endif

ifeq ($(UNAME), 'Darwin')
	ifeq ($(HOSTNAME), 'Tron.local')
		NUM_CORES = 4
	else
		NUM_CORES = 4
	endif
endif

CMAKE := $(shell which cmake)
CMAKE_GENERATOR ?= "Unix Makefiles"
#CMAKE_GENERATOR ?= Ninja
#CMAKE_GENERATOR ?= Xcode

FIND := $(shell which find)
LCOV := $(shell which lcov)
GCOV := $(shell which gcov)
GENHTML := $(shell which genhtml)

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
				xcode-debug xcode-build ninja ninja-all ninja-debug ninja-build test-gmp

all xcode-all xcode xcode-build xcode-debug ninja-all \
ninja ninja-build ninja-debug release build debug compile create-build-list::
	@for dir in $(shell $(FIND) $(PROJECT_DIR)/lib -mindepth 1 -type d); do \
		$(FIND) $$dir -name '*.cc' > $$dir/build_list.cmake; \
	done
	@$(FIND) bin -mindepth 1 -type d | cut -d '/' -f 2 > $(PROJECT_DIR)/bin/bin_list.cmake
	@$(FIND) test -mindepth 1 -type d | cut -d '/' -f 2 > $(PROJECT_DIR)/test/test_list.cmake
	@$(FIND) $(PROJECT_DIR)/bin -name '*.cc' > $(PROJECT_DIR)/bin/build_list.cmake
	@$(FIND) $(PROJECT_DIR)/lib -name '*.cc' > $(PROJECT_DIR)/lib/build_list.cmake
	@$(FIND) $(PROJECT_DIR)/test -name '*.cc' > $(PROJECT_DIR)/test/build_list.cmake

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

install-deps install-ccache::
	@echo ======================================
	@echo Start Installing Better Defaults
	@echo ======================================
	@(cd share/scripts; bash install-ccache.sh)
	@echo ======================================
	@echo Done Installing Better Defaults
	@echo ======================================

install-deps install-libsndfile::
	@echo ======================================
	@echo Start Installing libsndfile
	@echo ======================================
	@(cd share/scripts; bash install-libsndfile.sh)
	@echo ======================================
	@echo Done Installing libsndfile
	@echo ======================================

install-openssl::
	@echo ======================================
	@echo Start Installing OpenSSL
	@echo ======================================
	@(cd share/scripts; bash install-openssl.sh)
	@echo ======================================
	@echo Done Installing OpenSSL
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

install-deps install-lcov::
	@echo ======================================
	@echo Start Installing lcov
	@echo ======================================
	@(cd share/scripts; bash install-lcov.sh)
	@echo ======================================
	@echo Done Installing lcov
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
	$(MAKE) all
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
	@$(CMAKE) -E chdir $(DEBUG_DIR) $(MAKE) -C $(DEBUG_DIR) -j $(NUM_CORES)
endif
	@echo ======================================
	@echo Debug Build Finished
	@echo ======================================

coverage::
	-@$(CMAKE) -E chdir $(DEBUG_DIR) $(LCOV) --directory $(DEBUG_DIR) --capture --initial --output-file coverage.info --gcov-tool $(GCOV)
	-@$(MAKE) run-all
	-@$(CMAKE) -E chdir $(DEBUG_DIR) $(LCOV) --directory $(DEBUG_DIR) --capture --output-file coverage.info --gcov-tool $(GCOV)
	-@$(CMAKE) -E chdir $(DEBUG_DIR) $(LCOV) --remove coverage.info 'include/*' 'test/*' '/usr/*' --output-file coverage.info
	-@$(CMAKE) -E chdir $(DEBUG_DIR) $(LCOV) --list coverage.info
	-@$(CMAKE) -E chdir $(DEBUG_DIR) mkdir -p $(DEBUG_DIR)/html
	-@$(CMAKE) -E chdir $(DEBUG_DIR) $(GENHTML) $(DEBUG_DIR)/coverage.info -o $(DEBUG_DIR)/html

upload-coverage:: coverage
	-@$(CMAKE) -E chdir $(DEBUG_DIR) $(shell which coveralls-lcov) --repo-token zhZo6XJnHCSiPtFKhLuFulVvgZgvwMsm2 coverage.info
	-@$(CMAKE) -E chdir $(DEBUG_DIR) $(MAKE) -C $(DEBUG_DIR) coveralls

run-all:: all
	@echo ======================================
	@echo Running all binaries and test
	@echo ======================================

run-all test-all:: all
run-all test-all test test-build:: build
	@echo ======================================
	@echo Starting Release Tests
	@echo ======================================

run-all test-all test test-build test-rsa-crypt:: build
	@$(CMAKE) -E chdir $(BUILD_DIR)/test $(BUILD_DIR)/test/rsa-crypt-test --gtest_color=yes
run-all test-all test test-build test-rsa-attack:: build
	@$(CMAKE) -E chdir $(BUILD_DIR)/test $(BUILD_DIR)/test/rsa-attack-test --gtest_color=yes
run-all test-all test test-build test-stego-crypt:: build
	@$(CMAKE) -E chdir $(BUILD_DIR)/test $(BUILD_DIR)/test/stego-crypt-test --gtest_color=yes
run-all test-all test test-build test-stego-attack:: build
	@$(CMAKE) -E chdir $(BUILD_DIR)/test $(BUILD_DIR)/test/stego-attack-test --gtest_color=yes
run-all test-all test test-build test-dgcrypto:: build
	@$(CMAKE) -E chdir $(BUILD_DIR)/test $(BUILD_DIR)/test/dgcrypto-test --gtest_color=yes
run-all test-all test test-build test-dgtype:: build
	@$(CMAKE) -E chdir $(BUILD_DIR)/test $(BUILD_DIR)/test/dgtype-test --gtest_color=yes
run-all test-all test test-build test-dgimg:: build
	@$(CMAKE) -E chdir $(BUILD_DIR)/test $(BUILD_DIR)/test/dgimg-test --gtest_color=yes
run-all test-all test test-build test-dgsnd:: build
	@$(CMAKE) -E chdir $(BUILD_DIR)/test $(BUILD_DIR)/test/dgsnd-test --gtest_color=yes
run-all test-all test test-build test-libgnump:: build
	@$(CMAKE) -E chdir $(BUILD_DIR)/test $(BUILD_DIR)/test/libgnump-test --gtest_color=yes

run-all test-all test test-build:: build
	@echo ======================================
	@echo Finished Release Tests
	@echo ======================================

run-all test-all test-debug:: debug
	@echo ======================================
	@echo Starting Debug Tests
	@echo ======================================

run-all test-all test-debug test-debug-rsa-crypt:: debug
	@$(CMAKE) -E chdir $(DEBUG_DIR)/test $(DEBUG_DIR)/test/rsa-crypt-test --gtest_color=yes
run-all test-all test-debug test-debug-rsa-attack:: debug
	@$(CMAKE) -E chdir $(DEBUG_DIR)/test $(DEBUG_DIR)/test/rsa-attack-test --gtest_color=yes
run-all test-all test-debug test-debug-stego-crypt:: debug
	@$(CMAKE) -E chdir $(DEBUG_DIR)/test $(DEBUG_DIR)/test/stego-crypt-test --gtest_color=yes
run-all test-all test-debug test-debug-stego-attack:: debug
	@$(CMAKE) -E chdir $(DEBUG_DIR)/test $(DEBUG_DIR)/test/stego-attack-test --gtest_color=yes
run-all test-all test-debug test-debug-dgcrypto:: debug
	@$(CMAKE) -E chdir $(DEBUG_DIR)/test $(DEBUG_DIR)/test/dgcrypto-test --gtest_color=yes
run-all test-all test-debug test-debug-dgtype:: debug
	@$(CMAKE) -E chdir $(DEBUG_DIR)/test $(DEBUG_DIR)/test/dgtype-test --gtest_color=yes
run-all test-all test-debug test-debug-dgimg:: debug
	@$(CMAKE) -E chdir $(DEBUG_DIR)/test $(DEBUG_DIR)/test/dgimg-test --gtest_color=yes
run-all test-all test-debug test-debug-dgsnd:: debug
	@$(CMAKE) -E chdir $(DEBUG_DIR)/test $(DEBUG_DIR)/test/dgsnd-test --gtest_color=yes
run-all test-all test-debug test-debug-libgnump:: debug
	@$(CMAKE) -E chdir $(DEBUG_DIR)/test $(DEBUG_DIR)/test/libgnump-test --gtest_color=yes

run-all test-all test-debug:: debug
	@echo ======================================
	@echo Finished Debug Tests
	@echo ======================================

run-all:: debug
	@echo ======================================
	@echo Starting Debug Binaries
	@echo ======================================

run-all run-debug-rsa-crypt:: debug
	@$(CMAKE) -E chdir $(DEBUG_DIR)/bin $(DEBUG_DIR)/bin/rsa-crypt
run-all run-debug-rsa-attack:: debug
	@$(CMAKE) -E chdir $(DEBUG_DIR)/bin $(DEBUG_DIR)/bin/rsa-attack --attack chinese_rt
	@$(CMAKE) -E chdir $(DEBUG_DIR)/bin $(DEBUG_DIR)/bin/rsa-attack --attack factoring
	@$(CMAKE) -E chdir $(DEBUG_DIR)/bin $(DEBUG_DIR)/bin/rsa-attack --help
run-all run-debug-stego-crypt:: debug
	@$(CMAKE) -E chdir $(DEBUG_DIR)/bin $(DEBUG_DIR)/bin/stego-crypt
run-all run-debug-stego-attack:: debug
	@$(CMAKE) -E chdir $(DEBUG_DIR)/bin $(DEBUG_DIR)/bin/stego-attack

run-all:: debug
	@echo ======================================
	@echo Finished Running Debug binaries
	@echo ======================================

all::
	@echo ""
	@echo Finished $(PROJECT_NAME) Build
	@echo ======================================

clean-all clean clean-release clean-build::
	-@$(FIND) . -name '*.gcda' -delete
ifeq ($(CMAKE_GENERATOR), Ninja)
	@ninja -C $(BUILD_DIR) clean
else
	@$(MAKE) -C $(BUILD_DIR) clean
endif

clean-all clean-debug::
	-@$(FIND) . -name '*.gcda' -delete
ifeq ($(CMAKE_GENERATOR), Ninja)
	@ninja -C $(DEBUG_DIR) clean
else
	@$(MAKE) -C $(DEBUG_DIR) clean
endif

clean-force clean-build-dirs::
	-rm -rf $(DEBUG_DIR) $(BUILD_DIR)

cppcheck::
	cppcheck --enable=all lib/ bin/

# clang-format::
# 	$(shell which clang-format) -style="{BasedOnStyle: Google, Standard: Cpp11}" -i `git ls-files -m | egrep '(cc|hh|h|cpp)$'`

clang-format-all::
	$(shell which clang-format) -style="{BasedOnStyle: Google, Standard: Cpp11}" -i `$(FIND) lib -name '*.hh'`
	$(shell which clang-format) -style="{BasedOnStyle: Google, Standard: Cpp11}" -i `$(FIND) lib -name '*.cc'`
	$(shell which clang-format) -style="{BasedOnStyle: Google, Standard: Cpp11}" -i `$(FIND) bin -name '*.cc'`
	$(shell which clang-format) -style="{BasedOnStyle: Google, Standard: Cpp11}" -i `$(FIND) test -name '*.cc'`

valgrind-all:: debug
	@echo ======================================
	@echo Running Valgrind on debug binaries
	@echo ======================================

valgrind-all valgrind-test-rsa-crypt valgrind-test-debug-rsa-crypt::
	valgrind --tool=memcheck --dsymutil=yes $(DEBUG_DIR)/test/rsa-crypt-test --gtest_color=yes
valgrind-all valgrind-test-rsa-attack valgrind-test-debug-rsa-attack::
	valgrind --tool=memcheck --dsymutil=yes $(DEBUG_DIR)/test/rsa-attack-test --gtest_color=yes
valgrind-all valgrind-test-stego-crypt valgrind-test-debug-stego-crypt::
	valgrind --tool=memcheck --dsymutil=yes $(DEBUG_DIR)/test/stego-crypt-test --gtest_color=yes
valgrind-all valgrind-test-stego-attack valgrind-test-debug-stego-attack::
	valgrind --tool=memcheck --dsymutil=yes $(DEBUG_DIR)/test/stego-attack-test --gtest_color=yes
valgrind-all valgrind-test-dgcrypto valgrind-test-debug-dgcrypto::
	valgrind --tool=memcheck --dsymutil=yes $(DEBUG_DIR)/test/dgcrypto-test --gtest_color=yes
valgrind-all valgrind-test-dgtype valgrind-test-debug-dgtype::
	valgrind --tool=memcheck --dsymutil=yes $(DEBUG_DIR)/test/dgtype-test --gtest_color=yes
valgrind-all valgrind-test-dgimg valgrind-test-debug-dgimg::
	valgrind --tool=memcheck --dsymutil=yes $(DEBUG_DIR)/test/dgimg-test --gtest_color=yes
valgrind-all valgrind-test-dgsnd valgrind-test-debug-dgsnd::
	valgrind --tool=memcheck --dsymutil=yes $(DEBUG_DIR)/test/dgsnd-test --gtest_color=yes
valgrind-all valgrind-test-libgnump valgrind-test-debug-libgnump::
	valgrind --tool=memcheck --dsymutil=yes $(DEBUG_DIR)/test/libgnump-test --gtest_color=yes

valgrind-all::
	@echo ======================================
	@echo Finished Running Valgrind
	@echo ======================================

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
	$(info make test-all                - run test suite on release and debug build)
help-all::
	$(info make test-build              - run test suite on release build)
	$(info make test-debug              - run test suite on debug build)
	$(info make test-rsa-crypt          - run (release build) rsa-crypt test)
	$(info make test-rsa-attack         - run (release build) rsa-attack test)
	$(info make test-stego-crypt        - run (release build) stego-crypt test)
	$(info make test-stego-attack       - run (release build) stego-attack test)
	$(info make test-dgcrypto           - run (release build) dgcrypto test)
	$(info make test-dgtype             - run (release build) dgtype test)
	$(info make test-dgimg              - run (release build) dgimg test)
	$(info make test-dgsnd              - run (release build) dgsnd test)
	$(info make test-libgnump           - run (release build) gmp library test)
	$(info make test-debug-rsa-crypt    - run (debug build) rsa-crypt test)
	$(info make test-debug-rsa-attack   - run (debug build) rsa-attack test)
	$(info make test-debug-stego-crypt  - run (debug build) stego-crypt test)
	$(info make test-debug-stego-attack - run (debug build) stego-attack test)
	$(info make test-debug-dgcrypto     - run (debug build) dgcrypto test)
	$(info make test-debug-dgtype       - run (debug build) dgtype test)
	$(info make test-debug-dgimg        - run (debug build) dgimg test)
	$(info make test-debug-dgsnd        - run (debug build) dgsnd test)
	$(info make test-debug-libgnump     - run (debug build) gmp library test)
help help-all::
	$(info )
	$(info Cleaning)
	$(info ========)
	$(info make clean                   - remove compiled files in both build/ and debug/)
help-all::
	$(info make clean-all               - same as clean)
	$(info make clean-build             - remove compiled files in build/)
	$(info make clean-debug             - remove compiled files in debug/)
	$(info make clean-force             - remove debug and build completely)
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
	$(info make install-ccache          - install ccache (highly reccomended))
help help-all::
	@echo ""
