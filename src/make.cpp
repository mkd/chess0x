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



// @file make.cpp
//
// This file contains the code for making (and unmaking) a move. By making a
// move, the following things are updated:
//
// 1) update the board structure by moving the piece and removing any captured
//    piece. This involves the vector representation as well as all the
//    bitboards involved in the move.
//
// 2) update piece and material counts
//
// 3) update castling status, fifty-fold rule, 3-fold rule
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "definitions.h"
#include "functions.h"
#include "extglobals.h"
#include "move.h"



using namespace std;



// makeMove
//
// Apply a move to the current board.
void makeMove(Move &move)
{
    unsigned int from = move.getFrom();
    unsigned int to = move.getTosq();
    unsigned int piece = move.getPiece();
    unsigned int captured = move.getCapture();

    board.gameLine[board.endOfSearch].move.moveInt = move.moveInt;
    board.gameLine[board.endOfSearch].castleWhite  = board.castleWhite;
    board.gameLine[board.endOfSearch].castleBlack  = board.castleBlack;
    board.gameLine[board.endOfSearch].fiftyMove    = board.fiftyMove;
    board.gameLine[board.endOfSearch].epSquare     = board.epSquare;
    board.gameLine[board.endOfSearch].key          = board.hashkey;

    Bitboard fromBitboard  = BITSET[from];
    Bitboard fromToBitboard = fromBitboard  | BITSET[to];
    board.hashkey ^= (KEY.keys[from][piece] ^ KEY.keys[to][piece]);
    if (board.epSquare) board.hashkey ^= KEY.ep[board.epSquare];

    switch (piece)
    {
        case 1: // white pawn:
            board.whitePawns           ^= fromToBitboard;
            board.whitePieces          ^= fromToBitboard;
            board.square[from]        = EMPTY;
            board.square[to]          = WHITE_PAWN;
            board.epSquare            = 0;
            board.fiftyMove           = 0;
            if ((RANKS[from] == 2) && (RANKS[to] == 4)) 
            { 
                board.epSquare = from + 8;
                board.hashkey ^= KEY.ep[from + 8];
            }
            if (captured)
            {
                if (move.isEnpassant())
                {
                    board.blackPawns           ^= BITSET[to-8];
                    board.blackPieces          ^= BITSET[to-8];
                    board.occupiedSquares    ^= fromToBitboard | BITSET[to-8];
                    board.square[to-8]       = EMPTY;
                    board.totalBlackPawns     -= PAWN_VALUE;
                    board.Material           += PAWN_VALUE;
                    board.hashkey             ^= KEY.keys[to-8][BLACK_PAWN];   
                }
                else
                {
                    makeCapture(captured, to);
                    board.occupiedSquares ^= fromBitboard;
                }
            }
            else board.occupiedSquares ^= fromToBitboard;

            if (move.isPromo())
            {
                makeWhitePromotion(move.getPromo(), to);
                board.square[to]         = move.getPromo();
            }
            break;

        case 2: // white king:
            board.whiteKing             ^= fromToBitboard;
            board.whitePieces          ^= fromToBitboard;
            board.square[from]        = EMPTY;
            board.square[to]          = WHITE_KING;
            board.epSquare            = 0;    
            board.fiftyMove++;
            if (board.castleWhite & CANCASTLEOO)  board.hashkey ^= KEY.wk;
            if (board.castleWhite & CANCASTLEOOO) board.hashkey ^= KEY.wq;
            board.castleWhite = 0;
            if (captured)
            {
                makeCapture(captured, to);
                board.occupiedSquares ^= fromBitboard;
            }
            else board.occupiedSquares ^= fromToBitboard;

            if (move.isCastle())
            {
                if (move.isCastleOO())
                {
                    board.whiteRooks         ^= BITSET[H1] | BITSET[F1];
                    board.whitePieces        ^= BITSET[H1] | BITSET[F1];
                    board.occupiedSquares    ^= BITSET[H1] | BITSET[F1];
                    board.square[H1]          = EMPTY;
                    board.square[F1]          = WHITE_ROOK;
                    board.hashkey ^= (KEY.keys[H1][WHITE_ROOK] ^ KEY.keys[F1][WHITE_ROOK]);
                }
                else
                {
                    board.whiteRooks         ^= BITSET[A1] | BITSET[D1];
                    board.whitePieces          ^= BITSET[A1] | BITSET[D1];
                    board.occupiedSquares    ^= BITSET[A1] | BITSET[D1];
                    board.square[A1]          = EMPTY;
                    board.square[D1]          = WHITE_ROOK;
                    board.hashkey ^= (KEY.keys[A1][WHITE_ROOK] ^ KEY.keys[D1][WHITE_ROOK]);
                }
            }
            break;

        case 3: // white knight:
            board.whiteKnights         ^= fromToBitboard;
            board.whitePieces          ^= fromToBitboard;
            board.square[from]        = EMPTY;
            board.square[to]          = WHITE_KNIGHT;
            board.epSquare            = 0;    
            board.fiftyMove++;
            if (captured)
            {
                makeCapture(captured, to);
                board.occupiedSquares ^= fromBitboard;
            }
            else board.occupiedSquares ^= fromToBitboard;
            break;

        case 5: // white bishop:
            board.whiteBishops         ^= fromToBitboard;
            board.whitePieces          ^= fromToBitboard;
            board.square[from]        = EMPTY;
            board.square[to]          = WHITE_BISHOP;
            board.epSquare            = 0;
            board.fiftyMove++;
            if (captured)
            {
                makeCapture(captured, to);
                board.occupiedSquares ^= fromBitboard;
            }
            else board.occupiedSquares ^= fromToBitboard;
            break;

        case 6: // white rook:
            board.whiteRooks         ^= fromToBitboard;
            board.whitePieces          ^= fromToBitboard;
            board.square[from]        = EMPTY;
            board.square[to]          = WHITE_ROOK;
            board.epSquare            = 0;    
            board.fiftyMove++;
            if (from == A1) 
            {
                if (board.castleWhite & CANCASTLEOOO)  board.hashkey ^= KEY.wq;
                board.castleWhite &= ~CANCASTLEOOO;
            }
            if (from == H1) 
            {
                if (board.castleWhite & CANCASTLEOO)  board.hashkey ^= KEY.wk;
                board.castleWhite &= ~CANCASTLEOO;
            }
            if (captured)
            {
                makeCapture(captured, to);
                board.occupiedSquares ^= fromBitboard;
            }
            else board.occupiedSquares ^= fromToBitboard;
            break;

        case 7: // white queen:
            board.whiteQueens          ^= fromToBitboard;
            board.whitePieces          ^= fromToBitboard;
            board.square[from]        = EMPTY;
            board.square[to]          = WHITE_QUEEN;
            board.epSquare            = 0;    
            board.fiftyMove++;
            if (captured)
            {
                makeCapture(captured, to);
                board.occupiedSquares ^= fromBitboard;
            }
            else board.occupiedSquares ^= fromToBitboard;
            break;

        case 9: // black pawn:
            board.blackPawns           ^= fromToBitboard;
            board.blackPieces          ^= fromToBitboard;
            board.square[from]        = EMPTY;
            board.square[to]          = BLACK_PAWN;
            board.epSquare            = 0;
            board.fiftyMove = 0;
            if ((RANKS[from] == 7) && (RANKS[to] == 5))
            {
                board.epSquare = from - 8;                                        
                board.hashkey ^= KEY.ep[from - 8];
            }
            if (captured)
            {
                if (move.isEnpassant())
                {
                    board.whitePawns           ^= BITSET[to+8];
                    board.whitePieces          ^= BITSET[to+8];
                    board.occupiedSquares    ^= fromToBitboard | BITSET[to+8];
                    board.square[to+8]       = EMPTY;
                    board.totalWhitePawns     -= PAWN_VALUE;
                    board.Material           -= PAWN_VALUE;
                    board.hashkey             ^= KEY.keys[to+8][WHITE_PAWN]; 
                }
                else
                {
                    makeCapture(captured, to);
                    board.occupiedSquares ^= fromBitboard;
                }
            }
            else board.occupiedSquares ^= fromToBitboard;

            if (move.isPromo())
            {
                makeBlackPromotion(move.getPromo(), to);
                board.square[to]         = move.getPromo();
            }
            break;

        case 10: // black king:
            board.blackKing             ^= fromToBitboard;
            board.blackPieces          ^= fromToBitboard;
            board.square[from]        = EMPTY;
            board.square[to]          = BLACK_KING;
            board.epSquare            = 0;    
            board.fiftyMove++;
            if (board.castleBlack & CANCASTLEOO)  board.hashkey ^= KEY.bk;
            if (board.castleBlack & CANCASTLEOOO) board.hashkey ^= KEY.bq;
            board.castleBlack = 0;
            if (captured)
            {
                makeCapture(captured, to);
                board.occupiedSquares ^= fromBitboard;
            }
            else board.occupiedSquares ^= fromToBitboard;

            if (move.isCastle())
            {
                if (move.isCastleOO())
                {
                    board.blackRooks         ^= BITSET[H8] | BITSET[F8];
                    board.blackPieces          ^= BITSET[H8] | BITSET[F8];
                    board.occupiedSquares    ^= BITSET[H8] | BITSET[F8];
                    board.square[H8]          = EMPTY;
                    board.square[F8]          = BLACK_ROOK;
                    board.hashkey ^= (KEY.keys[H8][BLACK_ROOK] ^ KEY.keys[F8][BLACK_ROOK]);                            
                }
                else
                {
                    board.blackRooks         ^= BITSET[A8] | BITSET[D8];
                    board.blackPieces          ^= BITSET[A8] | BITSET[D8];
                    board.occupiedSquares    ^= BITSET[A8] | BITSET[D8];
                    board.square[A8]          = EMPTY;
                    board.square[D8]          = BLACK_ROOK;
                    board.hashkey ^= (KEY.keys[A8][BLACK_ROOK] ^ KEY.keys[D8][BLACK_ROOK]);                            
                }
            }
            break;

        case 11: // black knight:
            board.blackKnights         ^= fromToBitboard;
            board.blackPieces          ^= fromToBitboard;
            board.square[from]        = EMPTY;
            board.square[to]          = BLACK_KNIGHT;
            board.epSquare            = 0;    
            board.fiftyMove++;
            if (captured)
            {
                makeCapture(captured, to);
                board.occupiedSquares ^= fromBitboard;
            }
            else board.occupiedSquares ^= fromToBitboard;
            break;

        case 13: // black bishop:
            board.blackBishops         ^= fromToBitboard;
            board.blackPieces          ^= fromToBitboard;
            board.square[from]        = EMPTY;
            board.square[to]          = BLACK_BISHOP;
            board.epSquare            = 0;
            board.fiftyMove++;
            if (captured)
            {
                makeCapture(captured, to);
                board.occupiedSquares ^= fromBitboard;
            }
            else board.occupiedSquares ^= fromToBitboard;
            break;

        case 14: // black rook:
            board.blackRooks         ^= fromToBitboard;
            board.blackPieces          ^= fromToBitboard;
            board.square[from]        = EMPTY;
            board.square[to]          = BLACK_ROOK;
            board.epSquare            = 0;    
            board.fiftyMove++;
            if (from == A8)
            {
                if (board.castleBlack & CANCASTLEOOO)  board.hashkey ^= KEY.bq;
                board.castleBlack &= ~CANCASTLEOOO;
            }
            if (from == H8) 
            {
                if (board.castleBlack & CANCASTLEOO)  board.hashkey ^= KEY.bk;
                board.castleBlack &= ~CANCASTLEOO;
            }
            if (captured)
            {
                makeCapture(captured, to);
                board.occupiedSquares ^= fromBitboard;
            }
            else board.occupiedSquares ^= fromToBitboard;
            break;

        case 15: // black queen:
            board.blackQueens          ^= fromToBitboard;
            board.blackPieces          ^= fromToBitboard;
            board.square[from]        = EMPTY;
            board.square[to]          = BLACK_QUEEN;
            board.epSquare            = 0;    
            board.fiftyMove++;
            if (captured)
            {
                makeCapture(captured, to);
                board.occupiedSquares ^= fromBitboard;
            }
            else board.occupiedSquares ^= fromToBitboard;
            break;
    }

    board.nextMove = !board.nextMove;
    board.hashkey ^= KEY.side; 
    board.endOfSearch++;
}

