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



// @file functions.h
//
// This file contains a list of all functions that will be visible across
// multiple files.
#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_



#include <iostream>
#include "board.h"
#include "move.h"



using namespace std;



unsigned int    bitCnt(Bitboard);
int             captgen(int);
void            dataInit();
void            displayBitboard(Bitboard);
void            displayMove(Move &);
void            displayPV();
void            displayUCIPV();
void            commands();
unsigned int    firstOne(Bitboard);
bool            isAttacked(Bitboard &, const unsigned char &);
bool            isOtherKingAttacked();
bool            isOwnKingAttacked();
unsigned int    lastOne(Bitboard);
void            makeBlackPromotion(unsigned int, unsigned int &);
void            makeCapture(unsigned int &, unsigned int &);
void            makeMove(Move &);
void            makeWhitePromotion(unsigned int, unsigned int &);
int             movegen(int);
void            mstostring(uint64_t dt, char *);
uint64_t        perft(int, int);
bool            readFen(char *);
void            setupFen(char *, char *, char *, char *, int , int );
void            test(char *);
bool            toSan(Move &, char *);
void            unmakeBlackPromotion(unsigned int, unsigned int &);
void            unmakeCapture(unsigned int &, unsigned int &);
void            unmakeMove(Move &);
void            unmakeWhitePromotion(unsigned int, unsigned int &);
string          getInput();
void            terminateApp();
bool            isValidTextMove(string, Move &);
string          getBoardSerial(string, int, int, int);
string          getMLreply();
bool            sortByScore(const tuple<string, string, float>&, const tuple<string, string, float>&);
void            resetTimeControl();
string          moveToUCI(Move);


// isPiece()
//
// Check if the given character represents a piece (N for Knight, B for
// Bishop, R for Rook, Q for Queen and K for King).
inline bool isPiece(char p)
{
    return ((p == 'N') || (p == 'B') || (p == 'R') || (p == 'Q') ||
            (p == 'K'));
}




#endif // _FUNCTIONS_H_
