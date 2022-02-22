cmake_minimum_required(VERSION 3.7.2)

project("Red Black Tree" VERSION 1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(libRBTree SHARED "${PROJECT_SOURCE_DIR}/lib/RBTree.c")
add_library(libRBTreeStatic STATIC "${PROJECT_SOURCE_DIR}/lib/RBTree.c")
set_target_properties(libRBTree PROPERTIES OUTPUT_NAME RBTree)
set_target_properties(libRBTreeStatic PROPERTIES OUTPUT_NAME RBTree)

include_directories(${PROJECT_SOURCE_DIR}/include)
