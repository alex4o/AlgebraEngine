#include <iostream>
#include <vector>
#include <string.h>
#include <sstream>
#include <stdlib.h>

using namespace std;
#define DEBUG true
#include "Equation.hpp"
#include "Expression.hpp"
#include "ExpressionDescriptor.hpp"
#include "Generator.hpp"
#include "Interface.hpp"
#include "Inequation.hpp"
#include "CompoundExpression.h"

int parse(string s)
{
    int n = 0;
    for(int i = 0; i < s.size(); i++)
    {
        n*=10;
        n+=s[i]-'0';
    }
    return n;
}

void printSigns(Node** arr, int n)
{
	cout << "signs: ";
	for (int i = 0; i < n; i++) cout << arr[i]->getSign() << " ";
	cout << endl;
}

void printSigns(Node** arr, int n, stringstream& ss)
{
	ss << "signs: ";
	for (int i = 0; i < n; i++) ss << arr[i]->getSign() << " ";
	ss << endl;
}

int main()
{
	initPrintFunctions();

	Polynomial** p = new Polynomial*[4];
	string s;

	for (int i = 0; i < 4; i++)
	{
		getline(cin, s);
		p[i] = new Polynomial(s);
	}

	cout << endl;

	Number pow(1);

	stringstream ss;

	Node** nodes = new Node*[4];
	for (int i = 0; i < 4; i++) nodes[i] = new Node(p[i], pow, i>2);
	printSigns(nodes, 4);

	add(nodes[0], nodes[1], true);
	//simplifyProductSign(nodes[0]);
	//doProductMath(nodes[0], 2);

	ss << "0 + 1 = ";
	nodes[0]->print(true, false, ss);
	ss << endl << endl;



	ss << "3 + 0 = ";
	add(nodes[3], nodes[0], true);
	//simplifyProductSign(nodes[2]);
	//doProductMath(nodes[2], 2);

	nodes[3]->print(true, false, ss);
	ss << endl << endl;

	ss << "2 + 3 = ";
	add(nodes[2], nodes[3], true);
	//simplifyProductSign(nodes[0]);

	nodes[2]->print(true, false, ss);

	//ss << endl << endl << " after doMath: ";
	//doProductMath(nodes[0], 4);
	//nodes[0]->print(true, false, ss);
	//ss << endl << endl;

	cout << ss.str() <<endl;

	system("pause");
	
	/*CompoundExpression ce(nodes, 4);

	ce.print(ss);
	cout << ss.str();*/
}
