#ifndef GeneratorH
#define GeneratorH

#include "Polynomial.hpp"
#include "RootDescriptor.hpp"
#include "CoefDescriptor.hpp"
#include <ctime>
#include <random>

int rng(int low, int high,std::random_device *rand_dev);
Number gen(RootDescriptor &rd, char type, std::random_device *rand_dev);
Polynomial generate(int power, RootDescriptor rd, char letter,std::random_device *rand_dev);
Polynomial generate(int power, CoefDescriptor cd, char letter);

#endif