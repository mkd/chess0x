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



// @file hash.cpp
//
// This file contains the implementation for the Zobrist Hash implementation.
#include <ctime>
#include <iostream>
#include <stdlib.h>
#include "hash.h"
#include "timer.h"
#include "functions.h"



// HashKeys::init()
//
// Initialize all random 64-bit numbers.
void HashKeys::init()
{
    int i,j;
    time_t now;

    // use current time (in seconds) as random seed:
    srand((unsigned int)time(&now));

    for (i = 0; i < 64; i++)
    {
        ep[i] = rand64();
        for (j=0; j < 16; j++) keys[i][j] = rand64();
    }
    side = rand64();
    wk = rand64();
    wq = rand64();
    bk = rand64();
    bq = rand64();

    return;
}



// HashKeys::rand64()
//
// Generate random Zobrist key
uint64_t HashKeys::rand64()
{
    return rand()^((uint64_t)rand()<<15)^((uint64_t)rand()<<30)^((uint64_t)rand()<<45)^((uint64_t)rand()<<60);
}
