cmake_minimum_required (VERSION 3.23)

project (chatgqt)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED true)
set (CMAKE_EXPORT_COMPILE_COMMANDS true)
set (CMAKE_BUILD_TYPE Release)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -m64")

include_directories (./include)

aux_source_directory(./src src)

add_executable (chatgqt ${src})
