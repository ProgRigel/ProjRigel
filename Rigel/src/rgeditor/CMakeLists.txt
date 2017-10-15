FILE(GLOB_RECURSE header_rgeditor ./include/*.h)
FILE(GLOB_RECURSE source_rgeditor ./source/*.cpp)


add_executable(RigelEditor ${header_rgeditor} ${source_rgeditor})

#pch
use_pch("${SRCS_RIGEL_EDITOR}" "rgeditor.h")
set_pch(./source/rgeditor.cpp "rgeditor.h")

add_dependencies(RigelEditor RigelEngine)
add_dependencies(RigelEditor example-common)

target_include_directories(RigelEditor PUBLIC ./include/rgeditor)
target_include_directories(RigelEditor PUBLIC ../rgengine/include)
target_include_directories(RigelEditor PUBLIC ../../thirdpart/bgfx.cmake/bgfx/examples)

# target_include_directories(RigelEditor PUBLIC ../../thirdpart/bgfx.cmake/bgfx/include)
# target_include_directories(RigelEditor PUBLIC ../../thirdpart/bgfx.cmake/bimg/include)
# target_include_directories(RigelEditor PUBLIC ../../thirdpart/bgfx.cmake/bx/include)

target_link_libraries(RigelEditor RigelEngine)
target_link_libraries(RigelEditor example-common)

target_compile_definitions(RigelEditor PRIVATE "-D_CRT_SECURE_NO_WARNINGS" "-DENTRY_CONFIG_IMPLEMENT_MAIN=1" )