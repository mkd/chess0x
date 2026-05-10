// This file is part of Chess0x, a computer chess program based on Winglet chess
// by Stef Luijten.
//
// Copyright (C) 2022 Claudio M. Camacho
//
// Chess0x is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Chess0x is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Foobar. If not, see <http://www.gnu.org/licenses/>.



// @file cmd.h
//
// This file contains all the variables and method definitions that are used by
// exec.cpp to run commands inside the application.
#ifndef _CMD_H_
#define _CMD_H_



#include <vector>
#include "definitions.h"



using namespace std;



// Application methods
void initListOfCommands();
void exec(string);
uint64_t perft(unsigned, ColorType);
void displayHelp(string);
void displayEval();
void displayMaterial();
void displayGameStatus();



#endif // _CMD_H_
