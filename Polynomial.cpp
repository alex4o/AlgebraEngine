#include "Polynomial.hpp"

Polynomial operator+(const Polynomial &p1, const Polynomial &p2)
{

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
                    Number nc = p1.monos[idx1].coef + p2.monos[idx2].coef;
                    if(nc.null==false)
                    {
                        Monomial c(nc, p1.monos[idx1].simples);
                        v.push_back(c);
                    }
                    idx1++;
                    idx2++;
                }

                if(idx2<lim2)
                {
                    while(p1.monos[idx1]>p2.monos[idx2] and idx1<lim1)
                    {
                        v.push_back(p1.monos[idx1]);
                        idx1++;
                    }
                }
                else while(idx1<lim1) v.push_back(p1.monos[idx1++]);

                if(idx1<lim1)
                {
                    while(p2.monos[idx2]>p1.monos[idx1] and idx2<lim2)
                    {
                        v.push_back(p2.monos[idx2]);
                        idx2++;
                    }
                } else while(idx2<lim2) v.push_back(p2.monos[idx2++]);

            }
            else
            {
                while(idx1<lim1) v.push_back(p1.monos[idx1++]);
            }
        }
        else
        {
            while(idx2<lim2) v.push_back(p2.monos[idx2++]);
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



    Polynomial result = multByMono(p1, p2.monos[0]);
    for(int i = 1; i < p2.monos.size(); i++)
    {
        result = result+multByMono(p1, p2.monos[i]);
    }

    return result;
}