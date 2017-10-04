cmake_minimum_required(VERSION 3.2)
#project basis
project(Rigel)

#configs

#c++latest
if (MSVC_VERSION GREATER_EQUAL "1900")
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
if (_cpp_latest_flag_supported)
    add_compile_options("/std:c++latest")
endif()
endif()

#remove zero_test
set(CMAKE_SUPPRESS_REGENERATION true)

#options
option(BUILD_RIGEL_EDITOR "build RigelEditor" ON)
option(BUILD_RIGEL_ENGINE "build RigelEngine" OFF)

set(PROJECT_SOURCE_DIR ./)

add_subdirectory(./rigel_editor)
add_subdirectory(./rgcore)
add_subdirectory(./rggraphics)
add_subdirectory(./rggui)

add_subdirectory(./rigel_engine)
add_subdirectory(./rigel_launcher)

