#unicode
add_definitions(-DUNICODE -D_UNICODE)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)


FILE(GLOB_RECURSE HEAD_RGGRAPHICS ./include/*.h)
FILE(GLOB_RECURSE SRCS_RGGRAPHICS ./source/*.cpp)

#source grpup
FILE(GLOB SRCS_RGGRAPHICS_CORE ./source/*.cpp)
FILE(GLOB SRCS_RGGRAPHICS_DIRECTX11 ./source/directx11/*.cpp)

FILE(GLOB HEAD_RGGRAPHICS_CORE ./include/rggraphics/*.h)
FILE(GLOB HEAD_RGGRAPHICS_DIRECTX11 ./include/rggraphics/directx11/*.h)

add_library(rggraphics STATIC ${HEAD_RGGRAPHICS} ${SRCS_RGGRAPHICS})

#pch
use_pch("${SRCS_RGGRAPHICS}" "rggraphics.h")
set_pch(./source/rggraphics.cpp "rggraphics.h")

source_group("source\\core" FILES ${SRCS_RGGRAPHICS_CORE})
source_group("source\\directx11" FILES ${SRCS_RGGRAPHICS_DIRECTX11})
source_group("header\\core" FILES ${HEAD_RGGRAPHICS_CORE})
source_group("header\\directx11" FILES ${HEAD_RGGRAPHICS_DIRECTX11})

add_dependencies(rggraphics rgcore)

target_include_directories(rggraphics PUBLIC ./include/rggraphics)
target_include_directories(rggraphics PUBLIC ../rgcore/include)