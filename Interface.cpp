#include <string>
#include "ExpressionDescriptor.hpp"
#include "Generator.hpp"
#include "Interface.hpp"

#include <sstream>

using namespace std;

extern "C"
{

	Result oprosti(ExpressionDescriptor ed)
	{
		RNJ jesus;

		Result res;
		Expression e1,e2;
		createEquivalentExpressions(e1, e2, ed, jesus);
		stringstream ss1, ss2;
		e1.print(ss1);
		e2.print(ss2);
		string s1 = ss1.str();
		string s2 = ss2.str();

		res.problem = (char*)malloc(s1.size() + 1);
		res.solution = (char*)malloc(s2.size() + 1);

		strcpy(res.problem, s1.c_str());
		strcpy(res.solution, s2.c_str());
		return res;
	}
}


MultiResult getEquations(EquationDescriptor ed, int count) {

	MultiResult mr;
	mr.count=count;
	mr.problem= (char*)malloc(4096);
	mr.solution= (char*)malloc(1024);

	RNJ jesus;

	Generator generator;


	stringstream ssp, sss;
	char* probIdx = mr.problem;
	char* solIdx = mr.solution;
	for(int i = 0; i < count; i++)
	{
		Equation eq = generator.generateEquation(ed, jesus);
		eq.print(ssp);
		eq.printRoots(sss);

		strcpy(probIdx, ssp.str().c_str());
		strcpy(solIdx, sss.str().c_str());

		mr.ptrProblem[i]=probIdx;
		mr.ptrSolution[i]=solIdx;

		probIdx+=strlen((const char*)probIdx)+1;
		solIdx+=strlen((const char*)solIdx)+1;

		ssp.str("");
		sss.str("");
	}

	return mr;
}

MultiResult getExpressions(ExpressionDescriptor ed, int count) {
	MultiResult mr;
	mr.count=count;
	mr.problem= (char*)malloc(4096);
	mr.solution= (char*)malloc(1024);

	RNJ jesus;

	stringstream ssp, sss;
	char* probIdx = mr.problem;
	char* solIdx = mr.solution;
	for(int i = 0; i < count; i++)
	{
		Expression e1,e2;
		createEquivalentExpressions(e1, e2, ed, jesus);

		e1.print(ssp);
		e2.print(sss);

		strcpy(probIdx, ssp.str().c_str());
		strcpy(solIdx, sss.str().c_str());

		mr.ptrProblem[i]=probIdx;
		mr.ptrSolution[i]=solIdx;

		probIdx+=strlen((const char*)probIdx)+1;
		solIdx+=strlen((const char*)solIdx)+1;

		ssp.str("");
		sss.str("");
	}

	return mr;
}
