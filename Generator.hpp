#ifndef GeneratorH
#define GeneratorH

#include "Polynomial.hpp"
#include "RootDescriptor.hpp"
#include "CoefDescriptor.hpp"
#include <ctime>
#include <random>
class Generator{
private:

	std::random_device rand_dev;

public:
	RootDescriptor descriptor;

	int rng(int low, int high);
	Polynomial generate(int power, char letter);

	Number gen(char t);
};

Polynomial generate(int power, CoefDescriptor cd, char letter);

#endif