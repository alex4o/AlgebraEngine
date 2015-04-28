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
    char type; //0 - power на брой корени, 1 - без корени, 2 - всякакви корени
    RootDescriptor rd;
    CoefDescriptor cd;
    CoefDescriptor transformCF;
    bool nice;
};

#endif