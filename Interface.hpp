#include "ExpressionDescriptor.hpp"
#include "Generator.hpp"
#include <string>
#include <sstream>

using namespace std;

extern "C"
{
    struct Result //Структура за 1 задача
    {
        char* problem; //низ със условието
        char* solution; //низ със отговора
    };

    struct MultiResult //Структура за множество задачи
    {
        char* problem; // тук се съхраняват всичките задачи
        char* solution; // и съответните отговори. Отделени са с 0
        char* ptrProblem[30]; //тук се съхрнавят съответните индекси на задачите
        char* ptrSolution[30]; //и отговорите, което прави работата лесна
        int count; //а това е броят задачи.
    };

    Result oprosti(ExpressionDescriptor ed);
    MultiResult getEquations(EquationDescriptor ed, int count);
    MultiResult getExpressions(ExpressionDescriptor ed, int count);
    MultiResult getInequations(InequationDescriptor id, int count);
}



