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



// @file book.h
//
// This file contains the structures to hold an opening book database for the
// chess engine.
#ifndef _BOOK_H_
#define _BOOK_H_



#include <unordered_map>



using namespace std;



// Book functionality
void initBook();
string getReplyTo(string);



// Dictionary containing the database with the openings. We use unordered_map
// because it is the fastest STL data structure for this purpose.
extern unordered_map<string, string> book;



#endif // _BOOK_H_
