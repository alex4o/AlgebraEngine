#include "Generator.hpp"


using namespace std;

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
            Term currentTerm;

            int cSubTerms = jesus.nextInt(ed.minSubTerm, ed.maxSubTerm); //number of subterms for current term
            int power = jesus.nextInt(cSubTerms, ed.maxPow); //distrbution of power to subterms

            int powers[cSubTerms];
            createListOfInts(powers, cSubTerms, power, &jesus);

            for(int j = 0; j < cSubTerms; j++)//Subterm(aka Polynomial)
            {
                int cPower = powers[j];

                ChooseList cl(ed.letters.size(), &jesus);
                int cLetters = jesus.nextInt(ed.minLetters, ed.maxLetters);

                Polynomial poly;

                for (int k = 0; k < cLetters; k++)//Letters
                {
                    char letter = ed.letters[cl.choose()];
                    Number coef = jesus.nextNumber(ed.cf);

                    Monomial mono(coef, letter);
                    poly.monos.push_back(mono);
                }

                currentTerm.polys.push_back(poly);
                currentTerm.powers.push_back(cPower);
            }

            e1.addTerm(currentTerm, false);
            e2.addTerm(currentTerm, true);
        }

    }
}

int Generator::rng(int low, int high)
{
     rnGenerator.nextInt(low, high);

}

Number Generator::gen(char t)
{
    int sign = -1;
    if(rand()%2) sign=1;

    if(t=='n')
    {
        return Number(rng(sign*this->descriptor.upLow, this->descriptor.upHigh));
    }
    if(t=='f')
    {
        return Number(rng(sign*this->descriptor.upLow, this->descriptor.upHigh), rng(this->descriptor.downLow, this->descriptor.downHigh));
    }
    return Number(0);
}

Polynomial Generator::generate(int power, char letter){
    Simple s(letter, 1);
    std::vector<Simple> vs;
    vs.push_back(s);
    Monomial m(Number(1), vs);

    Polynomial result(Number(1));

    string ca = "x + 1";
    ca[0] = letter;

    Polynomial po(ca);

    int last=-1;

    char type[3];
    int rem[3];

    if(this->descriptor.pNatural>0)
    {
        last++;
        type[last]='n';
        rem[last]=(this->descriptor.pNatural*power)/100+1;
    }
    if(this->descriptor.pFraction>0)
    {
        last++;
        type[last]='f';
        rem[last]=(this->descriptor.pFraction*power)/100+1;
    }
    if(this->descriptor.pIrational>0)
    {
        last++;
        type[last]='i';
        rem[last]=(this->descriptor.pIrational*power)/100+1;
    }


    for(int i = 0; i < power; i++)
    {
        int r = rng(0, last);
        char t = type[r];

        rem[r]--;
        if(rem[r]<=0)
        {
            rem[r]=rem[last];
            type[r]=type[last];
            last--;
        }

        Number nc = gen(t);
        cout<<"Root: "<<nc.fraction.up<<"/"<<nc.fraction.down<<endl;

        if(nc.null==false)po.monos[1].coef = nc;
        else po.monos.pop_back();
        /*cout<<"adding root: ";
        po.print();
        std::cout<<"\n";*/

        result = result * po;
        if(nc.null) po.monos.push_back(m);
        /*std::cout<<"Result is now: ";
        result.print();
        std::cout<<"\n";*/
    }
    return result;
}