#ifndef RNG
#define RNG

#include <ctime>
#include <stdlib.h>
#include "Number.hpp"
#include "CoefDescriptor.hpp"

using namespace std;

class RNJ
{

public:
    void init()
    {
        srand(time(0));
    }


    RNJ()
    {
        init();
    }

    bool nextBool()
    {
        return rand()%2;
    }

    int nextInt(int low, int high)
    {
        return rand()%(high-low+1) + low;
    }

    Number nextNumber(CoefDescriptor& cd)
    {
        int r = nextInt(1, 100);
        int sign = 1;
        int r2 = nextInt(1, 100);
        if(r2<=cd.pNegative) sign = -1;

        if(r<=cd.pNatural)
        {
            return Number(sign*nextInt(cd.upLow, cd.upHigh));
        }
        else if(r>cd.pNatural and r<= cd.pRational)
        {
            return Number(sign*nextInt(cd.upLow, cd.upHigh), nextInt(cd.downLow, cd.downHigh));
        }
        else
        {
            return Number();
        }
    }
};

#endif