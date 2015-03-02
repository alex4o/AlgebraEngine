#include "Polynomial.hpp"
#include "Debug.hpp"

using namespace std;

Polynomial operator+(const Polynomial &p1, const Polynomial &p2)
{
    //cout<<"\t[Sum]\n";
    int pow = 0;
    std::vector<Monomial> v;

    int lim1 = p1.monos.size();
    int lim2 = p2.monos.size();
    int idx1 = 0, idx2 = 0;

    while(idx1<lim1 or idx2<lim2)
    {

        if(idx1<lim1)
        {
            if(idx2<lim2)
            {
                if(p1.monos[idx1]==p2.monos[idx2])
                {
                    //cout<<"\t\t same elements at "<<idx1<<" and "<<idx2;
                    Number nc = p1.monos[idx1].coef + p2.monos[idx2].coef;

                    Number n1 = p1.monos[idx1].coef;
                    Number n2 = p2.monos[idx2].coef;


                    //cout<<" -> "<<n1.fraction.up<<"/"<<n1.fraction.down<<" + "<<n2.fraction.up<<"/"<<n2.fraction.down<<" = "<<nc.fraction.up<<"/"<<nc.fraction.down;
                    if(nc.null==false)
                    {
                        Monomial c(nc, p1.monos[idx1].simples);
                        v.push_back(c);
                        //cout<<" - added\n";
                    }
                    idx1++;
                    idx2++;
                }

                if(idx2<lim2)
                {
                    while(p1.monos[idx1]>p2.monos[idx2] and idx1<lim1)
                    {
                        //cout<<"\t\t added "<<idx1<<" from first"<<endl;
                        v.push_back(p1.monos[idx1]);
                        idx1++;
                    }
                }
                else while(idx1<lim1)
                    {
                        //cout<<"\t\t added "<<idx1<<" from first"<<endl;
                        v.push_back(p1.monos[idx1++]);
                    }

                if(idx1<lim1)
                {
                    while(p2.monos[idx2]>p1.monos[idx1] and idx2<lim2)
                    {
                        //cout<<"\t\t added "<<idx2<<" from second"<<endl;
                        v.push_back(p2.monos[idx2]);
                        idx2++;
                    }
                } else while(idx2<lim2)
                    {
                        //cout<<"\t\t added "<<idx2<<" from second"<<endl;
                        v.push_back(p2.monos[idx2++]);
                    }

            }
            else
            {
                while(idx1<lim1)
                {
                    //cout<<"\t\t added "<<idx1<<" from first"<<endl;
                    v.push_back(p1.monos[idx1++]);
                }
            }
        }
        else
        {
            while(idx2<lim2)
            {
                //cout<<"\t\t added "<<idx2<<" from second"<<endl;
                v.push_back(p2.monos[idx2++]);
            }
        }
    }

    Polynomial result(v, v[0].totalPower);

    return result;
}

Polynomial multByMono(const Polynomial &p, const Monomial &m)
{
    std::vector<Monomial> v;
    for(int i = 0 ; i < p.monos.size(); i++)
    {
        v.push_back(p.monos[i]*m);
    }

    return Polynomial(v);
}

Polynomial operator*(const Polynomial &p1, const Polynomial &p2)
{
    /*cout<<"[Mult]Operands: ";
    p1.print();
    cout<<" and ";
    p2.print();
    cout<<endl;*/

    Polynomial result = multByMono(p1, p2.monos[0]);
    /*cout<<"\t Single mult(first): ";
    result.print();
    cout<<endl;*/
    for(int i = 1; i < p2.monos.size(); i++)
    {
        /*cout<<"\t Singe mult: ";
        Polynomial t = multByMono(p1, p2.monos[i]);
        t.print();
        cout<<endl;*/

        result = result+multByMono(p1, p2.monos[i]);
    }

    /*cout<<"Result: ";
    result.print();
    cout<<endl;*/

    return result;
}

Polynomial pow(Polynomial p, int num)
{
    Polynomial result(Number(1));
    Polynomial tmp = p;

    int idx = 1;
    while(idx<=num)
    {
        if(num&idx)  result = result*tmp;
        idx<<=1;
        tmp = tmp*tmp;
    }

    return result;
}

Polynomial pow(Polynomial p, Number num)
{
    if(num.isNatural()) return pow(p, num.fraction.up);
    else return Polynomial();
}

void Polynomial::negate() {
    for(int i = 0; i < monos.size(); i++)
    {
        monos[i].coef*=-1;
    }
}

void Polynomial::clear() {
    monos.clear();
    totalPower=0;
}

void Polynomial::multByNumber(Number &n) {
    for(int i = 0; i < monos.size(); i++)
    {
        monos[i].coef*=n;
    }
}
