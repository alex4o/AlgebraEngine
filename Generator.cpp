#include "Generator.hpp"


using namespace std;

int Generator::rng(int low, int high)
{
     std::uniform_int_distribution<int> d(low, high);
     return d(this->rand_dev);

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