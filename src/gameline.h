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



// @file gameline.h
//
// This file contains the necessary structure to keep a record of every move in
// the game line.
#ifndef _GAMELINE_H_
#define _GAMELINE_H_



#include "move.h"



struct GameLineRecord
{
    Move move;
    unsigned char castleWhite;     // White's castle status, CANCASTLEOO = 1, CANCASTLEOOO = 2
    unsigned char castleBlack;     // Black's castle status, CANCASTLEOO = 1, CANCASTLEOOO = 2
    int epSquare;                  // En-passant target square after double pawn move
    int fiftyMove;                 // Moves since the last pawn move or capture
    uint64_t key;                  // hash key of the position
};



#endif // _GAMELINE_H_
