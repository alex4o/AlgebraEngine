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
	void addNode(Node* node, bool calc); //calc - ���� �� �����(��� � ��������)
	void multByNode(Node* node, bool spread); //���� �� �����(��� � ��������)
	void divideByNode(Node* node, bool spread); //�����/���, spread �� �� ������ � �������
	void divideByNodeRec(Node* node); //���/�����
};

#endif