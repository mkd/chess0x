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



// @file board.cpp
//
// @see board.h
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <string>
#include "definitions.h"
#include "functions.h"
#include "extglobals.h"
#include "board.h"



using namespace std;




// init
//
// Initialize the board and reset all data structures (i.e., used when starting
// a new game).
void Board::init()
{
    flipBoard = false;

    for (int i = 0; i < 64; i++) square[i] = EMPTY;

    square[E1] = WHITE_KING;
    square[D1] = WHITE_QUEEN;
    square[A1] = WHITE_ROOK;
    square[H1] = WHITE_ROOK;
    square[B1] = WHITE_KNIGHT;
    square[G1] = WHITE_KNIGHT;
    square[C1] = WHITE_BISHOP;
    square[F1] = WHITE_BISHOP;
    square[A2] = WHITE_PAWN;
    square[B2] = WHITE_PAWN;
    square[C2] = WHITE_PAWN;
    square[D2] = WHITE_PAWN;
    square[E2] = WHITE_PAWN;
    square[F2] = WHITE_PAWN;
    square[G2] = WHITE_PAWN;
    square[H2] = WHITE_PAWN;

    square[E8] = BLACK_KING;
    square[D8] = BLACK_QUEEN;
    square[A8] = BLACK_ROOK;
    square[H8] = BLACK_ROOK;
    square[B8] = BLACK_KNIGHT;
    square[G8] = BLACK_KNIGHT;
    square[C8] = BLACK_BISHOP;
    square[F8] = BLACK_BISHOP;
    square[A7] = BLACK_PAWN;
    square[B7] = BLACK_PAWN;
    square[C7] = BLACK_PAWN;
    square[D7] = BLACK_PAWN;
    square[E7] = BLACK_PAWN;
    square[F7] = BLACK_PAWN;
    square[G7] = BLACK_PAWN;
    square[H7] = BLACK_PAWN;

    initFromSquares(square, WHITE_MOVE, 0, CANCASTLEOO + CANCASTLEOOO, CANCASTLEOO + CANCASTLEOOO, 0);
}



