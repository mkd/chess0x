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



// @file board.h
//
// Board specification and behavior.
//
//  A7 B7 C7 D7 E7 F7 G7 H7
//  A6 B6 C6 D6 E6 F6 G6 H6
//  A5 B5 C5 D5 E5 F5 G5 H5
//  A4 B4 C4 D4 E4 F4 G4 H4
//  A3 B3 C3 D3 E3 F3 G3 H3
//  A2 B2 C2 D2 E2 F2 G2 H2
//  A1 B1 C1 D1 E1 F1 G1 H1
// 
//  56 57 58 59 60 61 62 63
//  48 49 50 51 52 53 54 55
//  40 41 42 43 44 45 46 47
//  32 33 34 35 36 37 38 39
//  24 25 26 27 28 29 30 31
//  16 17 18 19 20 21 22 23
//   8  9 10 11 12 13 14 15
//   0  1  2  3  4  5  6  7
#ifndef _BOARD_H_
#define _BOARD_H_



#include "definitions.h"
#include "move.h"
#include "gameline.h"
#include "timer.h"



using namespace std;



struct Board
{
    Bitboard whiteKing, whiteQueens, whiteRooks, whiteBishops, whiteKnights, whitePawns;
    Bitboard blackKing, blackQueens, blackRooks, blackBishops, blackKnights, blackPawns;
    Bitboard whitePieces, blackPieces, occupiedSquares;

    unsigned char nextMove;        // WHITE_MOVE or BLACK_MOVE
    unsigned char castleWhite;     // White's castle status, CANCASTLEOO = 1, CANCASTLEOOO = 2
    unsigned char castleBlack;     // Black's castle status, CANCASTLEOO = 1, CANCASTLEOOO = 2
    int epSquare;                  // En-passant target square after double pawn move
    int fiftyMove;                 // Moves since the last pawn move or capture
    uint64_t hashkey;                   // Random 'almost' unique signature for current board position.

    // additional variables:
    int square[64];                // incrementally updated, this array is usefull if we want to

    // probe what kind of piece is on a particular square.
    int Material;                  // incrementally updated, total material balance on board,

    // in centipawns, from white’s side of view
    int totalWhitePawns;           // sum of P material value for white (in centipawns)
    int totalBlackPawns;           // sum of P material value for black  (in centipawns)
    int totalWhitePieces;          // sum of Q+R+B+N material value for white (in centipawns)
    int totalBlackPieces;          // sum of Q+R+B+N material value for black  (in centipawns)

    bool flipBoard;          // only used for displaying the board. TRUE or FALSE.


    // storing moves
    Move moveBuffer[MAX_MOV_BUFF];      // all generated moves of the current search
    unsigned int moveBufLen[MAX_PLY];   // this arrays keeps track of which moves belong to which ply
    int endOfGame;                 // index for board.gameLine
    int endOfSearch;               // index for board.gameLine
    GameLineRecord gameLine[MAX_GAME_LINE];


    // search variables:
    int triangularLength[MAX_PLY];
    Move triangularArray[MAX_PLY][MAX_PLY];
    Timer timer;
    uint64_t msStart, msStop;
    int searchDepth;
    int lastPVLength;
    Move lastPV[MAX_PLY];
    unsigned int whiteHeuristics[64][64];
    unsigned int blackHeuristics[64][64];
    bool followPV;
    bool scorePV;
    bool allownull;
    uint64_t nodes;
    uint64_t countdown;
    uint64_t maxTime; 
    bool timedout;
    bool ponder;


    void init();
    int eval();
    Move think();
    int alphabetapvs(int ply, int depth, int alpha, int beta);
    int qsearch(int ply, int alpha, int beta);
    void displaySearchStats(int mode, int depth, int score);
    bool isEndOfgame(int &legalmoves, Move &singlemove);
    int repetitionCount();
    void initFromSquares(int input[64], unsigned char next, int fiftyM, int castleW, int castleB, int epSq);
    void display();
    void rememberPV();
    void selectmove(int &ply, unsigned int &i, int &depth, bool &followpv); 
    void addCaptScore(int &ifirst, int &index);
    int SEE(Move &move);
    Bitboard attacksTo(int &target);
    Bitboard revealNextAttacker(Bitboard &attackers, Bitboard &nonremoved, int &target, int &heading);
    void readClockAndInput();
    string toFEN();

};



#endif // _BOARD_H_
