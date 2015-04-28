//
// Created by Kosyo on 27.4.2015 ã..
//

#ifndef ALGEBRAENGINE_INEQUATIONDESCRIPTOR_HPP
#define ALGEBRAENGINE_INEQUATIONDESCRIPTOR_HPP

#include "CoefDescriptor.hpp"
#include "RootDescriptor.hpp"

class InequationDescriptor
{
public:
    CoefDescriptor cf, transformCF;
    RootDescriptor rd;
    char letter;
    bool nice;
    int minTerms, maxTerms;
};

#endif //ALGEBRAENGINE_INEQUATIONDESCRIPTOR_HPP
