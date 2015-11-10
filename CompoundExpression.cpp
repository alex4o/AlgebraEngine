#include "CompoundExpression.h"

void Node::print(bool isFirst, stringstream& ss)
{
	char trigTest = type&trigMask;
	if (trigTest >= fsin && trigMask <= fcotg)
	{
		ss << fLookUp[trigMask] << "(";
		if (nChildren == 0) ss << "error) ";
		else children[0].print(false, ss);
		return;
	}

	char t = type&typeMask;
	if (t == polynomial)
	{
		if (power->isNatural)
		{
			if(power->fraction.up==1)poly->print(ss, isFirst);
			else
			{
				ss << "(";
				poly->print(ss, false);
				ss << ")^" << power->fraction.up;
			}
		}
		else
		{
			ss << "root(";
			poly->print(ss, false);
			ss << ")";
			if (power->fraction.up > 1) ss << "^" << power->fraction.up;
		}
		
	}
	else if (t == fraction)
	{
		if (nChildren < 2) ss << "error/error";
		else
		{
			children[0].print(false, ss);
			ss << "/";
			children[1].print(false, ss);
		}
	}
	else if (t == product)
	{
		if (nChildren < 2) ss << "error*error";
		else
		{
			for (int i = 0; i < nChildren; i++)
			{
				ss << "(";
				children[i].print(false, ss);
				ss << ")";
				if (i < nChildren - 1) ss << "*";
			}
		}
	}
	else if (t == sum)
	{
		if (nChildren < 2) ss << "error + error";
		else
		{
			for (int i = 0; i < nChildren; i++)
			{
				children[i].print(i==0, ss);
				if (i < nChildren - 1) ss << " + ";
			}
		}
	}
	else if (t == flog)
	{
		if (nChildren < 2) ss << "log(error, error)";
		ss << fLookUp[flog] << "(";
		children[0].print(true, ss);
		ss << ", ";
		children[1].print(true, ss);
		ss << ") ";
	}
	else if (t == fpower)
	{
		if (nChildren < 2) ss << "error^error";
		else
		{
			children[0].print(isFirst, ss);
			ss << "^(";
			children[1].print(true, ss);
			ss << ")";
		}
	}
}