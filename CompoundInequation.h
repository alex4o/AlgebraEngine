
#ifndef CInequation
#define CInequation

#include "CompoundExpression.h"
#include "Inequation.hpp"
#include "CompoundInequationDescriptor.h"

class CompoundInequation
{
public:
	CompoundExpression* left, *right;
	vector<Number> roots;
	vector<Interval> solutions;
	int maxVisualPower;

	char sign; // lookup[4] = { ">", "\\geq", "\\leq", "<" };

	CoefDescriptor cd;
	Generator gen;
	RNJ* rnj;

	char letter;

	CompoundInequation();
	~CompoundInequation();

	void construct(vector<Number> &nv, char sign);
	void getSolutions();
	void findAndSplitPoly(bool choice);
	void addPolyBothSides();
	void generateAndAddNode();

	void print(stringstream& ss);
	void printSolutions(stringstream& ss);

	void generate(CompoundInequationDescriptor& cind);

	void dbgPrint();
};
#endif