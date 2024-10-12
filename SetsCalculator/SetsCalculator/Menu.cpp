#pragma once

#include "Menu.h"

void StartUp()
{
	std::map<std::string, MathSet>* workMap = new std::map<std::string, MathSet>;

	MenuMain(*workMap);
}

bool CheckNameIsExist(std::map<std::string, MathSet>& SetMap, std::string name)
{
	if (SetMap.find(name) == SetMap.end())
	{
		std::cout << "��������� ��������� �� ����������. �������� ������������ �����." << std::endl;
		system("pause");
		return false;
	}

	return true;
}

void ViewSetContent(MathSet mathSet)
{
	std::cout << mathSet.GetName() << " ={ ";

	bool isFirst = true;

	for (const auto& element : mathSet.GetContent())
	{
		if (isFirst)
			isFirst = false;
		else
			std::cout << ", ";

		std::cout << element;
	}

	std::cout << "}" << std::endl;
}

void ViewNamesMap(std::map<std::string, MathSet>& SetMap)
{
	std::cout << "������ ���� ��������" << std::endl;

	for (const auto& element : SetMap)
	{
		std::cout << element.first << std::endl;
	}

	std::cout << std::endl;
}

void MenuMain(std::map<std::string, MathSet>& SetMap)
{
	int navig;

	do
	{
		system("cls");

		std::cout << "1. �������� ��������" << std::endl;
		std::cout << "2. �������� ���������" << std::endl;
		std::cout << "3. �������� ���������" << std::endl;
		std::cout << "4. ���������� ��������" << std::endl;
		std::cout << "5. ������� �������" << std::endl;
		std::cout << "9. ���������� ������" << std::endl;

		std::cout << std::endl << "������� �������: ";

		std::cin >> navig;

		switch (navig)
		{
		case 1:
			MenuViewSets(SetMap);
			break;
		case 2:
			MenuMakeSet(SetMap);
			break;
		case 3:
			MenuDeleteSets(SetMap);
			break;
		case 4:
			MenuSolveOne(SetMap);
			break;
		case 5:
			MenuSolveFormula(SetMap);
			break;
		}
	} while (navig != 9);

	return;
}

void MenuViewSets(std::map<std::string, MathSet>& SetMap)
{
	system("cls");

	ViewNamesMap(SetMap);

	std::cout << "������� ��� ��������� ��� ���������: ";

	std::string setName;

	std::cin >> setName;

	if (!CheckNameIsExist(SetMap, setName))
		return;

	ViewSetContent(SetMap[setName]);

	system("pause");

	return;
}

void MenuMakeSet(std::map<std::string, MathSet>& SetMap)
{
	system("cls");

	ViewNamesMap(SetMap);

	std::cout << "������� ��� ��������� ��� ����������: ";

	std::string name;

	std::cin >> name;

	if (SetMap.find(name) != SetMap.end())
	{
		std::cout << "���������� ��������� � ���������� ������. �������� ������������ �����." << std::endl;
		system("pause");
		return;
	}

	int start = -100;
	int end = 100;
	std::vector<int> inVect;

	char buff;

	do
	{
		system("cls");
		std::cout << std::endl << "�������� �������� �����? (y/n): ";
		std::cin.clear();
		std::cin >> buff;
	} while (buff != 'y' && buff != 'n');

	if (buff == 'y')
	{
		do
		{
			system("cls");
			std::cout << "��������� �������� [-100 ; 100]" << std::endl;
			std::cout << std::endl << "������� ������ �������: ";
			std::cin >> start;
			std::cout << std::endl << "������� ������� �������: ";
			std::cin >> end;
		} while (!((start <= end) && (-100 <= start && start <= 100) && (-100 <= end && end <= 100)));
	}

	do
	{
		system("cls");
		std::cout << std::endl << "���������������� ����? (y/n): ";
		std::cin >> buff;
	} while (buff != 'y' && buff != 'n');

	if (buff == 'y')
	{
		int howMuch;
		do
		{
			system("cls");
			std::cout << std::endl << "������� ���������� ���������: ";
			std::cin >> howMuch;
		} while (!(0 <= howMuch && howMuch <= end - start + 1));

		for (int i = 0; i < howMuch; i++)
		{
			int inValue = rand() % (end - start + 1) + start;
			if (std::find(inVect.begin(), inVect.end(), inValue) == inVect.end())
				inVect.push_back(inValue);
			else
				i--;
		}
	}

	if (buff == 'n')
	{
		int inValue;
		bool isNotError = true;
		do
		{
			system("cls");
			std::cout << "��� ��������� ����� ������� ����� �������� �� ��������� ��������� ��� ����� �����.\n\n������� �������: ";
			std::cin >> inValue;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore();
				isNotError = false;
			}
			if (start < inValue && inValue < end
				&& std::find(inVect.begin(), inVect.end(), inValue) == inVect.end()
				&& isNotError)
				inVect.push_back(inValue);
		} while (start < inValue && inValue < end && isNotError);
	}

	std::sort(inVect.begin(), inVect.end());

	MathSet newSet(inVect, name);

	SetMap[name] = newSet;
}