void unmakeMove(Move &move)
{
    unsigned int piece = move.getPiece();
    unsigned int captured = move.getCapture();
    unsigned int from = move.getFrom();
    unsigned int to = move.getTosq();

    Bitboard fromBitboard  = BITSET[from];
    Bitboard fromToBitboard = fromBitboard  | BITSET[to];

    switch (piece)
    {
        case 1: // white pawn:
            board.whitePawns           ^= fromToBitboard;
            board.whitePieces          ^= fromToBitboard;
            board.square[from]        = WHITE_PAWN;
            board.square[to]          = EMPTY;
            if (captured)
            {
                if (move.isEnpassant())
                {
                    board.blackPawns           ^= BITSET[to-8];
                    board.blackPieces          ^= BITSET[to-8];
                    board.occupiedSquares    ^= fromToBitboard | BITSET[to-8];
                    board.square[to-8]        = BLACK_PAWN;
                    board.totalBlackPawns     += PAWN_VALUE;
                    board.Material           -= PAWN_VALUE;
                }
                else
                {
                    unmakeCapture(captured, to);
                    board.occupiedSquares ^= fromBitboard;
                }
            }
            else board.occupiedSquares ^= fromToBitboard;

            if (move.isPromo())
            {
                unmakeWhitePromotion(move.getPromo(), to);
            }
            break;

        case 2: // white king:
            board.whiteKing             ^= fromToBitboard;
            board.whitePieces          ^= fromToBitboard;
            board.square[from]        = WHITE_KING;
            board.square[to]          = EMPTY;
            if (captured)
            {
                unmakeCapture(captured, to);
                board.occupiedSquares ^= fromBitboard;
            }
            else board.occupiedSquares ^= fromToBitboard;

            if (move.isCastle())
            {
                if (move.isCastleOO())
                {
                    board.whiteRooks         ^= BITSET[H1] | BITSET[F1];
                    board.whitePieces          ^= BITSET[H1] | BITSET[F1];
                    board.occupiedSquares    ^= BITSET[H1] | BITSET[F1];
                    board.square[H1]          = WHITE_ROOK;
                    board.square[F1]          = EMPTY;
                }
                else
                {
                    board.whiteRooks         ^= BITSET[A1] | BITSET[D1];
                    board.whitePieces          ^= BITSET[A1] | BITSET[D1];
                    board.occupiedSquares    ^= BITSET[A1] | BITSET[D1];
                    board.square[A1]          = WHITE_ROOK;
                    board.square[D1]          = EMPTY;
                }
            }
            break;

        case 3: // white knight:
            board.whiteKnights         ^= fromToBitboard;
            board.whitePieces          ^= fromToBitboard;
            board.square[from]        = WHITE_KNIGHT;
            board.square[to]          = EMPTY;
            if (captured)
            {
                unmakeCapture(captured, to);
                board.occupiedSquares ^= fromBitboard;
            }
            else board.occupiedSquares ^= fromToBitboard;
            break;

        case 5: // white bishop:
            board.whiteBishops         ^= fromToBitboard;
            board.whitePieces          ^= fromToBitboard;
            board.square[from]        = WHITE_BISHOP;
            board.square[to]          = EMPTY;
            if (captured)
            {
                unmakeCapture(captured, to);
                board.occupiedSquares ^= fromBitboard;
            }
            else board.occupiedSquares ^= fromToBitboard;

            break;

        case 6: // white rook:
            board.whiteRooks         ^= fromToBitboard;
            board.whitePieces          ^= fromToBitboard;
            board.square[from]        = WHITE_ROOK;
            board.square[to]          = EMPTY;
            if (captured)
            {
                unmakeCapture(captured, to);
                board.occupiedSquares ^= fromBitboard;
            }
            else board.occupiedSquares ^= fromToBitboard;
            break;

        case 7: // white queen:
            board.whiteQueens          ^= fromToBitboard;
            board.whitePieces          ^= fromToBitboard;
            board.square[from]        = WHITE_QUEEN;
            board.square[to]          = EMPTY;
            if (captured)
            {
                unmakeCapture(captured, to);
                board.occupiedSquares ^= fromBitboard;
            }
            else board.occupiedSquares ^= fromToBitboard;
            break;

        case 9: // black pawn:
            board.blackPawns           ^= fromToBitboard;
            board.blackPieces          ^= fromToBitboard;
            board.square[from]        = BLACK_PAWN;
            board.square[to]          = EMPTY;
            if (captured)
            {
                if (move.isEnpassant())
                {
                    board.whitePawns           ^= BITSET[to+8];
                    board.whitePieces          ^= BITSET[to+8];
                    board.occupiedSquares    ^= fromToBitboard | BITSET[to+8];
                    board.square[to+8]        = WHITE_PAWN;
                    board.totalWhitePawns     += PAWN_VALUE;
                    board.Material           += PAWN_VALUE;
                }
                else
                {
                    unmakeCapture(captured, to);
                    board.occupiedSquares ^= fromBitboard;
                }
            }
            else board.occupiedSquares ^= fromToBitboard;

            if (move.isPromo())
            {
                unmakeBlackPromotion(move.getPromo(), to);
            }
            break;

        case 10: // black king:
            board.blackKing             ^= fromToBitboard;
            board.blackPieces          ^= fromToBitboard;
            board.square[from]        = BLACK_KING;
            board.square[to]          = EMPTY;
            if (captured)
            {
                unmakeCapture(captured, to);
                board.occupiedSquares ^= fromBitboard;
            }
            else board.occupiedSquares ^= fromToBitboard;

            if (move.isCastle())
            {
                if (move.isCastleOO())
                {
                    board.blackRooks         ^= BITSET[H8] | BITSET[F8];
                    board.blackPieces          ^= BITSET[H8] | BITSET[F8];
                    board.occupiedSquares    ^= BITSET[H8] | BITSET[F8];
                    board.square[H8]          = BLACK_ROOK;
                    board.square[F8]          = EMPTY;
                }
                else
                {
                    board.blackRooks         ^= BITSET[A8] | BITSET[D8];
                    board.blackPieces          ^= BITSET[A8] | BITSET[D8];
                    board.occupiedSquares    ^= BITSET[A8] | BITSET[D8];
                    board.square[A8]          = BLACK_ROOK;
                    board.square[D8]          = EMPTY;
                }
            }
            break;

        case 11: // black knight:
            board.blackKnights         ^= fromToBitboard;
            board.blackPieces          ^= fromToBitboard;
            board.square[from]        = BLACK_KNIGHT;
            board.square[to]          = EMPTY;
            if (captured)
            {
                unmakeCapture(captured, to);
                board.occupiedSquares ^= fromBitboard;
            }
            else board.occupiedSquares ^= fromToBitboard;                  
            break;

        case 13: // black bishop:
            board.blackBishops         ^= fromToBitboard;
            board.blackPieces          ^= fromToBitboard;
            board.square[from]        = BLACK_BISHOP;
            board.square[to]          = EMPTY;
            if (captured)
            {
                unmakeCapture(captured, to);
                board.occupiedSquares ^= fromBitboard;
            }
            else board.occupiedSquares ^= fromToBitboard;                  
            break;

        case 14: // black rook:
            board.blackRooks         ^= fromToBitboard;
            board.blackPieces          ^= fromToBitboard;
            board.square[from]        = BLACK_ROOK;
            board.square[to]          = EMPTY;
            if (captured)
            {
                unmakeCapture(captured, to);
                board.occupiedSquares ^= fromBitboard;
            }
            else board.occupiedSquares ^= fromToBitboard;                  
            break;

        case 15: // black queen:
            board.blackQueens          ^= fromToBitboard;
            board.blackPieces          ^= fromToBitboard;
            board.square[from]        = BLACK_QUEEN;
            board.square[to]          = EMPTY;
            if (captured)
            {
                unmakeCapture(captured, to);
                board.occupiedSquares ^= fromBitboard;
            }
            else board.occupiedSquares ^= fromToBitboard;                  
            break;
    }

    board.nextMove = !board.nextMove;

    board.endOfSearch--;
    board.castleWhite         = board.gameLine[board.endOfSearch].castleWhite;
    board.castleBlack         = board.gameLine[board.endOfSearch].castleBlack;
    board.epSquare            = board.gameLine[board.endOfSearch].epSquare;
    board.fiftyMove           = board.gameLine[board.endOfSearch].fiftyMove;
    board.hashkey             = board.gameLine[board.endOfSearch].key; 
}

