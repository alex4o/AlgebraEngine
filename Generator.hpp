#ifndef GeneratorH
#define GeneratorH

#include "RNG.hpp"
#include "Polynomial.hpp"
#include "RootDescriptor.hpp"
#include "CoefDescriptor.hpp"
#include <ctime>
#include <random>
#include <string.h>
#include "Expression.hpp"
#include "ExpressionDescriptor.hpp"
#include "ChooseList.hpp"
#include "SPolynomial.hpp"
#include "Equation.hpp"
#include "EquationDescriptor.hpp"
#include "Inequation.hpp"

class Generator{
private:
    RNJ rnGenerator;

public:
	RootDescriptor descriptor;

	Generator()
	{
		rnGenerator.init();
	}

	Generator(RNJ& external)
	{
		rnGenerator=external;
	}

	Polynomial generatePoly(int power, char letter);
	Polynomial generatePoly(CoefDescriptor& cd, int power, char letter);
	SPolynomial generateSPoly(int power, char letter);
	Equation generateEquation(EquationDescriptor ed);
	Equation generateEquation(EquationDescriptor ed, RNJ& jesus);
	Inequation generateInequation(InequationDescriptor& id);
};

void createEquivalentExpressions(Expression& e1, Expression& e2, ExpressionDescriptor& ed, RNJ& jesus);

#endif