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
	if (p->isNegative()) type &= 1 << 6;
	poly = p;
	
	nChildren = 0;
	children = 0;

	power = new Number(1);
}

Node::Node(Polynomial* p, Number& pow, bool isNegative)
{
	type = polynomial;
	if (isNegative) type &= 6 << 7;
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

char Node::getVisualSign()
{
	if (getType() == polynomial)
	{
		if (getSign() == '-') return '-';
		else if (type&(1 << 6)) return '-';
		else return '+';
	}
	return getSign();
}

void Node::print(bool isFirst, bool attachSign, stringstream& ss)
{
	printArr[type&typeMask](this, isFirst, attachSign, ss);
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
{												// dest - звеното, върху което прилагаме операци€та. ћоже да сочи към друго след операци€та
	if (compact)								// src - звеното модификатор. Ќе се промен€
	{											// compact - дали да остане визуално 1 елемент(ако е възможно)
		if (dest->getType() == product)
		{
			if (src->getType() == product) // и двете звена са произведени€, затова просто преписваме децата
			{// не се смен€ корена
				int spaceNeeded = src->nChildren - dest->capacity + dest->nChildren;
				if (spaceNeeded > 0) dest->resize(dest->capacity + spaceNeeded);
				for (int i = 0; i < src->nChildren; i++)
				{
					dest->children[dest->nChildren + i] = src->children[i];
				}
				dest->nChildren += src->nChildren;
			}
			else if (src->getType() == fraction) // умножаваме с дроб, затова смен€ме типа
			{// тук всъщност смен€ме корена, но визуално остава 1 елемент
				Node* newNode = new Node(fraction);
				newNode->children[0] = dest; // преписваме числител€
				newNode->children[1] = src->children[1]; // и знаменател€(той не се промен€)
				mult(newNode->children[0], src->children[0], true); // умножаваме двата числител€

				if (dest->getSign != src->getSign()) newNode->type |= 1 << 7; //оправ€ме знаците
				dest = newNode;
				return; //н€ма смисъл да отива и на другата процедура за знаци
			}
			else // единствено можем да добавим src в масива на произведението
			{ //не смен€ме корене
				if (dest->capacity > dest->nChildren) dest->children[(dest->nChildren)++] = src; //проверки за м€сто
				else
				{
					dest->resize(dest->capacity + 1);
					dest->children[(dest->nChildren)++] = src;
				}
			}

			if (dest->getSign() != src->getSign()) dest->type |= 1 << 7; //знаците
		}
		else if (dest->getType() == fraction)
		{
			if (src->getType() == fraction) //ако и двете са дроби, умножаваме им числителите и знаменателите
			{
				mult(dest->children[0], src->children[0], true);
				mult(dest->children[1], src->children[1], true);
			}
			else mult(dest->children[0], src, true); // иначе просто умножаваме числител€

			if (dest->getSign() != src->getSign()) dest->type |= 1 << 7;
		}
		else if (src->getType() == product || src->getType == fraction)
		{ // ако src е "по-хубав" от dest, просто ги смен€ме
			Node* old = dest;
			dest = src;
			mult(dest, old, true);
		}
	}

	Node* newNode = new Node(product);  // общи€ случай
	newNode->children[0] = src;			// правим си ново звено за произведение
	newNode->children[1] = dest;		// и там си записваме двата аргумента
	dest = newNode;						// новото звено измества dest

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

void add(Node* &dest, Node* src, bool compact)
{
	if (compact)
	{
		if (src->getType() == sum) // и двете звена са суми, затова просто преписваме децата
		{// не се смен€ корена
			int spaceNeeded = src->nChildren - dest->capacity + dest->nChildren;
			if (spaceNeeded > 0) dest->resize(dest->capacity + spaceNeeded);
			for (int i = 0; i < src->nChildren; i++)
			{
				dest->children[dest->nChildren + i] = src->children[i];
			}
			dest->nChildren += src->nChildren;
		}
	}

	Node* newNode = new Node(sum);
	newNode->children[0] = dest;
	newNode->children[1] = src;
	dest = newNode;
}