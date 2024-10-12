#pragma once

#include "MathSet.h"

MathSet FormulaSolve(std::map<std::string, MathSet>, std::string);
MathSet FormulaSolveComposed(std::map<std::string, MathSet>&, std::string, int&);
MathSet FormulaSolveSimple(std::map<std::string, MathSet>&, std::string);