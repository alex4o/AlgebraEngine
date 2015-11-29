#include "FracEquation.h"

FracEquation::FracEquation()
{
	letter = 'x';
	left = new CompoundExpression();
	right = new CompoundExpression();

	rnj = new RNJ();
}

FracEquation::FracEquation(CoefDescriptor &cd)
{
	letter = 'x';
	this->cd = cd;
	left = new CompoundExpression();
	right = new CompoundExpression();

	rnj = new RNJ();
}

FracEquation::FracEquation(CoefDescriptor &cd, char letter)
{
	this->letter = letter;
	this->cd = cd;
	left = new CompoundExpression();
	right = new CompoundExpression();

	rnj = new RNJ();
}

void FracEquation::initGenerator()
{
	RootDescriptor rd;
	CoefDescriptor* cdp = (CoefDescriptor*)&rd; //workaround oriented programming
	*cdp = cd;
	gen.descriptor = rd;
}

void FracEquation::construct(vector<Number> &roots, int maxPow)
{
	this->roots = roots;
	maxVisualPower = maxPow;

	SPolynomial seed;
	seed.coef[0] = 1;
	SPolynomial sp;
	sp.power = 1;
	for (int i = 0; i < roots.size(); i++)
	{		
		sp.coef[0] = roots[i]*-1;
		sp.coef[1] = 1;
		if (roots[i].isNatural() == false)
		{
			sp.coef[0] *= roots[i].fraction.down;
			sp.coef[1] *= roots[i].fraction.down;
		}

		seed *= sp;
	}

	Polynomial* leftPoly = new Polynomial();
	*leftPoly = seed.toPolynomial();

	Node* leftNode = new Node(leftPoly);
	left->addNode(leftNode, false);

	Polynomial* rightPoly = new Polynomial();
	Node* rightNode = new Node(rightPoly);

	right->addNode(rightNode, false);
}

void FracEquation::construct2(vector<Number> &roots, vector<Number> &bads, int maxPow)
{
	this->roots = roots;
	this->badValues = bads;
	badIdx = bads.size();

	this->maxVisualPower = maxPow;

	Number a = bads[0];
	Number b = bads[1];
	Number p, q;

	if (solveSystem(p, q, a, b, roots[0], roots[1]))
	{
		Node* first = new Node(fraction);
		Node* second = new Node(fraction);

		Polynomial* pPoly = new Polynomial(letter, p);
		Polynomial* aPoly = new Polynomial(letter, a);
		Polynomial* qPoly = new Polynomial(letter, q);
		Polynomial* bPoly = new Polynomial(letter, b);

		first->children[0] = new Node(pPoly);
		first->children[1] = new Node(aPoly);

		second->children[0] = new Node(qPoly);
		second->children[1] = new Node(bPoly);

		left->addNode(first, false);
		left->addNode(second, false);

		Polynomial* rPoly = new Polynomial();
		Node* rNode = new Node(rPoly);
		right->addNode(rNode, false);
	}
}

void FracEquation::addBadValue(Number &n)
{
	badValues.push_back(n);
	badIdx++;
}

void FracEquation::modSide(bool choice)
{
	if (!genInit)
	{
		genInit = true;
		initGenerator();
	}

	CompoundExpression* ce = this->left;
	if (choice) ce = this->right;

	if (ce->nNodes == 1) //имаме само един елемент, не е библейско
	{
		if (ce->nodes[0]->getType() == polynomial)
		{
			int pow = ce->nodes[0]->poly->getMaxPower();

			Node* current = ce->nodes[0];

			Polynomial* part = new Polynomial();

			while (true)
			{
				*part = gen.generatePoly(rnj->nextInt(1, maxVisualPower), letter);
				if (part->equals(current->poly) == false) break;
			}
			
			Polynomial* np = current->poly;
			part->negate();
			*np = *np + *part;
			part->negate();

			Node* newNode = new Node(part);
			ce->addNode(newNode, false);
			return;
		}
	}

	Node* &chosen = ce->nodes[rnj->nextInt(0, ce->nNodes - 1)];

	cout << "chosen: ";
	chosen->dbgPrint();

	int nodePow = chosen->getMaxPower();

	Node* newNode = new Node(fraction);
	Polynomial* top = new Polynomial();
	*top = gen.generatePoly(maxVisualPower-nodePow, letter);

	Polynomial* bottom = new Polynomial(letter, badValues[badIdx--]);

	if (badIdx == -1) badIdx = badValues.size() - 1;

	newNode->children[0] = new Node(top);
	newNode->children[1] = new Node(bottom);

	if (newNode->children[0]->poly->isNegative())
	{
		newNode->children[0]->poly->negate();
		newNode->children[0]->flipSign();
	}

	if (newNode->children[1]->poly->isNegative())
	{
		newNode->children[1]->poly->negate();
		newNode->children[1]->flipSign();
	}

	simplifyFractionSign(newNode);

	cout << "newNode: ";
	newNode->dbgPrint();
	

	add(chosen, newNode, true);

	cout << "chosen after add: ";
	chosen->dbgPrint();

	cout << "newNode after add: ";
	newNode->dbgPrint();

	doMathRec(chosen, 100);

	cout << "chosen after math: ";
	chosen->dbgPrint();

	cout << "newNode after math: ";
	newNode->dbgPrint();

	newNode->flipSign();
	ce->addNode(newNode, false);
}

void FracEquation::balanceSides()
{
	int totalCount = left->nNodes + right->nNodes;
}

void FracEquation::print(stringstream& ss)
{
	left->print(ss);
	ss << " = ";
	right->print(ss);
}

bool solveSystem(Number& p, Number& q, Number& a, Number& b, Number& x1, Number& x2)
{
	if (a == b) return false; //при еднакви знаменатели нямаме втора степен
	if (a.null)
	{
		Number tmp = a;
		a = b;
		b = tmp;
	} // за удобство само b може да е нула(ако и двете са нула първия if връща)

	Number w = x1*x2;
	Number z = x1 + x2;

	if (b.null)
	{
		q = (w * 2) / a;
		p = (-1 * a*a + 2 * a*z - 2 * w) / a;
		return true;
	}

	q = (b*(2 * z - a - b) - 2 * w) / (b - a);
	p = (2 * w - a*q) / b;
	return true;
}