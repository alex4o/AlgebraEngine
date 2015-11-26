cmake_minimum_required(VERSION 2.8.4)
project(AlgebraEngine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -std=c++11")

if(WIN32)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif(WIN32)

if(${CMAKE_SYSTEM_NAME} STREQUAL Emscripten)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --bind -g -Os --memory-init-file 0 -std=c++11")

endif(${CMAKE_SYSTEM_NAME} STREQUAL Emscripten)

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
    Interval.hpp
    InequationDescriptor.hpp
    Inequation.hpp
    7klas.hpp
    Interface.hpp
    Interface.cpp
    Equation.hpp
	Node.h
	Node.cpp
	CompoundExpression.h
	CompoundExpression.cpp
	FracEquation.h
	FracEquation.cpp)


add_library(AlgebraEngineStatic STATIC ${SOURCE_FILES})
add_library(AlgebraEngine SHARED ${SOURCE_FILES})


add_executable(AEEXEC main.cpp)
TARGET_LINK_LIBRARIES(AEEXEC AlgebraEngine)

install(TARGETS AlgebraEngine DESTINATION /lib64 )
