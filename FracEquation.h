#ifndef FEquation
#define FEquation

#include "CompoundExpression.h"
#include "CoefDescriptor.hpp"
#include "SPolynomial.hpp"
#include "RNG.hpp"
#include "Generator.hpp"
#include "FracEquationDescriptor.h"

class FracEquation
{
private:
	int badIdx; // къде е първата недопустима стойност
	void initGenerator();
	bool genInit;
	

public:
	CompoundExpression* left, *right;
	vector<Number> badValues;
	vector<Number> roots;
	int maxVisualPower;
	
	CoefDescriptor cd;
	Generator gen;
	RNJ* rnj;
	char letter;

	bool empty;

	FracEquation();
	FracEquation(CoefDescriptor &cd);
	FracEquation(CoefDescriptor &cd, char letter);

	~FracEquation();

	void construct(vector<Number> &roots, int maxPow);
	void construct2(vector<Number> &roots, vector<Number> &bads, int maxPow);
	void addBadValue(Number &badVal);

	void splitToRight();

	void mangle(); // не работи

	void modOneSide(); // не работи
	void modSide(bool choice);  // работи, но не ползвай

	void modBothSides(); // не работи

	bool addPoly(bool choice); // работи; добавя полином 
	bool addNumberToFraction(bool choice); // работи
	bool splitPolyL(Node* &pnode, bool sideToAdd); // намира и прехвърля от другата страна
	bool findAndSplitPolySS(bool choice); // намира и разделя от същата страна(SS = Same Side)
	bool findAndSplitFraction(bool choice);
	bool mergeFractions(bool choice); // работи, прави гадно

	void balanceSides();

	void print(stringstream& ss);
	void printSolutions(stringstream& ss);
	void dbgPrint();
};

// решава за p и q в (x-p)/(x-a) + (x-q)/(x-b) = 0, където x1 и х2 са корени
bool solveSystem(Number& p, Number& q, Number& a, Number& b, Number& x1, Number& x2);

void generateFracEquation(FracEquation* fe, FracEquationDescriptor& fed);

#endif