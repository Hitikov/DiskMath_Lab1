#include "MathSet.h"

MathSet::MathSet()
{
	content = std::vector<int>();
	name = "NULL";
}

MathSet::MathSet(std::vector<int> inVector, std::string inName)
{
	content = inVector;
	name = inName;
}

MathSet::MathSet(std::string inName)
{
	content = std::vector<int>();
	name = inName;
}

MathSet::MathSet(const MathSet& inSet)
{
	content = inSet.content;
	name = inSet.name;
}

std::string MathSet::GetName()
{
	return name;
}

std::vector<int> MathSet::GetContent()
{
	return content;
}

MathSet MathSet::operator=(const MathSet& orig)
{
	this->content = orig.content;
	this->name = orig.name;

	return *this;
}

MathSet ResultAddition(MathSet Set1, std::string newName)
{
	std::vector<int> result;

	std::vector<int> base1 = Set1.GetContent();

	int i1 = 0;
	int addInt;


	for (int i = 0; i < 201; i++)
	{
		addInt = i - 100;
		if (i1 < base1.size()) {
			if (base1[i1] != addInt) {
				result.push_back(addInt);
			}
			else {
				++i1;
			}
		}
		else
			result.push_back(addInt);
	}

	MathSet newSet(result, newName);

	return newSet;
}

MathSet ResultCross(MathSet Set1, MathSet Set2, std::string newName)
{
	std::vector<int> result;

	std::vector<int> base1 = Set1.GetContent();
	std::vector<int> base2 = Set2.GetContent();

	int i1 = 0;
	int i2 = 0;

	while (i1 < base1.size() && i2 < base2.size())
	{
		if (base1[i1] < base2[i2]) {
			++i1;
		}
		else if (base2[i2] < base1[i1])
		{
			++i2;
		}
		else
		{
			result.push_back(base1[i1]);
			++i1;
			++i2;
		}
	}

	MathSet newSet(result, newName);

	return newSet;
}

MathSet ResultUnion(MathSet Set1, MathSet Set2, std::string newName)
{
	std::vector<int> result;

	std::vector<int> base1 = Set1.GetContent();
	std::vector<int> base2 = Set2.GetContent();

	int i1 = 0;
	int i2 = 0;

	while (i1 < base1.size() || i2 < base2.size())
	{
		if (i1 == base1.size())
		{
			result.push_back(base2[i2]);
			++i2;
		}
		else if (i2 == base2.size())
		{
			result.push_back(base1[i1]);
			++i1;
		}
		else
		{
			if (base1[i1] < base2[i2]) {
				result.push_back(base1[i1]);
				++i1;
			}
			else if (base2[i2] < base1[i1])
			{
				result.push_back(base2[i2]);
				++i2;
			}
			else
			{
				result.push_back(base1[i1]);
				++i1;
				++i2;
			}
		}
	}

	MathSet newSet(result, newName);

	return newSet;
}

MathSet ResultMinus(MathSet Set1, MathSet Set2, std::string newName)
{
	std::vector<int> result;

	std::vector<int> base1 = Set1.GetContent();
	std::vector<int> base2 = Set2.GetContent();

	int i1 = 0;
	int i2 = 0;

	while (i1 < base1.size() || i2 < base2.size())
	{
		if (i2 == base2.size())
		{
			result.push_back(base1[i1]);
			++i1;
		}
		else if (i1 == base1.size())
		{
			i2 = base2.size();
		}
		else
		{
			if (base1[i1] == base2[i2])
			{
				++i1;
				++i2;
			}
			else if (base1[i1] < base2[i2]) {
				result.push_back(base1[i1]);
				++i1;
			}
			else
			{
				++i2;
			}
		}
	}

	MathSet newSet(result, newName);;

	return newSet;
}

MathSet ResultMinusSym(MathSet Set1, MathSet Set2, std::string newName)
{
	std::vector<int> result;

	std::vector<int> base1 = Set1.GetContent();
	std::vector<int> base2 = Set2.GetContent();

	int i1 = 0;
	int i2 = 0;

	while (i1 < base1.size() || i2 < base2.size())
	{
		if (i1 == base1.size())
		{
			result.push_back(base2[i2]);
			++i2;
		}
		else if (i2 == base2.size())
		{
			result.push_back(base1[i1]);
			++i1;
		}
		else
		{
			if (base1[i1] == base2[i2])
			{
				++i1;
				++i2;
			}
			else if (base1[i1] < base2[i2]) {
				result.push_back(base1[i1]);
				++i1;
			}
			else if (base1[i1] > base2[i2])
			{
				result.push_back(base2[i2]);
				++i2;
			}
		}
	}

	MathSet newSet(result, newName);

	return newSet;
}