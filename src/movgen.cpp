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



// @file movgen.cpp
//
// This file contains the code for generating all the pseudo-legal and legal
// (valid) moves for all pieces existing on the board.
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "definitions.h"
#include "functions.h"
#include "extglobals.h"
#include "move.h"



// Macro's to define sliding attacks:
#define RANKMOVES(a)       (RANK_ATTACKS[(a)][((board.occupiedSquares & RANKMASK[(a)]) >> RANKSHIFT[(a)])] & targetBitmap)
#define FILEMOVES(a)       (FILE_ATTACKS[(a)][((board.occupiedSquares & FILEMASK[(a)]) * FILEMAGIC[(a)]) >> 57] & targetBitmap)
#define SLIDEA8H1MOVES(a)  (DIAGA8H1_ATTACKS[(a)][((board.occupiedSquares & DIAGA8H1MASK[(a)]) * DIAGA8H1MAGIC[(a)]) >> 57] & targetBitmap)
#define SLIDEA1H8MOVES(a)  (DIAGA1H8_ATTACKS[(a)][((board.occupiedSquares & DIAGA1H8MASK[(a)]) * DIAGA1H8MAGIC[(a)]) >> 57] & targetBitmap)
#define ROOKMOVES(a)       (RANKMOVES(a) | FILEMOVES(a))
#define BISHOPMOVES(a)     (SLIDEA8H1MOVES(a) | SLIDEA1H8MOVES(a))
#define QUEENMOVES(a)      (BISHOPMOVES(a) | ROOKMOVES(a))



