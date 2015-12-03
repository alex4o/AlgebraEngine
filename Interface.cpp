#include <string>
#include "Generator.hpp"
#include "Interface.hpp"

#include <sstream>

using namespace std;

struct NewResult
{
	std::string problem;
	std::string solution;
};

extern "C"
{

	Result oprosti(ExpressionDescriptor ed)
	{
		RNJ jesus;

		Result res;
		Expression e1, e2;
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


	MultiResult getEquations(EquationDescriptor ed, int count) {

		MultiResult mr;
		mr.count = count;
		mr.problem = (char*)malloc(4096);
		mr.solution = (char*)malloc(1024);

		Generator generator;

		stringstream ssp, sss;
		char* probIdx = mr.problem;
		char* solIdx = mr.solution;
		for (int i = 0; i < count; i++)
		{
			Equation eq = generator.generateEquation(ed);
			eq.print(ssp);
			eq.printRoots(sss);

			strcpy(probIdx, ssp.str().c_str());
			strcpy(solIdx, sss.str().c_str());

			mr.ptrProblem[i] = probIdx;
			mr.ptrSolution[i] = solIdx;

			probIdx += strlen((const char*)probIdx) + 1;
			solIdx += strlen((const char*)solIdx) + 1;

			ssp.str("");
			sss.str("");
		}

		return mr;
	}

	MultiResult getExpressions(ExpressionDescriptor ed, int count) {
		MultiResult mr;
		mr.count = count;
		mr.problem = (char*)malloc(4096);
		mr.solution = (char*)malloc(1024);

		RNJ jesus;

		stringstream ssp, sss;
		char* probIdx = mr.problem;
		char* solIdx = mr.solution;
		for (int i = 0; i < count; i++)
		{
			Expression e1, e2;
			createEquivalentExpressions(e1, e2, ed, jesus);

			e1.print(ssp);
			e2.print(sss);

			strcpy(probIdx, ssp.str().c_str());
			strcpy(solIdx, sss.str().c_str());

			mr.ptrProblem[i] = probIdx;
			mr.ptrSolution[i] = solIdx;

			probIdx += strlen((const char*)probIdx) + 1;
			solIdx += strlen((const char*)solIdx) + 1;

			ssp.str("");
			sss.str("");
		}

		return mr;
	}

	MultiResult getInequations(InequationDescriptor id, int count) {
		MultiResult mr;
		mr.count = count;
		mr.problem = (char*)malloc(4096);
		mr.solution = (char*)malloc(1024);

		RNJ jesus;

		Generator generator;

		stringstream ssp, sss;
		char* probIdx = mr.problem;
		char* solIdx = mr.solution;
		for (int i = 0; i < count; i++)
		{
			Inequation eq = generator.generateInequation(id);
			eq.print(ssp);
			eq.printRoots(sss);

			strcpy(probIdx, ssp.str().c_str());
			strcpy(solIdx, sss.str().c_str());

			mr.ptrProblem[i] = probIdx;
			mr.ptrSolution[i] = solIdx;

			probIdx += strlen((const char*)probIdx) + 1;
			solIdx += strlen((const char*)solIdx) + 1;

			ssp.str("");
			sss.str("");
		}

		return mr;
	}

	MultiResult getFracEquations(FracEquationDescriptor fed, int count)
	{
		MultiResult mr;
		mr.count = count;
		mr.problem = (char*)malloc(4096);
		mr.solution = (char*)malloc(1024);

		Generator gen;

		stringstream ssp, sss;
		char* probIdx = mr.problem;
		char* solIdx = mr.solution;

		for (int i = 0; i < count; i++)
		{
			FracEquation* fe = new FracEquation(fed.cf, fed.letter);
			generateFracEquation(fe, fed);

			fe->print(ssp);
			fe->printSolutions(sss);

			strcpy(probIdx, ssp.str().c_str());
			strcpy(solIdx, sss.str().c_str());

			mr.ptrProblem[i] = probIdx;
			mr.ptrSolution[i] = solIdx;

			probIdx += strlen((const char*)probIdx) + 1;
			solIdx += strlen((const char*)solIdx) + 1;

			ssp.str("");
			sss.str("");

			delete fe;
		}

		return mr;
	}

	MultiResult getCInequations(CompoundInequationDescriptor cind, int count)
	{
		MultiResult mr;
		mr.count = count;
		mr.problem = (char*)malloc(4096);
		mr.solution = (char*)malloc(1024);

		stringstream ssp, sss;
		char* probIdx = mr.problem;
		char* solIdx = mr.solution;

		for (int i = 0; i < count; i++)
		{
			CompoundInequation* ci = new CompoundInequation();
			ci->generate(cind);

			ci->print(ssp);
			ci->printSolutions(sss);

			strcpy(probIdx, ssp.str().c_str());
			strcpy(solIdx, sss.str().c_str());

			mr.ptrProblem[i] = probIdx;
			mr.ptrSolution[i] = solIdx;

			probIdx += strlen((const char*)probIdx) + 1;
			solIdx += strlen((const char*)solIdx) + 1;

			ssp.str("");
			sss.str("");

			delete ci;
		}

		return mr;
	}
}



#ifdef EMSCRIPTEN

#include <emscripten/bind.h>
#include <emscripten/val.h>

using namespace emscripten;

val valInequations(InequationDescriptor id, int count) {
	RNJ jesus;
	val res = val::array();
	Generator generator;

	stringstream ssp, sss;
	for(int i = 0; i < count; i++)
	{
		Inequation eq = generator.generateInequation(id);
		eq.print(ssp);
		eq.printRoots(sss);
		val result = val::array();
		result.set(0,ssp.str());
		result.set(1,sss.str());
		res.set(i,result);
	}

	return res;
}

val valOprosti(ExpressionDescriptor ed)
	{
		RNJ jesus;
		val res = val::array();
		Expression e1,e2;
		createEquivalentExpressions(e1, e2, ed, jesus);
		stringstream ss1, ss2;
		e1.print(ss1);
		e2.print(ss2);
		string s1 = ss1.str();
		string s2 = ss2.str();

		val result = val::array();
		result.set(0,s1);
		result.set(1,s2);

		return result;
	}


val valEquations(EquationDescriptor ed, int count) {

	val mr = val::array();
	Generator generator;

	stringstream ssp, sss;
	for(int i = 0; i < count; i++)
	{
		Equation eq = generator.generateEquation(ed);
		eq.print(ssp);
		eq.printRoots(sss);

		val result = val::array();
		result.set(0,ssp.str());
		result.set(1,sss.str());
		mr.set(i,result);

	}

	return mr;
}

val valExpressions(ExpressionDescriptor ed, int count) {
	val mr = val::array();
	RNJ jesus;

	stringstream ssp, sss;
	for(int i = 0; i < count; i++)
	{
		Expression e1,e2;
		createEquivalentExpressions(e1, e2, ed, jesus);

		e1.print(ssp);
		e2.print(sss);
		
		val result = val::array();
		result.set(0,ssp.str());
		result.set(1,sss.str());
		mr.set(i,result);
	}

	return mr;
}


EMSCRIPTEN_BINDINGS(interface) {

	emscripten::function("getInequations", &valInequations);
	emscripten::function("getExpressions", &valExpressions);
	emscripten::function("getEquations", &valEquations);
	emscripten::function("oprosti", &valOprosti);

	value_object<InequationDescriptor>("InequationDescriptor")
		.field("cf",&InequationDescriptor::cf)
		.field("transformCF",&InequationDescriptor::transformCF)
		.field("letter", &InequationDescriptor::letter)
		.field("nice", &InequationDescriptor::nice)
		.field("minTerms", &InequationDescriptor::minTerms)
		.field("maxTermPower", &InequationDescriptor::maxTermPower)
		.field("maxTerms", &InequationDescriptor::maxTerms);

	value_object<CoefDescriptor>("CoefDescriptor")
		.field("pNatural",&CoefDescriptor::pNatural)
		.field("pRational",&CoefDescriptor::pRational)
		.field("pIrational",&CoefDescriptor::pIrational)
		.field("pNegative",&CoefDescriptor::pNegative)
		.field("upLow",&CoefDescriptor::upLow)
		.field("upHigh",&CoefDescriptor::upHigh)
		.field("downLow",&CoefDescriptor::downLow)
		.field("downHigh",&CoefDescriptor::downHigh);

	value_object<RootDescriptor>("RootDescriptor")
		.field("pNatural",&RootDescriptor::pNatural)
		.field("pFraction",&RootDescriptor::pFraction)
		.field("pIrational",&RootDescriptor::pIrational)
		.field("pNegative",&RootDescriptor::pNegative)
		.field("upLow",&RootDescriptor::upLow)
		.field("upHigh",&RootDescriptor::upHigh)
		.field("downLow",&RootDescriptor::downLow)
		.field("downHigh",&RootDescriptor::downHigh);

	value_object<ExpressionDescriptor>("ExpressionDescriptor")
		.field("maxPow",&ExpressionDescriptor::maxPow)
		.field("maxLetters",&ExpressionDescriptor::maxLetters)
		.field("minLetters",&ExpressionDescriptor::minLetters)
		.field("maxTerms",&ExpressionDescriptor::maxTerms)
		.field("minTerms",&ExpressionDescriptor::minTerms)
		.field("minSubTerm",&ExpressionDescriptor::minSubTerm)
		.field("maxSubTerm",&ExpressionDescriptor::maxSubTerm)
		.field("factored",&ExpressionDescriptor::factored)
		.field("cf",&ExpressionDescriptor::cf)
		.field("transformCF",&ExpressionDescriptor::transformCF)
//		.field("letters",&ExpressionDescriptor::letters)
		.field("cLetters",&ExpressionDescriptor::cLetters);

	value_object<EquationDescriptor>("EquationDescriptor")
		.field("power",&EquationDescriptor::power)
		.field("maxTermPower",&EquationDescriptor::maxTermPower)
		.field("minTerms",&EquationDescriptor::minTerms)
		.field("maxTerms",&EquationDescriptor::maxTerms)
		.field("letter",&EquationDescriptor::letter)
		.field("type",&EquationDescriptor::type)
		.field("rd",&EquationDescriptor::rd)
		.field("cd",&EquationDescriptor::cd)
		.field("transformCF",&EquationDescriptor::transformCF)
		.field("nice",&EquationDescriptor::nice);


	value_object<NewResult>("Result")
		.field("problem",&NewResult::problem)
		.field("solution",&NewResult::solution);

	register_vector<NewResult>("Results");



	 /*value_object<NewResult>("NewResult")
		.field("problem",&MultiResult::problem)
		.field("solution",&MultiResult::solution)
		.field("ptrProblem",&MultiResult::ptrProblem)
		.field("ptrSolution",&MultiResult::ptrSolution)
		.field("count",&MultiResult::count);
*/


}
#endif

