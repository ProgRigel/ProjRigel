#unicode
add_definitions(-DUNICODE -D_UNICODE)

FILE(GLOB_RECURSE HEAD_RGGUI ./include/*.h)
FILE(GLOB_RECURSE SRCS_RGGUI ./source/*.cpp)

add_library(rggui STATIC ${HEAD_RGGUI} ${SRCS_RGGUI})

#pch
use_pch("${SRCS_RGGUI}" "rggui.h")
set_pch(./source/rggui.cpp "rggui.h")

add_dependencies(rggui rgcore)
add_dependencies(rggui rggraphics)

target_include_directories(rggui PUBLIC ./include/rggui)
target_include_directories(rggui PUBLIC ../rgcore/include)
target_include_directories(rggui PUBLIC ../rggraphics/include)