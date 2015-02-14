#include <string.h>
#include "7klas.hpp"
#include "RNG.hpp"
#include "ChooseList.hpp"

int min(int a, int b)
{
    if(a<b) return a;
    else return b;
}



void createEquivalentExpressions(Expression& e1, Expression& e2, ExpressionDescriptor& ed)
{
    RNJ jesus;



    if(ed.factored=true)
    {
        int cTerms = jesus.nextInt(ed.minTerms, ed.maxTerms);
        for(int i = 0; i < cTerms; i++)//Term
        {
            int cSubTerms = jesus.nextInt(ed.minSubTerm, ed.maxSubTerm);

            int power = jesus.nextInt(1, ed.maxPow);
            int remPower = power;

            Term t(jesus.nextNumber(ed.transformCF));
            for(int j = 0; j < cSubTerms; j++)//Subterm(aka Polynomial)
            {
                int cPower = jesus.nextInt(1, remPower);

                ChooseList cl(ed.letters.size(), &jesus);
                int cLetters = jesus.nextInt(ed.minLetters, ed.maxLetters);

                for(int k = 0; k < cLetters; k++)//Letters
                {
                    char letter = ed.letters[cl.choose()];
                    Number coef = jesus.nextNumber(ed.cf);
                }
            }
        }
    }
}