// movegen
//
// This is Chess0x pseudo-legal bitboard move generator,
// using magic multiplication instead of rotated bitboards.
//
// There is no check if a move leaves the king in check.
//
// The first free location in moveBuffer[] is supplied in index,
// and the new first free location is returned
int movegen(int index)
{
    unsigned char opponentSide;
    unsigned int from, to;
    Bitboard tempPiece, tempMove;
    Bitboard targetBitmap, freeSquares;
    Move move;

    move.clear();
    opponentSide = !board.nextMove;
    freeSquares = ~board.occupiedSquares;

    // Black to move
    if (board.nextMove)
    {
        targetBitmap = ~board.blackPieces; // we cannot capture one of our own pieces!

        // Black Pawns
        move.setPiece(BLACK_PAWN);
        tempPiece = board.blackPawns;
        while (tempPiece)   
        {
            from = firstOne(tempPiece);
            move.setFrom(from);
            tempMove = BLACK_PAWN_MOVES[from] & freeSquares;                // normal moves
            if (RANKS[from] == 7 && tempMove)                               
                tempMove |= (BLACK_PAWN_DOUBLE_MOVES[from] & freeSquares);  // add double moves
            tempMove |= BLACK_PAWN_ATTACKS[from] & board.whitePieces;       // add captures
            while (tempMove)
            {
                to = firstOne(tempMove);
                move.setTosq(to);
                move.setCapture(board.square[to]);
                if ((RANKS[to]) == 1)                                       // add promotions
                {
                    move.setPromo(BLACK_QUEEN);   board.moveBuffer[index++].moveInt = move.moveInt;
                    move.setPromo(BLACK_ROOK);    board.moveBuffer[index++].moveInt = move.moveInt;
                    move.setPromo(BLACK_BISHOP);  board.moveBuffer[index++].moveInt = move.moveInt;
                    move.setPromo(BLACK_KNIGHT);  board.moveBuffer[index++].moveInt = move.moveInt;
                    move.setPromo(EMPTY);      
                }
                else
                {
                    board.moveBuffer[index++].moveInt = move.moveInt;
                }
                tempMove ^= BITSET[to];
            }
            // add en-passant captures:
            if (board.epSquare)   // do a quick check first
            {
                if (BLACK_PAWN_ATTACKS[from] & BITSET[board.epSquare])
                {
                    if (board.whitePawns & BITSET[board.epSquare + 8])  // final check to protect against same color capture during null move
                    {
                        move.setPromo(BLACK_PAWN);
                        move.setCapture(WHITE_PAWN);
                        move.setTosq(board.epSquare);
                        board.moveBuffer[index++].moveInt = move.moveInt;
                    }
                }
            }
            tempPiece ^= BITSET[from];
            move.setPromo(EMPTY);
        }                         

        // Black Knights
        move.setPiece(BLACK_KNIGHT);
        tempPiece = board.blackKnights;
        while (tempPiece)
        {
            from = firstOne(tempPiece);
            move.setFrom(from);
            tempMove = KNIGHT_ATTACKS[from] & targetBitmap;
            while (tempMove)          
            {
                to = firstOne(tempMove);
                move.setTosq(to);
                move.setCapture(board.square[to]);
                board.moveBuffer[index++].moveInt = move.moveInt;
                tempMove ^= BITSET[to];
            }
            tempPiece ^= BITSET[from];
        }

        // Black Bishops
        move.setPiece(BLACK_BISHOP);
        tempPiece = board.blackBishops;
        while (tempPiece)
        {
            from = firstOne(tempPiece);
            move.setFrom(from);
            tempMove = BISHOPMOVES(from);   // see Macro's
            while (tempMove)
            {
                to = firstOne(tempMove);
                move.setTosq(to);
                move.setCapture(board.square[to]);
                board.moveBuffer[index++].moveInt = move.moveInt;
                tempMove ^= BITSET[to];
            }
            tempPiece ^= BITSET[from];
        }

        // Black Rooks
        move.setPiece(BLACK_ROOK);
        tempPiece = board.blackRooks;
        while (tempPiece)
        {
            from = firstOne(tempPiece);
            move.setFrom(from);
            tempMove = ROOKMOVES(from);
            while (tempMove)
            {
                to = firstOne(tempMove);
                move.setTosq(to);
                move.setCapture(board.square[to]);
                board.moveBuffer[index++].moveInt = move.moveInt;
                tempMove ^= BITSET[to];
            }
            tempPiece ^= BITSET[from];
        }

        // Black Queens
        move.setPiece(BLACK_QUEEN);
        tempPiece = board.blackQueens;
        while (tempPiece)
        {
            from = firstOne(tempPiece);
            move.setFrom(from);
            tempMove = QUEENMOVES(from);
            while (tempMove)
            {
                to = firstOne(tempMove);
                move.setTosq(to);
                move.setCapture(board.square[to]);
                board.moveBuffer[index++].moveInt = move.moveInt;
                tempMove ^= BITSET[to];
            }
            tempPiece ^= BITSET[from];
        }

        // Black King
        move.setPiece(BLACK_KING);
        tempPiece = board.blackKing;
        while (tempPiece)
        {
            from = firstOne(tempPiece);
            move.setFrom(from);
            tempMove = KING_ATTACKS[from] & targetBitmap;
            while (tempMove)
            {
                to = firstOne(tempMove);
                move.setTosq(to);
                move.setCapture(board.square[to]);
                board.moveBuffer[index++].moveInt = move.moveInt;
                tempMove ^= BITSET[to];
            }

            // Black 0-0 Castling
            if (board.castleBlack & CANCASTLEOO)
            {
                if (!(maskFG[1] & board.occupiedSquares))
                {
                    if (!isAttacked(maskEG[BLACK_MOVE], WHITE_MOVE))
                    {
                        board.moveBuffer[index++].moveInt = BLACK_OO_CASTL;
                    }
                }
            }

            // Black 0-0-0 Castling
            if (board.castleBlack & CANCASTLEOOO)
            {
                if (!(maskBD[1] & board.occupiedSquares))
                {
                    if (!isAttacked(maskCE[BLACK_MOVE], WHITE_MOVE))
                    {
                        board.moveBuffer[index++].moveInt = BLACK_OOO_CASTL;
                    }
                }
            }

            tempPiece ^= BITSET[from];
            move.setPromo(EMPTY);
        }
    }


    // White to move
    else 
    {
        // we cannot capture one of our own pieces
        targetBitmap = ~board.whitePieces;

        // White Pawns
        move.setPiece(WHITE_PAWN);
        tempPiece = board.whitePawns;
        while (tempPiece)   
        {
            from = firstOne(tempPiece);
            move.setFrom(from);
            tempMove = WHITE_PAWN_MOVES[from] & freeSquares;
            if (RANKS[from] == 2 && tempMove)                               
                tempMove |= (WHITE_PAWN_DOUBLE_MOVES[from] & freeSquares);
            tempMove |= WHITE_PAWN_ATTACKS[from] & board.blackPieces;
            while (tempMove)
            {
                to = firstOne(tempMove);
                move.setTosq(to);
                move.setCapture(board.square[to]);
                if ((RANKS[to]) == 8)
                {
                    move.setPromo(WHITE_QUEEN);   board.moveBuffer[index++].moveInt = move.moveInt;
                    move.setPromo(WHITE_ROOK);    board.moveBuffer[index++].moveInt = move.moveInt;
                    move.setPromo(WHITE_BISHOP);  board.moveBuffer[index++].moveInt = move.moveInt;
                    move.setPromo(WHITE_KNIGHT);  board.moveBuffer[index++].moveInt = move.moveInt;
                    move.setPromo(EMPTY);      
                }
                else
                {
                    board.moveBuffer[index++].moveInt = move.moveInt;
                }
                tempMove ^= BITSET[to];
            }

            // add en-passant captures
            if (board.epSquare)
            {
                if (WHITE_PAWN_ATTACKS[from] & BITSET[board.epSquare])
                {
                    if (board.blackPawns & BITSET[board.epSquare - 8])
                    {
                        move.setPromo(WHITE_PAWN);
                        move.setCapture(BLACK_PAWN);
                        move.setTosq(board.epSquare);
                        board.moveBuffer[index++].moveInt = move.moveInt;
                    }
                }
            }
            tempPiece ^= BITSET[from];
            move.setPromo(EMPTY);
        }                         

        // White Knights
        move.setPiece(WHITE_KNIGHT);
        tempPiece = board.whiteKnights;
        while (tempPiece)
        {
            from = firstOne(tempPiece);
            move.setFrom(from);
            tempMove = KNIGHT_ATTACKS[from] & targetBitmap;
            while (tempMove)          
            {
                to = firstOne(tempMove);
                move.setTosq(to);
                move.setCapture(board.square[to]);
                board.moveBuffer[index++].moveInt = move.moveInt;
                tempMove ^= BITSET[to];
            }
            tempPiece ^= BITSET[from];
        }

        // White Bishops
        move.setPiece(WHITE_BISHOP);
        tempPiece = board.whiteBishops;
        while (tempPiece)
        {
            from = firstOne(tempPiece);
            move.setFrom(from);
            tempMove = BISHOPMOVES(from);
            while (tempMove)
            {
                to = firstOne(tempMove);
                move.setTosq(to);
                move.setCapture(board.square[to]);
                board.moveBuffer[index++].moveInt = move.moveInt;
                tempMove ^= BITSET[to];
            }
            tempPiece ^= BITSET[from];
        }

        // White Rooks
        move.setPiece(WHITE_ROOK);
        tempPiece = board.whiteRooks;
        while (tempPiece)
        {
            from = firstOne(tempPiece);
            move.setFrom(from);
            tempMove = ROOKMOVES(from);
            while (tempMove)
            {
                to = firstOne(tempMove);
                move.setTosq(to);
                move.setCapture(board.square[to]);
                board.moveBuffer[index++].moveInt = move.moveInt;
                tempMove ^= BITSET[to];
            }
            tempPiece ^= BITSET[from];
        }

        // White Queens
        move.setPiece(WHITE_QUEEN);
        tempPiece = board.whiteQueens;
        while (tempPiece)
        {
            from = firstOne(tempPiece);
            move.setFrom(from);
            tempMove = QUEENMOVES(from);
            while (tempMove)
            {
                to = firstOne(tempMove);
                move.setTosq(to);
                move.setCapture(board.square[to]);
                board.moveBuffer[index++].moveInt = move.moveInt;
                tempMove ^= BITSET[to];
            }
            tempPiece ^= BITSET[from];
        }

        // White king
        move.setPiece(WHITE_KING);
        tempPiece = board.whiteKing;
        while (tempPiece)
        {
            from = firstOne(tempPiece);
            move.setFrom(from);
            tempMove = KING_ATTACKS[from] & targetBitmap;
            while (tempMove)
            {
                to = firstOne(tempMove);
                move.setTosq(to);
                move.setCapture(board.square[to]);
                board.moveBuffer[index++].moveInt = move.moveInt;
                tempMove ^= BITSET[to];
            }

            // White 0-0 Castling
            if (board.castleWhite & CANCASTLEOO)
            {
                if (!(maskFG[0] & board.occupiedSquares))
                {
                    if (!isAttacked(maskEG[WHITE_MOVE], BLACK_MOVE))
                    {
                        board.moveBuffer[index++].moveInt = WHITE_OO_CASTL;
                    }
                }
            }

            // White 0-0-0 Castling
            if (board.castleWhite & CANCASTLEOOO)
            {
                if (!(maskBD[0] & board.occupiedSquares))
                {
                    if (!isAttacked(maskCE[WHITE_MOVE], BLACK_MOVE))
                    {
                        board.moveBuffer[index++].moveInt = WHITE_OOO_CASTL;
                    }
                }
            }
            tempPiece ^= BITSET[from];
            move.setPromo(EMPTY);
        }
    }     

    return index;
}



