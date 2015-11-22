#include "Node.h"

Node::Node()
{
	type = 0;
	nChildren = 0;
	poly = 0;
	power = 0;
}

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
	if (t == fraction || t == fpower || t == flog)
	{
		children = new Node*[2];
		nChildren = capacity = 2;
	}
	else if ((t >= fsin && t <= fcotg) || (t >= fsind && t <= fcotgd))
	{
		children = new Node*[1];
		nChildren = capacity = 1;
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

Node::Node(Polynomial* p, bool isNegative)
{
	type = polynomial;
	if (isNegative) type |= 1 << 7;
	poly = p;

	nChildren = 0;
	children = 0;

	power = new Number(1);
}

Node::Node(Polynomial* p, Number& pow, bool isNegative)
{
	type = polynomial;
	if (isNegative) type |= 1 << 7;
	poly = p;

	nChildren = 0;
	children = 0;

	power = new Number(pow);
}
/*
Node::~Node()
{
	if(power) delete power;
	if(children) delete children;
}
*/
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

void Node::flipSign()
{
	type ^= 1 << 7;
}

void mult(Node* &dest, Node* src, bool compact) // dest = dest*src
{												// dest - звеното, върху което прилагаме операцията. Може да сочи към друго след операцията
	if (compact)								// src - звеното модификатор. Не се променя
	{											// compact - дали да остане визуално 1 елемент(ако е възможно)
		if (dest->getType() == product)
		{
			if (src->getType() == product) // и двете звена са произведения, затова просто преписваме децата
			{// не се сменя корена
				int spaceNeeded = src->nChildren - dest->capacity + dest->nChildren;
				if (spaceNeeded > 0) dest->resize(dest->capacity + spaceNeeded);
				for (int i = 0; i < src->nChildren; i++)
				{
					dest->children[dest->nChildren + i] = new Node(*(src->children[i]));
				}
				dest->nChildren += src->nChildren;

				if (src->getSign() == '-') dest->flipSign(); //знаците
				return;
			}
			else if (src->getType() == fraction) // умножаваме с дроб, затова сменяме типа
			{// тук всъщност сменяме корена, но визуално остава 1 елемент
				Node* newNode = new Node(fraction);
				newNode->children[0] = dest; // преписваме числителя
				newNode->children[1] = new Node(*(src->children[1])); // и знаменателя(той не се променя)
				mult(newNode->children[0], src->children[0], true); // умножаваме двата числителя

				if (dest->getSign() != src->getSign()) newNode->type |= (char)(1 << 7); //оправяме знаците
				simplifyFractionSign(newNode);
				dest = newNode;
				return; //няма смисъл да отива и на другата процедура за знаци
			}
			else // единствено можем да добавим src в масива на произведението
			{ //не сменяме корене
				if (dest->capacity > dest->nChildren) dest->children[(dest->nChildren)++] = new Node(*src); //проверки за място
				else
				{
					dest->resize(dest->capacity + 1);
					dest->children[(dest->nChildren)++] = src;
				}
			}

			simplifyProductSign(dest);

			return;
		}
		else if (dest->getType() == fraction)
		{
			if (src->getType() == fraction) //ако и двете са дроби, умножаваме им числителите и знаменателите
			{
				mult(dest->children[0], src->children[0], true);
				mult(dest->children[1], src->children[1], true);
			}
			else mult(dest->children[0], src, true); // иначе просто умножаваме числителя

			if (dest->getSign() != src->getSign()) dest->type |= 1 << 7;
			else dest->type = fraction;

			simplifyFractionSign(dest);

			return;
		}
		else if (src->getType() == product || src->getType() == fraction)
		{ // ако src е "по-хубав" от dest, просто ги сменяме
			Node* old = dest;
			dest = new Node(*src);
			mult(dest, old, true);
			return;
		}
	}

	Node* newNode = new Node(product);  // общия случай
	newNode->children[0] = new Node(*src);			// правим си ново звено за произведение
	newNode->children[1] = new Node(*dest);		// и там си записваме двата аргумента
	newNode->nChildren = 2;					
	simplifyProductSign(newNode);
	dest = newNode; // новото звено измества dest
	
}

void divide(Node* &dest, Node* src, bool compact)
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
			else dest->type = fraction;

			dest->type |= ((dest->children[0]->type >> 7) ^ (dest->children[1]->type >> 7))<<7;
			
			simplifyFractionSign(dest);

			return;
		}
	}
	
	Node* newNode = new Node(fraction);
	newNode->children[0] = dest;
	newNode->children[1] = src;
	simplifyFractionSign(newNode);
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
	bool flag = dest->getSign() != src->getSign(); //дали трябва да обръщаме знаците

	if (compact)
	{
		if (src->getType() == sum) // и двете звена са суми, затова просто преписваме децата
		{// не се сменя корена
			int spaceNeeded = src->nChildren - dest->capacity + dest->nChildren;
			if (spaceNeeded > 0) dest->resize(dest->capacity + spaceNeeded);
			for (int i = 0; i < src->nChildren; i++)
			{
				Node* child =  dest->children[dest->nChildren + i] = new Node(*(src->children[i]));
				if (flag) child->flipSign();
			}
			dest->nChildren += src->nChildren;
			return;
		}
	}

	Node* newNode = new Node(sum);
	newNode->children[0] = new Node(*dest);
	newNode->children[1] = new Node(*src);
	//if (flag) newNode->children[1]->flipSign();
	newNode->nChildren = 2;
	dest = newNode;
}

