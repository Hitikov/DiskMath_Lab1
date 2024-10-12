#pragma once

#include "MathSet.h"
#include "FormulaSolve.h"

#include <iostream>
#include <algorithm>

void StartUp();

bool CheckNameIsExist(std::map<std::string, MathSet>&, std::string);
void ViewSetContent(MathSet);
void ViewNamesMap(std::map<std::string, MathSet>&);

void MenuMain(std::map<std::string, MathSet>&);
void MenuViewSets(std::map<std::string, MathSet>&);
void MenuMakeSet(std::map<std::string, MathSet>&);
void MenuDeleteSets(std::map<std::string, MathSet>&);
void MenuSolveOne(std::map<std::string, MathSet>&);
void MenuSolveFormula(std::map<std::string, MathSet>&);