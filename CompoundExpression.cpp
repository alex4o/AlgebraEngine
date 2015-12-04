#include "CompoundExpression.h"

CompoundExpression::CompoundExpression()
{
	capacity = initialCoExCapacity;
	nodes = new Node*[capacity];
	nNodes = 0;
}

CompoundExpression::CompoundExpression(Node** nodes, int n)
{
	capacity = nNodes = n;
	this->nodes = new Node*[n];
	for (int i = 0; i < n; i++) this->nodes[i] = nodes[i];
}

CompoundExpression::~CompoundExpression()
{
	for (int i = 0; i < nNodes; i++) delete nodes[i];
	delete[] nodes;
}

void CompoundExpression::print(stringstream& ss)
{
	for (int i = 0; i < nNodes; i++)
	{
		nodes[i]->print(i == 0, i>0, ss);
		//if (i < nNodes - 1) ss <<nodes[i + 1]->getSign()<<" ";
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

int CompoundExpression::findPolyIdx()
{
	for (int i = 0; i < nNodes; i++) if (nodes[i]->getType() == polynomial) return i;
	return -1;
}

Node* CompoundExpression::findNodeForSum(Node* start)
{
	char t = start->getType();
	if (t == polynomial) return start;
	if (t == sum)
	{
		int lim = start->nChildren;
		for (int i = 0; i < lim; i++)
		{
			Node* cand = findNodeForSum(start->children[i]);
			if (cand != 0) return cand;
		}
	}
	return 0;
}

void CompoundExpression::addNode(Node* node, bool calc)
{
	if (!calc)
	{
		if (nNodes == capacity) resize();
		nodes[nNodes++] = new Node(node);
		return;
	}

	Node* newNode = new Node(node);
	doMathRec(newNode, 100);

	for (int i = 0; i < nNodes; i++)
	{
		Node* &current = nodes[i];
		char t = current->getType();

		if (t == polynomial || t == sum || t == fraction)
		{
			add(current, newNode, true);
			doMathRec(current, 100);
			return;
		}
	}

	if (nNodes == capacity) resize();
	nodes[nNodes++] = new Node(node);
	return;
}

void CompoundExpression::multByNode(Node* node, bool spread)
{
	if (!spread)
	{
		Node** arr = new Node*[nNodes];
		for (int i = 0; i < nNodes; i++) arr[i] = nodes[i];
		nodes[0] = new Node(product);

		nodes[0]->children[0] = node;
		if (nNodes == 1) nodes[0]->children[1] = arr[0];
		else
		{
			Node* s = nodes[0]->children[1] = new Node(sum);
			s->resize(nNodes);
			for (int i = 0; i < nNodes; i++) s->children[i] = arr[i];
		}
		delete[] arr;
	}
	else
	{
		for (int i = 0; i < nNodes; i++)
		{
			if (nodes[i]->getType() == polynomial)
			{
				if (node->type == polynomial)
				{
					Polynomial* p1 = nodes[i]->poly;
					Polynomial* p2 = node->poly;
					*p1 = (*p1)*(*p2);
					continue;
				}
			}

			Node* current = nodes[i];
			Node* newNode = nodes[i] = new Node(product);
			newNode->children[0] = node;
			newNode->children[1] = current;
		}
	}
}

void CompoundExpression::divideByNode(Node* node, bool spread)
{
	for (int i = 0; i < nNodes; i++)
	{
		Node* current = nodes[i];
		Node* newNode = nodes[i] = new Node(fraction);
		newNode->children[0] = current;
		newNode->children[1] = node;
	}
}

void CompoundExpression::divideByNodeRec(Node* node)
{
	for (int i = 0; i < nNodes; i++)
	{
		Node* current = nodes[i];
		Node* newNode = nodes[i] = new Node(fraction);
		newNode->children[1] = current;
		newNode->children[0] = node;
	}
}

void CompoundExpression::fixUp()
{
	removeZero();
	for (int i = 0; i < nNodes; i++) simplifySign(nodes[i]);
}

void CompoundExpression::removeZero()
{
	for (int i = 0; i < nNodes; i++)
	{
		Node* current = nodes[i];
		if (current->getType() == polynomial)
		{
			if (current->poly->isZero())
			{
				for (int j = i + 1; j < nNodes; j++) nodes[j - 1] = nodes[j];
				nNodes--;
				delete current;
			}
		}
	}
}