void MenuDeleteSets(std::map<std::string, MathSet>& SetMap)
{
	system("cls");
	ViewNamesMap(SetMap);

	std::cout << "������� ��� ��������� ��� ��������: ";

	std::string name;

	std::cin >> name;

	if (!CheckNameIsExist(SetMap, name))
		return;

	SetMap.erase(name);

	system("pause");

	return;
}

void MenuSolveOne(std::map<std::string, MathSet>& SetMap)
{
	MathSet set1;
	MathSet set2;

	MathSet result;

	int navig;

	system("cls");

	std::cout << "��������� ��������" << std::endl << std::endl;
	std::cout << "1. ����������" << std::endl;
	std::cout << "2. �����������" << std::endl;
	std::cout << "3. �����������" << std::endl;
	std::cout << "4. ��������" << std::endl;
	std::cout << "5. ������������� ��������" << std::endl;
	std::cout << std::endl << "������� ����� ��������: ";

	std::cin >> navig;

	if (navig < 1 || navig > 5)
	{
		std::cout << "�������� �� ���������� ������ �� ����������. �������� ������������ �����." << std::endl;
		system("pause");
		return;
	}

	system("cls");
	ViewNamesMap(SetMap);

	bool isCorrect;
	std::string name;

	do
	{
		std::cout << "������� ��� ������� ���������: ";
		std::cin >> name;

		isCorrect = CheckNameIsExist(SetMap, name);
	} while (!isCorrect);

	set1 = SetMap[name];

	if (navig != 1)
	{
		do
		{
			std::cout << std::endl << "������� ��� ������� ���������: ";
			std::cin >> name;

			isCorrect = CheckNameIsExist(SetMap, name);
		} while (!isCorrect);

		set2 = SetMap[name];
	}

	switch (navig)
	{
	case 1:
		result = ResultAddition(set1, "result");
		break;
	case 2:
		result = ResultUnion(set1, set2, "result");
		break;
	case 3:
		result = ResultCross(set1, set2, "result");
		break;
	case 4:
		result = ResultMinus(set1, set2, "result");
		break;
	case 5:
		result = ResultMinusSym(set1, set2, "result");
		break;
	}

	std::cout << "��������� ��������" << std::endl << std::endl;

	ViewSetContent(result);

	system("pause");

	return;

}

void MenuSolveFormula(std::map<std::string, MathSet>& SetMap)
{
	system("cls");
	ViewNamesMap(SetMap);

	std::cout << "������� ���� ��������\n'-' ����������\n'+' �����������\n'*' �����������\n'/' ��������\n'|' ������������� ��������" << std::endl << std::endl;

	std::cout << "������� �������:" << std::endl << std::endl;

	std::string formulaString;

	std::cin.ignore();

	std::getline(std::cin, formulaString);

	MathSet result = FormulaSolve(SetMap, formulaString);

	if (result.GetName() == "NoCloseBracket")
	{
		std::cout << "����������� ����������� ������. �������� ������������ ������ �������." << std::endl << std::endl;
	}
	else if (result.GetName() == "NoOpenBracket")
	{
		std::cout << "����������� ����������� ������. �������� ������������ ������ �������." << std::endl << std::endl;
	}
	else if (result.GetName() == "NoSetName")
	{
		std::cout << "������� ��� ���������, �������������� � �������.\n�������� ������������ ������ ������� ��� ������� ������������� ���������." << std::endl << std::endl;
	}
	else
	{
		std::cout << "��������� ����������" << std::endl << std::endl;

		ViewSetContent(result);
	}

	system("pause");

	return;
}
