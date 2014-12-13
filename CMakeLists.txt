cmake_minimum_required(VERSION 2.8.4)
project(AlgebraEngine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -std=c++11")


set(SOURCE_FILES
    Fraction.hpp
    main.cpp
    Monomial.cpp
    Monomial.hpp
    Number.cpp
    Number.hpp
    Polynomial.cpp
    Polynomial.hpp
    Simple.cpp
    Simple.hpp
    Debug.cpp
    CoefDescriptor.hpp
    RootDescriptor.hpp
    Generator.cpp
    Generator.hpp)

add_executable(Algebra_Engine ${SOURCE_FILES})
#add_library(AlgebraEngine SHARED ${SOURCE_FILES})
