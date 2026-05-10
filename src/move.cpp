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



// @file move.cpp
//
// This file contains operations to work set and get information from Move
// objects.
#include <sstream>
#include "move.h"



using namespace std;



// Move::clear()
//
// Set a move to null/void. 
void Move::clear()
{
    moveInt = 0;
}



// Move::setFrom()
//
// Set the origin square of the moving piece (bits 0..5). 
void Move::setFrom(unsigned int from)  
{ 
    moveInt &= 0xffffffc0;
    moveInt |= (from & 0x0000003f);
}



// Move::setTosq()
//
// Set the destination square of the moving piece (bits 6..11).
void Move::setTosq(unsigned int tosq)  
{
    moveInt &= 0xfffff03f;
    moveInt |= (tosq & 0x0000003f) << 6;
}



// Move::setPiece()
//
// Set the moving piece (bits 12..15).
void Move::setPiece(unsigned int p)  
{
    moveInt &= 0xffff0fff;
    moveInt |= (p & 0x0000000f) << 12;
} 



// Move::setCapture 
//
// Set the captured piece of the move (bits 16..19).
void Move::setCapture(unsigned int c)
{
    moveInt &= 0xfff0ffff;
    moveInt |= (c & 0x0000000f) << 16;
} 



// Move::setPromo()
//
// Set the promotion piece of the move (bits 20..23). 
void Move::setPromo(unsigned int p)
{
    moveInt &= 0xff0fffff;
    moveInt |= (p & 0x0000000f) << 20;
} 



// Move::getFrom()
//
// Get the origin square of the moving piece (bits 0..5). 
unsigned int Move::getFrom()  
{
    return (moveInt & 0x0000003f);
}



// Move::getTosq()
//
// Get the destination square of the moving piece (bits 6..11). 
unsigned int Move::getTosq()
{
    return (moveInt >> 6) & 0x0000003f; 
}



// Move::getPiece()
//
// Get the moving piece (bits 12..15). 
unsigned int Move::getPiece()
{
    return (moveInt >> 12) & 0x0000000f; 
}   



// Move::getCapture()
//
// Get the captured piece (bits 16..19). 
unsigned int Move::getCapture()
{
    return (moveInt >> 16) & 0x0000000f; 
}   



// Move::getPromo()
//
// Get the promotion piece from a move (bits 20..23). 
unsigned int Move::getPromo()
{
    return (moveInt >> 20) & 0x0000000f; 
}   



// Move::isWhiteMove()
//
// The moving piece is white (bit 15 = 0).
bool Move::isWhiteMove()
{
    return (~moveInt & 0x00008000) == 0x00008000;
} 



// Move::isBlackMove()
//
// The moving piece is black (bit 15 = 1). 
bool Move::isBlackMove()
{
    return (moveInt & 0x00008000) == 0x00008000;
} 



// Move:isCapture()
//
// The move is a capture (bits 16 and 19 != 0). 
bool Move::isCapture()
{
    return (moveInt & 0x000f0000) != 0x00000000;
} 



// Move::isKingCaptured()
//
// Detect if the captured piece is a king (bits 17..19 = 010). 
bool Move::isKingCaptured()
{
    return (moveInt & 0x00070000) == 0x00020000;
} 



// Move::isRookMove()
//
// The moving piece is a rook (bits 13..15 = 110). 
bool Move::isRookMove()
{
    return (moveInt & 0x00007000) == 0x00006000;
}



// Move::isRookCaptured()
//
// Captured piece is a rook (bits 17..19 = 110). 
bool Move::isRookCaptured()
{
    return (moveInt & 0x00070000) == 0x00060000;
}



// Move::isKingMove() 
//
// The moving piece is a king (bits 13..15 = 010).
bool Move::isKingMove()
{
    return (moveInt & 0x00007000) == 0x00002000;
} 



// Move::isPawnMove()
//
// The moving piece is a pawn (bits 13..15 = 001).
bool Move::isPawnMove()
{
    return (moveInt & 0x00007000) == 0x00001000;
} 



// Move::isPawnDoubleMove()
//
// The move is a 2-step pawn move (bits 13..15 = 001, AND
//     bits 4 to 6 must be 001 (from rank 2) & bits 10 to 12 must be 011 (to rank 4)
// OR: bits 4 to 6 must be 110 (from rank 7) & bits 10 to 12 must be 100 (to rank 5)
bool Move::isPawnDoubleMove()
{
    return (((moveInt & 0x00007000) == 0x00001000) && ((((moveInt & 0x00000038) == 0x00000008) && (((moveInt & 0x00000e00) == 0x00000600))) || 
                (((moveInt & 0x00000038) == 0x00000030) && (((moveInt & 0x00000e00) == 0x00000800)))));
} 



// Move::isEnpassant()
//
// The move is an enpassant capture (bits 21..23 = 001). 
bool Move::isEnpassant()
{
    return (moveInt & 0x00700000) == 0x00100000;
} 



// Move::isPromo()
//
// The move is a promotion (with color bit removed, .xxx > 2 (not king or
// pawn)).
bool Move::isPromo()  
{
    return (moveInt & 0x00700000) >  0x00200000;
} 



// Move::isCastle()
//
// The move is a castle (bits 21..23 = 010). 
bool Move::isCastle()
{
    return (moveInt & 0x00700000) == 0x00200000;
} 



// Move::isCastleOO()
//
// The move is a short castle (prom is king and tosq is on the g-file). 
bool Move::isCastleOO()
{
    return (moveInt & 0x007001c0) == 0x00200180;
} 



// Move::isCastleOOO()
//
// The move is a long castle (prom is a king and tosq is on the c-file).
bool Move::isCastleOOO()
{
    return (moveInt & 0x007001c0) == 0x00200080;
}