void makeCapture(unsigned int &captured, unsigned int &to)
{
    // deals with all captures, except en-passant
    Bitboard toBitboard;
    toBitboard = BITSET[to];
    board.hashkey ^= KEY.keys[to][captured];

    switch (captured)
    {
        case 1: // white pawn:
            board.whitePawns           ^= toBitboard;
            board.whitePieces          ^= toBitboard;
            board.totalWhitePawns     -= PAWN_VALUE;
            board.Material           -= PAWN_VALUE;
            break;

        case 2: // white king:
            board.whiteKing             ^= toBitboard;
            board.whitePieces          ^= toBitboard;
            break;

        case 3: // white knight:
            board.whiteKnights         ^= toBitboard;
            board.whitePieces          ^= toBitboard;
            board.totalWhitePieces     -= KNIGHT_VALUE;
            board.Material           -= KNIGHT_VALUE;
            break;

        case 5: // white bishop:
            board.whiteBishops         ^= toBitboard;
            board.whitePieces          ^= toBitboard;
            board.totalWhitePieces     -= BISHOP_VALUE;
            board.Material           -= BISHOP_VALUE;
            break;

        case 6: // white rook:
            board.whiteRooks         ^= toBitboard;
            board.whitePieces          ^= toBitboard;
            board.totalWhitePieces     -= ROOK_VALUE;
            board.Material           -= ROOK_VALUE;
            if (to == A1) 
            {
                if (board.castleWhite & CANCASTLEOOO)  board.hashkey ^= KEY.wq;
                board.castleWhite &= ~CANCASTLEOOO;
            }
            if (to == H1) 
            {
                if (board.castleWhite & CANCASTLEOO)  board.hashkey ^= KEY.wk;
                board.castleWhite &= ~CANCASTLEOO;
            }
            break;

        case 7: // white queen:
            board.whiteQueens          ^= toBitboard;
            board.whitePieces          ^= toBitboard;
            board.totalWhitePieces     -= QUEEN_VALUE;
            board.Material           -= QUEEN_VALUE;
            break;

        case 9: // black pawn:
            board.blackPawns           ^= toBitboard;
            board.blackPieces          ^= toBitboard;
            board.totalBlackPawns     -= PAWN_VALUE;
            board.Material           += PAWN_VALUE;
            break;

        case 10: // black king:
            board.blackKing             ^= toBitboard;
            board.blackPieces          ^= toBitboard;
            break;

        case 11: // black knight:
            board.blackKnights         ^= toBitboard;
            board.blackPieces          ^= toBitboard;
            board.totalBlackPieces     -= KNIGHT_VALUE;
            board.Material           += KNIGHT_VALUE;
            break;

        case 13: // black bishop:
            board.blackBishops         ^= toBitboard;
            board.blackPieces          ^= toBitboard;
            board.totalBlackPieces     -= BISHOP_VALUE;
            board.Material           += BISHOP_VALUE;
            break;

        case 14: // black rook:
            board.blackRooks         ^= toBitboard;
            board.blackPieces          ^= toBitboard;
            board.totalBlackPieces     -= ROOK_VALUE;
            board.Material           += ROOK_VALUE;
            if (to == A8) 
            {
                if (board.castleBlack & CANCASTLEOOO)  board.hashkey ^= KEY.bq;
                board.castleBlack &= ~CANCASTLEOOO;
            }
            if (to == H8) 
            { 
                if (board.castleBlack & CANCASTLEOO)  board.hashkey ^= KEY.bk;
                board.castleBlack &= ~CANCASTLEOO;
            }
            break;

        case 15: // black queen:
            board.blackQueens          ^= toBitboard;
            board.blackPieces          ^= toBitboard;
            board.totalBlackPieces     -= QUEEN_VALUE;
            board.Material           += QUEEN_VALUE;
            break;
    }
    board.fiftyMove = 0;
}

