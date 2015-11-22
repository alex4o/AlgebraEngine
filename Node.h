#ifndef NODE
#define NODE

#include "Polynomial.hpp"

const int initialNodeCapacity = 5;

const char polynomial = 0; // ������ �������, power �� ������ �� ������� ������
const char fraction = 1; // children[0]/children[1]
const char product = 2; // <- children[0]*children[1]*.....
const char sum = 8;
const char flog = 3; //log(children[0], children[1])
const char fpower = 9; // exp(children[0], children[1])

const char fsin = 4; // f(children[0]), rad
const char fcos = 5;
const char ftg = 6;
const char fcotg = 7;

const char fsind = 4 + 16; // f(children[0]), degrees
const char fcosd = 5 + 16;
const char ftgd = 6 + 16;
const char fcotgd = 7 + 16;

const char letter = 10; //overload-�� nChildren � �� ������ ���� ��� �� �����, ������� letterLookUp; power -> ����������

const char typeMask = 63;
const char trigMask = 15;

const string fLookUp[] = { "", "", "", "log", "sin", "cos", "tg", "cotg" };
const string letterLookUp[127];

class Node
{
public:
	int nChildren;
	char type;
	Polynomial* poly;
	Number* power;
	Node** children;
	int capacity;

	void resize();
	void resize(int newSize);
	void flipChildren(); // ����� children[0] � children[1]
	void flipSign();

	void print(bool isFirst, bool attachSign, stringstream& ss);

	char getType();
	char getSign(); // ������� ����, �.�. ����. +/-1 ���� ������
	char getVisualSign(); // ����� ���� ������ �� �� ������, ������ ������� �� � �����

	Node();
	Node(char t); //���� ������� ������ � ����� ����� ������������ ������
	Node(Polynomial* p); //���������� � ��������
	Node(Polynomial* p, bool isNegative);
	Node(Polynomial* p, Number& pow, bool isNegative); //������ ��� ������ ������ (....) ������ ����� ������ �� � ������� ��������

	/*~Node();*/
};

typedef void(*printFunction)(Node* node, bool isFirst, bool attachSign, stringstream& ss);
static printFunction printArr[32];

bool cmp(Node* n1, Node* n2);

void add(Node* &dest, Node* src, bool compact);
void mult(Node* &dest, Node* src, bool compact); // dest *= src; ����� ���� �� dest �� product, ��� � ����������
void divide(Node* &dest, Node* src, bool compact); // dest /= src; ����� ���� �� dest �� fraction, ��� � ����������
void divRec(Node* &dest, Node* src, bool compact); // dest = src/dest

void simplifyProductSign(Node* prod); //������ ���� �� ��������(����� ����� �� �� ������) �� 0 ��� 1
void simplifyFractionSign(Node* frac); //������ ���� �� ��������(����� ����� �� �� ������) �� 0 ��� 1
void simplifySumSign(Node* s); //��� ���� �� �������� � ��-�����, ����� �����

void doSumMath(Node* &s, int maxGroupSize); //maxGroupSize - ����� ���-����� �������� �� ��������

void printLetter(Node* node, bool isFirst, bool attachSign, stringstream& ss);
void printPoly(Node* node, bool isFirst, bool attachSign, stringstream& ss);
void printProduct(Node* node, bool isFirst, bool attachSign, stringstream& ss);
void printFraction(Node* node, bool isFirst, bool attachSign, stringstream& ss);
void printSum(Node* node, bool isFirst, bool attachSign, stringstream& ss);
void printPower(Node* node, bool isFirst, bool attachSign, stringstream& ss);
void printLog(Node* node, bool isFirst, bool attachSign, stringstream& ss);
void printTrig(Node* node, bool isFirst, bool attachSign, stringstream& ss);

void initPrintFunctions();

#endif