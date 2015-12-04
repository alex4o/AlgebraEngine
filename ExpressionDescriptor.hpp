#ifndef ExpDesc
#define ExpDesc

#include "CoefDescriptor.hpp"


struct ExpressionDescriptor
{
    int maxPow; //Maximum power of expression

    int maxLetters; //Minimal && maximum number of letters in subterm
    int minLetters;

    int maxTerms;
    int minTerms;

    int minSubTerm, maxSubTerm;

    bool factored;

    CoefDescriptor cf;//Descriptor for the coef of letters, for example the 3 in 3a
    CoefDescriptor transformCF;
    char letters[8];
    int cLetters;
};

#endif