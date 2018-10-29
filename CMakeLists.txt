cmake_minimum_required(VERSION 3.7)

set(project_name fain_projet)

project(${project_name} LANGUAGES C)

file(GLOB_RECURSE source_files src/**/*.c src/*.c)
file(GLOB_RECURSE header_files src/**/*.h src/*.h)

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})
if(NOT GLUT_FOUND)
    message(ERROR "GLUT not found!")
endif(NOT GLUT_FOUND)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR "OPENGL not found!")
endif(NOT OPENGL_FOUND)

add_executable(${project_name} ${source_files} ${header_files})
target_link_libraries(${project_name} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