void simplifyProductSign(Node* prod)
{ //може и да променим знака на самото звено
	int* negCompIdx = new int[prod->nChildren]; //отрицателни елемнти, които са съставни(sum, product, fraction)
	int* negSimpIdx = new int[prod->nChildren]; //отрицателни елементи, които са прости(polynomial, power, log, trig, letter)

	int idx1 = 0;
	int idx2 = 0;

	for (int i = 0; i < prod->nChildren; i++)
	{
		Node* current = prod->children[i];
		if (current->getSign() == '-')
		{
			char t = current->getType();
			if (t == sum || t == product || t == fraction)
			{
				if (t == product) simplifyProductSign(current);
				if (t == fraction) simplifyFractionSign(current);

				if(current->type>>7) negCompIdx[idx1++] = i;
			}
			else negSimpIdx[idx2++] = i;
		}
	}

	if (idx2 >= 2)
	{
		for (int i = idx2 - 1; i >= idx2 % 2; i--) prod->children[negSimpIdx[i]]->flipSign();
		idx2 &= 1;
	}

	if (idx1 >= 2)
	{
		for (int i = idx1 - 1; i >= idx1 % 2; i--) prod->children[negCompIdx[i]]->flipSign();
		idx1 &= 1;
	}

	if (idx1 == 0 && idx2 == 0) return;
	if (idx1 && idx2)
	{
		prod->children[negCompIdx[0]]->flipSign();
		prod->children[negSimpIdx[0]]->flipSign();
		idx1 = idx2 = 0;
	}
	else if (idx1)
	{
		prod->children[negCompIdx[0]]->flipSign();
		prod->flipSign();
	}
	else if (idx2)
	{
		prod->children[negSimpIdx[0]]->flipSign();
		prod->flipSign();
	}
	
}

void simplifyFractionSign(Node* frac)
{
	Node* top = frac->children[0];
	Node* bottom = frac->children[1];

	char t_type = top->getType();
	char b_type = bottom->getType();

	int negCnt = 0;

	if (t_type == product) simplifyProductSign(top);
	else if (t_type == fraction) simplifyFractionSign(top);
	if (top->type >> 7) negCnt++;

	if (b_type == product) simplifyProductSign(bottom);
	else if (b_type == fraction) simplifyFractionSign(bottom);
	if (bottom->type >> 7) negCnt++;

	if (negCnt == 0) return;
	if (negCnt == 2)
	{
		top->flipSign();
		bottom->flipSign();
	}
	else if (negCnt == 1)
	{
		if (top->type >> 7) top->flipSign();
		else bottom->flipSign();
		frac->flipSign();
	}
}

void simplifySumSign(Node* s)
{
	int cntNeg = 0;
	for (int i = 0; i < s->nChildren; i++) if (s->children[0]->getSign() == '-') cntNeg++;
	
	if (cntNeg < s->nChildren / 2) return;

	s->flipSign();
	for (int i = 0; i < s->nChildren; i++) s->children[i]->flipSign();
}

bool cmp(Node* n1, Node* n2)
{
	return n1->getType() < n2->getType();
}

