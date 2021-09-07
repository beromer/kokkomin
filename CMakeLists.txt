cmake_minimum_required(VERSION 3.14)
include(ExternalProject)
include(FetchContent)

# set project name and languages
project(kokkomin CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

set(Kokkos_ENABLE_CUDA ON CACHE BOOL "")
set(Kokkos_ENABLE_CUDA_LAMBDA ON CACHE BOOL "")
set(Kokkos_ENABLE_LAUNCH_COMPILER ON CACHE BOOL "")
#set(Kokkos_ENABLE_HIP ON CACHE BOOL "")
#set(Kokkos_ARCH_VEGA900 ON CACHE BOOL "")
#set(Kokkos_ENABLE_OPENMP ON CACHE BOOL "")
#set(Kokkos_ENABLE_SERIAL ON CACHE BOOL "")

add_executable(kokkomin main.cpp)

# compile flags
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -pedantic -Wall -Wextra -fdiagnostics-color=always")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(Kokkos_ENABLE_DEBUG ON CACHE BOOL "" FORCE)
    set(Kokkos_ENABLE_DEBUG_BOUNDS_CHECK ON CACHE BOOL "" FORCE)
endif()

FetchContent_Declare(kokkos
    GIT_REPOSITORY https://github.com/kokkos/kokkos.git
    GIT_TAG 3.4.01
 )

FetchContent_MakeAvailable(kokkos)

target_link_libraries(kokkomin
                      Kokkos::kokkos
                      #fmt::fmt
)
