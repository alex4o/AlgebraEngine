cmake_minimum_required(VERSION 2.8.4)
project(Algebra_Engine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

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
    Simple.hpp)

add_executable(Algebra_Engine ${SOURCE_FILES})