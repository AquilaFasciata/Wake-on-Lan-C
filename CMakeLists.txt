cmake_minimum_required(VERSION 3.0.0)
project(wake-on-lan VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

add_executable(wake-on-lan src/main.c src/networking.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)