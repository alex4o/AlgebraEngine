#ifndef INTERFACE
#define INTERFACE

#include "ExpressionDescriptor.hpp"
#include "Generator.hpp"
#include "FracEquation.h"
#include "FracEquationDescriptor.h"
#include "CompoundInequation.h"
#include "CompoundInequationDescriptor.h"
#include <string>
#include <sstream>

using namespace std;

extern "C"
{
    struct Result
    {
        char* problem;
        char* solution;
    };

    struct MultiResult
    {
        char* problem;
        char* solution;
        char* ptrProblem[30];
        char* ptrSolution[30];
        int count;
    };

    Result oprosti(ExpressionDescriptor ed);
    MultiResult getEquations(EquationDescriptor ed, int count);
    MultiResult getExpressions(ExpressionDescriptor ed, int count);
    MultiResult getInequations(InequationDescriptor id, int count);
	MultiResult getFracEquations(FracEquationDescriptor fed, int count);
	MultiResult getCInequations(CompoundInequationDescriptor cind, int count);
}

#endif

