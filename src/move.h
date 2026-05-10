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



// @file move.h
//
// This file contains the Move structure.
#ifndef _MOVE_H_
#define _MOVE_H_



#include "definitions.h"



//  There are at least 3 different ways to store a move in max 32 bits
//  1) using shift & rank in an unsigned int                
//  2) using 4 unsigned chars, union-ed with an unsigned int
//  3) using C++ bitfields, union-ed with an unsigned int   


//  this is 1) using shift & rank in an unsigned int (32 bit):
struct Move                                  
{
    // from (6 bits)
    // tosq (6 bits)
    // piec (4 bits)
    // capt (4 bits)
    // prom (4 bits)
    int moveInt;

    void clear();
    void setFrom(unsigned int);
    void setTosq(unsigned int);  
    void setPiece(unsigned int);  
    void setCapture(unsigned int);  
    void setPromo(unsigned int); 
    unsigned int getFrom();  
    unsigned int getTosq();  
    unsigned int getPiece();  
    unsigned int getCapture();
    unsigned int getPromo();  
    bool isWhiteMove();
    bool isBlackMove();
    bool isCapture();
    bool isKingCaptured();
    bool isRookMove();
    bool isRookCaptured();
    bool isKingMove();
    bool isPawnMove();
    bool isPawnDoubleMove();
    bool isEnpassant();
    bool isPromo();
    bool isCastle();
    bool isCastleOO();
    bool isCastleOOO();
};



#endif // _MOVE_H_
