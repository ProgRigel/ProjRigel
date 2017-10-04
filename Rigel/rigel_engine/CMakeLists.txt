
FILE(GLOB_RECURSE HEAD_RIGEL_ENGINE ./include/*.h)
FILE(GLOB_RECURSE SRCS_RIGEL_ENGINE ./source/*.cpp)

add_library(rigel_engine STATIC ${HEAD_RIGEL_ENGINE} ${SRCS_RIGEL_ENGINE})

add_dependencies(rigel_engine rgcore)
add_dependencies(rigel_engine rggraphics)

target_link_libraries(rigel_engine rgcore)
target_link_libraries(rigel_engine rggraphics)

target_include_directories(rigel_engine PUBLIC ./include/rgengine)
target_include_directories(rigel_engine PUBLIC ../rgcore/include)
target_include_directories(rigel_engine PUBLIC ../rggraphics/include)