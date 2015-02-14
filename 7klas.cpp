#include "7klas.hpp"
#include "RNG.hpp"
#include "ChooseList.hpp"

int min(int a, int b)
{
    if(a<b) return a;
    else return b;
}

void createListOfInts(int* array, int size, int sum, RNJ* jesus)
{
    memset(array+4, 0, (size-1)*4);
    array[0]=sum;

    int chArr[size];

    for(int i = 0; i < size - 1; i++)
    {
        int chArrLen = 0;
        for(int j = 0; j <= i; j++)
        {
            if(array[j]>1) chArr[chArrLen++] = j;
        }

        int choice = jesus->nextInt(0, chArrLen-1);

        int newInt = jesus->nextInt(1, array[chArr[choice]]-1);
        array[i+1] = newInt;
        array[chArr[choice]] -= newInt;
    }
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