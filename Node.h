#ifndef NODE
#define NODE

#include "Polynomial.hpp"

const int initialNodeCapacity = 5;

const char polynomial = 0; // просто полином, power се ползва за числова степен
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

const char letter = 10; //overload-ва nChildren и го ползва като код за буква, ползвай letterLookUp; power -> коефициент

const char typeMask = 63;
const char trigMask = 15;

const string fLookUp[] = { "", "", "", "log", "sin", "cos", "tg", "cotg" };
const string letterLookUp[127];

static string dbgString;

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
	void flipChildren(); // сменя children[0] и children[1]
	void flipSign();

	void print(bool isFirst, bool attachSign, stringstream& ss);
	void dbgPrint();

	char getType();
	char getSign(); // реалния знак, т.е. коеф. +/-1 пред нещото
	char getVisualSign(); // какъв знак трябва да се покаже, когато звеното не е първо

	int getMaxPower();

	Node();
	Node(char t); //само създава масива и някои други задължителни работи
	Node(Node &src);
	Node(Polynomial* p); //действието е събиране
	Node(Polynomial* p, bool isNegative);
	Node(Polynomial* p, Number& pow, bool isNegative); //когато има степен излиза (....) затова знака трябва да е изрично споменат

	/*~Node();*/
};

typedef void(*printFunction)(Node* node, bool isFirst, bool attachSign, stringstream& ss);
static printFunction printArr[32];

bool cmp(Node* n1, Node* n2);

void halfCopy(Node* dest, Node* src); // копира само децата

void add(Node* &dest, Node* src, bool compact);
void mult(Node* &dest, Node* src, bool compact); // dest *= src; сменя типа на dest на product, ако е необходимо
void divide(Node* &dest, Node* src, bool compact); // dest /= src; сменя типа на dest на fraction, ако е необходимо
void divRec(Node* &dest, Node* src, bool compact); // dest = src/dest

void simplifySign(Node* node); //интерфейс за избягване на грешки
void simplifyProductSign(Node* prod); //свежда броя на минусите(които обаче не се виждат) до 0 или 1
void simplifyFractionSign(Node* frac); //свежда броя на минусите(които обаче не се виждат) до 0 или 1
void simplifySumSign(Node* s); //ако броя на минусите е по-голям, сменя знака

void doMathRec(Node* &node, int maxGroupSize);
void doSumMath(Node* &s, int maxGroupSize); //maxGroupSize - колко най-много елемента да обединим
void doProductMath(Node* &p, int maxGroupSize); //maxGroupSize - колко най-много елемента да обединим

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