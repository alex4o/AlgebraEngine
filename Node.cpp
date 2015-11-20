#include "Node.h"

Node::Node(char t)
{
	type = t;
	nChildren = 0;
	poly = 0;
	power = 0;
	if (t == sum || t == product)
	{
		children = new Node*[initialNodeCapacity];
		capacity = initialNodeCapacity;
	}
	if (t == polynomial || t == letter)
	{
		children = 0;
		capacity = 0;
	}
	if (t == fraction || t == fpower || t == flog || (t >= fsin && t <= fcotg) || (t >= fsind && t <= fcotgd))
	{
		children = new Node*[2];
		capacity = 2;
	}
}

Node::Node(Polynomial* p)
{
	type = polynomial;
	if (p->isNegative()) type &= 1 << 7;
	poly = p;
	
	nChildren = 0;
	children = 0;

	power = new Number(1);
}

Node::Node(Polynomial* p, Number& pow, bool isNegative)
{
	type = polynomial;
	if (isNegative) type &= 1 << 7;
	poly = p;

	nChildren = 0;
	children = 0;

	power = new Number(pow);
}

char Node::getType()
{
	return type&typeMask;
}

char Node::getSign()
{
	if (type&(1 << 7)) return '-';
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

	char t = getType();
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
			if (power->fraction.up == 1)poly->print(ss, !isFirst);
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
				children[i]->print(i == 0, ss);
				if (i < nChildren - 1) ss << " " << children[i + 1]->getSign() << " ";
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

void Node::resize()
{
	Node** newArr = new Node*[capacity * 2];
	for (int i = 0; i < capacity; i++) newArr[i] = children[i];
	capacity *= 2;

	Node** old = children;
	children = newArr;
	delete old;
}

void Node::resize(int newSize)
{
	Node** newArr = new Node*[newSize];
	for (int i = 0; i < nChildren; i++) newArr[i] = children[i];
	capacity = newSize;

	Node** old = children;
	children = newArr;
	delete old;
}

void Node::flipChildren()
{
	if (nChildren != 2) return;
	Node* tmp = children[0];
	children[0] = children[1];
	children[1] = tmp;
}

void mult(Node* &dest, Node* src, bool compact) // dest = dest*src
{												// dest - �������, ����� ����� ��������� ����������. ���� �� ���� ��� ����� ���� ����������
	if (compact)								// src - ������� �����������. �� �� �������
	{											// compact - ���� �� ������ �������� 1 �������(��� � ��������)
		if (dest->getType() == product)
		{
			if (src->getType() == product) // � ����� ����� �� ������������, ������ ������ ���������� ������
			{// �� �� ����� ������
				int spaceNeeded = src->nChildren - dest->capacity + dest->nChildren;
				if (spaceNeeded > 0) dest->resize(dest->capacity + spaceNeeded);
				for (int i = 0; i < src->nChildren; i++)
				{
					dest->children[dest->nChildren + i] = src->children[i];
				}
				dest->nChildren += src->nChildren;
			}
			else if (src->getType() == fraction) // ���������� � ����, ������ ������� ����
			{// ��� �������� ������� ������, �� �������� ������ 1 �������
				Node* newNode = new Node(fraction);
				newNode->children[0] = dest; // ���������� ���������
				newNode->children[1] = src->children[1]; // � �����������(��� �� �� �������)
				mult(newNode->children[0], src->children[0], true); // ���������� ����� ���������

				if (dest->getSign != src->getSign()) newNode->type |= 1 << 7; //�������� �������
				dest = newNode;
				return; //���� ������ �� ����� � �� ������� ��������� �� �����
			}
			else // ���������� ����� �� ������� src � ������ �� ��������������
			{ //�� ������� ������
				if (dest->capacity > dest->nChildren) dest->children[(dest->nChildren)++] = src; //�������� �� �����
				else
				{
					dest->resize(dest->capacity + 1);
					dest->children[(dest->nChildren)++] = src;
				}
			}

			if (dest->getSign() != src->getSign()) dest->type |= 1 << 7; //�������
		}
		else if (dest->getType() == fraction)
		{
			if (src->getType() == fraction) //��� � ����� �� �����, ���������� �� ����������� � �������������
			{
				mult(dest->children[0], src->children[0], true);
				mult(dest->children[1], src->children[1], true);
			}
			else mult(dest->children[0], src, true); // ����� ������ ���������� ���������

			if (dest->getSign() != src->getSign()) dest->type |= 1 << 7;
		}
		else if (src->getType() == product || src->getType == fraction)
		{ // ��� src � "��-�����" �� dest, ������ �� �������
			Node* old = dest;
			dest = src;
			mult(dest, old, true);
		}
	}

	Node* newNode = new Node(product);  // ����� ������
	newNode->children[0] = src;			// ������ �� ���� ����� �� ������������
	newNode->children[1] = dest;		// � ��� �� ��������� ����� ���������
	dest = newNode;						// ������ ����� �������� dest

	if (dest->children[0]->getSign != dest->children[1]->getSign) dest->type |= 1 << 7;	
}

void div(Node* &dest, Node* src, bool compact)
{
	if (compact)
	{
		if (dest->getType() == fraction)
		{
			if (src->getType() == fraction)
			{
				mult(dest->children[0], src->children[1], true);
				mult(dest->children[1], src->children[0], true);
			} else	mult(dest->children[1], src, compact);

			if (dest->getSign() != src->getSign()) dest->type |= 1 << 7;
		}
	}
	
	Node* newNode = new Node(fraction);
	newNode->children[0] = dest;
	newNode->children[1] = src;
	if (dest->getSign() != src->getSign()) newNode->type |= 1 << 7;
	dest = newNode;
}

void divRec(Node* &dest, Node* src, bool compact)
{
	if (compact)
	{
		if (dest->getType() == fraction)
		{
			dest->flipChildren();
			mult(dest, src, true);
		}
	}	

	Node* newNode = new Node(fraction);
	newNode->children[0] = src;
	newNode->children[1] = dest;
	if (src->getSign() != dest->getType()) newNode->type |= 1 << 7;

	dest = newNode;
}