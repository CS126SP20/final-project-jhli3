# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Use Cinder CMake macros.
get_filename_component(CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../" ABSOLUTE)
include("${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake")
include("${FinalProject_SOURCE_DIR}/cmake/make_cinder_library.cmake")


file(GLOB SOURCE_LIST CONFIGURE_DEPENDS
        "${FinalProject_SOURCE_DIR}/src/*.h"
        "${FinalProject_SOURCE_DIR}/src/*.hpp"
        "${FinalProject_SOURCE_DIR}/src/*.cc"
        "${FinalProject_SOURCE_DIR}/src/*.cpp")

# Make an automatic library - will be static or dynamic based on user setting
add_library(wordsearch ${SOURCE_LIST} ${HEADER_LIST} ../include/wordsearch/puzzle.h puzzle.cc ../include/wordsearch/parser.h parser.cc ../include/trie/trie.h ../include/trie/utility.h)

# We need this directory, and users of our library will need it too
target_include_directories(wordsearch PUBLIC ../include)

# All users of this library will need at least C++11
target_compile_features(wordsearch PUBLIC cxx_std_11)

ci_make_library(
        LIBRARY_NAME mylibrary
        CINDER_PATH  ${CINDER_PATH}
        SOURCES      ${SOURCE_LIST}
        INCLUDES     "${FinalProject_SOURCE_DIR}/include"
        LIBRARIES
        BLOCKS
)

# All users of this library will need at least C++14
target_compile_features(mylibrary PUBLIC cxx_std_14)

set_property(TARGET mylibrary PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Cross-platform compiler lints
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang"
        OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(mylibrary PRIVATE
            -Wall
            -Wextra
            -Wswitch
            -Wconversion
            -Wparentheses
            -Wfloat-equal
            -Wzero-as-null-pointer-constant
            -Wpedantic
            -pedantic
            -pedantic-errors)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    cmake_policy(SET CMP0091 NEW)
    target_compile_options(mylibrary PRIVATE
            /W3)
endif ()

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})
