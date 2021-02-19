cmake_minimum_required(VERSION 3.19)

project(cpp_modern_development LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules
                      ${CMAKE_MODULE_PATH})


add_compile_options(-Wall -Werror -Wextra -Wpedantic)

add_subdirectory(src)

enable_testing()
set(CMAKE_CTEST_ARGUMENTS "--output-on-failure")

set(CLANG_FORMAT_BIN_NAME clang-format)
set(CLANG_FORMAT_EXCLUDE_PATTERNS  "build/" ${CMAKE_BINARY_DIR})
find_package(ClangFormat)
