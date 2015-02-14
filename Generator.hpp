#ifndef GeneratorH
#define GeneratorH

#include "RNG.hpp"
#include "Polynomial.hpp"
#include "RootDescriptor.hpp"
#include "CoefDescriptor.hpp"
#include <ctime>
#include <random>
#include <string.h>
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

#endif