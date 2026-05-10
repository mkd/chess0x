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



// @file extglobals.h
//
// This file includes external global variables to give direct access to
// them from anywhere in the program. This quirk is used to speed-up the
// search in most cases.
#ifndef _EXTGLOBALS_H_
#define _EXTGLOBALS_H_

#include <iostream>
#include <vector>
#include <unordered_map>
#include <vector>
#include "definitions.h"
#include "board.h"
#include "hash.h"

using namespace std;



extern char INIFILE[];
extern char PATHNAME[];
extern char CMD_BUFF[];
extern int CMD_BUFF_COUNT;

extern Board board;
extern vector<tuple<string, string, float>> ML;
extern vector<tuple<string, string, float>> learned;

extern const int A8; extern const int B8; extern const int C8; extern const int D8;
extern const int E8; extern const int F8; extern const int G8; extern const int H8;
extern const int A7; extern const int B7; extern const int C7; extern const int D7;
extern const int E7; extern const int F7; extern const int G7; extern const int H7;
extern const int A6; extern const int B6; extern const int C6; extern const int D6;
extern const int E6; extern const int F6; extern const int G6; extern const int H6;
extern const int A5; extern const int B5; extern const int C5; extern const int D5;
extern const int E5; extern const int F5; extern const int G5; extern const int H5;
extern const int A4; extern const int B4; extern const int C4; extern const int D4;
extern const int E4; extern const int F4; extern const int G4; extern const int H4;
extern const int A3; extern const int B3; extern const int C3; extern const int D3;
extern const int E3; extern const int F3; extern const int G3; extern const int H3;
extern const int A2; extern const int B2; extern const int C2; extern const int D2;
extern const int E2; extern const int F2; extern const int G2; extern const int H2;
extern const int A1; extern const int B1; extern const int C1; extern const int D1;
extern const int E1; extern const int F1; extern const int G1; extern const int H1;

extern const char* SQUARENAME[];

extern const int FILES[];
extern const int RANKS[];

extern const unsigned char WHITE_MOVE; 
extern const unsigned char BLACK_MOVE; 

extern const unsigned char EMPTY;
extern const unsigned char WHITE_KNIGHT;
extern const unsigned char WHITE_PAWN;
extern const unsigned char WHITE_KING;
extern const unsigned char WHITE_BISHOP;
extern const unsigned char WHITE_ROOK;
extern const unsigned char WHITE_QUEEN;
extern const unsigned char BLACK_KNIGHT;
extern const unsigned char BLACK_PAWN;
extern const unsigned char BLACK_KING;
extern const unsigned char BLACK_BISHOP;
extern const unsigned char BLACK_ROOK;
extern const unsigned char BLACK_QUEEN;

extern const char* PIECENAMES[];
extern const char* PIECECHARS[];

extern Bitboard BITSET[];
extern int BOARDINDEX[9][9];

extern const int PAWN_VALUE;
extern const int KNIGHT_VALUE;
extern const int BISHOP_VALUE;
extern const int ROOK_VALUE;
extern const int QUEEN_VALUE;
extern const int KING_VALUE;
extern int PIECEVALUES[];

extern int MS1BTABLE[];

extern Bitboard WHITE_PAWN_ATTACKS[];
extern Bitboard WHITE_PAWN_MOVES[];
extern Bitboard WHITE_PAWN_DOUBLE_MOVES[];
extern Bitboard BLACK_PAWN_ATTACKS[];
extern Bitboard BLACK_PAWN_MOVES[];
extern Bitboard BLACK_PAWN_DOUBLE_MOVES[];
extern Bitboard KNIGHT_ATTACKS[];
extern Bitboard KING_ATTACKS[];
extern Bitboard RANK_ATTACKS[64][64];
extern Bitboard FILE_ATTACKS[64][64];
extern Bitboard DIAGA8H1_ATTACKS[64][64];
extern Bitboard DIAGA1H8_ATTACKS[64][64];

extern const int RANKSHIFT[];
extern const Bitboard _FILEMAGICS[];
extern const Bitboard _DIAGA8H1MAGICS[];
extern const Bitboard _DIAGA1H8MAGICS[];

extern Bitboard RANKMASK[];
extern Bitboard FILEMAGIC[];
extern Bitboard FILEMASK[];
extern Bitboard DIAGA8H1MASK[];
extern Bitboard DIAGA8H1MAGIC[];
extern Bitboard DIAGA1H8MASK[];
extern Bitboard DIAGA1H8MAGIC[];
extern Bitboard KINGCASTLED_MASK_W;
extern Bitboard KINGCASTLED_MASK_B;

extern unsigned char GEN_SLIDING_ATTACKS[8][64];

extern unsigned char CANCASTLEOO;
extern unsigned char CANCASTLEOOO;
extern Bitboard maskEG[];
extern Bitboard maskFG[];
extern Bitboard maskBD[];
extern Bitboard maskCE[];
extern unsigned int WHITE_OOO_CASTL;
extern unsigned int BLACK_OOO_CASTL;
extern unsigned int WHITE_OO_CASTL;
extern unsigned int BLACK_OO_CASTL;

extern int ICAPT;
extern int IEP;
extern int IPROM;
extern int ICASTLOO;
extern int ICASTLOOO;
extern int ICHECK;

