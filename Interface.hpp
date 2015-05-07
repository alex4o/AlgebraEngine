#include "ExpressionDescriptor.hpp"
#include "Generator.hpp"
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
}



