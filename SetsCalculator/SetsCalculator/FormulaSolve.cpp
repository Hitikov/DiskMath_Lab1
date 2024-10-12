#pragma once

#include "FormulaSolve.h"

MathSet FormulaSolve(std::map<std::string, MathSet> SetMap, std::string formulaToSolve)
{
	std::string& str = formulaToSolve;

	str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

	int nameSetUnique = 0;

	return FormulaSolveComposed(SetMap, str, nameSetUnique);
}

//For strings in which brackets possible
MathSet FormulaSolveComposed(std::map<std::string, MathSet>& SetMap, std::string formulaToSolve, int& nameSetUnique)
{
	std::string::size_type posCloseBracket = formulaToSolve.find(")");

	std::string::size_type posFirstOpenBracket = formulaToSolve.find("(");

	if (posCloseBracket == -1 && posFirstOpenBracket != -1)
	{
		return MathSet("NoCloseBracket");
	}

	if (posCloseBracket == -1)
	{
		return FormulaSolveSimple(SetMap, formulaToSolve);
	}

	int posCurrent = posCloseBracket;	
	bool isOpenBracketFound = false;

	while (posCurrent != -1 && !isOpenBracketFound)	
	{
		if (formulaToSolve[posCurrent] == '(')
		{
			isOpenBracketFound = true;
		}
		--posCurrent;
	}

	posCurrent += 2;

	if (isOpenBracketFound)
	{
		std::string innerFormula = formulaToSolve.substr(posCurrent, posCloseBracket - posCurrent);
		
		std::string nameSub = "_" + std::to_string(nameSetUnique);
		++nameSetUnique;
		
		MathSet setSub = FormulaSolveComposed(SetMap, innerFormula, nameSetUnique);

		if (setSub.GetName() == "NoSetName")
			return MathSet("NoSetName");

		SetMap[nameSub] = setSub;

		formulaToSolve.replace(posCurrent - 1, posCloseBracket - posCurrent + 2, nameSub);

		return FormulaSolveComposed(SetMap, formulaToSolve, nameSetUnique);
	}

	return MathSet("NoOpenBracket");

}

//For strings w/o brackets
MathSet FormulaSolveSimple(std::map<std::string, MathSet>& SetMap, std::string formulaToSolve)
{
	int posCurrent = 0;
	int posLastNoSymbol = 0;

	int posOfSetInVect = 0;

	std::vector<std::string> nameSets;	
	//First - command number, second - start possition for operation
	std::vector<std::pair<int, int>> operations;

	std::pair<int, int> operation;

	while (posCurrent != formulaToSolve.size())
	{
		if (strchr("-+*/|", formulaToSolve[posCurrent]) != nullptr)
		{
			operation.second = posOfSetInVect;
			if (formulaToSolve[posCurrent] == '-')
			{
				operation.first = 0;
				++posLastNoSymbol;
			}
			if (strchr("+*/|", formulaToSolve[posCurrent]) != nullptr)
			{
				if (formulaToSolve[posCurrent] == '+')
					operation.first = 1;
				if (formulaToSolve[posCurrent] == '*')
					operation.first = 2;
				if (formulaToSolve[posCurrent] == '/')
					operation.first = 3;
				if (formulaToSolve[posCurrent] == '|')
					operation.first = 4;

				nameSets.push_back(formulaToSolve.substr(posLastNoSymbol, posCurrent - posLastNoSymbol));
				posLastNoSymbol = posCurrent + 1;

				++posOfSetInVect;
				
			}
			operations.push_back(operation);
		}
		++posCurrent;
	}

	nameSets.push_back(formulaToSolve.substr(posLastNoSymbol, posCurrent - posLastNoSymbol));

	std::vector<MathSet> sets;

	int posLast = 0;

	for (auto name : nameSets)
	{
		if (!SetMap.count(name))
			return MathSet("NoSetName");
		sets.push_back(SetMap[name]);
	}

	for (auto oper : operations)
	{
		int navig = oper.first;

		posLast = oper.second + 1;

		switch (navig)
		{
		case 0:
			sets[oper.second] = ResultAddition(sets[oper.second], "Addition");
			--posLast;
			break;
		case 1:
			sets[oper.second + 1] = ResultUnion(sets[oper.second], sets[oper.second + 1], "Union");
			break;
		case 2:
			sets[oper.second + 1] = ResultCross(sets[oper.second], sets[oper.second + 1], "Cross");
			break;
		case 3:
			sets[oper.second + 1] = ResultMinus(sets[oper.second], sets[oper.second + 1], "Minus");
			break;
		case 4:
			sets[oper.second + 1] = ResultMinusSym(sets[oper.second], sets[oper.second + 1], "MinusSym");
			break;
		}
	}

	MathSet result(sets[posLast].GetContent(), "result"); 

	return result;
}