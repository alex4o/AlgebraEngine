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

    void oprosti(ExpressionDescriptor ed, Result *res);
}



