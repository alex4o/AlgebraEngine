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

    Result oprosti(ExpressionDescriptor ed)
    {
        Result res;

        Expression e1,e2;
        createEquivalentExpressions(e1, e2, ed);
        stringstream ss1, ss2;
        e1.print(ss1);
        e2.print(ss2);

        string s1 = ss1.str();
        string s2 = ss2.str();

        res.problem = (char*)malloc(s1.size() + 1);
        res.solution = (char*)malloc(s2.size() + 1);

        strcpy(res.problem, (const char*)s1.c_str());
        strcpy(res.solution, (const char*)s2.c_str());

        return res;
    }
}



