cmake_minimum_required(VERSION 3.9)
# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Games_Engineering)

#### Setup Dirs ####
# Main output dir
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Output all DLLs from all libs into main build folder
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Add External Dependencies ####
# SFML
add_subdirectory("lib/sfml")
set(SFML_INCS "lib/sfml/include")
link_Directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

# Box2D
add_subdirectory("lib/b2d/Box2D")
set(B2D_INCS "lib/b2d/Box2D/")
link_Directories("${CMAKE_BINARY_DIR}/lib/b2d/lib")

add_custom_target(copy_res ALL COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/res" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res)

# Maths Lib #
file(GLOB_RECURSE SOURCE_FILES maths_lib/*.cpp maths_lib/*.h)
add_library(maths_lib STATIC ${SOURCE_FILES})
target_include_directories(maths_lib INTERFACE "${CMAKE_SOURCE_DIR}/maths_lib/")
target_include_directories(maths_lib SYSTEM PUBLIC ${SFML_INCS} ${B2D_INCS})
target_link_libraries(maths_lib sfml-graphics)
target_link_libraries(maths_lib Box2D)

# Assets Lib #
file(GLOB_RECURSE SOURCE_FILES assets_lib/*.cpp assets_lib/*.h)
add_library(assets_lib STATIC ${SOURCE_FILES})
target_include_directories(assets_lib INTERFACE "${CMAKE_SOURCE_DIR}/assets_lib/")
target_include_directories(assets_lib SYSTEM PUBLIC ${SFML_INCS} ${B2D_INCS})
target_link_libraries(assets_lib sfml-graphics)
target_link_libraries(assets_lib Box2D)

add_dependencies(assets_lib copy_res)

# Entity Component Lib #
file(GLOB_RECURSE SOURCE_FILES basics_lib/*.cpp basics_lib/*.h)
add_library(basics_lib STATIC ${SOURCE_FILES})
target_include_directories(basics_lib INTERFACE "${CMAKE_SOURCE_DIR}/basics_lib/")
target_include_directories(basics_lib SYSTEM PUBLIC ${SFML_INCS} ${B2D_INCS})
target_link_libraries(basics_lib sfml-graphics)
target_link_libraries(basics_lib Box2D)
target_link_libraries(basics_lib assets_lib)
target_link_libraries(basics_lib maths_lib)

# Tile Lib #
file(GLOB_RECURSE SOURCE_FILES tile_lib/*.cpp tile_lib/*.h)
add_library(tile_lib STATIC ${SOURCE_FILES})
target_include_directories(tile_lib INTERFACE "${CMAKE_SOURCE_DIR}/tile_lib/")
target_include_directories(tile_lib SYSTEM PUBLIC ${SFML_INCS} ${B2D_INCS} )
target_link_libraries(tile_lib basics_lib)
target_link_libraries(tile_lib sfml-graphics)
target_link_libraries(tile_lib Box2D)
target_link_libraries(tile_lib assets_lib)
target_link_libraries(tile_lib maths_lib)

#### Game Engine ####
file(GLOB_RECURSE SOURCES game_src/*.cpp game_src/*.h)
add_executable(GAME_SRC ${SOURCES})
target_include_directories(GAME_SRC SYSTEM PRIVATE ${SFML_INCS} ${B2D_INCS})
target_link_libraries(GAME_SRC basics_lib tile_lib assets_lib maths_lib sfml-graphics)
target_link_libraries(GAME_SRC basics_lib tile_lib assets_lib maths_lib Box2D)
set(EXECUTABLES ${EXECUTABLES} GAME_SRC_EXE)

set_target_properties(GAME_SRC PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration))

add_dependencies(GAME_SRC copy_res)