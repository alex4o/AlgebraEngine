#ifndef CoefDescriptorH
#define CoefDescriptorH

struct CoefDescriptor
{
    int pNatural;
    int pRational;
    int pIrational;

	int pNegative;

    int upLow, upHigh, downLow, downHigh;
};

#endif