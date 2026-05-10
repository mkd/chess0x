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



// @file displaymove.cpp
//
// This is the implementation of showing moves in Simplified Algebraic
// Notation (SAN) format.
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#include "definitions.h"
#include "functions.h"
#include "extglobals.h"


using namespace std;



// displayMove()
//
// Display a single move on the console, no disambiguation.
void displayMove(Move &move)
{
    if (((move.getPiece() == WHITE_KING) && (move.isCastleOO())) || ((move.getPiece() == BLACK_KING) && (move.isCastleOO())))
    {
        cout << "0-0";
        return;      
    };

    if (((move.getPiece() == WHITE_KING) && (move.isCastleOOO())) || ((move.getPiece() == BLACK_KING) && (move.isCastleOOO())))
    {
        cout << "0-0-0";
        return;      
    };

    if (!move.isPawnMove()) cout << PIECECHARS[move.getPiece()];
    if (move.isPawnMove() && move.isCapture()) cout << char('a' + FILES[move.getFrom()]-1);
    if (move.isCapture()) cout << "x" ; 
    cout << char('a' + FILES[move.getTosq()]-1);
    cout << RANKS[move.getTosq()]; 
    if (move.isPromo()) 
    {
        cout << "=";
        cout << PIECECHARS[move.getPromo()];
    }
    cout.flush();
    return;
}



// displayPV()
//
// Display the list of moves in the Principal Variation.
void displayPV()
{
    int i;
    char sanMove[12];

    for (i = 0; i < board.triangularLength[0]; i++) 
    {
        toSan(board.triangularArray[0][i], sanMove);
        cout << sanMove << " ";
        makeMove(board.triangularArray[0][i]);
    }
    for (i = board.triangularLength[0]-1; i >= 0; i--) 
    {
        unmakeMove(board.triangularArray[0][i]);
    }

    // make sure to overwrite any remaining output of mode 3
    if (i < 3)
        cout << "     ";
    cout << endl;
    cout.flush();
}



// displayUCIPV()
//
// Display the list of moves in the Principal Variation, in UCI format
// (i.e., "e2e4")
void displayUCIPV()
{
    int i;

    for (i = 0; i < board.triangularLength[0]; i++) 
    {
        cout << moveToUCI(board.triangularArray[0][i]) << " ";
        makeMove(board.triangularArray[0][i]);
    }
    for (i = board.triangularLength[0]-1; i >= 0; i--) 
    {
        unmakeMove(board.triangularArray[0][i]);
    }

    // make sure to overwrite any remaining output of mode 3
    if (i < 3)
        cout << "     ";
    cout << endl;
    cout.flush();
}



