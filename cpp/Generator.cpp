#include "Generator.hpp"

using namespace std;



void createEquivalentExpressions(Expression& e1, Expression& e2, ExpressionDescriptor& ed, RNJ& jesus)
{

    if(ed.factored==false)
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

                ChooseList cl(ed.cLetters, &jesus);
                int cLetters = jesus.nextInt(ed.minLetters, ed.maxLetters);

                Polynomial poly;

                bool hasNumber = jesus.nextBool();
                if(hasNumber) cLetters--;

                for (int k = 0; k < cLetters; k++)//Letters
                {
                    int choice = cl.choose();

                    char letter = ed.letters[choice];
                    Number coef = jesus.nextNumber(ed.cf);

                    Monomial mono(coef, letter);
                    poly.monos.push_back(mono);

                }

                if(hasNumber)
                {
                    Monomial mono(jesus.nextNumber(ed.cf));
                    poly.monos.push_back(mono);
                }

                currentTerm.polys.push_back(poly);
                currentTerm.powers.push_back(cPower);
            }

            currentTerm.coef = jesus.nextNumber(ed.transformCF);

            e1.addTerm(currentTerm, false);
            e2.addTerm(currentTerm, true);
        }

    }
}

Polynomial Generator::generatePoly(int power, char letter){
    Simple s(letter, 1);
    std::vector<Simple> vs;
    vs.push_back(s);
    Monomial m(Number(1), vs);

    Polynomial result(Number(1));

    string ca = "x + 1";
    ca[0] = letter;

    Polynomial po(ca);


    for(int i = 0; i < power; i++)
    {
        Number nc = rnGenerator.nextNumber(descriptor);
        cout<<"Root: "<<nc.fraction.up<<"/"<<nc.fraction.down<<endl;

        if(nc.null==false)po.monos[1].coef = nc;
        else po.monos.pop_back();
        result = result * po;
        if(nc.null) po.monos.push_back(m);
    }
    return result;
}

SPolynomial Generator::generateSPoly(int power, char letter)
{
    SPolynomial result;
    result.letter=letter;
    result.power=0;
    result.coef[0]=1;

    SPolynomial current;
    current.power=1;
    current.coef[1]=1;

    for(int i = 0; i < power; i++)
    {
        current.coef[0] = rnGenerator.nextNumber(descriptor);
        result = result * current;
    }

    return result;
}

Equation Generator::generateEquation(EquationDescriptor ed) {
    Equation result;
    result.create(ed.power, ed.rd, ed.nice, ed.letter, rnGenerator);

    int cTerms = rnGenerator.nextInt(ed.minTerms, ed.maxTerms);
    for(int i = 0; i < cTerms; i++)
    {
        result.addTerm(ed.maxTermPower, ed.nice, rnGenerator);
    }

    result.condenseFree();

    result.balance();

    return result;
}

Equation Generator::generateEquation(EquationDescriptor ed, RNJ &rnj) {
    Equation result;
    result.create(ed.power, ed.rd, ed.nice, ed.letter, rnj);

    int cTerms = rnj.nextInt(ed.minTerms, ed.maxTerms);
    for(int i = 0; i < cTerms; i++)
    {
        result.addTerm(ed.maxTermPower, ed.nice, rnj);
    }

    result.condenseFree();

    result.balance();

    return result;
}