void unmakeCapture(unsigned int &captured, unsigned int &to)
{
    // deals with all captures, except en-passant
    Bitboard toBitboard;
    toBitboard = BITSET[to];

    switch (captured)
    {
        case 1: // white pawn:
            board.whitePawns           ^= toBitboard;
            board.whitePieces          ^= toBitboard;
            board.square[to]             = WHITE_PAWN;
            board.totalWhitePawns    += PAWN_VALUE;
            board.Material           += PAWN_VALUE;
            break;

        case 2: // white king:
            board.whiteKing             ^= toBitboard;
            board.whitePieces          ^= toBitboard;
            board.square[to]             = WHITE_KING;
            break;

        case 3: // white knight:
            board.whiteKnights         ^= toBitboard;
            board.whitePieces          ^= toBitboard;
            board.square[to]             = WHITE_KNIGHT;
            board.totalWhitePieces   += KNIGHT_VALUE;
            board.Material           += KNIGHT_VALUE;
            break;

        case 5: // white bishop:
            board.whiteBishops         ^= toBitboard;
            board.whitePieces          ^= toBitboard;
            board.square[to]             = WHITE_BISHOP;
            board.totalWhitePieces   += BISHOP_VALUE;
            board.Material           += BISHOP_VALUE;
            break;

        case 6: // white rook:
            board.whiteRooks         ^= toBitboard;
            board.whitePieces          ^= toBitboard;
            board.square[to]             = WHITE_ROOK;
            board.totalWhitePieces   += ROOK_VALUE;
            board.Material           += ROOK_VALUE;
            break;

        case 7: // white queen:
            board.whiteQueens          ^= toBitboard;
            board.whitePieces          ^= toBitboard;
            board.square[to]             = WHITE_QUEEN;
            board.totalWhitePieces   += QUEEN_VALUE;
            board.Material           += QUEEN_VALUE;
            break;

        case 9: // black pawn:
            board.blackPawns           ^= toBitboard;
            board.blackPieces          ^= toBitboard;
            board.square[to]             = BLACK_PAWN;
            board.totalBlackPawns     += PAWN_VALUE;
            board.Material           -= PAWN_VALUE;
            break;

        case 10: // black king:
            board.blackKing             ^= toBitboard;
            board.blackPieces          ^= toBitboard;
            board.square[to]             = BLACK_KING;
            break;

        case 11: // black knight:
            board.blackKnights         ^= toBitboard;
            board.blackPieces          ^= toBitboard;
            board.square[to]             = BLACK_KNIGHT;
            board.totalBlackPieces    += KNIGHT_VALUE;
            board.Material           -= KNIGHT_VALUE;
            break;

        case 13: // black bishop:
            board.blackBishops         ^= toBitboard;
            board.blackPieces          ^= toBitboard;
            board.square[to]             = BLACK_BISHOP;
            board.totalBlackPieces    += BISHOP_VALUE;
            board.Material           -= BISHOP_VALUE;
            break;

        case 14: // black rook:
            board.blackRooks         ^= toBitboard;
            board.blackPieces          ^= toBitboard;
            board.square[to]             = BLACK_ROOK;
            board.totalBlackPieces    += ROOK_VALUE;
            board.Material           -= ROOK_VALUE;
            break;

        case 15: // black queen:
            board.blackQueens          ^= toBitboard;
            board.blackPieces          ^= toBitboard;
            board.square[to]             = BLACK_QUEEN;
            board.totalBlackPieces    += QUEEN_VALUE;
            board.Material           -= QUEEN_VALUE;
            break;
    }
}

