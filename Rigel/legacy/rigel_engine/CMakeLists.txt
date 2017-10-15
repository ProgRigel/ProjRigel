
FILE(GLOB_RECURSE HEAD_RIGEL_ENGINE ./include/*.h)
FILE(GLOB_RECURSE SRCS_RIGEL_ENGINE ./source/*.cpp)

add_library(RigelEngine STATIC ${HEAD_RIGEL_ENGINE} ${SRCS_RIGEL_ENGINE})

add_dependencies(RigelEngine rgcore)
add_dependencies(RigelEngine rggraphics)

target_link_libraries(RigelEngine rgcore)
target_link_libraries(RigelEngine rggraphics)

target_include_directories(RigelEngine PUBLIC ./include/rgengine)
target_include_directories(RigelEngine PUBLIC ../rgcore/include)
target_include_directories(RigelEngine PUBLIC ../rggraphics/include)