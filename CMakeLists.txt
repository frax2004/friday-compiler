cmake_minimum_required(VERSION 3.41)
project(fridayc)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ..)
file(GLOB SOURCES src/*.cpp)

set(PRECOMPILED_HEADERS <bits/stdc++.h>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
add_executable(fridayc ${SOURCES})

target_include_directories(fridayc PRIVATE
  include
)

target_precompile_headers(fridayc PRIVATE 
  ${PRECOMPILED_HEADERS}
)

target_link_libraries(fridayc PRIVATE
  stdc++exp
)
