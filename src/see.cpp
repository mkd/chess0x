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



// @file see.cpp
//
// This file contains the functionality of the Static Exchange Evaluator (SEE).
#include <iostream>
#include "definitions.h"
#include "functions.h"
#include "extglobals.h"
#include "move.h" 



// Macro's to define sliding attacks (note that these macro's slightly differ from the ones used in the move generator)
#define RANKATTACKS(a)       (RANK_ATTACKS[(a)][((board.occupiedSquares & RANKMASK[(a)]) >> RANKSHIFT[(a)])])
#define FILEATTACKS(a)       (FILE_ATTACKS[(a)][((board.occupiedSquares & FILEMASK[(a)]) * FILEMAGIC[(a)]) >> 57])
#define SLIDEA8H1ATTACKS(a)  (DIAGA8H1_ATTACKS[(a)][((board.occupiedSquares & DIAGA8H1MASK[(a)]) * DIAGA8H1MAGIC[(a)]) >> 57])
#define SLIDEA1H8ATTACKS(a)  (DIAGA1H8_ATTACKS[(a)][((board.occupiedSquares & DIAGA1H8MASK[(a)]) * DIAGA1H8MAGIC[(a)]) >> 57])
#define ROOKATTACKS(a)       (RANKATTACKS(a) | FILEATTACKS(a))
#define BISHOPATTACKS(a)     (SLIDEA8H1ATTACKS(a) | SLIDEA1H8ATTACKS(a))



//  Board::SEE()
//
//  This is a Bitboard implementation of SEE (Static Exchange Evaluator), 
//  Captures that don't gain material are discarded during the quiescence search.
//  SEE speeds up the search in two ways: 
//  1) not all captures are searched, as in MVV/LVA
//  2) move ordering of captures is improved
//  there is no check for captures that leave the king in check 
int Board::SEE(Move &move)
{
    int nrcapts, from, target, heading, attackedpieceval;
    int materialgains[32];
    Bitboard attackers, nonremoved;
    unsigned char stm;
    bool ispromorank;

    nrcapts = 0;
    nonremoved = ~0;
    stm = nextMove;
    target = move.getTosq();
    ispromorank = ((RANKS[target] == 8) || (RANKS[target] == 1));
    attackers = attacksTo(target);

    // do the first capture 'manually', outside of the loop, because it is prescribed
    // take the first attacker from the supplied capture move:
    from = move.getFrom();

    // update the materialgains array:
    materialgains[0] = PIECEVALUES[board.square[target]];

    // remember the value of the moving piece because this is going to be captured next:
    attackedpieceval = PIECEVALUES[board.square[from]];

    // if it was a promotion, we need to add this into materialgains and attackedpieceval: 
    if (ispromorank && ((board.square[from] & 7) == 1)) 
    {
        materialgains[0] += PIECEVALUES[move.getPromo()] - PIECEVALUES[WHITE_PAWN];
        attackedpieceval += PIECEVALUES[move.getPromo()] - PIECEVALUES[WHITE_PAWN];
    }
    nrcapts++;

    // clear the bit of the last attacker:
    attackers &= ~BITSET[from];
    nonremoved &= ~BITSET[from];

    // what direction did the attack come from:
    heading = HEADINGS[target][from];

    // another attacker might be revealed, update attackers accordingly:
    if (heading) attackers = revealNextAttacker(attackers, nonremoved, target, heading);

    // switch side to move:
    stm = !stm;

    while (attackers)
    {
        // select the least valuable attacker:
        if (stm)
        {
            // pawn is only the first candidate if it does not promote:
            if  (RANKS[target] != 8 && blackPawns & attackers)   from = firstOne(blackPawns & attackers);
            else if (blackKnights & attackers) from = firstOne(blackKnights & attackers);
            else if (blackBishops & attackers) from = firstOne(blackBishops & attackers);
            else if (blackRooks & attackers)   from = firstOne(blackRooks & attackers);
            else if  (RANKS[target] == 8 && blackPawns & attackers) from = firstOne(blackPawns & attackers);
            else if (blackQueens & attackers)  from = firstOne(blackQueens & attackers);
            // king can only capture if there is no opponent attacker left
            else if ((blackKing & attackers) && !(attackers & whitePieces)) from = firstOne(blackKing);
            else break;
        } 
        else 
        {
            // pawn is only the first candidate if it does not promote:
            if (RANKS[target] != 1 && whitePawns & attackers)   from = firstOne(whitePawns & attackers);
            else if (whiteKnights & attackers) from = firstOne(whiteKnights & attackers);
            else if (whiteBishops & attackers) from = firstOne(whiteBishops & attackers);
            else if (whiteRooks & attackers)   from = firstOne(whiteRooks & attackers);
            else if (RANKS[target] == 1 && whitePawns & attackers) from = firstOne(whitePawns & attackers);
            else if (whiteQueens & attackers)  from = firstOne(whiteQueens & attackers);
            // king can only capture if there is no opponent attacker left
            else if ((whiteKing & attackers) && !(attackers & blackPieces)) from = firstOne(whiteKing);
            else break;
        }

        // update the materialgains array:
        materialgains[nrcapts] = -materialgains[nrcapts - 1] + attackedpieceval;

        // remember the value of the moving piece because this is going to be captured next:
        attackedpieceval = PIECEVALUES[board.square[from]];

        // if it was a promotion, we need to add this into materialgains and attackedpieceval: 
        if (ispromorank && ((board.square[from] & 7) == 1)) 
        {
            materialgains[nrcapts] += PIECEVALUES[WHITE_QUEEN]-PIECEVALUES[WHITE_PAWN];
            attackedpieceval = PIECEVALUES[WHITE_QUEEN]-PIECEVALUES[WHITE_PAWN];
        }
        nrcapts++;

        // clear the bit of the last attacker:
        attackers ^= BITSET[from];
        nonremoved ^= BITSET[from];

        // what direction did it come from:
        heading = HEADINGS[target][from];

        // another attacker might be revealed, update attackers accordingly:
        if (heading) attackers = revealNextAttacker(attackers, nonremoved, target, heading);

        // switch side to move:
        stm = !stm;
    }


    // Start at the end of the capture sequence and use a Minimax-type procedure 
    // to calculate the SEE value of the first capture:                                            
    while (--nrcapts)
        if (materialgains[nrcapts] > -materialgains[nrcapts - 1]) 
            materialgains[nrcapts - 1] = -materialgains[nrcapts];

    return (materialgains[0]);

}



