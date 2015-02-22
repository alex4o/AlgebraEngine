#ifndef RNG
#define RNG




#include "Number.hpp"
#include "CoefDescriptor.hpp"
#include "RootDescriptor.hpp"
#include <stdlib.h>


#ifdef __linux__
	#include <iostream>
	#include <sys/time.h>


#elif _WIN32
	#include <ctime>

#else
		
#endif



using namespace std;

class RNJ
{
private:

public:

	void init()
	{

	#ifdef __linux__
		timeval time_seed;
		gettimeofday(&time_seed, NULL);
		srand(time_seed.tv_usec + time_seed.tv_sec);
		std::cout<<"init rand\n";

	#elif _WIN32
		srand(time(0));
	#endif
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

		if(low > high){
			std::cout<<low<<" > "<<high<<"\n";
			return 0;
		}
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