// initFromSquares
//
// Set up the board variables according to the information found in the
// input[64] array. All board & game initializations are done through this
// function (including readfen and setup).
void Board::initFromSquares(int input[64], unsigned char next, int fiftyM, int castleW, int castleB, int epSq)
{
    int i;


    // bitboards
    whiteKing    = 0;
    whiteQueens  = 0;
    whiteRooks   = 0;
    whiteBishops = 0;
    whiteKnights = 0;
    whitePawns   = 0;
    blackKing    = 0;
    blackQueens  = 0;
    blackRooks   = 0;
    blackBishops = 0;
    blackKnights = 0;
    blackPawns   = 0;
    whitePieces  = 0;
    blackPieces  = 0;
    occupiedSquares = 0;
    hashkey = 0;


    // populate all the initial bitboards
    for (i = 0; i < 64; i++)
    {
        square[i] = input[i];
        if (square[i] == WHITE_KING) 
        {  
            whiteKing    = whiteKing | BITSET[i]; 
            hashkey     ^= KEY.keys[i][WHITE_KING];  
        }
        if (square[i] == WHITE_QUEEN)
        {
            whiteQueens  = whiteQueens  | BITSET[i];
            hashkey     ^= KEY.keys[i][WHITE_QUEEN];        
        }
        if (square[i] == WHITE_ROOK)
        {
            whiteRooks   = whiteRooks   | BITSET[i];
            hashkey     ^= KEY.keys[i][WHITE_ROOK];         
        }
        if (square[i] == WHITE_BISHOP)
        {
            whiteBishops = whiteBishops | BITSET[i];
            hashkey     ^= KEY.keys[i][WHITE_BISHOP];       
        }
        if (square[i] == WHITE_KNIGHT) 
        {
            whiteKnights = whiteKnights | BITSET[i];
            hashkey     ^= KEY.keys[i][WHITE_KNIGHT];       
        }
        if (square[i] == WHITE_PAWN)   
        {
            whitePawns   = whitePawns   | BITSET[i];
            hashkey     ^= KEY.keys[i][WHITE_PAWN];         
        }
        if (square[i] == BLACK_KING)   
        {
            blackKing    = blackKing    | BITSET[i];
            hashkey     ^= KEY.keys[i][BLACK_KING];         
        }
        if (square[i] == BLACK_QUEEN)  
        {
            blackQueens  = blackQueens  | BITSET[i];
            hashkey     ^= KEY.keys[i][BLACK_QUEEN];        
        }
        if (square[i] == BLACK_ROOK)   
        {
            blackRooks   = blackRooks   | BITSET[i];
            hashkey     ^= KEY.keys[i][BLACK_ROOK];         
        }
        if (square[i] == BLACK_BISHOP) 
        {
            blackBishops = blackBishops | BITSET[i];
            hashkey     ^= KEY.keys[i][BLACK_BISHOP];       
        }
        if (square[i] == BLACK_KNIGHT) 
        {
            blackKnights = blackKnights | BITSET[i];
            hashkey     ^= KEY.keys[i][BLACK_KNIGHT];       
        }
        if (square[i] == BLACK_PAWN)   
        {
            blackPawns   = blackPawns   | BITSET[i];
            hashkey     ^= KEY.keys[i][BLACK_PAWN];         
        }
    }

    whitePieces = whiteKing | whiteQueens | whiteRooks | whiteBishops | whiteKnights | whitePawns;
    blackPieces = blackKing | blackQueens | blackRooks | blackBishops | blackKnights | blackPawns;
    occupiedSquares = whitePieces | blackPieces;

    nextMove = next;


    // initialize castling rights
    castleWhite = castleW;
    castleBlack = castleB;
    epSquare = epSq;
    fiftyMove = fiftyM;

    if (castleWhite & CANCASTLEOO)  hashkey ^= KEY.wk;
    if (castleWhite & CANCASTLEOOO) hashkey ^= KEY.wq;
    if (castleBlack & CANCASTLEOO)  hashkey ^= KEY.bk;
    if (castleBlack & CANCASTLEOOO) hashkey ^= KEY.bq;
    if (nextMove) hashkey ^= KEY.side;
    if (epSq) hashkey ^= KEY.ep[epSq];


    // initialize pawn structures and value
    totalWhitePawns = bitCnt(whitePawns) * PAWN_VALUE;
    totalBlackPawns = bitCnt(blackPawns) * PAWN_VALUE;
    totalWhitePieces =  bitCnt(whiteKnights) * KNIGHT_VALUE + bitCnt(whiteBishops) * BISHOP_VALUE +
        bitCnt(whiteRooks) * ROOK_VALUE + bitCnt(whiteQueens) * QUEEN_VALUE;
    totalBlackPieces =  bitCnt(blackKnights) * KNIGHT_VALUE + bitCnt(blackBishops) * BISHOP_VALUE +
        bitCnt(blackRooks) * ROOK_VALUE + bitCnt(blackQueens) * QUEEN_VALUE;
    Material  = totalWhitePawns + totalWhitePieces - totalBlackPawns - totalBlackPieces;

    endOfGame = 0;
    endOfSearch = 0;


    // clear triangular array for storing principal variation (PV)
    for (i = 0; i < MAX_PLY; i++) 
    {
        moveBufLen[i] = 0;
        triangularLength[i] = 0;
    }
    nodes = 0;
}



// display
//
// Convert the internal representation of the board into a human-readable string
// (capable of being shown and represented as a Board in ASCII) and show it on
// the screen.
void Board::display()
{
    int rank, file;
    int lastMove = 0;


    // check the last move
    if (endOfGame)
        lastMove = ((gameLine[endOfGame - 1]).move).getTosq();


    // display white front
    cout << endl << endl;
    if (!flipBoard)
    {
        cout << "    +----+----+----+----+----+----+----+----+" << endl;
        for (rank = 8; rank >= 1; rank--)
        {
            cout << setw(3) << rank <<  " |";
            for (file = 1; file <= 8; file++)
            {
                if (lastMove == BOARDINDEX[file][rank])
                	cout << " \033[96m\033[1m" << PIECENAMES[square[BOARDINDEX[file][rank]]] << "\033[0m |";
		        else
                	cout << " " << PIECENAMES[square[BOARDINDEX[file][rank]]] << " |";
            }
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
            for (file = 8; file >= 1; file--)
            {
                if (lastMove == BOARDINDEX[file][rank])
                	cout << " \033[96m\033[1m" << PIECENAMES[square[BOARDINDEX[file][rank]]] << "\033[0m |";
		        else
                    cout << " " << PIECENAMES[square[BOARDINDEX[file][rank]]] << " |";
            }
            cout << endl << "    +----+----+----+----+----+----+----+----+" << endl;
        }
        cout << "      h    g    f    e    d    c    b    a" << endl << endl;
    }
}



