#ifndef RNG
#define RNG




#include "Number.hpp"
#include "CoefDescriptor.hpp"
#include "RootDescriptor.hpp"

#ifdef linux
	#include <random>


#elif _WIN32
	#include <ctime>
	#include <stdlib.h>

#else
		
#endif



using namespace std;

class RNJ
{
private:

#ifdef linux
	std::random_device rd("/dev/urandom");
#endif

public:

	void init()
	{
	#ifdef _WIN32
		srand(time(0));
	#endif
	}


	RNJ()
	{
		#ifdef linux

		#elif _WIN32
			init();
		#else
		
		#endif
		
	}

	bool nextBool()
	{
		#ifdef linux
			std::uniform_int_distribution<int> dist(0,1);
			return dist(this.rd);
		#elif _WIN32
			return rand()%2;
		#else

		#endif
	}

	int nextInt(int low, int high)
	{
		#ifdef linux
			std::uniform_int_distribution<int> dist(low,high);
			return dist(this.rd);
		#elif _WIN32
			return rand()%(high-low+1) + low;
		#else
		
		#endif

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

    Number nextNumber(RootDescriptor& rd)
    {
        int r = nextInt(1, 100);
        int sign = 1;
        int r2 = nextInt(1, 100);
        if(r2<=rd.pNegative) sign = -1;

        if(r<=rd.pNatural)
        {
            return Number(sign*nextInt(rd.upLow, rd.upHigh));
        }
        else if(r>rd.pNatural and r<= rd.pFraction)
        {
            return Number(sign*nextInt(rd.upLow, rd.upHigh), nextInt(rd.downLow, rd.downHigh));
        }
        else
        {
            return Number();
        }
    }
};

#endif