void makeWhitePromotion(unsigned int prom, unsigned int &to)
{
    Bitboard toBitboard;
    toBitboard = BITSET[to];

    board.whitePawns ^= toBitboard;
    board.totalWhitePawns -= PAWN_VALUE;
    board.Material -= PAWN_VALUE;
    board.hashkey ^= (KEY.keys[to][WHITE_PAWN] ^ KEY.keys[to][prom]);

    if (prom == 7)
    {
        board.whiteQueens          ^= toBitboard;
        board.totalWhitePieces    += QUEEN_VALUE;
        board.Material           += QUEEN_VALUE;
    }
    else if (prom == 6)
    {
        board.whiteRooks         ^= toBitboard;
        board.totalWhitePieces    += ROOK_VALUE;
        board.Material           += ROOK_VALUE;
    }
    else if (prom == 5)
    {
        board.whiteBishops       ^= toBitboard;
        board.totalWhitePieces    += BISHOP_VALUE;
        board.Material           += BISHOP_VALUE;
    }
    else if (prom == 3)
    {
        board.whiteKnights       ^= toBitboard;
        board.totalWhitePieces    += KNIGHT_VALUE;
        board.Material           += KNIGHT_VALUE;
    }
}

void unmakeWhitePromotion(unsigned int prom, unsigned int &to)
{
    Bitboard toBitboard;
    toBitboard = BITSET[to];

    board.whitePawns ^= toBitboard;
    board.totalWhitePawns += PAWN_VALUE;
    board.Material += PAWN_VALUE;

    if (prom == 7)
    {
        board.whiteQueens          ^= toBitboard;
        board.totalWhitePieces    -= QUEEN_VALUE;
        board.Material           -= QUEEN_VALUE;
    }
    else if (prom == 6)
    {
        board.whiteRooks         ^= toBitboard;
        board.totalWhitePieces    -= ROOK_VALUE;
        board.Material           -= ROOK_VALUE;
    }
    else if (prom == 5)
    {
        board.whiteBishops       ^= toBitboard;
        board.totalWhitePieces    -= BISHOP_VALUE;
        board.Material           -= BISHOP_VALUE;
    }
    else if (prom == 3)
    {
        board.whiteKnights       ^= toBitboard;
        board.totalWhitePieces    -= KNIGHT_VALUE;
        board.Material           -= KNIGHT_VALUE;
    }
}