//  attacksTo returns the first-line 'attackers' Bitboard for SEE, it has all pieces that 
//  attack the target square (both colors), excluding any attackers that might be lined-up 
//  behind the first-line attackers (e.g. queen behind rook) - they will be dealt with by 
//  revealNextAttacker
Bitboard Board::attacksTo(int &target)
{
    Bitboard attacks, attackBitmap;

    // attacks along ranks/files (rooks & queens)
    attackBitmap = ROOKATTACKS(target);
    attacks = (attackBitmap & (blackQueens | whiteQueens | blackRooks | whiteRooks));

    // attacks along diagonals (bishops & queens)
    attackBitmap = BISHOPATTACKS(target);
    attacks |= (attackBitmap & (blackQueens | whiteQueens | blackBishops | whiteBishops));

    // attacks from knights
    attackBitmap = KNIGHT_ATTACKS[target];
    attacks |= (attackBitmap & (blackKnights | whiteKnights));

    // white pawn attacks (except en/passant)
    attackBitmap = BLACK_PAWN_ATTACKS[target];
    attacks |= (attackBitmap & (whitePawns));

    // black pawn attacks (except en/passant)
    attackBitmap = WHITE_PAWN_ATTACKS[target];
    attacks |= (attackBitmap & (blackPawns));

    // king attacks 
    attackBitmap = KING_ATTACKS[target];
    attacks |= (attackBitmap & (blackKing | whiteKing));

    return attacks;
}



