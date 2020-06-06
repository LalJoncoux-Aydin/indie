cmake_minimum_required(VERSION 3.14)
project(bomber)

set(CMAKE_CXX_STANDARD 17)

include(lib/Irrlicht/FindIrrlicht.cmake)

if (NOT Irrlicht_INCLUDE_DIRS OR NOT Irrlicht_LIBRARIES)
    message(FATAL_ERROR
    "Irrlicht not found !\n"
    "Include: " ${Irrlicht_INCLUDE_DIRS} "\n"
    "Lib: " ${Irrlicht_LIBRARIES} "\n")
endif (NOT Irrlicht_INCLUDE_DIRS OR NOT Irrlicht_LIBRARIES)

include_directories(${Irrlicht_INCLUDE_DIRS})
link_libraries(${Irrlicht_LIBRARIES})

include_directories(${bomber_SOURCE_DIR}/lib/Irrlicht)
include_directories(${bomber_SOURCE_DIR}/include)
include_directories(${X11_INCLUDE_DIR})
link_directories(${X11_LIBRARIES})
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

add_subdirectory(graphic)
add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(character)

set_property(DIRECTORY PROPERTY ADDITIONAL_CMAKE_CLEAN_FILES "${bomber_SOURCE_DIR}/assets/")
SET(FLAGS "-Wall -Wextra  -lGL -lGLU -lXxf86vm -lsfml-audio") # Les flag a rajouter tout le temps
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${FLAGS}") # concat simplement nos flags
add_executable(bomberman ${bomber_SOURCE_DIR}/src/main.cpp)
target_link_libraries(bomberman lib)
target_link_libraries(bomberman lib_charac)
target_link_libraries(bomberman lib_graph)
target_link_libraries(bomberman -lX11 -lXxf86vm -lGL -lGLU -lsfml-audio)
