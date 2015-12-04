#ifndef SPoly
#define SPoly

#include "Number.hpp"
#include <iostream>


using namespace std;

#define MAXPOW 21

class SPolynomial
{ //���� � ���� �� ������� �� ���� ���� �����
public: //�� ���� �� �� �������� �� ���� ���� ����� Polynomial, �� �� ������ �� ���� � ��-����
    Number coef[MAXPOW]; //����� �� ����� ��-������� �� ��������� �� ���������, ��������.
    char letter; //������� �����, ������ i-���� ������� �������� ����������
    int power; //����� ������������ �� i-�� ������

    SPolynomial()
    {
        power=0;
        letter='x'; //�� ��������� �� default ������� � �
        coef[0]=0;
    }

    SPolynomial(char _letter)
    {
        letter=_letter;
        power=0;
        coef[0]=0;
    }

    void normalize()
    {
        while(coef[power]==0) power--; //�������� �� �������� ������� ������� �� �� 0
    }

    SPolynomial operator+(const SPolynomial& sp)
    { //���� ������� �� �������� ����
        SPolynomial n;
        int max = power;
        if(sp.power>power) max=sp.power;
        n.power=max;
        for(int i = 0; i <= power; i++) n.coef[i]+=coef[i];
        for(int i = 0; i <= sp.power; i++) n.coef[i]+=sp.coef[i];
        n.normalize();
        return n;
    }

    SPolynomial operator-(const SPolynomial& sp)
    { //���������� �� �������
        SPolynomial n;
        int max = power;
        if(sp.power>power) max=sp.power;
        n.power=max;
        for(int i = 0; i <= power; i++) n.coef[i]+=coef[i];
        for(int i = 0; i <= sp.power; i++) n.coef[i]-=sp.coef[i];
        n.normalize();
        return n;
    }

    SPolynomial operator*(const SPolynomial& sp)
    { //������� �� ���������, ���������� �� ���� �� Polynomial
        SPolynomial result; //�� ��-������ � �����
        result.power = power+sp.power;
        for(int i = 0; i <= power; i++)
        {
            for(int j = 0; j <= sp.power; j++)
            {
                result.coef[i+j]+=coef[i]*sp.coef[j];
            }
        }
        return result;
    }

    void operator*=(const SPolynomial& sp)
    { //���������� �� �������, �� ������ SPolynomial �� ��������
        Number oldCoef[MAXPOW];
        int oldPower=power;
        for(int i = 0; i <= oldPower; i++)
        {
            oldCoef[i]=coef[i];
        }

        power+=sp.power;
        for(int i = 0; i <= power; i++) coef[i]=0;

        for(int i = 0; i <= oldPower; i++)
        {
            for(int j = 0; j <=sp.power; j++)
            {
                coef[i+j]+=oldCoef[i]*sp.coef[j];
            }
        }
    }

    void print(stringstream& ss)
    { //������ �� �� debug
        for(int i = 0; i <= power; i++)
        {
            coef[i].print(false, false, ss);
            ss<<' ';
        }
    }

    Polynomial toPolynomial()
    { //����� ��������������� �� SPolynomial ��� Polynomial
        Polynomial result;

        for(int i = power; i > 0; i--)
        {
            if(coef[i]==0) continue;
            result.monos.push_back(Monomial(coef[i], letter, i));
            result.totalPower=power;
        }
        if(coef[0]!=0)result.monos.push_back(Monomial(coef[0]));
        return result;
    }
};

#endif