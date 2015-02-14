#ifndef ExpDesc
#define ExpDesc

#include "CoefDescriptor.hpp"
#include <string>

class ExpressionDescriptor
{
public:
    CoefDescriptor cf;//Descriptor for the coef of letters, for example the 3 in 3a
    CoefDescriptor transformCF; //Descriptor for the coef of a multiplication ,for example the 4 in 4(3a+2v)

    int maxPow; //Maximum power of expression
    string letters;
    int maxLetters; //Minimal and maximum number of letters in subterm
    int minLetters;

    int maxTerms;
    int minTerms;

    int minSubTerm, maxSubTerm;

    bool factored;

};

#endif