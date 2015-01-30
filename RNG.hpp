#ifndef RNG
#define RNG

#include <ctime>
#include <stdlib.h>

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
};

#endif