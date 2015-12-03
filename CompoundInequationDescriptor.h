#ifndef CInDesc
#define CInDesc

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