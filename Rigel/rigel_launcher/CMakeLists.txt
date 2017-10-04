
FILE(GLOB_RECURSE HEAD_RIGEL_LAUNCHER ./include/*.h)
FILE(GLOB_RECURSE SRCS_RIGEL_LAUNCHER ./source/*.cpp)

add_executable(rigel_launcher ${HEAD_RIGEL_LAUNCHER} ${SRCS_RIGEL_LAUNCHER})

add_dependencies(rigel_launcher rigel_engine)

target_include_directories(rigel_launcher PUBLIC ./include/rglauncher)
target_include_directories(rigel_launcher PUBLIC ../rigel_engine/include)

target_link_libraries(rigel_launcher rigel_engine)