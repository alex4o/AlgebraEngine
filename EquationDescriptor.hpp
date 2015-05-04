#ifndef EquationDesc
#define EquationDesc

#include "RootDescriptor.hpp"

struct EquationDescriptor
{
    int power;
    int maxTermPower;
    int minTerms;
    int maxTerms;
    char letter;
    char type;
    RootDescriptor rd;
    CoefDescriptor cd;
    CoefDescriptor transformCF;
    bool nice;
};

#endif