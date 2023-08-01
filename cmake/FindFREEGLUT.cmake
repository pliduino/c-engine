# Locate the glfw3 library
#
# This module defines the following variables:
#
# GLFW3_LIBRARY the name of the library;
# GLFW3_INCLUDE_DIR where to find glfw include files.
# GLFW3_FOUND true if both the GLFW3_LIBRARY and GLFW3_INCLUDE_DIR have been found.
#
# To help locate the library and include file, you can define a
# variable called GLFW3_ROOT which points to the root of the glfw library
# installation.
#
# default search dirs
#
# Cmake file from: https://github.com/daw42/glslcookbook

set(_freeglut_HEADER_SEARCH_DIRS
    "/usr/include"
    "/usr/local/include"
    "${CMAKE_SOURCE_DIR}/includes"
    "C:/Program Files (x86)/freeglut/include")
set(_freeglut_LIB_SEARCH_DIRS
    "/usr/lib"
    "/usr/local/lib"
    "${CMAKE_SOURCE_DIR}/lib"
    "C:/Program Files (x86)/freeglut/bin")

# Check environment for root search directory
set(_freeglut_ENV_ROOT $ENV{FREEGLUT_ROOT})

if(NOT FREEGLUT_ROOT AND _freeglut_ENV_ROOT)
    set(FREEGLUT_ROOT ${_freeglut_ENV_ROOT})
endif()

# Put user specified location at beginning of search
if(FREEGLUT_ROOT)
    list(INSERT _freeglut_HEADER_SEARCH_DIRS 0 "${FREEGLUT_ROOT}/include")
    list(INSERT _freeglut_LIB_SEARCH_DIRS 0 "${FREEGLUT_ROOT}/bin")
endif()

# Search for the header
FIND_PATH(FREEGLUT_INCLUDE_DIR "GL/freeglut.h"
    PATHS ${_freeglut_HEADER_SEARCH_DIRS})

# Search for the library
FIND_LIBRARY(FREEGLUT_LIBRARY NAMES freeglut.dll
    PATHS ${_freeglut_LIB_SEARCH_DIRS})
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(FREEGLUT DEFAULT_MSG
    FREEGLUT_LIBRARY FREEGLUT_INCLUDE_DIR)