cmake_minimum_required(VERSION 3.27)
project(CDataFrame VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

add_executable(CDataFrame main.c column.c column.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