//  Board::revealNextAttacker()
//
//  Check if there was another 'hidden' attacker that was
//  lined-up after an attacker has been removed. 
//  If so, the attackers Bitboard is updated accordingly.
Bitboard Board::revealNextAttacker(Bitboard &attackers, Bitboard &nonremoved, int &target, int &heading)
{  
    int state;
    Bitboard targetBitmap = 0;

    switch (heading) 
    {
        case 1:  // EAST:
            targetBitmap = RAY_E[target] & ((whiteRooks | whiteQueens | blackRooks | blackQueens) & nonremoved);
            if (targetBitmap)
            {
                state = int((occupiedSquares & nonremoved & RANKMASK[target]) >> RANKSHIFT[target]);
                targetBitmap = RANK_ATTACKS[target][state] & targetBitmap;
                return (attackers | targetBitmap);
            }
            else return attackers;
            break;

        case 7:  // NORTHWEST:
            targetBitmap = RAY_NW[target] & ((whiteBishops | whiteQueens | blackBishops | blackQueens) & nonremoved);
            if (targetBitmap)
            {
                state = ((occupiedSquares & nonremoved & DIAGA8H1MASK[target]) * DIAGA8H1MAGIC[target]) >> 57;
                targetBitmap = DIAGA8H1_ATTACKS[target][state] & targetBitmap;
                return (attackers | targetBitmap);
            }
            else return attackers;
            break;

        case 8:  // NORTH:
            targetBitmap = RAY_N[target] & ((whiteRooks | whiteQueens | blackRooks | blackQueens) & nonremoved);
            if (targetBitmap)
            {
                state = ((occupiedSquares & nonremoved & FILEMASK[target]) * FILEMAGIC[target]) >> 57;
                targetBitmap = FILE_ATTACKS[target][state] & targetBitmap;
                return (attackers | targetBitmap);
            }
            else return attackers;
            break;

        case 9:  // NORTHEAST:
            targetBitmap = RAY_NE[target] & ((whiteBishops | whiteQueens | blackBishops | blackQueens) & nonremoved);
            if (targetBitmap)
            {
                state = ((occupiedSquares & nonremoved & DIAGA1H8MASK[target]) * DIAGA1H8MAGIC[target]) >> 57;
                targetBitmap = DIAGA1H8_ATTACKS[target][state] & targetBitmap;
                return (attackers | targetBitmap);
            }
            else return attackers;
            break;

        case -1:  // WEST:
            targetBitmap = RAY_W[target] & ((whiteRooks | whiteQueens | blackRooks | blackQueens) & nonremoved);
            if (targetBitmap)
            {
                state = int((occupiedSquares & nonremoved & RANKMASK[target]) >> RANKSHIFT[target]);
                targetBitmap = RANK_ATTACKS[target][state] & targetBitmap;
                return (attackers | targetBitmap);
            }
            else return attackers;
            break;

        case -7:  // SOUTHEAST
            targetBitmap = RAY_SE[target] & ((whiteBishops | whiteQueens | blackBishops | blackQueens) & nonremoved);
            if (targetBitmap)
            {
                state = ((occupiedSquares & nonremoved & DIAGA8H1MASK[target]) * DIAGA8H1MAGIC[target]) >> 57;
                targetBitmap = DIAGA8H1_ATTACKS[target][state] & targetBitmap;
                return (attackers | targetBitmap);
            }
            else return attackers;
            break;


        case -8:  // SOUTH:
            targetBitmap = RAY_S[target] & ((whiteRooks | whiteQueens | blackRooks | blackQueens) & nonremoved);
            if (targetBitmap)
            {
                state = ((occupiedSquares & nonremoved & FILEMASK[target]) * FILEMAGIC[target]) >> 57;
                targetBitmap = FILE_ATTACKS[target][state] & targetBitmap;
                return (attackers | targetBitmap);
            }
            else return attackers;
            break;

        case -9:  // SOUTHWEST
            targetBitmap = RAY_SW[target] & ((whiteBishops | whiteQueens | blackBishops | blackQueens) & nonremoved);
            if (targetBitmap)
            {
                state = ((occupiedSquares & nonremoved & DIAGA1H8MASK[target]) * DIAGA1H8MAGIC[target]) >> 57;
                targetBitmap = DIAGA1H8_ATTACKS[target][state] & targetBitmap;
                return (attackers | targetBitmap);
            }
            else return attackers;
            break;
    }

    return (attackers);
}