void doSumMath(Node* &s, int maxGroupSize)
{
	if (maxGroupSize < 2) return;

	sort(s->children, s->children + s->nChildren, cmp);

	int nPoly = 0;
	int lim = s->nChildren;
	while (nPoly < lim && s->children[nPoly]->getType() == polynomial) nPoly++;

	if (nPoly < 2) return;
	if (maxGroupSize>nPoly) maxGroupSize = nPoly;

	int nNewPoly = nPoly / maxGroupSize + (nPoly%maxGroupSize!=0);
	Polynomial** polys = new Polynomial*[nNewPoly];

	int newSize = s->nChildren - (nPoly - nNewPoly);

	Node** newChildren = new Node*[newSize];

	int cnt = 0; //брой ненулеви полиноми

	for (int i = 0; i < nNewPoly; i++)
	{
		if (i == nNewPoly - 1)
		{
			int start = (nNewPoly - 1)*maxGroupSize; //откъде почват полиномите за последната група

			polys[cnt] = new Polynomial(*(s->children[start]->poly));
			if (s->children[start]->getSign() == '-') polys[cnt]->negate(); //знакова коректност

			for (int j = start + 1; j < nPoly; j++)
			{
				Polynomial tmp = *(s->children[j]->poly);
				if (s->children[j]->getSign() == '-') tmp.negate(); //знакова коректност
				*polys[cnt] = *polys[cnt] + tmp;
			}

			if (polys[cnt]->isZero())
			{
				delete polys[cnt];
				continue;
			}

			bool neg = polys[cnt]->isNegative();
			if (neg) polys[cnt]->negate();

			newChildren[cnt] = new Node(polys[cnt], neg);
			cnt++;
			continue;
		}

		polys[cnt] = new Polynomial(*(s->children[i*maxGroupSize]->poly));
		for (int j = 1; j < maxGroupSize; j++)
		{
			Polynomial tmp = *(s->children[i*maxGroupSize + j]->poly);
			if (s->children[i*maxGroupSize + j]->getSign() == '-') tmp.negate(); //знакова коректност
			*polys[cnt] = *polys[cnt] + tmp;
		}

		if (polys[cnt]->isZero())
		{
			delete polys[cnt];
			continue;
		}

		bool neg = polys[cnt]->isNegative();
		if (neg) polys[cnt]->negate();

		newChildren[cnt] = new Node(polys[cnt], neg);
		cnt++;
	}

	int actualSize = newSize - (nNewPoly - cnt);

	if (actualSize == 0)
	{
		delete s->power;
		delete s->children;
		s->power = 0;
		s->children = 0;

		delete s;
		delete newChildren;
		delete polys;

		Polynomial* p = new Polynomial();
		s = new Node(p);
		return;
	}
	if (actualSize == 1)
	{
		Node* last; //единствения останал елемент
		if (cnt == 0) last = s->children[s->nChildren - 1]; // и той не е полином => е последния елемент от оригиналния масив
		else last = newChildren[0]; // и той е полином => първия елемнт от новия масив

		if (s->getSign() == '-') last->flipSign();

		delete s;
		delete newChildren;
		delete polys;

		s = last;
		return;		
	}

	int idx = cnt;
	for (int i = nPoly; i < s->nChildren; i++) newChildren[idx++] = s->children[i];
	
	delete* s->children;
	s->children = newChildren;
	s->nChildren = actualSize;

	simplifySumSign(s);
}

// Грозен код за принтиране
// Преминавай само в краен случай
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
		if (!isFirst) ss << " " << node->getVisualSign() << " ";
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
		if (!isFirst) ss << " " << node->getVisualSign() << " ";
		else if (node->getVisualSign() == '-') ss << '-';
	}

	bool flag = node->getSign() == '-' || !(attachSign || isFirst);

	if (node->power->isNatural())
	{
		if (node->power->fraction.up == 1)
		{
			if (node->getSign() == '-' && (attachSign ^ isFirst) && attachSign==false) ss << '-';
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
		if (!isFirst) ss << " " << node->getVisualSign() << " ";
		else if (node->getVisualSign() == '-') ss << " - ";
	}
	else if (isFirst && node->getVisualSign() == '-') ss << "-";

	if (node->nChildren < 2) ss << "error*error; children = "<<node->nChildren;
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
		else if (node->getVisualSign() == '-') ss << "-";
	}
	else if (isFirst && node->getVisualSign() == '-')ss << "-";

	if (node->nChildren < 2) ss << "error/error; chldren = "<<node->nChildren;
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
		if (!isFirst) ss << " " << node->getVisualSign() << " ";
		else if (node->getVisualSign() == '-') ss << " - ";
	}
	else if (isFirst && node->getVisualSign() == '-') ss << '-';
	char sign = node->getSign();

	bool flag = sign == '-' || !attachSign; //дали е в скоби

	if (flag) ss << "(";

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