INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_AIUT AIUT)

FIND_PATH(
    AIUT_INCLUDE_DIRS
    NAMES AIUT/api.h
    HINTS $ENV{AIUT_DIR}/include
        ${PC_AIUT_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    AIUT_LIBRARIES
    NAMES gnuradio-AIUT
    HINTS $ENV{AIUT_DIR}/lib
        ${PC_AIUT_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(AIUT DEFAULT_MSG AIUT_LIBRARIES AIUT_INCLUDE_DIRS)
MARK_AS_ADVANCED(AIUT_LIBRARIES AIUT_INCLUDE_DIRS)

