#ifndef RNG
#define RNG

#include "Number.hpp"
#include "CoefDescriptor.hpp"
#include "RootDescriptor.hpp"
#include "Expression.hpp"
#include <stdlib.h>
#include <string.h>


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

	Term nextTerm(CoefDescriptor& cd, int maxPower, char letter, bool nice, char l);
};

void createListOfInts(int* array, int size, int sum, RNJ* jesus);


#endif
