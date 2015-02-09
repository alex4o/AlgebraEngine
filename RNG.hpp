#ifndef RNG
#define RNG




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
};

#endif