// captgen
//
// Generate pseudo-legal captures and promotions generator,
// using magic multiplication instead of rotated bitboards.
// The first free location in moveBuffer[] is supplied in index,
// and the new first free location is returned.
//  
// This function keeps the move list sorted (using SEE) and shortens 
// the list by discarding 'bad' moves. 
int captgen(int index)
{
    unsigned char opponentSide;
    unsigned int from, to;
    int ifirst;
    Bitboard tempPiece, tempMove;
    Bitboard targetBitmap, freeSquares;
    Move move;

    ifirst = index;
    move.clear();
    opponentSide = !board.nextMove;
    freeSquares = ~board.occupiedSquares;


    // Black to move
    if (board.nextMove) // black to move
    {
        // we want captures only
        targetBitmap = board.whitePieces;

        // Black Pawns
        move.setPiece(BLACK_PAWN);
        tempPiece = board.blackPawns;
        while (tempPiece)   
        {
            from = firstOne(tempPiece);
            move.setFrom(from);
            tempMove = BLACK_PAWN_ATTACKS[from] & targetBitmap; // pawn captures
            if ((RANKS[from]) == 2) tempMove |= BLACK_PAWN_MOVES[from] & freeSquares; // promotions
            while (tempMove)
            {
                to = firstOne(tempMove);
                move.setTosq(to);
                move.setCapture(board.square[to]);
                if ((RANKS[to]) == 1)
                {
                    move.setPromo(BLACK_QUEEN);      board.moveBuffer[index].moveInt = move.moveInt;
                    board.addCaptScore(ifirst,index);
                    index++;
                    move.setPromo(BLACK_ROOK);       board.moveBuffer[index].moveInt = move.moveInt;
                    board.addCaptScore(ifirst,index);
                    index++;
                    move.setPromo(BLACK_BISHOP);     board.moveBuffer[index].moveInt = move.moveInt;
                    board.addCaptScore(ifirst,index);
                    index++;
                    move.setPromo(BLACK_KNIGHT);     board.moveBuffer[index].moveInt = move.moveInt;
                    board.addCaptScore(ifirst,index);
                    index++;
                    move.setPromo(EMPTY);
                }
                else
                {
                    board.moveBuffer[index].moveInt = move.moveInt;
                    board.addCaptScore(ifirst,index);
                    index++;
                }
                tempMove ^= BITSET[to];
            }
            if (board.epSquare)
            {
                if (BLACK_PAWN_ATTACKS[from] & BITSET[board.epSquare])
                {
                    move.setPromo(BLACK_PAWN);
                    move.setCapture(WHITE_PAWN);
                    move.setTosq(board.epSquare);
                    board.moveBuffer[index].moveInt = move.moveInt;
                    board.addCaptScore(ifirst,index);
                    index++;
                }
            }
            tempPiece ^= BITSET[from];
            move.setPromo(EMPTY);
        }                         


        // Black Knights
        move.setPiece(BLACK_KNIGHT);
        tempPiece = board.blackKnights;
        while (tempPiece)
        {
            from = firstOne(tempPiece);
            move.setFrom(from);
            tempMove = KNIGHT_ATTACKS[from] & targetBitmap;
            while (tempMove)          
            {
                to = firstOne(tempMove);
                move.setTosq(to);
                move.setCapture(board.square[to]);
                board.moveBuffer[index].moveInt = move.moveInt;
                board.addCaptScore(ifirst,index);
                index++;
                tempMove ^= BITSET[to];
            }
            tempPiece ^= BITSET[from];
        }


        // Black Bishops
        move.setPiece(BLACK_BISHOP);
        tempPiece = board.blackBishops;
        while (tempPiece)
        {
            from = firstOne(tempPiece);
            move.setFrom(from);
            tempMove = BISHOPMOVES(from);   // see Macro's
            while (tempMove)
            {
                to = firstOne(tempMove);
                move.setTosq(to);
                move.setCapture(board.square[to]);
                board.moveBuffer[index].moveInt = move.moveInt;
                board.addCaptScore(ifirst,index);
                index++;
                tempMove ^= BITSET[to];
            }
            tempPiece ^= BITSET[from];
        }

        // Black Rooks
        move.setPiece(BLACK_ROOK);
        tempPiece = board.blackRooks;
        while (tempPiece)
        {
            from = firstOne(tempPiece);
            move.setFrom(from);
            tempMove = ROOKMOVES(from);   // see Macro's
            while (tempMove)
            {
                to = firstOne(tempMove);
                move.setTosq(to);
                move.setCapture(board.square[to]);
                board.moveBuffer[index].moveInt = move.moveInt;
                board.addCaptScore(ifirst,index);
                index++;
                tempMove ^= BITSET[to];
            }
            tempPiece ^= BITSET[from];
        }


        // Black Queens
        move.setPiece(BLACK_QUEEN);
        tempPiece = board.blackQueens;
        while (tempPiece)
        {
            from = firstOne(tempPiece);
            move.setFrom(from);
            tempMove = QUEENMOVES(from);   // see Macro's
            while (tempMove)
            {
                to = firstOne(tempMove);
                move.setTosq(to);
                move.setCapture(board.square[to]);
                board.moveBuffer[index].moveInt = move.moveInt;
                board.addCaptScore(ifirst,index);
                index++;
                tempMove ^= BITSET[to];
            }
            tempPiece ^= BITSET[from];
        }


        // Black King
        move.setPiece(BLACK_KING);
        tempPiece = board.blackKing;
        while (tempPiece)
        {
            from = firstOne(tempPiece);
            move.setFrom(from);
            tempMove = KING_ATTACKS[from] & targetBitmap;
            while (tempMove)
            {
                to = firstOne(tempMove);
                move.setTosq(to);
                move.setCapture(board.square[to]);
                board.moveBuffer[index].moveInt = move.moveInt;
                board.addCaptScore(ifirst,index);
                index++;
                tempMove ^= BITSET[to];
            } 
            tempPiece ^= BITSET[from];
            move.setPromo(EMPTY);
        }
    }



    // White to move
    else 
    {
        targetBitmap = board.blackPieces;

        // White Pawns
        move.setPiece(WHITE_PAWN);
        tempPiece = board.whitePawns;
        while (tempPiece)   
        {
            from = firstOne(tempPiece);
            move.setFrom(from);
            tempMove = WHITE_PAWN_ATTACKS[from] & targetBitmap; // pawn captures
            if ((RANKS[from]) == 7) tempMove |= WHITE_PAWN_MOVES[from] & freeSquares; // promotions
            while (tempMove)
            {
                to = firstOne(tempMove);
                move.setTosq(to);
                move.setCapture(board.square[to]);
                if ((RANKS[to]) == 8)
                {
                    move.setPromo(WHITE_QUEEN);      board.moveBuffer[index].moveInt = move.moveInt;
                    board.addCaptScore(ifirst,index);
                    index++;
                    move.setPromo(WHITE_ROOK);       board.moveBuffer[index].moveInt = move.moveInt;
                    board.addCaptScore(ifirst,index);
                    index++;
                    move.setPromo(WHITE_BISHOP);     board.moveBuffer[index].moveInt = move.moveInt;
                    board.addCaptScore(ifirst,index);
                    index++;
                    move.setPromo(WHITE_KNIGHT);     board.moveBuffer[index].moveInt = move.moveInt;
                    board.addCaptScore(ifirst,index);
                    index++;
                    move.setPromo(EMPTY);
                }
                else
                {
                    board.moveBuffer[index].moveInt = move.moveInt;
                    board.addCaptScore(ifirst,index);
                    index++;
                }
                tempMove ^= BITSET[to];
            }
            if (board.epSquare)
            {
                if (WHITE_PAWN_ATTACKS[from] & BITSET[board.epSquare])
                {
                    move.setPromo(WHITE_PAWN);
                    move.setCapture(BLACK_PAWN);
                    move.setTosq(board.epSquare);
                    board.moveBuffer[index].moveInt = move.moveInt;
                    board.addCaptScore(ifirst,index);
                    index++;
                }
            }
            tempPiece ^= BITSET[from];
            move.setPromo(EMPTY);
        }                         

        // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // White Knights
        // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        move.setPiece(WHITE_KNIGHT);
        tempPiece = board.whiteKnights;
        while (tempPiece)
        {
            from = firstOne(tempPiece);
            move.setFrom(from);
            tempMove = KNIGHT_ATTACKS[from] & targetBitmap;
            while (tempMove)          
            {
                to = firstOne(tempMove);
                move.setTosq(to);
                move.setCapture(board.square[to]);
                board.moveBuffer[index].moveInt = move.moveInt;
                board.addCaptScore(ifirst,index);
                index++;
                tempMove ^= BITSET[to];
            }
            tempPiece ^= BITSET[from];
        }

        // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // White Bishops
        // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        move.setPiece(WHITE_BISHOP);
        tempPiece = board.whiteBishops;
        while (tempPiece)
        {
            from = firstOne(tempPiece);
            move.setFrom(from);
            tempMove = BISHOPMOVES(from);   // see Macro's
            while (tempMove)
            {
                to = firstOne(tempMove);
                move.setTosq(to);
                move.setCapture(board.square[to]);
                board.moveBuffer[index].moveInt = move.moveInt;
                board.addCaptScore(ifirst,index);
                index++;
                tempMove ^= BITSET[to];
            }
            tempPiece ^= BITSET[from];
        }

        // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // White Rooks
        // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        move.setPiece(WHITE_ROOK);
        tempPiece = board.whiteRooks;
        while (tempPiece)
        {
            from = firstOne(tempPiece);
            move.setFrom(from);
            tempMove = ROOKMOVES(from);   // see Macro's
            while (tempMove)
            {
                to = firstOne(tempMove);
                move.setTosq(to);
                move.setCapture(board.square[to]);
                board.moveBuffer[index].moveInt = move.moveInt;
                board.addCaptScore(ifirst,index);
                index++;
                tempMove ^= BITSET[to];
            }
            tempPiece ^= BITSET[from];
        }

        // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // White Queens
        // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        move.setPiece(WHITE_QUEEN);
        tempPiece = board.whiteQueens;
        while (tempPiece)
        {
            from = firstOne(tempPiece);
            move.setFrom(from);
            tempMove = QUEENMOVES(from);   // see Macro's
            while (tempMove)
            {
                to = firstOne(tempMove);
                move.setTosq(to);
                move.setCapture(board.square[to]);
                board.moveBuffer[index].moveInt = move.moveInt;
                board.addCaptScore(ifirst,index);
                index++;
                tempMove ^= BITSET[to];
            }
            tempPiece ^= BITSET[from];
        }

        // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // White king
        // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        move.setPiece(WHITE_KING);
        tempPiece = board.whiteKing;
        while (tempPiece)
        {
            from = firstOne(tempPiece);
            move.setFrom(from);
            tempMove = KING_ATTACKS[from] & targetBitmap;
            while (tempMove)
            {
                to = firstOne(tempMove);
                move.setTosq(to);
                move.setCapture(board.square[to]);
                board.moveBuffer[index].moveInt = move.moveInt;
                board.addCaptScore(ifirst, index);
                index++;
                tempMove ^= BITSET[to];
            } 
            tempPiece ^= BITSET[from];
            move.setPromo(EMPTY);
        }
    }     
    return index;
}



