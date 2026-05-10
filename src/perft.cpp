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



// @file perft.cpp
//
// This file includes only one fuction that performs a Perft test. See more
// detailed description below.
#include <iostream>
#include "definitions.h"
#include "extglobals.h"
#include "functions.h"



// perft
//
// Raw node count, up to depth, doing a full tree search.
// perft is very similar to the search algorithm - instead of evaluating the leaves, we count them.
//
// perft is a good way of verifying correctness of the movegenerator and (un)makeMove,
// because you can compare the results with published results for certain test positions.
//
// perft is also used to measure the performance of the move generator and (un)makeMove in terms
// of speed, and to compare different implementations of generating, storing and (un)making moves.
uint64_t perft(int ply, int depth)
{
    uint64_t retVal = 0;     
    int i;


    // count this node
    if (depth == 0)
        return 1;


    // generate moves from this position
    board.moveBufLen[ply+1] = movegen(board.moveBufLen[ply]);


    // loop over moves
    for (i = board.moveBufLen[ply]; i < board.moveBufLen[ply+1]; i++)
    {
        makeMove(board.moveBuffer[i]);
        if (!isOtherKingAttacked())
            retVal += perft(ply + 1, depth-1);
        unmakeMove(board.moveBuffer[i]);
    }


    return retVal;
}
