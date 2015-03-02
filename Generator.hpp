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

class Generator{
private:
    RNJ rnGenerator;

public:
	RootDescriptor descriptor;

	Polynomial generatePoly(int power, char letter);
	SPolynomial generateSPoly(int power, char letter);
	Equation generateEquation(EquationDescriptor ed);
};

void createEquivalentExpressions(Expression& e1, Expression& e2, ExpressionDescriptor& ed);

#endif