# ---------------------------------------------------------
# SETUP SECTION
# ---------------------------------------------------------
cmake_minimum_required(VERSION 3.30)
project(friday)

set(CMAKE_C_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../lib)
set(PRECOMPILED_HEADERS <stdlib.h> <stdio.h> <string.h>)

file(GLOB ALL_SOURCES src/*.c)
set(LIB_SOURCES ${ALL_SOURCES})
list(REMOVE_ITEM LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

# ---------------------------------------------------------





# ---------------------------------------------------------
# LIBRARY SECTION
# ---------------------------------------------------------
add_library(fridaylib STATIC ${LIB_SOURCES})
target_include_directories(fridaylib PRIVATE include)
target_precompile_headers(fridaylib PRIVATE ${PRECOMPILED_HEADERS})
# ---------------------------------------------------------





# ---------------------------------------------------------
# MAIN SECTION
# ---------------------------------------------------------
add_executable(fridayc src/main.c)
target_include_directories(fridayc PRIVATE include)
target_link_directories(fridayc PRIVATE lib)
target_link_libraries(fridayc PRIVATE fridaylib)
target_precompile_headers(fridayc PRIVATE ${PRECOMPILED_HEADERS})
# ---------------------------------------------------------







# ---------------------------------------------------------
# SEZIONE TESTING
# ---------------------------------------------------------

enable_testing()

# All and only Test files
file(GLOB TEST_FILES CONFIGURE_DEPENDS "tests/*.c")

foreach(test_file ${TEST_FILES})
  # Get file name without extension
  get_filename_component(test_name ${test_file} NAME_WE)

  # Create test executable
  add_executable(${test_name} ${test_file})

  target_link_directories(${test_name} PRIVATE lib)
  target_link_libraries(${test_name} PRIVATE fridaylib)
  target_include_directories(${test_name} PRIVATE include)
  
  target_precompile_headers(${test_name} PRIVATE ${PRECOMPILED_HEADERS})

  # Register the test in the CTest system
  add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
