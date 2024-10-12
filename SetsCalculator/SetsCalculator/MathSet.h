#pragma once

#include <vector>
#include <string>
#include <map>

class MathSet
{
public:

	MathSet();

	MathSet(std::vector<int>, std::string);

	MathSet(std::string);

	MathSet(const MathSet&);

	std::string GetName();

	std::vector<int> GetContent();

	MathSet operator=(const MathSet&);

	friend MathSet ResultAddition(MathSet Set1, std::string newName);

	friend MathSet ResultCross(MathSet Set1, MathSet Set2, std::string newName);

	friend MathSet ResultUnion(MathSet Set1, MathSet Set2, std::string newName);

	friend MathSet ResultMinus(MathSet Set1, MathSet Set2, std::string newName);

	friend MathSet ResultMinusSym(MathSet Set1, MathSet Set2, std::string newName);

private:

	std::vector<int> content;
	
	std::string name;

};