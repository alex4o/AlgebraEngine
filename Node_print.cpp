#include "Node.h"

void initPrintFunctions()
{
	printArr[letter] = printLetter;
	printArr[polynomial] = printPoly;
	printArr[product] = printProduct;
	printArr[fraction] = printFraction;
	printArr[sum] = printSum;
	printArr[fpower] = printPower;
	printArr[flog] = printLog;
	for (int i = fsin; i <= fcotg; i++)
	{
		printArr[i] = printTrig;
		printArr[i + 16] = printTrig;
	}
}

void printLetter(Node* node, bool isFirst, bool attachSign, stringstream& ss)
{
	if (attachSign)
	{
		if (!isFirst) ss<<" " << node->getVisualSign() << " ";
		else if (node->getVisualSign() == '-') ss << " - ";
	}	

	node->power->print(true, attachSign, ss);
	ss << letterLookUp[node->nChildren];
}

void printPoly(Node* node, bool isFirst, bool attachSign, stringstream& ss)
{
	if (isFirst && attachSign) attachSign = false; // няма как хем да трябва да слепваме и да сме първи

	if (attachSign)
	{
		if (!isFirst) ss << node->getVisualSign() << " ";
		else if (node->getVisualSign() == '-') ss << '-';
	}

	bool flag = node->getSign() == '-' || !(attachSign || isFirst);

	if (node->power->isNatural())
	{
		if (node->power->fraction.up == 1)
		{
			if (node->getSign() == '-' && (attachSign ^ isFirst)) ss << '-';
			if (flag) ss << "(";
			node->poly->print(ss, false);
			if (flag) ss << ")";
		}
		else
		{
			if (node->getSign() == '-' && (attachSign ^ isFirst)) ss << '-';
			ss << "(";
			node->poly->print(ss, false);
			ss << ")^" << node->power->fraction.up;
		}
	}
	else
	{
		if (node->getSign() == '-' && (attachSign ^ isFirst)) ss << '-';
		ss << "root(";
		node->poly->print(ss, false);
		ss << ", " << node->power->fraction.down << ")";
		if (node->power->fraction.up > 1) ss << "^" << node->power->fraction.up;
	}
}

void printProduct(Node* node, bool isFirst, bool attachSign, stringstream& ss)
{
	if (attachSign)
	{
		if (!isFirst) ss << " "<< node->getVisualSign() << " ";
		else if (node->getVisualSign() == '-') ss << " - ";
	}

	if (node->nChildren < 2) ss << "error*error";
	else
	{
		for (int i = 0; i < node->nChildren; i++)
		{
			node->children[i]->print(false, false, ss);
			if (i < node->nChildren - 1) ss << "*";
		}
	}
}

void printFraction(Node* node, bool isFirst, bool attachSign, stringstream& ss)
{
	if (attachSign)
	{
		if (!isFirst) ss << " " << node->getVisualSign() << " ";
		else if (node->getVisualSign() == '-') ss << " - ";
	}

	if (node->nChildren < 2) ss << "error/error";
	else
	{
		node->children[0]->print(true, false, ss);
		ss << "/";
		node->children[1]->print(true, false, ss);
	}
}

void printSum(Node* node, bool isFirst, bool attachSign, stringstream& ss)
{
	if (attachSign)
	{
		if (!isFirst) ss <<" "<< node->getVisualSign() << " ";
		else if (node->getVisualSign() == '-') ss << " - ";
	}
	char sign = node->getSign();

	bool flag = sign == '-' || !attachSign; //дали е в скоби

	if (node->nChildren < 2) ss << "error + error";
	else
	{
		for (int i = 0; i < node->nChildren; i++)
		{
			node->children[i]->print(((isFirst || flag) && i == 0), true, ss);
			//if (i < nChildren - 1) ss << " " << children[i + 1]->getVisualSign() << " ";
		}
	}

	if (flag) ss << ")";
}

void printPower(Node* node, bool isFirst, bool attachSign, stringstream& ss)
{
	if (attachSign)
	{
		if (!isFirst) ss << " " << node->getVisualSign() << " ";
		else if (node->getVisualSign() == '-') ss << " - ";
	}

	if (node->nChildren != 2) ss << "error^error";
	else
	{
		node->children[0]->print(false, false, ss);
		ss << "^(";
		node->children[1]->print(true, false, ss);
		ss << ")";
	}
}

void printLog(Node* node, bool isFirst, bool attachSign, stringstream& ss)
{
	if (attachSign)
	{
		if (!isFirst) ss << " " << node->getVisualSign() << " ";
		else if (node->getVisualSign() == '-') ss << " - ";
	}
	else if (isFirst && node->getSign() == '-') ss << "-";

	if (node->nChildren != 2) ss << "log(error, error)";
	ss << fLookUp[flog] << "(";
	node->children[0]->print(true, false, ss);
	ss << ", ";
	node->children[1]->print(true, false, ss);
	ss << ") ";
}

void printTrig(Node* node, bool isFirst, bool attachSign, stringstream& ss)
{
	if (attachSign)
	{
		if (!isFirst) ss << " " << node->getVisualSign() << " ";
		else if (node->getVisualSign() == '-') ss << " - ";
	}
	else if (isFirst && node->getSign() == '-') ss << "-";

	ss << fLookUp[trigMask];
	if (node->power)
	{
		if (node->power->fraction.up != 1 || node->power->fraction.down != 1)
		{
			ss << "^";
			node->power->print(true, false, ss);
		}
	}
	ss << "(";
	if (node->nChildren == 1) ss << "error";
	else node->children[0]->print(true, false, ss);
	ss << ")";
	return;
}