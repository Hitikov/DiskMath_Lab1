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
		std::cout << "Введенное множество не обнаружено. Проверте правильность ввода." << std::endl;
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
	std::cout << "Список имен множеств" << std::endl;

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

		std::cout << "1. Просмотр множеств" << std::endl;
		std::cout << "2. Создание множества" << std::endl;
		std::cout << "3. Удаление множества" << std::endl;
		std::cout << "4. Выполнение операции" << std::endl;
		std::cout << "5. Решение формулы" << std::endl;
		std::cout << "9. Завершение работы" << std::endl;

		std::cout << std::endl << "Введите команду: ";

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

	std::cout << "Введите имя множества для просмотра: ";

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

	std::cout << "Введите имя множества для добавления: ";

	std::string name;

	std::cin >> name;

	if (SetMap.find(name) != SetMap.end())
	{
		std::cout << "Обнаружено множество с идентичным именем. Проверте правильность ввода." << std::endl;
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
		std::cout << std::endl << "Изменить диапазон ввода? (y/n): ";
		std::cin.clear();
		std::cin >> buff;
	} while (buff != 'y' && buff != 'n');

	if (buff == 'y')
	{
		do
		{
			system("cls");
			std::cout << "Доступный диапазон [-100 ; 100]" << std::endl;
			std::cout << std::endl << "Введите нижнюю границу: ";
			std::cin >> start;
			std::cout << std::endl << "Введите верхнюю границу: ";
			std::cin >> end;
		} while (!((start <= end) && (-100 <= start && start <= 100) && (-100 <= end && end <= 100)));
	}

	do
	{
		system("cls");
		std::cout << std::endl << "Автоматизировать ввод? (y/n): ";
		std::cin >> buff;
	} while (buff != 'y' && buff != 'n');

	if (buff == 'y')
	{
		int howMuch;
		do
		{
			system("cls");
			std::cout << std::endl << "Введите количество элементов: ";
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
			std::cout << "Для остановки ввода введите любое значение за пределами диапазона или любую букву.\n\nВведите элемент: ";
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

	std::cout << "Введите имя множества для удаления: ";

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

	std::cout << "Доступные операции" << std::endl << std::endl;
	std::cout << "1. Дополнение" << std::endl;
	std::cout << "2. Объединение" << std::endl;
	std::cout << "3. Пересечение" << std::endl;
	std::cout << "4. Разность" << std::endl;
	std::cout << "5. Симетрическая разность" << std::endl;
	std::cout << std::endl << "Введите номер операции: ";

	std::cin >> navig;

	if (navig < 1 || navig > 5)
	{
		std::cout << "Операции по введенному номеру не обнаружено. Проверте правильность ввода." << std::endl;
		system("pause");
		return;
	}

	system("cls");
	ViewNamesMap(SetMap);

	bool isCorrect;
	std::string name;

	do
	{
		std::cout << "Введите имя первого множества: ";
		std::cin >> name;

		isCorrect = CheckNameIsExist(SetMap, name);
	} while (!isCorrect);

	set1 = SetMap[name];

	if (navig != 1)
	{
		do
		{
			std::cout << std::endl << "Введите имя второго множества: ";
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

	std::cout << "Результат операции" << std::endl << std::endl;

	ViewSetContent(result);

	system("pause");

	return;

}

void MenuSolveFormula(std::map<std::string, MathSet>& SetMap)
{
	system("cls");
	ViewNamesMap(SetMap);

	std::cout << "Словарь спец символов\n'-' дополнение\n'+' объединение\n'*' пересечение\n'/' разность\n'|' симетрическая разность" << std::endl << std::endl;

	std::cout << "Введите формулу:" << std::endl << std::endl;

	std::string formulaString;

	std::cin.ignore();

	std::getline(std::cin, formulaString);

	MathSet result = FormulaSolve(SetMap, formulaString);

	if (result.GetName() == "NoCloseBracket")
	{
		std::cout << "Отсутствует закрывающая скобка. Проверте правильность записи формулы." << std::endl << std::endl;
	}
	else if (result.GetName() == "NoOpenBracket")
	{
		std::cout << "Отсутствует открывающая скобка. Проверте правильность записи формулы." << std::endl << std::endl;
	}
	else if (result.GetName() == "NoSetName")
	{
		std::cout << "Найдено имя множества, отсутствующего в словаре.\nПроверте правильность записи формулы или добавте отсутствующее множество." << std::endl << std::endl;
	}
	else
	{
		std::cout << "Результат вычислений" << std::endl << std::endl;

		ViewSetContent(result);
	}

	system("pause");

	return;
}
