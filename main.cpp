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
#include "EquationDescriptor.hpp"

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
	initPrintFunctions();
	CompoundInequationDescriptor cind;
	cind.cf.pNatural = 100;
	cind.cf.pRational = 50;
	cind.cf.upHigh = 7;
	cind.cf.upLow = 1;
	cind.cf.downHigh = 1;
	cind.cf.downHigh = 1;
	cind.letter = 'x';
	cind.maxTrans = 3;
	cind.maxVisualPower = 2;
	cind.minTrans = 1;
	cind.power = 2;
	cind.rd.pNatural = 100;
	cind.rd.pFraction = 50;
	cind.rd.upHigh = 7;
	cind.rd.upLow = 1;
	cind.rd.downHigh = 10;
	cind.rd.downLow = 1;
	int n = 13;
	MultiResult mr = getCInequations(cind, n);
	/*for (int i = 0; i < n; i++)
	{
		cout << mr.ptrProblem[i] << endl;
		cout << mr.ptrSolution[i] << endl;
		cout << endl;
	}*/

	system("pause");
}
