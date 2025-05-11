cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 3.0.1
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL
  SYSTEM)
FetchContent_MakeAvailable(SFML)

include_directories(.)

add_executable(main src/main.cpp src/ThreeBodySimulator.cpp src/pch.cpp)
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)
target_precompile_headers(main PRIVATE src/pch.h)


if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")
# set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall")
