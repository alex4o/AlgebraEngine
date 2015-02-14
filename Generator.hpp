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
class Generator{
private:
    RNJ rnGenerator;

public:
	RootDescriptor descriptor;

	int rng(int low, int high);
	Polynomial generate(int power, char letter);

	Number gen(char t);
};

Polynomial generate(int power, CoefDescriptor cd, char letter);
void createEquivalentExpressions(Expression& e1, Expression& e2, ExpressionDescriptor& ed);
void createListOfInts(int* array, int size, int sum, RNJ* jesus);

#endif