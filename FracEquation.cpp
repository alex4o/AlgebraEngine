#include "FracEquation.h"

FracEquation::FracEquation()
{
	letter = 'x';
	left = new CompoundExpression();
	right = new CompoundExpression();

	rnj = new RNJ();
	
	badIdx = -1;
	genInit = false;
}

FracEquation::FracEquation(CoefDescriptor &cd)
{
	letter = 'x';
	this->cd = cd;
	left = new CompoundExpression();
	right = new CompoundExpression();

	rnj = new RNJ();


	badIdx = -1;
	genInit = false;
}

FracEquation::FracEquation(CoefDescriptor &cd, char letter)
{
	this->letter = letter;
	this->cd = cd;
	left = new CompoundExpression();
	right = new CompoundExpression();

	rnj = new RNJ();

	badIdx = -1;
	genInit = false;
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
	badIdx = bads.size() - 1;

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

void FracEquation::splitToRight()
{
	for (int i = 0; i < left->nNodes; i++)
	{
		Node* newNode;
		splitNode(left->nodes[i], newNode, cd, &gen, letter);
		if (newNode != 0)
		{
			newNode->flipSign();
			simplifySign(newNode);
			right->addNode(newNode, false);
			simplifySign(left->nodes[i]);
		}
	}

	if (right->nNodes > 1)
	{
		right->removeZero();
	}
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

	if (ce->nNodes == 1) // има само един полином и го делим
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
	*top = gen.generatePoly(1, letter);

	Polynomial* bottom = new Polynomial(letter, badValues[badIdx--]);

	if (badIdx == -1) badIdx = badValues.size() - 1;

	newNode->children[0] = new Node(top);
	newNode->children[1] = new Node(bottom);

	simplifySign(newNode);

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

bool FracEquation::addPoly(bool choice)
{
	Polynomial* poly = new Polynomial();
	*poly = gen.generatePoly(cd, 1, letter);

	CompoundExpression* chosenSide = left;
	if (choice) chosenSide = right;

	if (chosenSide->nNodes < 1)
	{
		chosenSide->addNode(new Node(poly), false);

		CompoundExpression* otherSide = right;
		if (choice) otherSide = left;

		otherSide->addNode(new Node(poly, false), false);

		return true;
	}

	Node* &chosenNode = chosenSide->nodes[rnj->nextInt(0, chosenSide->nNodes - 1)];

	Node* newNode = new Node(poly);
	newNode->flipSign();

	cout << endl << "chosenNode: ";
	chosenNode->dbgPrint();
	cout <<"newNode: ";
	newNode->dbgPrint();
	cout << endl;


	add(chosenNode, newNode, true);
	doMathRec(chosenNode, 100);
	simplifySign(chosenNode);

	newNode->flipSign();

	simplifySign(newNode);
	chosenSide->addNode(newNode, false);

	/*cout << "before splitPoly: ";
	dbgPrint();*/

	splitPolyL(chosenSide->nodes[chosenSide->nNodes-1], !choice);
	return true;
}

bool FracEquation::addNumberToFraction(bool choice)
{
	CompoundExpression* chosenSide = left;
	if (choice) chosenSide = right;

	if (chosenSide->nNodes == 0) return false;

	vector<int> fractionsIdx;
	for (int i = 0; i < chosenSide->nNodes; i++)
	{
		Node* current = chosenSide->nodes[i];
		if (current->getType() == fraction) fractionsIdx.push_back(i);
	}

	if (fractionsIdx.size() == 0) return false;

	int chosenIdx = fractionsIdx[rnj->nextInt(0, fractionsIdx.size() - 1)];

	Number* num = new Number();
	*num = rnj->nextInt(1, 10);

	Polynomial* poly = new Polynomial(*num);

	Node* newNode = new Node(poly);
	newNode->flipSign(); // първо изваждаме от избрания елемент

	add(chosenSide->nodes[chosenIdx], newNode, true);
	doMathRec(chosenSide->nodes[chosenIdx], 100);

	newNode->flipSign();
	simplifySign(newNode);
	
	int idx = chosenSide->findPolyIdx();

	if (idx != -1) // след това добавяме към друг елемент
	{
		add(chosenSide->nodes[idx], newNode, true);
		doSumMath(chosenSide->nodes[idx], 100);
		return true;
	}

	chosenSide->addNode(newNode, false); 
	return true;
}

bool FracEquation::splitPolyL(Node* &pnode, bool sideToAdd)
{
	Node* newNode;
	splitNode(pnode, newNode, cd, &gen, letter);
	simplifySign(pnode);

	CompoundExpression* chosen = left;
	if (sideToAdd) chosen = right;

	newNode->flipSign();
	simplifySign(newNode);
	chosen->addNode(newNode, false);
	return true;
}

bool FracEquation::findAndSplitPolySS(bool choice)
{
	CompoundExpression* chosenSide = left;
	if (choice) chosenSide = right;

	if (chosenSide->nNodes == 0) return false;

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

	if (idxChosen != -1)
	{
		splitPoly(chosenSide->nodes[idxChosen], 2, letter, cd, rnj);
		return true;
	}
	return false;
}

bool FracEquation::mergeFractions(bool choice)
{
	CompoundExpression* chosenSide = left;
	if (choice) chosenSide = right;

	if (chosenSide->nNodes < 2) return false; // няма как да съберем 2 дроби като имаме по-малко от два елемента

	int args[2];
	int idx = 0;
	for (int i = 0; i < chosenSide->nNodes; i++)
	{
		Node* current = chosenSide->nodes[i];
		if (current->getType() == fraction)
		{
			args[idx++] = i;
			if (idx == 2) break;
		}
	}

	if (idx != 2) return false;

	add(chosenSide->nodes[args[0]], chosenSide->nodes[args[1]], true);

	/*cout << "before doMathRec: ";
	chosenSide->nodes[args[0]]->dbgPrint();*/

	doMathRec(chosenSide->nodes[args[0]], 100);

	/*cout << "after doMathRec: ";
	chosenSide->nodes[args[0]]->dbgPrint();
	cout << endl;*/

	delete chosenSide->nodes[args[1]];

	for (int i = args[1]; i < chosenSide->nNodes - 1; i++) chosenSide->nodes[i] = chosenSide->nodes[i + 1];
	chosenSide->nNodes--;
	return true;
}

void FracEquation::balanceSides()
{
	left->fixUp();
	right->fixUp();

	int totalCount = left->nNodes + right->nNodes;
	int half = totalCount / 2;

	if (left->nNodes > half)
	{
		int nTransfer = (left->nNodes - half) / 2;
		if (nTransfer < 1) return;

		for (int i = 0; i < nTransfer; i++)
		{
			int choice = rnj->nextInt(0, left->nNodes - 1);
			Node* current = left->nodes[choice];
			for (int j = choice + 1; j < left->nNodes; j++)
			{
				left->nodes[j - 1] = left->nodes[j];
			}
			left->nNodes--;

			current->flipSign();
			right->addNode(current, false);
		}
	}
	else if (right->nNodes > half)
	{
		int nTransfer = (right->nNodes - half) / 2;
		if (nTransfer < 1) return;

		for (int i = 0; i < nTransfer; i++)
		{
			int choice = rnj->nextInt(0, right->nNodes - 1);
			Node* current = right->nodes[choice];
			for (int j = choice + 1; j < right->nNodes; j++)
			{
				right->nodes[j - 1] = right->nodes[j];
			}
			right->nNodes--;

			current->flipSign();
			left->addNode(current, false);
		}
	}
}

void FracEquation::print(stringstream& ss)
{
	left->print(ss);
	ss << " = ";
	right->print(ss);
}

void FracEquation::printSolutions(stringstream& ss)
{
	for (int i = 0; i < roots.size(); i++)
	{
		Number &root = roots[i];
		if (find(badValues.begin(), badValues.end(), root) != badValues.end()) continue;
		ss << letter << "_{" << i + 1 << "}=";
		roots[i].print(false, false, ss);
		if (i != roots.size()-1)ss << ", ";
	}
}

void FracEquation::dbgPrint()
{
	stringstream ss;
	print(ss);
	cout << ss.str() << endl;
}

bool solveSystem(Number& p, Number& q, Number& a, Number& b, Number& x1, Number& x2)
{
	if (a == b) return false; //ако са равни нямаме 2ра степен
	if (a.null)
	{
		Number tmp = a;
		a = b;
		b = tmp;
	} // за удобство само b може да е 0

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

void generateFracEquation(FracEquation* fe, FracEquationDescriptor& fed)
{
	if (fed.genType == 0)
	{
		vector<Number> roots;
		for (int i = 0; i < fed.power; i++) roots.push_back(fe->rnj->nextNumber(fed.rd));

#ifdef __linux__
		Number tmp = fe->rnj->nextNumber(fed.rd);
		for (int i = 0; i < fed.power; i++) fe->addBadValue(tmp);
#else
		for (int i = 0; i < fed.power; i++) fe->addBadValue(fe->rnj->nextNumber(fed.rd));
#endif
		fe->construct(roots, 2);
	}
	else if (fed.genType == 1)
	{
		vector<Number> bad;
		for (int i = 0; i < fed.power; i++) bad.push_back(fe->rnj->nextNumber(fed.rd)); // Недопустими стойности
		vector<Number> roots;
		for (int i = 0; i < fed.power; i++) roots.push_back(fe->rnj->nextNumber(fed.rd)); // корени

		fe->construct2(roots, bad, fed.power);
	}

	int nTransform = fe->rnj->nextInt(fed.minTransformations, fed.maxTransformations);

	if (fed.genType == 0)
	{
		fe->modSide(false);
		fe->modSide(false);
		fe->modSide(false);
		nTransform--;
		fe->balanceSides();
	}

	if (nTransform <= 0) return;

	for (int i = 0; i < nTransform; i++)
	{
		int transformChoice = fe->rnj->nextInt(0, 3);

		cout << "i = " << i << "; choice: " << transformChoice << "; before:\n";
		fe->dbgPrint();

		//if (!fe->addPoly(fe->rnj->nextBool())) i--;

		if (transformChoice == 0) // добавяме полином към случаен елемент
		{
			if(!fe->addPoly(fe->rnj->nextBool())) i--;
		}
		else /*if (transformChoice == 1)*/
		{
			if (!fe->addNumberToFraction(fe->rnj->nextBool())) i--;
		}


		cout << "after: ";
		fe->dbgPrint();
		cout << endl;
	}

	fe->balanceSides();
}