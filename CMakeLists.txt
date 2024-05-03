cmake_minimum_required(VERSION 3.20.0)
project(wake-on-lan VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

add_library(wake-on-lib STATIC src/networking.c)

add_executable(wake-on-lan src/main.c )
target_link_libraries(wake-on-lan wake-on-lib)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)