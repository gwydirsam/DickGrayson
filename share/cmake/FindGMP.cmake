# Copyright (c) 2006, Laurent Montel, <montel@kde.org>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

if (GMP_INCLUDE_DIR AND GMP_LIBRARIES)
  # Already in cache, be silent
  set(GMP_FIND_QUIETLY TRUE)
endif (GMP_INCLUDE_DIR AND GMP_LIBRARIES)

find_path(GMP_INCLUDE_DIR NAMES gmp.h PATHS /usr/include /usr/local/include $ENV{HOME}/local/$ENV{UNAME}/include)
find_library(GMP_LIBRARIES NAMES gmp libgmp /usr/lib /usr/local/lib $ENV{HOME}/local/$ENV{UNAME}/lib )
find_library(GMPXX_LIBRARIES NAMES gmpxx libgmpxx /usr/lib /usr/local/lib $ENV{HOME}/local/$ENV{UNAME}/lib )
MESSAGE(STATUS "GMP libs: " ${GMP_LIBRARIES} " " ${GMPXX_LIBRARIES} )

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GMP DEFAULT_MSG GMP_INCLUDE_DIR GMP_LIBRARIES)

mark_as_advanced(GMP_INCLUDE_DIR GMP_LIBRARIES)
