cmake_minimum_required(VERSION 2.8)

set(CMAKE_INCLUDE_PATH "../toolkits/glut")
set(CMAKE_LIBRARY_PATH "../toolkits/glut")

# Project Name
PROJECT(atb_demo)

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})

include_directories("../toolkits/AntTweakBar/")
link_directories("Path/To/AntTweakBar")

add_library(AntTweakBar SHARED IMPORTED) 
set_property(TARGET  AntTweakBar  PROPERTY IMPORTED_LOCATION "Path/To/AntTweakBar.lib")

if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} AntTweakBar.lib)
