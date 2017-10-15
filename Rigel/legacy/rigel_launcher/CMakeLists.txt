
FILE(GLOB_RECURSE HEAD_RIGEL_LAUNCHER ./include/*.h)
FILE(GLOB_RECURSE SRCS_RIGEL_LAUNCHER ./source/*.cpp)

add_executable(RigelLauncher ${HEAD_RIGEL_LAUNCHER} ${SRCS_RIGEL_LAUNCHER})

add_dependencies(RigelLauncher RigelEngine)

target_include_directories(RigelLauncher PUBLIC ./include/rglauncher)
target_include_directories(RigelLauncher PUBLIC ../rigel_engine/include)

target_link_libraries(RigelLauncher RigelEngine)