// toFEN
//
// Create a serial stream of characters representing a unique position, using
// FEN notation.
string Board::toFEN()
{
    string serial = "";
    unsigned rank, file;


    // 1) iterate over the entire board and write out in FEN 
    for (rank = 8; rank >= 1; rank--)
    {
        for (file = 1; file <= 8; file++)
        {
            if (square[BOARDINDEX[file][rank]] == EMPTY)         serial.append(1, '1');
            if (square[BOARDINDEX[file][rank]] == WHITE_PAWN)    serial.append(1, 'P');
            if (square[BOARDINDEX[file][rank]] == WHITE_KNIGHT)  serial.append(1, 'N');
            if (square[BOARDINDEX[file][rank]] == WHITE_BISHOP)  serial.append(1, 'B');
            if (square[BOARDINDEX[file][rank]] == WHITE_ROOK)    serial.append(1, 'R');
            if (square[BOARDINDEX[file][rank]] == WHITE_QUEEN)   serial.append(1, 'Q');
            if (square[BOARDINDEX[file][rank]] == WHITE_KING)    serial.append(1, 'K');
            if (square[BOARDINDEX[file][rank]] == BLACK_PAWN)    serial.append(1, 'p');
            if (square[BOARDINDEX[file][rank]] == BLACK_KNIGHT)  serial.append(1, 'n');
            if (square[BOARDINDEX[file][rank]] == BLACK_BISHOP)  serial.append(1, 'b');
            if (square[BOARDINDEX[file][rank]] == BLACK_ROOK)    serial.append(1, 'r');
            if (square[BOARDINDEX[file][rank]] == BLACK_QUEEN)   serial.append(1, 'q');
            if (square[BOARDINDEX[file][rank]] == BLACK_KING)    serial.append(1, 'k');
        }

        if (rank > 1)
            serial.append(1, '/');
    }
    serial.append(1, ' ');


    // 2) set the moving side ('w' or 'b')
    if (nextMove)
        serial.append(1, 'b');
    else
        serial.append(1, 'w');
    serial.append(1, ' ');


    // 3) add castling rights
    if (castleWhite & CANCASTLEOO)  serial.append(1, 'K');
    if (castleWhite & CANCASTLEOOO) serial.append(1, 'Q');
    if (castleBlack & CANCASTLEOO)  serial.append(1, 'k');
    if (castleBlack & CANCASTLEOOO) serial.append(1, 'q');
    if (!(castleWhite & CANCASTLEOO) && !(castleWhite & CANCASTLEOOO) &&
            !(castleBlack & CANCASTLEOO) && !(castleBlack & CANCASTLEOOO))
        serial.append(1, '-');
    serial.append(1, ' ');


    // 4) add enpassant square
    if (epSquare)
    {
        serial.append(SQUARENAME[epSquare]);
    }
    else
        serial.append(1, '-');
    serial.append(1, ' ');


    // 5) add 50-repetition rule
    serial += to_string(fiftyMove) + ' ';


    // 6) add move number
    serial.append(1, '1');


    // 7) compress the string
    size_t start_pos = 0;
    while((start_pos = serial.find("11111111", start_pos)) != std::string::npos)
    {
        serial.replace(start_pos, string("11111111").length(), "8");
        start_pos += string("8").length();
    }
    start_pos = 0;
    while((start_pos = serial.find("1111111", start_pos)) != std::string::npos)
    {
        serial.replace(start_pos, string("1111111").length(), "7");
        start_pos += string("7").length();
    }
    start_pos = 0;
    while((start_pos = serial.find("111111", start_pos)) != std::string::npos)
    {
        serial.replace(start_pos, string("111111").length(), "6");
        start_pos += string("6").length();
    }
    start_pos = 0;
    while((start_pos = serial.find("11111", start_pos)) != std::string::npos)
    {
        serial.replace(start_pos, string("11111").length(), "5");
        start_pos += string("5").length();
    }
    start_pos = 0;
    while((start_pos = serial.find("1111", start_pos)) != std::string::npos)
    {
        serial.replace(start_pos, string("1111").length(), "4");
        start_pos += string("4").length();
    }
    start_pos = 0;
    while((start_pos = serial.find("111", start_pos)) != std::string::npos)
    {
        serial.replace(start_pos, string("111").length(), "3");
        start_pos += string("3").length();
    }
    start_pos = 0;
    while((start_pos = serial.find("11", start_pos)) != std::string::npos)
    {
        serial.replace(start_pos, string("11").length(), "2");
        start_pos += string("2").length();
    }


    // append the depth as well
    return serial;
}



