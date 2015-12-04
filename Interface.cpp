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

		Generator generator;

		
		for (int i = 0; i < count; i++)
		{
			stringstream ssp, sss;
			Equation eq = generator.generateEquation(ed);
			eq.print(ssp);
			eq.printRoots(sss);

			string ss = sss.str();
			string sp = ssp.str();

			mr.ptrProblem[i] = (char*)malloc(sp.size() + 1);
			mr.ptrSolution[i] = (char*)malloc(ss.size() + 1);;

			sp.copy(mr.ptrProblem[i], sp.size(), 0);
			mr.ptrProblem[i][sp.size()] = 0;

			ss.copy(mr.ptrSolution[i], ss.size(), 0);
			mr.ptrSolution[i][ss.size()] = 0;
		}

		return mr;
	}

	MultiResult getExpressions(ExpressionDescriptor ed, int count) {
		MultiResult mr;
		mr.count = count;
		
		RNJ jesus;

		stringstream ssp, sss;
		for (int i = 0; i < count; i++)
		{
			stringstream ssp, sss;
			Expression e1, e2;
			createEquivalentExpressions(e1, e2, ed, jesus);

			e1.print(ssp);
			e2.print(sss);

			string ss = sss.str();
			string sp = ssp.str();

			mr.ptrProblem[i] = (char*)malloc(sp.size() + 1);
			mr.ptrSolution[i] = (char*)malloc(ss.size() + 1);;

			sp.copy(mr.ptrProblem[i], sp.size(), 0);
			mr.ptrProblem[i][sp.size()] = 0;

			ss.copy(mr.ptrSolution[i], ss.size(), 0);
			mr.ptrSolution[i][ss.size()] = 0;
				
		}

		return mr;
	}

	MultiResult getInequations(InequationDescriptor id, int count) {
		MultiResult mr;
		mr.count = count;
		
		RNJ jesus;

		Generator generator;

		
		for (int i = 0; i < count; i++)
		{
			stringstream ssp, sss;
			Inequation eq = generator.generateInequation(id);
			eq.print(ssp);
			eq.printRoots(sss);

			string ss = sss.str();
			string sp = ssp.str();

			mr.ptrProblem[i] = (char*)malloc(sp.size() + 1);
			mr.ptrSolution[i] = (char*)malloc(ss.size() + 1);;

			sp.copy(mr.ptrProblem[i], sp.size(), 0);
			mr.ptrProblem[i][sp.size()] = 0;

			ss.copy(mr.ptrSolution[i], ss.size(), 0);
			mr.ptrSolution[i][ss.size()] = 0;
				
		}

		return mr;
	}

	MultiResult getFracEquations(FracEquationDescriptor fed, int count)
	{
		MultiResult mr;
		mr.count = count;
		
		for (int i = 0; i < count; i++)
		{
			try
			{
				stringstream ssp, sss;
				FracEquation fe;

				try
				{
					generateFracEquation(&fe, fed);
				}
					catch (std::bad_alloc& e)
				{
					cout << e.what() << "; ";
					cout << "bad alloc at generate, stopping loop!\n";
					cout<<"i = "<< i << endl;
					mr.count = i -1;
					break;
				}
				
				

				fe.print(ssp);
				fe.printSolutions(sss);
				string ss = sss.str();
				string sp = ssp.str();

				mr.ptrProblem[i] = (char*)malloc(sp.size() + 1);
				mr.ptrSolution[i] = (char*)malloc(ss.size() + 1);;

				sp.copy(mr.ptrProblem[i], sp.size(), 0);
				mr.ptrProblem[i][sp.size()] = 0;

				ss.copy(mr.ptrSolution[i], ss.size(), 0);
				mr.ptrSolution[i][ss.size()] = 0;
				//cout << mr.ptrProblem[i] << endl;
				//cout << mr.ptrSolution[i] << endl;
			}
			catch (std::bad_alloc& e)
			{
				cout << e.what() << "; ";
				cout << "bad alloc happenned, stopping loop!\n";
				cout<<"i = "<< i << endl;
				mr.count = i;
				mr.ptrSolution[i] = "Error";
				mr.ptrProblem[i] = "Error";
				return mr;

			}
		}

		return mr;
	}

	MultiResult getCInequations(CompoundInequationDescriptor cind, int count)
	{
		MultiResult mr;
		mr.count = count;
				
		for (int i = 0; i < count; i++)
		{
			try
			{
				CompoundInequation ci;
				ci.generate(cind);
				stringstream ssp, sss;

				ci.print(ssp);
				ci.printSolutions(sss);
				
				string sp = ssp.str();
				string ss = sss.str();

				mr.ptrProblem[i] = (char*)malloc(sp.size() + 1);
				mr.ptrSolution[i] = (char*)malloc(ss.size() + 1);

				sp.copy(mr.ptrProblem[i], sp.size(), 0);
				mr.ptrProblem[i][sp.size()] = 0;

				ss.copy(mr.ptrSolution[i], ss.size(), 0);
				mr.ptrSolution[i][ss.size()] = 0;


				//strcpy(mr.ptrProblem[i], sp.c_str());
				//strcpy(mr.ptrSolution[i], ss.c_str());

				cout << mr.ptrProblem[i] << endl;
				cout << mr.ptrSolution[i] << endl;
			}
			catch (std::bad_alloc& e)
			{
				cout << e.what() << "; ";
				cout << "bad alloc happenned, stopping loop!\n";
				mr.count = i;
				mr.ptrSolution[i] = "Error";
				mr.ptrProblem[i] = "Error";
				return mr;
			}
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

val valFracEquations(FracEquationDescriptor fed, int count)
{
	val mr = val::array();
	Generator gen;
	stringstream ssp, sss;


	for (int i = 0; i < count; i++)
	{
		FracEquation* fe = new FracEquation(fed.cf, fed.letter);
		generateFracEquation(fe, fed);
		
		val result = val::array();
		result.set(0,ssp.str());
		result.set(1,sss.str());
		mr.set(i,result);
		mr.set(i,result);

		delete fe;
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

