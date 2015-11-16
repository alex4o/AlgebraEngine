#ifndef CExpression
#define CExpression

#include "Expression.hpp"


const char polynomial = 0; // a simple polynomial, power field used for numerical power
const char fraction = 1; // children[0]/children[1]
const char product = 2; // <- equivalent of Term; children[0]*children[1]*.....
const char sum = 8; 
const char flog = 3; //log(children[0], children[1])
const char fpower = 9; // exp(children[0], children[1])

const char fsin = 4; // f(children[0]), rad
const char fcos = 5;
const char ftg = 6;
const char fcotg = 7;

const char fsind = 4 + 16; // f(children[0]), degrees
const char fcosd = 5 + 16;
const char ftgd =  6 + 16;
const char fcotgd =7 + 16;

const char letter = 10; //overload-ва nChildren и го ползва като код за буква, ползвай letterLookUp; power -> коефициент

const char typeMask = 127;
const char trigMask = 15;

const string fLookUp[] = { "", "", "", "log", "sin", "cos", "tg", "cotg" };
const string letterLookUp[127];

class Node
{
public:
	char type;
	Polynomial* poly;
	Number* power;
	Node** children;
	int nChildren;

	void print(bool isFirst, stringstream& ss);
	char getSign();
};

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
	void divideByNode(Node* node, bool spread); //текущ/нов
	void divideByNodeRec(Node* node); //нов/текущ
};

#endif