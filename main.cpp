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
#include "CompoundExpression.h"
#include "FracEquation.h"
#include "CompoundInequation.h"

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

void printSigns(Node** arr, int n)
{
	cout << "signs: ";
	for (int i = 0; i < n; i++) cout << arr[i]->getSign() << " ";
	cout << endl;
}

void printSigns(Node** arr, int n, stringstream& ss)
{
	ss << "signs: ";
	for (int i = 0; i < n; i++) ss << arr[i]->getSign() << " ";
	ss << endl;
}

int main()
{
	ExpressionDescriptor ed;

	ed.maxPow = 2;

	ed.letters[0] = 'x';
	ed.letters[1] = 'y';
	ed.letters[2] = 'z';
	ed.cLetters = 3;

	ed.factored = false;
	ed.minLetters = 2;
	ed.maxLetters = 3;

	ed.minTerms = 1;
	ed.maxTerms = 3;

	ed.cf.pNatural = 50;
	ed.cf.pRational = 50;

	ed.cf.upHigh = 10;
	ed.cf.upLow = 1; 
	ed.cf.downHigh = 10;
	ed.cf.downLow = 1;

	ed.transformCF.pNatural = 50;
	ed.transformCF.pRational = 50;

	ed.transformCF.upHigh = 10;
	ed.transformCF.upLow = 1;
	ed.transformCF.downHigh = 10;
	ed.transformCF.downLow = 1;

	ed.minSubTerm = 1;
	ed.maxSubTerm = ed.maxPow;

	Expression e1, e2;
	
	MultiResult mr = getExpressions(ed, 1);
	cout << mr.problem << endl << mr.solution << endl;

	system("pause");
}