void makeBlackPromotion(unsigned int prom, unsigned int &to)
{
    Bitboard toBitboard;
    toBitboard = BITSET[to];

    board.blackPawns ^= toBitboard;
    board.totalBlackPawns -= PAWN_VALUE;
    board.Material += PAWN_VALUE;
    board.hashkey ^= (KEY.keys[to][BLACK_PAWN] ^ KEY.keys[to][prom]);

    if (prom == 15)
    {
        board.blackQueens          ^= toBitboard;
        board.totalBlackPieces    += QUEEN_VALUE;
        board.Material           -= QUEEN_VALUE;
    }
    else if (prom == 14)
    {
        board.blackRooks         ^= toBitboard;
        board.totalBlackPieces    += ROOK_VALUE;
        board.Material           -= ROOK_VALUE;
    }
    else if (prom == 13)
    {
        board.blackBishops       ^= toBitboard;
        board.totalBlackPieces    += BISHOP_VALUE;
        board.Material           -= BISHOP_VALUE;
    }
    else if (prom == 11)
    {
        board.blackKnights       ^= toBitboard;
        board.totalBlackPieces    += KNIGHT_VALUE;
        board.Material           -= KNIGHT_VALUE;
    }
}



// unmakeBlackPromotion()
//
// XXX 
void unmakeBlackPromotion(unsigned int prom, unsigned int &to)
{
    Bitboard toBitboard;
    toBitboard = BITSET[to];

    board.blackPawns ^= toBitboard;
    board.totalBlackPawns += PAWN_VALUE;
    board.Material -= PAWN_VALUE;

    if (prom == 15)
    {
        board.blackQueens          ^= toBitboard;
        board.totalBlackPieces    -= QUEEN_VALUE;
        board.Material           += QUEEN_VALUE;
    }
    else if (prom == 14)
    {
        board.blackRooks         ^= toBitboard;
        board.totalBlackPieces    -= ROOK_VALUE;
        board.Material           += ROOK_VALUE;
    }
    else if (prom == 13)
    {
        board.blackBishops       ^= toBitboard;
        board.totalBlackPieces    -= BISHOP_VALUE;
        board.Material           += BISHOP_VALUE;
    }
    else if (prom == 11)
    {
        board.blackKnights       ^= toBitboard;
        board.totalBlackPieces    -= KNIGHT_VALUE;
        board.Material           += KNIGHT_VALUE;
    }
}