extern int PENALTY_DOUBLED_PAWN_MG;
extern int PENALTY_DOUBLED_PAWN_EG;
extern int PENALTY_ISOLATED_PAWN_MG;
extern int PENALTY_ISOLATED_PAWN_EG;
extern int PENALTY_BACKWARD_PAWN_MG;
extern int PENALTY_BACKWARD_PAWN_EG;
extern int PENALTY_KING_ON_OPEN_FILE_AH;
extern int PENALTY_KING_ON_OPEN_FILE_BG;
extern int PENALTY_KING_ON_OPEN_FILE_CDEF;
extern int PENALTY_KING_ON_SEMIOPEN_ABGH;
extern int PENALTY_KING_ON_SEMIOPEN_CDEF;
extern int BONUS_PASSED_PAWN;
extern int BONUS_BISHOP_PAIR_MG;
extern int BONUS_BISHOP_PAIR_EG;
extern int BONUS_ROOK_BEHIND_PASSED_PAWN_MG;
extern int BONUS_ROOK_BEHIND_PASSED_PAWN_EG;
extern int BONUS_ROOK_ON_OPEN_FILE_MG;
extern int BONUS_ROOK_ON_OPEN_FILE_EG;
extern int BONUS_ROOK_ON_SEMIOPEN_FILE_MG;
extern int BONUS_ROOK_ON_SEMIOPEN_FILE_EG;
extern int BONUS_PAWN_SHIELD_STRONG;
extern int BONUS_PAWN_SHIELD_WEAK;
extern int BONUS_TEMPO_MIDGAME;
extern int BONUS_TEMPO_ENDGAME;
extern int PAWN_OWN_DISTANCE[];
extern int PAWN_OPPONENT_DISTANCE[];
extern int KNIGHT_DISTANCE[];
extern int BISHOP_DISTANCE[];
extern int ROOK_DISTANCE[];
extern int QUEEN_DISTANCE[];
extern int BONUS_KING_IS_CASTLED;


// short (s) and long (l) castle safety masks
extern Bitboard wKingSafeMask_S1;
extern Bitboard wKingSafeMask_SX;
extern Bitboard wKingSafeMask_L1;
extern Bitboard wKingSafeMask_LX;
extern Bitboard bKingSafeMask_S1;
extern Bitboard bKingSafeMask_SX;
extern Bitboard bKingSafeMask_L1;
extern Bitboard bKingSafeMask_LX;


extern int PAWNPOS_W_MG[];
extern int PAWNPOS_W_EG[];
extern int KNIGHTPOS_W_MG[];
extern int KNIGHTPOS_W_EG[];
extern int BISHOPPOS_W_MG[];
extern int BISHOPPOS_W_EG[];
extern int ROOKPOS_W[];
extern int QUEENPOS_W_MG[];
extern int QUEENPOS_W_EG[];
extern int KINGPOS_W_MG[];
extern int KINGPOS_W_EG[];
extern int MIRROR[];
extern int DISTANCE[64][64];
extern int PAWNPOS_B_MG[];
extern int PAWNPOS_B_EG[];
extern int KNIGHTPOS_B_MG[];
extern int KNIGHTPOS_B_EG[];
extern int BISHOPPOS_B_MG[];
extern int BISHOPPOS_B_EG[];
extern int ROOKPOS_B[];
extern int QUEENPOS_B_MG[];
extern int QUEENPOS_B_EG[];
extern int KINGPOS_B_MG[];
extern int KINGPOS_B_EG[];


extern Bitboard PASSED_WHITE[];
extern Bitboard PASSED_BLACK[];
extern Bitboard ISOLATED_WHITE[];
extern Bitboard ISOLATED_BLACK[];
extern Bitboard BACKWARD_WHITE[];
extern Bitboard BACKWARD_BLACK[];
extern Bitboard KINGSHIELD_STRONG_W[];
extern Bitboard KINGSHIELD_STRONG_B[];
extern Bitboard KINGSHIELD_WEAK_W[];
extern Bitboard KINGSHIELD_WEAK_B[];
extern Bitboard WHITE_SQUARES;
extern Bitboard BLACK_SQUARES;

extern int LARGE_NUMBER;
extern int CHECKMATESCORE;
extern int STALEMATESCORE;
extern int DRAWSCORE;
extern Move NOMOVE;
extern HashKeys KEY;

extern int OFFSET;
extern int MINCAPTVAL;
extern int WEST;
extern int NORTHWEST;
extern int NORTH;
extern int NORTHEAST;
extern int EAST;
extern int SOUTHEAST;
extern int SOUTH;
extern int SOUTHWEST;
extern Bitboard RAY_W[];
extern Bitboard RAY_NW[];
extern Bitboard RAY_N[];
extern Bitboard RAY_NE[];
extern Bitboard RAY_E[];
extern Bitboard RAY_SE[];
extern Bitboard RAY_S[];
extern Bitboard RAY_SW[];
extern int HEADINGS[64][64];

extern int NULLMOVE_REDUCTION;
extern int NULLMOVE_LIMIT;
extern int UPDATEINTERVAL;
extern double STOPFRAC;

extern int TO_CONSOLE;

extern float winingDelta;

extern string STARTPOS;

extern bool LMR;

extern bool beQuiet;

extern bool UCI;



// UCI time controls
extern int movestogo;
extern int movetime;
extern int comptime;
extern int otime;
extern int inc;
extern int starttime;
extern bool infsearch;

#endif // _EXTGLOBALS_H_