// toSan()
//
//  toSan will convert a move into non-ambiguous SAN-notation, returned in char sanMove[].
//  "move" must belong to the current "board". Returns true if successful.
//  The move is compared with other moves from the current board position. 
//  Ambiguities can arise if two (or more) identical pieces can move to the same square.
//  In such cases, the piece's initial is followed by (in this priority):
//  - the from file, if it's unique, 
//  - or else the from rank, if it's unique
//  - or else the from file and rank (this can happen after pawn promotions, 
//    e.g. with 4 rooks on c3, c7, a5 and e5; they all can move to c5, and then move notation would be: R3c5
//  'e.p.' is added for an en-passant capture 
//  '+'is added for check, '#' is added for mate.
bool toSan(Move &move, char *sanMove)
{
    unsigned int i, j, k, ibuf, from, to, piece, capt, prom, ambigfile, ambigrank;
    int asciiShift;
    bool legal, check, mate, ambig;

    asciiShift    = (int)'a';
    piece = move.getPiece();
    from = move.getFrom();
    to = move.getTosq();
    capt = move.getCapture();
    prom = move.getPromo();
    ibuf = 0;
    ambig = false;
    ambigfile = 0;
    ambigrank = 0;
    legal = false;
    check = false;
    mate = false;
    sprintf(sanMove, "");


    //  Generate all pseudo-legal moves to be able to remove any ambiguities 
    //  and check legality. Take the next free location in moveBufLen:
    while (board.moveBufLen[ibuf+1]) ibuf++;
    board.moveBufLen[ibuf+1] = movegen(board.moveBufLen[ibuf]);


    //  Loop over the moves to see what kind(s) of ambiguities exist, if any:
    for (i = board.moveBufLen[ibuf]; i < board.moveBufLen[ibuf+1]; i++)
    {
        makeMove(board.moveBuffer[i]);
        if (!isOtherKingAttacked())
        {
            if (board.moveBuffer[i].moveInt == move.moveInt) 
            {
                legal = true;
                // it is check:
                if (isOwnKingAttacked()) 
                {
                    check = true;
                    // is it checkmate?
                    k = 0;
                    board.moveBufLen[ibuf+2] = movegen(board.moveBufLen[ibuf+1]);
                    for (j = board.moveBufLen[ibuf+1]; j < board.moveBufLen[ibuf+2]; j++)
                    {
                        makeMove(board.moveBuffer[j]);
                        if (!isOtherKingAttacked()) k++;
                        unmakeMove(board.moveBuffer[j]);
                    }
                    if (!k) mate = true;
                }
            }
            // two same pieces can move to the same square:
            if ((board.moveBuffer[i].moveInt != move.moveInt) && (board.moveBuffer[i].getPiece() == piece) && (board.moveBuffer[i].getTosq() == to)) 
            {
                ambig = true;
                if (FILES[from] == FILES[board.moveBuffer[i].getFrom()]) ambigfile++; 
                if (RANKS[from] == RANKS[board.moveBuffer[i].getFrom()]) ambigrank++; 
            }
        }
        unmakeMove(board.moveBuffer[i]);
    }


    //  cleanup:
    board.moveBufLen[ibuf+1] = 0;
    board.moveBufLen[ibuf+2] = 0;


    //  construct the SAN string:
    if (!legal) 
    {
        strcpy(sanMove, "(null)");
        return false;
    }
    else
    {
        if (move.isCastleOO())
        {
            strcpy(sanMove, "0-0");
            return true;
        }   
        if (move.isCastleOOO())
        {
            strcpy(sanMove, "0-0-0");
            return true;
        }   
        // start building the string
        if (!move.isPawnMove()) 
        {
            sprintf(sanMove, "%s", PIECECHARS[piece]);
            if (ambig) 
            {
                if (ambigfile)
                {
                    if (ambigrank) sprintf(sanMove, "%s%c%d", sanMove, FILES[from] + asciiShift - 1,RANKS[from]);
                    else sprintf(sanMove, "%s%d", sanMove, RANKS[from]);
                }
                else
                {
                    sprintf(sanMove, "%s%c", sanMove, FILES[from] + asciiShift - 1);
                }
            }
        }
        else
        {
            if (move.isCapture()) 
            {
                sprintf(sanMove, "%s%c", sanMove, FILES[from] + asciiShift - 1);
            }
        }
        if (move.isCapture()) sprintf(sanMove, "%sx", sanMove);
        sprintf(sanMove, "%s%c%d", sanMove, FILES[to] + asciiShift - 1, RANKS[to]);
        if (move.isEnpassant()) sprintf(sanMove, "%s", sanMove);
        if (move.isPromo()) sprintf(sanMove, "%s=%s", sanMove, PIECECHARS[prom]);
        if (check)
        {
            if (mate) sprintf(sanMove, "%s#", sanMove); 
            else sprintf(sanMove, "%s+", sanMove);
        }
        return true;
    }
}




// moveToUCI
//
// Convert a Move object into a UCI move string (i.e, "e2e4").
string moveToUCI(Move mv)
{
    string UCImove;
    string s1, s2, tmpStr;

    s1 = SQUARENAME[mv.getFrom()];
    s2 = SQUARENAME[mv.getTosq()];
    tmpStr = s1 + s2;

    // if promo, append promo piece
    if (mv.isPromo())
    {
        string tc(PIECECHARS[mv.getPromo()]);
        tmpStr += tc;
        transform(tmpStr.begin(), tmpStr.end(), tmpStr.begin(), ::tolower);
    }

    return tmpStr;
}
