#ifndef Simple_h
#define Simple_h

#include <string>


bool isNumeric(char c);

class Simple //Клас за "прост" едночлен, например х2 или у3
{
public:

    char letter;
    int pow;

    Simple(char c, int p);

    Simple(std::string s, int* idx);

	bool equals(Simple& si)
	{
		return letter == si.letter && pow == si.pow;
	}
};

bool cmpSimple(Simple s1, Simple s2);
#endif