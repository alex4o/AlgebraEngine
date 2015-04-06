#ifndef EquationDesc
#define EquationDesc

#include "RootDescriptor.hpp"

struct EquationDescriptor
{
    int power;
    int maxTermPower;
    char letter;
    RootDescriptor rd;
    int minTerms;
    int maxTerms;
    bool nice;
};

#endif