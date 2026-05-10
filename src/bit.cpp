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



// @file bit.cpp
//
// This file contains the functionality to handle bit-wise operations and
// Bitboard operations.
#include <iostream>
#include <iomanip>
#include "definitions.h"
#include "extglobals.h"



using namespace std;



// bitCnt
//
// MIT HAKMEM algorithm to count bits in a Bitboard
// @see http://graphics.stanford.edu/~seander/bithacks.html
unsigned int bitCnt(uint64_t bitmap)
{
    static const uint64_t  M1 = 0x5555555555555555;  // 1 zero,  1 one ...
    static const uint64_t  M2 = 0x3333333333333333;  // 2 zeros,  2 ones ...
    static const uint64_t  M4 = 0x0f0f0f0f0f0f0f0f;  // 4 zeros,  4 ones ...
    static const uint64_t  M8 = 0x00ff00ff00ff00ff;  // 8 zeros,  8 ones ...
    static const uint64_t M16 = 0x0000ffff0000ffff;  // 16 zeros, 16 ones ...
    static const uint64_t M32 = 0x00000000ffffffff;  // 32 zeros, 32 ones

    bitmap = (bitmap & M1 ) + ((bitmap >>  1) & M1 );   //put count of each  2 bits into those  2 bits
    bitmap = (bitmap & M2 ) + ((bitmap >>  2) & M2 );   //put count of each  4 bits into those  4 bits
    bitmap = (bitmap & M4 ) + ((bitmap >>  4) & M4 );   //put count of each  8 bits into those  8 bits
    bitmap = (bitmap & M8 ) + ((bitmap >>  8) & M8 );   //put count of each 16 bits into those 16 bits
    bitmap = (bitmap & M16) + ((bitmap >> 16) & M16);   //put count of each 32 bits into those 32 bits
    bitmap = (bitmap & M32) + ((bitmap >> 32) & M32);   //put count of each 64 bits into those 64 bits

    return (int)bitmap;
}



// firstOne
//
// Find the first bit on a Bitboard using the De Bruijn Multiplication
// @see http://chessprogramming.wikispaces.com/BitScan
//
// Note: don't use this if bitmap = 0
unsigned int firstOne(uint64_t bitmap)
{
    static const int INDEX64[64] = {
        63,  0, 58,  1, 59, 47, 53,  2,
        60, 39, 48, 27, 54, 33, 42,  3,
        61, 51, 37, 40, 49, 18, 28, 20,
        55, 30, 34, 11, 43, 14, 22,  4,
        62, 57, 46, 52, 38, 26, 32, 41,
        50, 36, 17, 19, 29, 10, 13, 21,
        56, 45, 25, 31, 35, 16,  9, 12,
        44, 24, 15,  8, 23,  7,  6,  5  };

    static const uint64_t DEBRUIJN64 = uint64_t(0x07EDD5E59A4E28C2);

    return INDEX64[((bitmap & -bitmap) * DEBRUIJN64) >> 58];  
}



// lastOne
//
// Find the last bit on a Bitboard using Eugene Nalimov's bitScanReverse. Please
// use firstOne if you can, it is faster than lastOne.
//
// Note: don't use this if bitmap = 0
unsigned int lastOne(uint64_t bitmap)
{
    int result = 0;
    if (bitmap > 0xFFFFFFFF)
    {
        bitmap >>= 32;
        result = 32;
    }
    if (bitmap > 0xFFFF)
    {
        bitmap >>= 16;
        result += 16;
    }
    if (bitmap > 0xFF)
    {
        bitmap >>= 8;
        result += 8;
    }
    return result + MS1BTABLE[bitmap];
}



// displayBitboard
//
// Display a Bitboard on a chess board.
void displayBitboard(Bitboard in)
{
    int  i, rank, file;
    char boardc[64];


    // set up all 1s and 0s on a 64-square board
    for (i = 0 ; i < 64 ; i++)
    {
        if (in & BITSET[i])
            boardc[i] = '1';
        else
            boardc[i] = '.';
    }


    // display white front
    cout << endl << endl;
    if (!board.flipBoard)
    {
        cout << "    +----+----+----+----+----+----+----+----+" << endl;
        for (rank = 8; rank >= 1; rank--)
        {
            cout << setw(3) << rank <<  " |";

            for (file = 1; file <= 8; file++)
                cout << "  " << boardc[BOARDINDEX[file][rank]] << " |";

            cout << endl << "    +----+----+----+----+----+----+----+----+" << endl;
        }
        cout << "      a    b    c    d    e    f    g    h" << endl << endl;
    }

    // display black front
    else
    {
        cout << "    +----+----+----+----+----+----+----+----+" << endl;
        for (rank = 1; rank <= 8; rank++)
        {
            cout << setw(3) << rank << " |";

            for (file = 1; file <= 8; file++)
                cout << "  " << boardc[BOARDINDEX[file][rank]] << " |";

            cout << endl << "    +----+----+----+----+----+----+----+----+" << endl;
        }
        cout << "      h    g    f    e    d    c    b    a" << endl << endl;
    }
}
