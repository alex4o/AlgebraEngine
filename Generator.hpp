#ifndef GeneratorH
#define GeneratorH

#include "Polynomial.hpp"
#include "RootDescriptor.hpp"
#include "CoefDescriptor.hpp"
#include <ctime>

void init();
int rng(int low, int high);
Number gen(RootDescriptor &rd, char type);
Polynomial generate(int power, RootDescriptor rd, char letter);
Polynomial generate(int power, CoefDescriptor cd, char letter);

#endif