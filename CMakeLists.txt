cmake_minimum_required(VERSION 3.9)
project(network VERSION 1.22.0 LANGUAGES C CXX)

# C standard can be overridden when this is used as a sub-project.
if(NOT CMAKE_C_STANDARD)
  # This project can use C11, but will gracefully decay down to C89.
  set(CMAKE_C_STANDARD 11)
  set(CMAKE_C_STANDARD_REQUIRED OFF)
  set(CMAKE_C_EXTENSIONS OFF)
endif(NOT CMAKE_C_STANDARD)

# C++ standard can be overridden when this is used as a sub-project.
if(NOT CMAKE_CXX_STANDARD)
  # This project requires C++11.
  set(CMAKE_CXX_STANDARD 11)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif(NOT CMAKE_CXX_STANDARD)

#include(project1)
#check_library_exists(project1 project1_value "" HAVE_PROJECT1)

aux_source_directory(project1 DIR_SRCS)

set(TEST_MAIN
  ${DIR_SRCS}
)

add_executable(socket_server project1/socket_server.c)
add_executable(socket_client project1/socket_client.c)

add_executable(udp_server project2/udp_server.c)
add_executable(udp_client project2/udp_client.c)


