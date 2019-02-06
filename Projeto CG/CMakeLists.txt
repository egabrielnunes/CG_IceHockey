cmake_minimum_required(VERSION 3.13)
project(Projeto_CG)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Projeto_CG
        CMakeLists.txt
        includes.h
        main.c)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
target_link_libraries(Projeto_CG ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
