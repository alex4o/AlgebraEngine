﻿#include <iostream>
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
	FracEquationDescriptor fed;

	fed.bvd.pNatural = 50;
	fed.bvd.pRational = 50;
	fed.bvd.upHigh = 10;
	fed.bvd.upLow = 1;

	fed.bvd.downHigh = 1;
	fed.bvd.downLow = 1;
	fed.bvd.pNegative = 50;

	fed.cf.pNatural = 50;
	fed.cf.pRational = 50;
	fed.cf.upHigh = 7;
	fed.cf.upLow = 1;

	fed.cf.downLow = 1;
	fed.cf.downHigh = 1;
	fed.cf.pNegative = 50;

	fed.genType = 0;
	fed.letter = 'x';

	fed.maxTransformations = 5;
	fed.maxVisualPower = 2;
	fed.minTransformations = 0;

	fed.power = 2;

	fed.rd.pNatural = 50;
	fed.rd.pFraction = 50;
	fed.rd.upHigh = 7;
	fed.rd.upLow = 1;

	fed.rd.downHigh = 10;
	fed.rd.downLow = 1;
	fed.rd.pNegative = 50;

	/*FracEquation* fe = new FracEquation(fed.cf, 'x');
	cout << "orig: ";
	fe->dbgPrint();
	fe->addPoly(false);
	cout << "first add: ";
	fe->dbgPrint();
	fe->addPoly(true);
	cout << "second add: ";
	fe->dbgPrint();*/

	int n = 3;

	MultiResult mr = getFracEquations(fed, n);

	for (int i = 0; i < n; i++)
	{
		cout << mr.ptrProblem[i] << endl;
		cout << mr.ptrSolution[i] << endl;
		cout << endl;
	}

	system("pause");
}
