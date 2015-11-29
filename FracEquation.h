#ifndef FEquation
#define FEquation

#include "CompoundExpression.h"
#include "CoefDescriptor.hpp"
#include "SPolynomial.hpp"
#include "RNG.hpp"
#include "Generator.hpp"

class FracEquation
{
private:
	int badIdx = -1; // показва до коя стойност не са използвани
	void initGenerator();
	bool genInit = false;

public:
	CompoundExpression* left, *right;
	vector<Number> badValues;
	vector<Number> roots;
	int maxVisualPower;
	
	CoefDescriptor cd;
	Generator gen;
	RNJ* rnj;

	char letter;

	FracEquation();
	FracEquation(CoefDescriptor &cd);
	FracEquation(CoefDescriptor &cd, char letter);

	void construct(vector<Number> &roots, int maxPow);
	void construct2(vector<Number> &roots, vector<Number> &bads, int maxPow);
	void addBadValue(Number &badVal);

	void splitToRight();

	void mangle();

	void modOneSide();
	void modSide(bool choice); 

	void modBothSides();

	void addPoly(bool choice);
	void addNumberToFraction(bool choice);
	void splitPoly(Node* &pnode, bool sideToAdd);
	void findAndSplitPoly();
	void mergeFractions(bool choice);

	void balanceSides();

	void print(stringstream& ss);
	void printSolutions(stringstream& ss);
	void dbgPrint();
};

// намира p и q в (x-p)/(x-a) + (x-q)/(x-b) = 0, където x1 и х2 са корени
bool solveSystem(Number& p, Number& q, Number& a, Number& b, Number& x1, Number& x2);

#endif