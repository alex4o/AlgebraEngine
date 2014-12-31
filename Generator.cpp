#include "Generator.hpp"


using namespace std;

int rng(int low, int high, std::random_device *rd)
{
     std::uniform_int_distribution<int> d(low, high);
     return d(*rd);

}

Number gen(RootDescriptor &rd, char t,std::random_device *rand_dev)
{
    int sign = -1;
    if(rand()%2) sign=1;

    if(t=='n')
    {
        return Number(rng(sign*rd.upLow, rd.upHigh,rand_dev));
    }
    if(t=='f')
    {
        return Number(rng(sign*rd.upLow, rd.upHigh,rand_dev), rng(rd.downLow, rd.downHigh,rand_dev));
    }
    return Number(0);
}

Polynomial generate(int power, RootDescriptor rd, char letter,std::random_device *rand_dev)
{
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

    if(rd.pNatural>0)
    {
        last++;
        type[last]='n';
        rem[last]=(rd.pNatural*power)/100+1;
    }
    if(rd.pFraction>0)
    {
        last++;
        type[last]='f';
        rem[last]=(rd.pFraction*power)/100+1;
    }
    if(rd.pIrational>0)
    {
        last++;
        type[last]='i';
        rem[last]=(rd.pIrational*power)/100+1;
    }


    for(int i = 0; i < power; i++)
    {
        int r = rng(0, last,rand_dev);
        char t = type[r];

        rem[r]--;
        if(rem[r]<=0)
        {
            rem[r]=rem[last];
            type[r]=type[last];
            last--;
        }

        Number nc = gen(rd, t,rand_dev);
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