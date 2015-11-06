#include <iostream>
#include <vector>
#include <string.h>
#include <sstream>
#include <stdlib.h>

using namespace std;
#define DEBUG true
#include "Equation.hpp"
#include "Expression.hpp"
#include "ExpressionDescriptor.hpp"
#include "Generator.hpp"
#include "Interface.hpp"
#include "Inequation.hpp"

int parse(string s)
{
    int n = 0;
    for(int i = 0; i < s.size(); i++)
    {
        n*=10;
        n+=s[i]-'0';
    }
    return n;
}

int main()
{
    ExpressionDescriptor ed;
    ed.minTerms=2;
    ed.maxTerms=3;

    ed.factored=false;
    ed.letters[0]='a';
    ed.letters[1]='b';
    ed.letters[2]='c';
    ed.cLetters=1;

    ed.minLetters=1;
    ed.maxLetters=2;

    ed.cf.pNatural=100;
    ed.cf.pNegative=40;
    ed.cf.pIrational=0;
    ed.cf.pRational=0;
    ed.cf.upHigh=3;
    ed.cf.upLow=1;
    ed.cf.downHigh=5;
    ed.cf.downLow=1;

    ed.transformCF.pNatural=100;
    ed.transformCF.pIrational=0;
    ed.transformCF.pRational=0;
    ed.transformCF.upHigh=5;
    ed.transformCF.upLow=1;
    ed.transformCF.downHigh=7;
    ed.transformCF.downLow=1;
    ed.transformCF.pNegative=50;

    ed.minSubTerm=1;
    ed.maxSubTerm=2;

    ed.maxPow=2;


    while(true)
    {
        MultiResult mr = getExpressions(ed, 10);
        for(int i = 0; i < mr.count; i++)
        {
            cout<<mr.ptrProblem[i]<<endl;
            cout<<mr.ptrSolution[i]<<endl;
            cout<<"-----\n";
        }


        free(mr.problem);
        free(mr.solution);
        getchar();
    }

}
