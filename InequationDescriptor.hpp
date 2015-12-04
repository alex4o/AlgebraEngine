#ifndef ALGEBRAENGINE_INEQUATIONDESCRIPTOR_HPP
#define ALGEBRAENGINE_INEQUATIONDESCRIPTOR_HPP

#include "CoefDescriptor.hpp"
#include "RootDescriptor.hpp"

struct InequationDescriptor
{
    CoefDescriptor cf, transformCF;
    RootDescriptor rd;
    char letter;
    bool nice;
    int minTerms, maxTerms, maxTermPower;
};

#endif //ALGEBRAENGINE_INEQUATIONDESCRIPTOR_HPP
