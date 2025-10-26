cmake_minimum_required(VERSION 3.10)
project(lab3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=leak")

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(figure_lib src/figure.cpp src/rectangle.cpp src/trapezoid.cpp src/rhombus.cpp)
add_library(array_lib src/array.cpp src/figure_array.cpp)

target_include_directories(figure_lib PUBLIC include)
target_include_directories(array_lib PUBLIC include)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE figure_lib array_lib)

enable_testing()
add_executable(start_test test/test.cpp)
target_link_libraries(start_test figure_lib array_lib gtest_main)
add_test(NAME start_test COMMAND start_tests)