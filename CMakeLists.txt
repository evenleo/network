cmake_minimum_required(VERSION 3.1)
project(network VERSION 1.22.0 LANGUAGES C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(chap-04/)
add_subdirectory(chap-05/)
add_subdirectory(chap-06/)
add_subdirectory(chap-11/)
add_subdirectory(chap-12/)
add_subdirectory(chap-13/)
add_subdirectory(chap-14/)
