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



// @file fen.cpp
//
// This file contains the functionality for serializing, saving and loading a
// board from and to a file, using the FEN notation.
#include <iostream>
#include <fstream>
#include <cstring>
#include "definitions.h"
#include "functions.h"
#include "extglobals.h"



// readFen
//
// Open a file and read a board position from a FEN string.
bool readFen(char *filename)
{
    char s[180];
    char fen[100];
    char fencolor[2];     
    char fencastling[5];
    char fenenpassant[3];
    int fenhalfmoveclock;
    int fenfullmovenumber;
    bool returnValue;
    FILE *fp;
    bool foundFEN = false;

    returnValue = false;

    // open the file for read and scan through until we find the number-th position:
    fp=fopen(filename, "rt");
    if (fp != NULL)
    {
        foundFEN = true;
        while (fscanf(fp, "%s", s) != EOF) 
        {
            if (!strcmp(s, "[FEN"))
            {
                fscanf(fp, "%s", fen);
                fscanf(fp, "%s", fencolor);           // b or w
                fscanf(fp, "%s", fencastling);        // -, or KQkq
                fscanf(fp, "%s", fenenpassant);       // -, or e3, or b6, etc
                fscanf(fp, "%d", &fenhalfmoveclock);  // int, used for the fifty move draw rule
                fscanf(fp, "%d", &fenfullmovenumber); // int. start with 1, It is incremented after move by Black
            }

            if (!foundFEN)
            {
                cout << "Could not load FEN position from file '" << filename << "'" << endl;
                returnValue = false;
            }
            else
            {
                setupFen(fen, fencolor, fencastling, fenenpassant, fenhalfmoveclock, fenfullmovenumber);
                returnValue = true;
            }

            fclose(fp);
        }
    }
    else
    {
        cerr << "Error opening file '" << filename << "'" << endl;
        returnValue = false;
    }

    return returnValue;
}


// setupFen
//
// Setup a board position from a FEN string.
void setupFen(char *fen, char *fencolor, char *fencastling, char *fenenpassant, int fenhalfmoveclock, int fenfullmovenumber)
{
    int i, file, rank, counter, piece;
    int whiteCastle, blackCastle, next, epsq;


    // initially clear the board 
    piece = 0;
    for (i = 0; i < 64; i++)
        board.square[i] = EMPTY;


    // loop over the FEN string characters, and populate board.square[]
    // i is used as index for the FEN string
    // counter is the index for board.square[], 0..63
    // file and rank relate to the position on the chess board, 1..8
    // There is no error/legality checking on the FEN string!!
    file = 1;
    rank = 8;
    i = 0;
    counter = 0;
    while ((counter < 64) && (fen[i] != '\0'))
    {
        // '1'  through '8':
        if (((int) fen[i] > 48) && ((int) fen[i] < 57))
        {
            file+= (int) fen[i] - 48;
            counter+= (int) fen[i] - 48;
        }

        //  other characters:
        else
        {
            switch (fen[i])
            {
                case '/':   rank--;
                            file = 1;
                            break;

                case 'P':   board.square[BOARDINDEX[file][rank]] = WHITE_PAWN;
                            file += 1;
                            counter += 1;
                            break;

                case 'N':   board.square[BOARDINDEX[file][rank]] = WHITE_KNIGHT;
                            file += 1;
                            counter += 1;
                            break;

                case 'B':   board.square[BOARDINDEX[file][rank]] = WHITE_BISHOP;
                            file += 1;
                            counter += 1;
                            break;

                case 'R':   board.square[BOARDINDEX[file][rank]] = WHITE_ROOK;
                            file += 1;
                            counter += 1;
                            break;

                case 'Q':   board.square[BOARDINDEX[file][rank]] = WHITE_QUEEN;
                            file += 1;
                            counter += 1;
                            break;

                case 'K':   board.square[BOARDINDEX[file][rank]] = WHITE_KING;
                            file += 1;
                            counter += 1;
                            break;

                case 'p':   board.square[BOARDINDEX[file][rank]] = BLACK_PAWN;
                            file += 1;
                            counter += 1;
                            break;

                case 'n':   board.square[BOARDINDEX[file][rank]] = BLACK_KNIGHT;
                            file += 1;
                            counter += 1;
                            break;

                case 'b':   board.square[BOARDINDEX[file][rank]] = BLACK_BISHOP;
                            file += 1;
                            counter += 1;
                            break;

                case 'r':   board.square[BOARDINDEX[file][rank]] = BLACK_ROOK;
                            file += 1;
                            counter += 1;
                            break;

                case 'q':   board.square[BOARDINDEX[file][rank]] = BLACK_QUEEN;
                            file += 1;
                            counter += 1;
                            break;

                case 'k':   board.square[BOARDINDEX[file][rank]] = BLACK_KING;
                            file += 1;
                            counter += 1;
                            break;

                default:    break;
            }
        }

        i++;
    }
    next = WHITE_MOVE;
    if (fencolor[0] == 'b') next = BLACK_MOVE;

    whiteCastle = 0;
    blackCastle = 0;
    if (strstr(fencastling, "K")) whiteCastle += CANCASTLEOO;
    if (strstr(fencastling, "Q")) whiteCastle += CANCASTLEOOO;
    if (strstr(fencastling, "k")) blackCastle += CANCASTLEOO;
    if (strstr(fencastling, "q")) blackCastle += CANCASTLEOOO;
    if (strstr(fenenpassant, "-"))
    {
        epsq = 0;
    }
    else
    {
        // translate a square coordinate (as string) to int (eg 'e3' to 20):
        epsq = ((int) fenenpassant[0] - 96) + 8 * ((int) fenenpassant[1] - 48) - 9;
    }

    board.initFromSquares(board.square, next, fenhalfmoveclock, whiteCastle , blackCastle , epsq);
}
