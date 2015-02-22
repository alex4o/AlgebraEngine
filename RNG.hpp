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
	#include <iostream>
#else
		
#endif



using namespace std;

class RNJ
{
private:

public:

	void init();


	RNJ();

	bool nextBool();

	int nextInt(int low, int high);

    Number nextNumber(CoefDescriptor& cd);

    Number nextNumber(RootDescriptor& rd);
};

#endif
