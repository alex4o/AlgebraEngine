#include "Generator.hpp"

using namespace std;

void createEquivalentExpressions(Expression& e1, Expression& e2, ExpressionDescriptor& ed, RNJ& jesus)
{
	ed.minSubTerm = 1; // safeguard
	ed.maxSubTerm = ed.maxPow;

    int cSubTerms = jesus.nextInt(ed.minSubTerm, ed.maxSubTerm);
    int *powers = new int[cSubTerms];
    int power = jesus.nextInt(cSubTerms, ed.maxPow);

    if(ed.factored==false)
    {
        int cTerms = jesus.nextInt(ed.minTerms, ed.maxTerms);

        for(int i = 0; i < cTerms; i++)
        {
            Term currentTerm;
            createListOfInts(powers, cSubTerms, power, &jesus); //тази функция разпределя степенти по многочлените

            bool firstTime = true;

            for(int j = 0; j < cSubTerms; j++)
            {
                int cPower = powers[j];

                ChooseList cl(ed.cLetters, &jesus);
                int cLetters = jesus.nextInt(ed.minLetters, ed.maxLetters);
                if(firstTime)
                {
                    firstTime=false;
                    if(cLetters==1) cLetters=2;
                }

                Polynomial poly;

                for (int k = 0; k < cLetters; k++)//Letters
                {
                    if(k>=ed.cLetters)
                    {
                        Monomial mono(jesus.nextNumber(ed.cf));
                        poly.monos.push_back(mono);
                        continue;
                    }
                    int choice = cl.choose();

                    char letter = ed.letters[choice];
                    Number coef = jesus.nextNumber(ed.cf);

                    Monomial mono(coef, letter);
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
    else
    {
        ed.minTerms=1;
        ed.maxTerms=1;

        Term currentTerm;

        createListOfInts(powers, cSubTerms, power, &jesus);

        bool firstTime = true;

        for(int j = 0; j < cSubTerms; j++)
        {
            int cPower = powers[j];

            ChooseList cl(ed.cLetters, &jesus);
            int cLetters = jesus.nextInt(ed.minLetters, ed.maxLetters);
            if(firstTime)
            {
                firstTime=false;
                if(cLetters==1) cLetters=2;
            }

            Polynomial poly;
            for (int k = 0; k < cLetters; k++)//Letters
            {
                if(k>=ed.cLetters)
                {
                    Monomial mono(jesus.nextNumber(ed.cf));
                    poly.monos.push_back(mono);
                    continue;
                }
                int choice = cl.choose();

                char letter = ed.letters[choice];
                Number coef = jesus.nextNumber(ed.cf);

            currentTerm.coef = jesus.nextNumber(ed.transformCF); //избира се коефициента пред скобата
			delete powers;
            e1.addTerm(currentTerm, false); //от едната страна скобата се добавя както си е, а от другата
            e2.addTerm(currentTerm, true); //в нормален

                Monomial mono(coef, letter);
                poly.monos.push_back(mono);

            }

            currentTerm.polys.push_back(poly);
            currentTerm.powers.push_back(cPower);

        }

        currentTerm.coef = jesus.nextNumber(ed.transformCF);
        delete powers;
        e1.addTerm(currentTerm, true);
        e2.addTerm(currentTerm, false);
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

Polynomial Generator::generatePoly(CoefDescriptor& cd, int power, char letter)
{
	vector<Monomial> vm;
	for (int i = 0; i <= power; i++)
	{
		int p = power - i;
		if(p) vm.push_back(Monomial(rnGenerator.nextNumber(cd), letter, p));
		else vm.push_back(Monomial(rnGenerator.nextNumber(cd)));
	}
	

	return Polynomial(vm, power);
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
    ed.nice=true;
    result.create(ed, rnGenerator);

    int cTerms = rnGenerator.nextInt(ed.minTerms, ed.maxTerms);
    for(int i = 0; i < cTerms; i++)
    {
        result.addTerm(ed.maxTermPower,rnGenerator);
    }

    result.condenseFree();
    result.balance();

    return result;
}

Equation Generator::generateEquation(EquationDescriptor ed, RNJ &rnj) {
    Equation result;
    ed.nice=true;
    result.create(ed, rnGenerator);

    int cTerms = rnj.nextInt(ed.minTerms, ed.maxTerms);
    for(int i = 0; i < cTerms; i++)
    {
        result.addTerm(ed.maxTermPower,rnGenerator);
    }

    result.condenseFree();

    result.balance();

    return result;
}

Inequation Generator::generateInequation(InequationDescriptor &id) {
    Inequation result;
    id.nice=true;
    result.create(id);

    int cTerms = rnGenerator.nextInt(id.minTerms, id.maxTerms);
    for(int i = 0; i < cTerms; i++)
    {
        result.addTerm(rnGenerator.nextInt(1, id.maxTermPower));
    }

    return result;
}

