#unicode
add_definitions(-DUNICODE -D_UNICODE)

FILE(GLOB HEAD_RGCORE ./include/rgcore/*.h ./include/rgcore/*.hpp)
FILE(GLOB SRCS_RGCORE ./source/*.cpp)

add_library(rgcore STATIC ${HEAD_RGCORE} ${SRCS_RGCORE})

#pch
use_pch("${SRCS_RGCORE}" "rgcore.h")
set_pch(./source/rgcore.cpp "rgcore.h")

target_include_directories(rgcore PUBLIC ./include/rgcore)

target_include_directories(rgcore PUBLIC ./../thirdpart/freetype/include)
target_include_directories(rgcore PUBLIC ./../thirdpart/libpng/include)

set(THIDPART_LIB_DIR ${CMAKE_SOURCE_DIR}\\thirdpart)

if(CMAKE_CL_64)
    target_link_libraries(rgcore ${THIDPART_LIB_DIR}\\freetype\\libs\\x64\\freetype28.lib)
    target_link_libraries(rgcore ${THIDPART_LIB_DIR}\\libpng\\libs\\x64\\libpng16_static.lib)
    target_link_libraries(rgcore ${THIDPART_LIB_DIR}\\zlib\\libs\\x64\\zlibstatic.lib)
else()
    target_link_libraries(rgcore ${THIDPART_LIB_DIR}\\freetype\\libs\\x86\\freetype28.lib)
    target_link_libraries(rgcore ${THIDPART_LIB_DIR}\\libpng\\libs\\x86\\libpng16_static.lib)
    target_link_libraries(rgcore ${THIDPART_LIB_DIR}\\zlib\\libs\\x86\\zlibstatic.lib)
endif()
