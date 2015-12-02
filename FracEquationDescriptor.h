#ifndef FEQDescriptor
#define FEQDescriptor

#include "RootDescriptor.hpp"
#include "CoefDescriptor.hpp"

struct FracEquationDescriptor
{
	int power;// за сега ще е 2
	int maxVisualPower;
	int minTransformations;
	int maxTransformations;
	char letter;
	char genType; // 0 - гадно, 1 - по-малко гадно
	RootDescriptor rd; // корени
	CoefDescriptor bvd; // bad value descriptor
	CoefDescriptor cf; // за украшения
	//bool nice; не се използва за момента
};

#endif