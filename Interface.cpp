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
//Функция за генерация на много уравнения
	MultiResult mr;
	mr.count=count; //в началота се алокира памет за низовете
	mr.problem= (char*)malloc(4096);
	mr.solution= (char*)malloc(1024);

	RNJ jesus; //Създават се двата генератора
              //Това не е окончателната версия на кода,
	Generator generator; //най-вероятно RNJ jesus ще изчезне

	stringstream ssp, sss; //за принтиране се ползват stringstream-ове. Първият е за условие, вторият - за решение
	char* probIdx = mr.problem; //тези индекси сочат позицията, на която трябва да се запише
	char* solIdx = mr.solution; //текущата задача/отговор
	for(int i = 0; i < count; i++)
	{
		Equation eq = generator.generateEquation(ed, jesus);
		eq.print(ssp); //Генерира се уравнинеие
		eq.printRoots(sss);

		strcpy(probIdx, ssp.str().c_str()); //И се записва
		strcpy(solIdx, sss.str().c_str()); //на съответните места

		mr.ptrProblem[i]=probIdx; //след което се задават указатели към него
		mr.ptrSolution[i]=solIdx;

		probIdx+=strlen((const char*)probIdx)+1; // и се ъпдейтват индексите
		solIdx+=strlen((const char*)solIdx)+1;

		ssp.str(""); //чистене на стриймовете
		sss.str("");
	}

	return mr;
}

MultiResult getExpressions(ExpressionDescriptor ed, int count) {
	MultiResult mr; //Всичко е аналгично на горната функция
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
