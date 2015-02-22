#include "RNG.hpp"


	void RNJ::init()
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


	 RNJ::RNJ()
	{
		init();		
	}

	bool  RNJ::nextBool()
	{
		return rand()%2;
	}

	int  RNJ::nextInt(int low, int high)
	{

		if(low > high){
			std::cout<<low<<" > "<<high<<"\n";
			return 0;
		}
			return rand()%(high-low+1) + low;
	}

    Number  RNJ::nextNumber(CoefDescriptor& cd)
    {
        int r = nextInt(1, 100);
        int sign = 1;
        int r2 = nextInt(1, 100);
        if(r2<=cd.pNegative) sign = -1;

        if(r<=cd.pNatural)
        {
            return Number(sign*nextInt(cd.upLow, cd.upHigh));
        }
        else if(r>cd.pNatural and r<= cd.pRational + cd.pNatural)
        {
            return Number(sign*nextInt(cd.upLow, cd.upHigh), nextInt(cd.downLow, cd.downHigh));
        }
        else
        {
            return Number();
        }
    }

    Number  RNJ::nextNumber(RootDescriptor& rd)
    {
        int r = nextInt(1, 100);
        int sign = 1;
        int r2 = nextInt(1, 100);
        if(r2<=rd.pNegative) sign = -1;

        if(r<=rd.pNatural)
        {
            return Number(sign*nextInt(rd.upLow, rd.upHigh));
        }
        else if(r>rd.pNatural and r<= rd.pFraction + rd.pNatural)
        {
            return Number(sign*nextInt(rd.upLow, rd.upHigh), nextInt(rd.downLow, rd.downHigh));
        }
        else
        {
            return Number();
        }
    }
