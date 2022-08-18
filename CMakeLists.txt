cmake_minimum_required(VERSION 3.15)

project(Implementation_of_containers CXX)

add_executable(Implementation_of_containers    
    src/main.cpp
)

target_include_directories(Implementation_of_containers PRIVATE include)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(Implementation_of_containers PRIVATE 
        -g
        -Wall
        -Wextra
        -Werror
        -pedantic
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(Implementation_of_containers PRIVATE
        /EHsc
        /W4
        /WX
    )
endif()

target_compile_features(Implementation_of_containers PUBLIC cxx_std_17)
