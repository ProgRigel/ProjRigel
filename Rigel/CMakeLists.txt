cmake_minimum_required(VERSION 3.2)
#project basis
project(Rigel)

#options
option(BUILD_RIGEL_EDITOR "build RigelEditor" ON)
option(BUILD_RIGEL_ENGINE "build RigelEngine" OFF)

set(PROJECT_SOURCE_DIR ./)

add_subdirectory(./rigel_editor)
add_subdirectory(./rgcore)
add_subdirectory(./rggraphics)
add_subdirectory(./rggui)
