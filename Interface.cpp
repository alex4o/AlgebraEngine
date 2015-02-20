#include <string>
#include "ExpressionDescriptor.hpp"
#include "Generator.hpp"
#include "Interface.hpp"

#include <sstream>

using namespace std;

extern "C"
{

	void oprosti(ExpressionDescriptor ed, Result *res)
	{

		Expression e1,e2;
		createEquivalentExpressions(e1, e2, ed);
		stringstream ss1, ss2;
		e1.print(ss1);
		e2.print(ss2);
		string s1 = ss1.str();
		string s2 = ss2.str();

		res->problem = (char*)malloc(s1.size() + 1);
		res->solution = (char*)malloc(s2.size() + 1);

		strcpy(res->problem, s1.c_str());
		strcpy(res->solution, s2.c_str());
	}
}




