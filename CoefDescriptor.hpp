#ifndef CoefDescriptorH
#define CoefDescriptorH

struct CoefDescriptor
{
    int pNatural;
    int pRational;
    int pIrational;

    int upLow, upHigh, downLow, downHigh;

	int pNegative;
};

#endif