// is Attacked()
//
// isAttacked is used mainly as a move legality test to see if targetBitmap is
// attacked by white or black.
//
// Returns true at the first attack found, and returns false if no attack is found.
// It can be used for:
// - check detection, and
// - castling legality: test to see if the king passes through, or ends up on,
// a square that is attacked
bool isAttacked(Bitboard &targetBitmap, const unsigned char &fromSide)
{
    Bitboard tempTarget;
    Bitboard slidingAttackers;
    int to;

    tempTarget = targetBitmap;
    if (fromSide) // test for attacks from BLACK to targetBitmap
    {
        while (tempTarget)
        {
            to = firstOne(tempTarget);

            if (board.blackPawns & WHITE_PAWN_ATTACKS[to]) return true;
            if (board.blackKnights & KNIGHT_ATTACKS[to]) return true;
            if (board.blackKing & KING_ATTACKS[to]) return true;

            // file / rank attacks
            slidingAttackers = board.blackQueens | board.blackRooks;
            if (slidingAttackers)
            {
                if (RANK_ATTACKS[to][((board.occupiedSquares & RANKMASK[to]) >> RANKSHIFT[to])] & slidingAttackers) return true;
                if (FILE_ATTACKS[to][((board.occupiedSquares & FILEMASK[to]) * FILEMAGIC[to]) >> 57] & slidingAttackers) return true;
            }

            // diagonals
            slidingAttackers = board.blackQueens | board.blackBishops;
            if (slidingAttackers)
            {
                if (DIAGA8H1_ATTACKS[to][((board.occupiedSquares & DIAGA8H1MASK[to]) * DIAGA8H1MAGIC[to]) >> 57] & slidingAttackers) return true;
                if (DIAGA1H8_ATTACKS[to][((board.occupiedSquares & DIAGA1H8MASK[to]) * DIAGA1H8MAGIC[to]) >> 57] & slidingAttackers) return true;
            }

            tempTarget ^= BITSET[to];
        }
    }
    else // test for attacks from WHITE to targetBitmap
    {
        while (tempTarget)
        {
            to = firstOne(tempTarget);

            if (board.whitePawns & BLACK_PAWN_ATTACKS[to]) return true;
            if (board.whiteKnights & KNIGHT_ATTACKS[to]) return true;
            if (board.whiteKing & KING_ATTACKS[to]) return true;

            // file / rank attacks
            slidingAttackers = board.whiteQueens | board.whiteRooks;
            if (slidingAttackers)
            {
                if (RANK_ATTACKS[to][((board.occupiedSquares & RANKMASK[to]) >> RANKSHIFT[to])] & slidingAttackers) return true;
                if (FILE_ATTACKS[to][((board.occupiedSquares & FILEMASK[to]) * FILEMAGIC[to]) >> 57] & slidingAttackers) return true;
            }

            // diagonals:
            slidingAttackers = board.whiteQueens | board.whiteBishops;
            if (slidingAttackers)
            {
                if (DIAGA8H1_ATTACKS[to][((board.occupiedSquares & DIAGA8H1MASK[to]) * DIAGA8H1MAGIC[to]) >> 57] & slidingAttackers) return true;
                if (DIAGA1H8_ATTACKS[to][((board.occupiedSquares & DIAGA1H8MASK[to]) * DIAGA1H8MAGIC[to]) >> 57] & slidingAttackers) return true;
            }

            tempTarget ^= BITSET[to];
        }
    }

    return false;
}



// addCaptScore
//
// Use the static evaluator to find "better" moves by assigning them a score.
void Board::addCaptScore(int &ifirst, int &index)
{
    int i, val;
    Move capt;

    capt = moveBuffer[index];
    val = SEE(moveBuffer[index]);

    // Discard this move if the score is not high enough:
    if (val < MINCAPTVAL)
    {
        index--;
        return;
    }

    // now insert the move into the sorted list at the right location:
    // i = descending because the capture generated should deliver moves be in pretty reasonable order 
    // (captures by pawns are generated first, queens last), so if we're lucky we don't need to sort.
    i = index - 1;
    while (i > ifirst -1 && val > moveBuffer[i+OFFSET].moveInt)
        i--;

    memmove(&moveBuffer[i+2], &moveBuffer[i+1], (index-i-1)*sizeof(capt));  //  move aside moves
    memmove(&moveBuffer[i+2+OFFSET], &moveBuffer[i+1+OFFSET], (index-i-1)*sizeof(capt));  // move aside scores

    moveBuffer[i+1].moveInt = capt.moveInt; // insert the move
    moveBuffer[i+1+OFFSET].moveInt = val;  // insert the score
}
