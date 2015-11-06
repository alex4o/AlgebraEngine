#include "Generator.hpp"

using namespace std;



void createEquivalentExpressions(Expression& e1, Expression& e2, ExpressionDescriptor& ed, RNJ& jesus)
{
 //Фунцкия за създаване на тъждествени изрази
    if(ed.factored==false) //ако задачата не е опрости
    {                  //засега това е единствения вариант
        int cTerms = jesus.nextInt(ed.minTerms, ed.maxTerms);
        //броя на скоби
        for(int i = 0; i < cTerms; i++)//Term
        {
            Term currentTerm;

            int cSubTerms = jesus.nextInt(ed.minSubTerm, ed.maxSubTerm); //броят на полиноми, участващи в една скоба
            int power = jesus.nextInt(cSubTerms, ed.maxPow); //степента на текушата скоба

            int *powers = new int[cSubTerms];
            createListOfInts(powers, cSubTerms, power, &jesus); //тази функция разпределя степенти по многочлените

            for(int j = 0; j < cSubTerms; j++)//генерация на полином
            {
                int cPower = powers[j];

                ChooseList cl(ed.cLetters, &jesus); //това се ползв за избиране на букви
                int cLetters = jesus.nextInt(ed.minLetters, ed.maxLetters); //брой букви в полинома

                Polynomial poly;

                bool hasNumber = jesus.nextBool(); //дали в полинома ще има цифра, това може да се промени в бъдеще
                if(hasNumber) cLetters--;

                for (int k = 0; k < cLetters; k++)//Letters
                {
                    int choice = cl.choose();

                    char letter = ed.letters[choice];
                    Number coef = jesus.nextNumber(ed.cf); //Избира се буква(променлива) и коефициент за нея

                    Monomial mono(coef, letter);
                    poly.monos.push_back(mono);

                }

                if(hasNumber)
                {
                    Monomial mono(jesus.nextNumber(ed.cf));
                    poly.monos.push_back(mono);
                }

                currentTerm.polys.push_back(poly);
                currentTerm.powers.push_back(cPower);// полинома се добавя към скобата
            }

            currentTerm.coef = jesus.nextNumber(ed.transformCF); //избира се коефициента пред скобата
			delete powers;
            e1.addTerm(currentTerm, false); //от едната страна скобата се добавя както си е, а от другата
            e2.addTerm(currentTerm, true); //в нормален
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
    Equation result; //Функция за създаване на уравнение с украшения
    result.create(ed, rnGenerator); //Уравнение без украшения

    int cTerms = rnGenerator.nextInt(ed.minTerms, ed.maxTerms); //Брой на скобите, които ще се добавят
    for(int i = 0; i < cTerms; i++)
    {
        result.addTerm(ed.maxTermPower,rnGenerator);
    }

    result.condenseFree();
    //Прави уравнението по-красиво
    result.balance();

    return result;
}

Equation Generator::generateEquation(EquationDescriptor ed, RNJ &rnj) {
    Equation result;
    result.create(ed, rnGenerator); //Уравнение без украшения

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
    result.create(id);

    int cTerms = rnGenerator.nextInt(id.minTerms, id.maxTerms);
    for(int i = 0; i < cTerms; i++)
    {
        result.addTerm(rnGenerator.nextInt(1, id.maxTermPower));
    }

    return result;
}
