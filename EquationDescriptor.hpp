#ifndef EquationDesc
#define EquationDesc

#include "RootDescriptor.hpp"

struct EquationDescriptor
{
    int power;
    int maxTermPower;
    int minTerms;
    int maxTerms;
    char letter;
    char type; //0 - power �� ���� ������, 1 - ��� ������, 2 - �������� ������
    RootDescriptor rd;
    CoefDescriptor cd;
    CoefDescriptor transformCF;
    bool nice;
};

#endif