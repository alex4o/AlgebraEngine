#ifndef CExpression
#define CExpression

#include "Node.h"

const int initialCoExCapacity = 5;

class CompoundExpression
{
private:
	int capacity;
	int nNodes;
	Node** nodes;

	void resize();

	Node* findNodeForSum(Node* start);
public:	

	void print(stringstream& ss);
	void addNode(Node* node, bool calc); //calc - дали да смята(ако е възможно)
	void multByNode(Node* node, bool spread); //дали да смята(ако е възможно)
	void divideByNode(Node* node, bool spread); //текущ/нов, spread не се ползва в момента
	void divideByNodeRec(Node* node); //нов/текущ
};

#endif