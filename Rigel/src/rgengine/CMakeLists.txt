FILE(GLOB_RECURSE header_rgengine ./include/*.h)
FILE(GLOB_RECURSE source_rgengine ./source/*.cpp)

add_library(RigelEngine ${header_rgengine} ${source_rgengine})

#pch
use_pch("${SRCS_RIGEL_EDITOR}" "rgengine.h")
set_pch(./source/rgengine.cpp "rgengine.h")

add_dependencies(RigelEngine bgfx)
add_dependencies(RigelEngine bimg)
add_dependencies(RigelEngine bx)

target_include_directories(RigelEngine PUBLIC ./include/rgengine)
target_include_directories(RigelEngine PUBLIC ../../thirdpart/bgfx.cmake/bgfx/include)
target_include_directories(RigelEngine PUBLIC ../../thirdpart/bgfx.cmake/bimg/include)
target_include_directories(RigelEngine PUBLIC ../../thirdpart/bgfx.cmake/bx/include)

target_link_libraries(RigelEngine bgfx)
target_link_libraries(RigelEngine bimg)
target_link_libraries(RigelEngine bx)
