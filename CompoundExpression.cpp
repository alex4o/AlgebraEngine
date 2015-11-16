#include "CompoundExpression.h"

char Node::getSign()
{
	if(type&(1 << 7)) return '-';
	return '+';
}

void Node::print(bool isFirst, stringstream& ss)
{
	char trigTest = type&trigMask;
	if (trigTest >= fsin && trigMask <= fcotg)
	{
		ss << fLookUp[trigMask] << "(";
		if (nChildren == 0) ss << "error) ";
		else children[0]->print(false, ss);
		return;
	}

	char t = type&typeMask;
	if (t == letter)
	{
		if (isFirst)
		{
			power->print(true, false, ss);
			ss << letterLookUp[nChildren];
		}
		else
		{
			ss << power->getSign() << " ";
			power->print(true, true, ss);
			ss << letterLookUp[nChildren];
		}
	}
	if (t == polynomial)
	{
		if (power->isNatural)
		{
			if(power->fraction.up==1)poly->print(ss, !isFirst);
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
			children[0]->print(false, ss);
			ss << "/";
			children[1]->print(false, ss);
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
				children[i]->print(false, ss);
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
				children[i]->print(i==0, ss);
				if (i < nChildren - 1) ss << " " << children[i+1]->getSign() <<" ";
			}
		}
	}
	else if (t == flog)
	{
		if (nChildren < 2) ss << "log(error, error)";
		ss << fLookUp[flog] << "(";
		children[0]->print(true, ss);
		ss << ", ";
		children[1]->print(true, ss);
		ss << ") ";
	}
	else if (t == fpower)
	{
		if (nChildren < 2) ss << "error^error";
		else
		{
			children[0]->print(isFirst, ss);
			ss << "^(";
			children[1]->print(true, ss);
			ss << ")";
		}
	}
}

void CompoundExpression::print(stringstream& ss)
{
	for (int i = 0; i < nNodes; i++)
	{
		nodes[i]->print(i == 0, ss);
		if (i < nNodes - 1) ss << " " + nodes[i + 1]->getSign()<<" ";
	}
}

void CompoundExpression::resize()
{
	Node** newArr = new Node*[capacity * 2];
	for (int i = 0; i < capacity; i++) newArr[i] = nodes[i];
	capacity *= 2;

	Node** old = nodes;
	nodes = newArr;
	delete old;
}

Node* CompoundExpression::findNodeForSum(Node* start)
{
	char t = start->type&typeMask;
	if (t == polynomial) return start;
	if (t == sum)
	{
		int lim = start->nChildren;
		for (int i = 0; i < lim; i++) findNodeForSum(start->children[i]);
	}
}

void CompoundExpression::addNode(Node* node, bool calc)
{
	if (!calc)
	{
		if (nNodes == capacity) resize();
		nodes[nNodes++] = node;
		return;
	}


}