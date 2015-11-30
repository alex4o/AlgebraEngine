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
	initPrintFunctions();

	CoefDescriptor cd;
	cd.downHigh = 1;
	cd.downLow = 1;

	cd.upHigh = 3;
	cd.upLow = 1;

	cd.pNatural = 100;
	cd.pIrational = 0;
	cd.pRational = 0;
	cd.pNegative = 50;

	vector<Number> roots;
	roots.push_back(Number(2));
	roots.push_back(Number(6));

	vector<Number> bads;
	bads.push_back(Number(3));
	bads.push_back(Number(4));

	stringstream ss;

	CompoundInequation* ineq = new CompoundInequation();
	ineq->construct(roots, 2);
	ineq->cd = cd;
	ineq->getSolutions();

	ineq->print(ss);
	ss << endl;

	ineq->findAndSplitPoly(false);
	ineq->print(ss);
	ss << endl;

	ineq->printSolutions(ss);

	/*FracEquation* eq = new FracEquation(cd, 'x');
	eq->construct2(roots, bads, 2);

	stringstream ss;
	eq->print(ss);
	ss << endl;

	eq->splitToRight();
	eq->print(ss);
	ss << endl;

	eq->addPoly(false);
	eq->print(ss);
	ss << endl;

	eq->addNumberToFraction(false);
	eq->print(ss);
	ss << endl;

	//eq->mergeFractions(true);
	//eq->print(ss);
	//ss << endl;*/

	cout << endl << endl << ss.str();
	system("pause");
}
