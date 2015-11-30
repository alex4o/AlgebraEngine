#include "CompoundInequation.h"

void CompoundInequation::construct(vector<Number> &nv, char sign)
{
	letter = 'x';
	this->sign = sign;
	roots = nv;

	SPolynomial seed;
	seed.coef[0] = 1;
	SPolynomial sp;
	sp.power = 1;
	for (int i = 0; i < roots.size(); i++)
	{
		sp.coef[0] = roots[i] * -1;
		sp.coef[1] = 1;
		if (roots[i].isNatural() == false)
		{
			sp.coef[0] *= roots[i].fraction.down;
			sp.coef[1] *= roots[i].fraction.down;
		}

		seed *= sp;
	}

	left = new CompoundExpression();
	right = new CompoundExpression();

	Polynomial* leftPoly = new Polynomial();
	*leftPoly = seed.toPolynomial();

	Node* leftNode = new Node(leftPoly);
	left->addNode(leftNode, false);

	Polynomial* rightPoly = new Polynomial();
	Node* rightNode = new Node(rightPoly);

	right->addNode(rightNode, false);
}

void CompoundInequation::getSolutions()
{
	vector<Number*> points;
	for (int i = 0; i < roots.size(); i++) points.push_back(&roots[i]);

	sort(points.begin(), points.end(), cmpNum);

	bool isClosed = (sign == 1 || sign == 2);

	if (sign <= 1) // по-голямо
	{
		if (roots.size() % 2 == 0)
		{
			Interval first(*points[0], 1, isClosed);
			solutions.push_back(first);
			for (int i = 2; i < roots.size(); i += 2) solutions.push_back(Interval(*points[i - 1], *points[i], isClosed, isClosed));

			Interval last(*points[roots.size() - 1], 0, isClosed);
			solutions.push_back(last);
		}
		else
		{
			for (int i = 1; i < roots.size(); i += 2) solutions.push_back(Interval(*points[i - 1], *points[i], isClosed, isClosed));
			Interval last(*points[roots.size() - 1], 0, isClosed);
			solutions.push_back(last);
		}
	}
	else // по-малко
	{
		if (roots.size() % 2 == 0)
		{
			for (int i = 0; i < roots.size(); i += 2) solutions.push_back(Interval(*points[i], *points[i+1], isClosed, isClosed));
		}
		else
		{
			Interval first(*points[0], 1, isClosed);
			solutions.push_back(first);
			for (int i = 1; i < roots.size(); i += 2) solutions.push_back(Interval(*points[i], *points[i+1], isClosed, isClosed));
		}
	}
}

void CompoundInequation::findAndSplitPoly(bool choice)
{
	CompoundExpression* chosenSide = left;
	if (choice) chosenSide = right;

	int idxChosen = -1;
	for (int i = 0; i < chosenSide->nNodes; i++)
	{
		Node* current = chosenSide->nodes[i];
		if (current->getType() == polynomial)
		{
			idxChosen = i;
			/*cout << "The chosen one is: ";
			current->dbgPrint();*/
			break;
		}
	}

	if (idxChosen!=-1)
	{
		splitPoly(chosenSide->nodes[idxChosen], 2, letter, cd, rnj);
		/*cout << "after splitPoly: ";
		chosenSide->nodes[idxChosen]->dbgPrint();*/
	}
}

void CompoundInequation::generateAndAddNode()
{
	int pow = rnj->nextInt(2, maxVisualPower);
	//int pow = 2;
	Polynomial** parts = new Polynomial*[pow];

	for (int i = 0; i < pow; i++) parts[i] = new Polynomial(letter, rnj->nextNumber(cd));
	//parts[0] = new Polynomial(letter, Number(-1));
	//parts[1] = new Polynomial(letter, Number(2));

	Node* newNode = new Node(product, pow);
	for (int i = 0; i < pow; i++) newNode->children[i] = new Node(parts[i]);
	newNode->nChildren = pow;

	if (left->nNodes < right->nNodes)
	{
		left->addNode(newNode, true);
		right->addNode(newNode, false);
	}
	else
	{
		left->addNode(newNode, false);
		right->addNode(newNode, true);
	}
}

void CompoundInequation::print(stringstream& ss)
{
	left->print(ss);
	ss << " "<< lookup[sign] <<" ";
	right->print(ss);
}

void CompoundInequation::printSolutions(stringstream& ss)
{
	int size = solutions.size();
	for (int i = 0; i < size; i++)
	{
		solutions[i].print(ss);
		if (i != size - 1) ss << " \\cup ";
	}
}