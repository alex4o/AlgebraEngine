project(AlgebraEngine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -std=c++11 -s NO_EXIT_RUNTIME=1")


set(SOURCE_FILES
    Fraction.hpp
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
    Generator.hpp
    RNG.cpp
    RNG.hpp
    SPolynomial.hpp
    ChooseList.hpp
    Expression.hpp
    ExpressionDescriptor.hpp
    EquationDescriptor.hpp
    7klas.hpp
    Interface.hpp
    Interface.cpp
    Equation.hpp)

add_library(AlgebraEngine SHARED ${SOURCE_FILES})
