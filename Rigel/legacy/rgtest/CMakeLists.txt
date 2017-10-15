add_definitions(-DUNICODE -D_UNICODE)

FILE(GLOB_RECURSE HEAD_RGTEST ./include/*.h)
FILE(GLOB_RECURSE SRCS_RGTEST ./source/*.cpp)

add_executable(RgTest ${HEAD_RGTEST} ${SRCS_RGTEST})

add_dependencies(RgTest rgcore)
add_dependencies(RgTest rggraphics)

target_include_directories(RgTest PUBLIC ./include)
target_include_directories(RgTest PUBLIC ../rgcore/include)
target_include_directories(RgTest PUBLIC ../rggraphics/include)

target_link_libraries(RgTest rgcore)
target_link_libraries(RgTest rggraphics)