add_definitions(-DUNICODE -D_UNICODE)

FILE(GLOB_RECURSE HEAD_RIGEL_EDITOR ./include/*.h)
FILE(GLOB_RECURSE SRCS_RIGEL_EDITOR ./source/*.cpp)


add_executable(RigelEditor ${HEAD_RIGEL_EDITOR} ${SRCS_RIGEL_EDITOR})

#pch
use_pch("${SRCS_RIGEL_EDITOR}" "stdafx.h")
set_pch(./source/stdafx.cpp "stdafx.h")

add_dependencies(RigelEditor rgcore)
add_dependencies(RigelEditor rggraphics)
add_dependencies(RigelEditor rggui)

target_include_directories(RigelEditor PUBLIC ./include/rgeditor)
target_include_directories(RigelEditor PUBLIC ../rgcore/include)
target_include_directories(RigelEditor PUBLIC ../rggraphics/include)
target_include_directories(RigelEditor PUBLIC ../rggui/include)

target_link_libraries(RigelEditor rgcore)
target_link_libraries(RigelEditor rggraphics)
target_link_libraries(RigelEditor rggui)


set(BUILD_DIR_RIGELEDITOR_DEBUG "${CMAKE_BINARY_DIR}\\Build\\RigelEditor_Debug")
set(BUILD_DIR_RIGELEDITOR_RELEASE "${CMAKE_BINARY_DIR}\\Build\\RigelEditor_Release")
set_target_properties(RigelEditor PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BUILD_DIR_RIGELEDITOR_DEBUG}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BUILD_DIR_RIGELEDITOR_RELEASE}
)

set(RESOURCES_DIR ${CMAKE_SOURCE_DIR}\\resources\\)
set(CMD_COPY_DATA "\"${RESOURCES_DIR}Data\" \"$<$<CONFIG:DEBUG>:${BUILD_DIR_RIGELEDITOR_DEBUG}>$<$<CONFIG:RELEASE>:${BUILD_DIR_RIGELEDITOR_RELEASE}>\\Data\\\" /E /Y")

add_custom_command(TARGET RigelEditor POST_BUILD
    COMMAND xcopy ARGS ${CMD_COPY_DATA}
)