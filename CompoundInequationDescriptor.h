#ifndef CInDesc
#define CInDesc

#include "RootDescriptor.hpp"
#include "CoefDescriptor.hpp"


struct CompoundInequationDescriptor
{
	CoefDescriptor cf, transformCF;
	RootDescriptor rd;
	char letter;
	int power;
	int maxVisualPower;
	int minTrans, maxTrans;
};

#endif