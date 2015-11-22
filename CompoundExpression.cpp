#include "CompoundExpression.h"

CompoundExpression::CompoundExpression(Node** nodes, int n)
{
	capacity = nNodes = n;
	this->nodes = new Node*[n];
	for (int i = 0; i < n; i++) this->nodes[i] = nodes[i];
}

void CompoundExpression::print(stringstream& ss)
{
	for (int i = 0; i < nNodes; i++)
	{
		nodes[i]->print(i == 0, i>0, ss);
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
	if (!calc || (node->type)&typeMask!=polynomial)
	{
		if (nNodes == capacity) resize();
		nodes[nNodes++] = node;
		return;
	}
	else
	{
		Node* k;
		for (int i = 0; i < nNodes; i++)
		{
			k = findNodeForSum(nodes[i]);
			if (k != 0) break;
		}
		if (k)
		{
			Polynomial p = *(k->poly);
			p = p + *(node->poly);
		}
		else
		{
			if (nNodes == capacity) resize();
			nodes[nNodes++] = node;
			return;
		}
	}
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