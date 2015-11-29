#ifndef CInequation
#define CINequation

#include "CompoundExpression.h"
#include "Inequation.hpp"

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

	void construct(vector<Number> &nv, char sign);
	void getSolutions();

	void print(stringstream& ss);
	void printSolutions(stringstream& ss);
};

#endif