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



// @file definitions.h
//
// This file contains all the necessary definitions for the program to run,
// including application-specific definitions, game definitions, chess board
// definitions, piece types, move types, square values, etc.
#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_



#include <stdint.h>



#define PROGRAM_NAME    "Chess0"
#define PROGRAM_VERSION "1.3"
#define PROGRAM_AUTHOR  "Claudio M. Camacho <claudiomkd@gmail.com>"
#define PROGRAM_WEB     "http://github.com/mkd/chess0x"



#define MAX_CMD_BUFF     256   // Console command input buffer
#define MAX_INPUT_SIZE   256   // Console command input buffer
#define MAX_MOV_BUFF    4096   // Max number of moves that we can store (all plies)
#define MAX_PLY           64   // Max search depth
#define MAX_GAME_LINE   1024   // Max number of moves in the (game + search) line that we can store



// Search algorithm configuration
#define AI_SEARCH_DEPTH           64
#define SEARCH_WINDOW_SIZE        16
#define TIME_PER_MOVE              5
#define LMR_PLY_START              3
#define LMR_MOVE_START             3
#define LMR_SEARCH_DEPTH           3


#define SOLVE_MAX_DEPTH           64
#define SOLVE_MAX_TIME         18000
#define THINK_MAX_TIME        999999
#define NODES_TEST_DEPTH          64
#define NODES_TEST_TIME           20
#define MOVES_TEST_TIMES      250000
#define MOVES_TEST_ITER    100000000
#define PERFT_DEPTH_LIMIT          6


#define TT_EMPTY_VALUE             0
#define CACHE_HIT_LEVEL          0.6
#define BOARD_SERIAL_SIZE         16



// Define color types: +1 for white, -1 for black, 0 for none.
enum ColorType
{
    COLOR_TYPE_BLACK = -1,
    COLOR_TYPE_WHITE =  1,
    COLOR_TYPE_NONE  =  0,
    COLOR_TYPE_BOTH  =  2,
};



// End types.
enum EndType
{
    END_TYPE_NOEND,
    END_TYPE_ABORT,
    END_TYPE_RESIGN,
    END_TYPE_MATE,
    END_TYPE_DRAW,
    END_TYPE_DRAW_50RULE,
    END_TYPE_DRAW_3RULE,
    END_TYPE_DRAW_PIECES,
    END_TYPE_DRAW_AGREE,
    END_TYPE_DRAW_STALE,
    END_TYPE_SOLVE,
};



typedef uint64_t Bitboard;



#endif // _DEFINITIONS_H_