// isOwnKingAttacked()
//
// Check to see if we are leaving our king in check.
bool isOwnKingAttacked()
{
    if (board.nextMove)
        return isAttacked(board.blackKing, !board.nextMove);
    else
        return isAttacked(board.whiteKing, !board.nextMove);
}



// isOtherKingAttacked()
//
// Check to see if we are leaving our king in check.
bool isOtherKingAttacked()
{
    if (board.nextMove)
        return isAttacked(board.whiteKing, board.nextMove);
    else
        return isAttacked(board.blackKing, board.nextMove);
}



// isValidTextMove()
//
// Checks if userMove is valid by comparing it with moves from the move generator.
// If found valid, the move is returned in the &move variable.
bool isValidTextMove(string userInputMove, Move &move)
{
    char userMove[16];
    strcpy(userMove, userInputMove.c_str());

    unsigned char userFrom, userTo, userPromote;
    int i;

    if (strlen(userMove) > 3)
    {
        userFrom = userMove[0] - 97;
        userFrom += 8 * (userMove[1] - 49);
        userTo = userMove[2] - 97;
        userTo += 8 * (userMove[3] - 49);
    }

    userPromote = 0;
    if (strlen(userMove) > 4)
    {
        if (board.nextMove == WHITE_MOVE)
        {
            switch (userMove[4])
            {                   
                case 'q': userPromote = WHITE_QUEEN; break;
                case 'r': userPromote = WHITE_ROOK; break;
                case 'b': userPromote = WHITE_BISHOP; break;
                case 'n': userPromote = WHITE_KNIGHT; break;
            }
        }
        else
        {
            switch (userMove[4])
            {                   
                case 'q': userPromote = BLACK_QUEEN; break;
                case 'r': userPromote = BLACK_ROOK; break;
                case 'b': userPromote = BLACK_BISHOP; break;
                case 'n': userPromote = BLACK_KNIGHT; break;
            }
        }
    }

    for (i = board.moveBufLen[0]; i < board.moveBufLen[1]; i++)
    {
        if ((board.moveBuffer[i].getFrom() == userFrom) && (board.moveBuffer[i].getTosq() == userTo))
        { 
            if (((board.square[userFrom] == WHITE_PAWN) && (RANKS[userFrom] == 7)) ||
                    ((board.square[userFrom] == BLACK_PAWN) && (RANKS[userFrom] == 2)))
            {
                if (board.moveBuffer[i].getPromo() == userPromote)
                {
                    move.moveInt = board.moveBuffer[i].moveInt;
                    return true;
                }
            }
            else
            {
                move.moveInt = board.moveBuffer[i].moveInt;
                return true;
            }
        }
    }

    move.moveInt = 0;

    return false;
}
