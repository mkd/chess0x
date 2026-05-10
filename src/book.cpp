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



// This file contains an opening book with theory lines and replies to different
// opening moves.
//
// The majority of the moves have been taken from online Chess databases
// (specially from 365chess.com) and then further analyzed with Stockfish 7.0 to
// avoid opening flaws.
#include <algorithm>
#include <iostream>
#include <sstream>
#include <map>
#include <time.h>
#include <vector>
#include "book.h"
#include "app.h"

using namespace std;


unordered_map<string, string> book;


// initBook
//
// Fill in the openings book with all the theory lines.
void initBook()
{
    // different openings for White
    book["%"] = "e4 | d4 | Nf3 | c4";


    // first-move replies for Black
    book["1. e4"] = "c5 | e5 | e6 | c6 | d6";
    book["1. d4"] = "Nf6 | d5 | e6 | f5";
    book["1. Nf3"] = "Nf6 | d5 | c5 | g6 | e6";
    book["1. c4"] = "Nf6 | e5 | e6 | c5 | g6";



    // C24 Bishop's Opening: Berlin Defense -- WHITE
    book["1. e4 e5 2. Bc4 Nf6"] = "d3 | Nc3";


    // Sicilian defense (B20)
    book["1. e4 c5"] = "Nf3 | Nc3 | c3";
    book["1. e4 c5 2. Nf3"] = "d6 | Nc6 | e6 | g6";
    book["1. e4 c5 2. Nc3"] = "Nc6 | e6 | d6";
    book["1. e4 c5 2. c3"] = "d5 | Nf6 | e6 | d6 | Nc6";
    book["1. e4 c5 2. d4"] = "cxd4";


    // B20 Sicilian defence -- BLACK
    book["1. e4 c5 2. d3"] = "Nc6 | g6 | e6 | d5 | d6";
    book["1. e4 c5 2. d3 Nc6 3. g3"] = "g6";
    book["1. e4 c5 2. d3 Nc6 3. g3 g6 4. Bg2"] = "Bg7";
    book["1. e4 c5 2. d3 Nc6 3. f4"] = "d5";
    book["1. e4 c5 2. d3 Nc6 3. Be2"] = "g6";
    book["1. e4 c5 2. d3 Nc6 3. Nf3"] = "g6";
    book["1. e4 c5 2. d3 Nc6 3. Nc3"] = "g6";
    book["1. e4 c5 2. d3 Nc6 3. c3"] = "d5";
    book["1. e4 c5 2. d3 Nc6 3. c3 d5 4. Nd2"] = "Nf6";
    book["1. e4 c5 2. d3 Nc6 3. c3 d5 4. Nf3"] = "e5";
    book["1. e4 c5 2. d3 Nc6 3. c3 d5 4. f4"] = "e5";
    book["1. e4 c5 2. d3 Nc6 3. c3 d5 4. Be2"] = "Nf6";
    book["1. e4 c5 2. d3 Nc6 3. c3 d5 4. exd5"] = "Qxd5";


    // B21 Sicilian Defense: McDonnell Attack -- BLACK
    book["1. e4 c5 2. f4"] = "d5 | Nc6 | e6";


    // B20 Sicilian, Keres variation (2.Ne2) -- BLACK
    book["1. e4 c5 2. Ne2"] = "Nf6 | Nc6 | d6";
    book["1. e4 c5 2. Ne2 Nf6 3. e5"] = "Ng4";
    book["1. e4 c5 2. Ne2 Nf6 3. Nbc3"] = "d5";
    book["1. e4 c5 2. Ne2 Nf6 3. Nbc3 d5 4. e5"] = "Ng4";
    book["1. e4 c5 2. Ne2 Nf6 3. Nbc3 d5 4. exd5"] = "Nxd5";
    book["1. e4 c5 2. Ne2 Nf6 3. Nbc3 d5 4. exd5 Nxd5 5. Nxd5"] = "Qxd5";
    book["1. e4 c5 2. Ne2 Nf6 3. Nbc3 d5 4. exd5 Nxd5 5. g3"] = "Nxc3";
    book["1. e4 c5 2. Ne2 Nf6 3. Nbc3 d5 4. exd5 Nxd5 5. g3 Nxc3 6. Nxc3"] = "h5";


    // B22 Sicilian, Alapin's variation (2.c3) -- BLACK
    book["1. e4 c5 2. c3 Nf6 3. d3"] = "Nc6";
    book["1. e4 c5 2. c3 Nf6 3. e5"] = "Nd5";
    book["1. e4 c5 2. c3 Nf6 3. e5 Nd5 4. Nf3"] = "Nc6";
    book["1. e4 c5 2. c3 Nf6 3. e5 Nd5 4. d4"] = "cxd4";
    book["1. e4 c5 2. c3 Nf6 3. e5 Nd5 4. d4 cxd4 5. Nf3"] = "d6";
    book["1. e4 c5 2. c3 Nf6 3. e5 Nd5 4. d4 cxd4 5. cxd4"] = "d6";


    // B22 Sicilian, Alapin's variation (2.c3) -- WHITE
    book["1. e4 c5 2. c3 Nc6"] = "d4 | Nf3";
    book["1. e4 c5 2. c3 Nc6 3. d4 cxd4"] = "cxd4";
    book["1. e4 c5 2. c3 Nc6 3. d4 cxd4 4. cxd4 d5"] = "exd5";
    book["1. e4 c5 2. c3 Nc6 3. d4 cxd4 4. cxd4 d5 5. exd5 Qxd5"] = "Nf3";
    book["1. e4 c5 2. c3 Nc6 3. d4 cxd4 4. cxd4 e6"] = "d5";
    book["1. e4 c5 2. c3 Nc6 3. d4 d5"] = "exd5";
    book["1. e4 c5 2. c3 Nc6 3. d4 d5 4. exd5 Qxd5"] = "Nf3";

    book["1. e4 c5 2. c3 Nf6"] = "e5";
    book["1. e4 c5 2. c3 Nf6 3. e5 Nd5"] = "d4 | Nf3 | Bc4";
    book["1. e4 c5 2. c3 Nf6 3. e5 Nd5 4. Nf3 Nc6"] = "d4 | Bc4";
    book["1. e4 c5 2. c3 Nf6 3. e5 Nd5 4. Nf3 Nc6 5. d4 cxd4"] = "Bc4 | cxd4";
    book["1. e4 c5 2. c3 Nf6 3. e5 Nd5 4. Nf3 e6"] = "d4 | Bc4";
    book["1. e4 c5 2. c3 Nf6 3. e5 Nd5 4. Nf3 e6 5. d4 cxd4"] = "cxd4 | Bc4";
    book["1. e4 c5 2. c3 Nf6 3. e5 Nd5 4. Nf3 d6"] = "d4 | exd6 | Bc4";
    book["1. e4 c5 2. c3 Nf6 3. e5 Nd5 4. Nf3 d6 5. d4 cxd4"] = "cxd4 | Bc4 | Bb5+";


    book["1. e4 c5 2. c3 Nf6 3. e5 Nd5 4. Nf3 Nc6 5. d4 cxd4 6. Bc4 e6"] = "cxd4 | Bxd5";
    book["1. e4 c5 2. c3 Nf6 3. e5 Nd5 4. Nf3 Nc6 5. d4 cxd4 6. Bc4 Nb6"] = "Bb3";
    book["1. e4 c5 2. c3 Nf6 3. e5 Nd5 4. Nf3 Nc6 5. d4 cxd4 6. Bc4 Nb6 7. Bb3 d6"] = "Qe2 | exd6";
    book["1. e4 c5 2. c3 Nf6 3. e5 Nd5 4. Nf3 Nc6 5. d4 cxd4 6. Bc4 Nb6 7. Bb3 d5"] = "exd6";
    book["1. e4 c5 2. c3 Nf6 3. e5 Nd5 4. Nf3 Nc6 5. d4 cxd4 6. Bc4 Nb6 7. Bb3 a5"] = "a4";
    book["1. e4 c5 2. c3 Nf6 3. e5 Nd5 4. Nf3 Nc6 5. d4 cxd4 6. Bc4 Nb6 7. Bb3 dxc3"] = "Nxc3";


    // B23 Sicilian, closed -- WHITE
    book["1. e4 c5 2. Nc3 a6"] = "g3 | Nf3";
    book["1. e4 c5 2. Nc3 a6 3. Nf3 e6"] = "d4";
    book["1. e4 c5 2. Nc3 a6 3. Nf3 e6 4. d4 cxd4"] = "Nxd4";
    book["1. e4 c5 2. Nc3 a6 3. Nf3 e6 4. d4 b5"] = "Bd3";
    book["1. e4 c5 2. Nc3 a6 3. Nf3 e6 4. d4 Qc7"] = "d5";
    book["1. e4 c5 2. Nc3 a6 3. Nf3 d6"] = "d4";
    book["1. e4 c5 2. Nc3 a6 3. Nf3 b5"] = "d4";
    book["1. e4 c5 2. Nc3 a6 3. Nf3 Nc6"] = "d4";

    book["1. e4 c5 2. Nc3 Nf6"] = "Nf3 | e5";

    book["1. Nf3 c5 2. e4 d6"] = "d4 | Bb5+ | c3 | Nc3 | Bc4";


    // Sicilian closed (B23)
    book["1. e4 c5 2. Nc3 g6"] = "g3 | f4 | d4 | Nf3";
    book["1. e4 c5 2. Nc3 g6 3. d4 cxd4"] = "Qxd4";
    book["1. e4 c5 2. Nc3 g6 3. d4 cxd4 4. Qxd4 Nf6"] = "Nf3 | Bb5";
    book["1. e4 c5 2. Nc3 g6 3. d4 Bg7"] = "dxc5";
    book["1. e4 c5 2. Nc3 g6 3. Nf3 Bg7"] = "d4";

    book["1. e4 c5 2. c3 d6"] = "d4 | Nf3";



    // B22 Sicilian Defense: Alapin Variation -- BLACK
    book["1. e4 c5 2. c3 d6 3. d4"] = "Nf6";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. Bd3"] = "cxd4 | g6";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. dxc5"] = "Nc6";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. f3"] = "e6";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. Nd2"] = "Nxe4";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. Bb5+"] = "Bd7";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. Bb5+ Bd7 5. Bxd7+"] = "Nbxd7";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. Bc4"] = "cxd4";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. Bc4 cxd4 5. Qxd4"] = "Nbd7";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. Bc4 cxd4 5. cxd4"] = "Nxe4";
    book["1. e4 c5 2. c3 d6 3. Nf3"] = "Nf6";
    book["1. e4 c5 2. c3 d6 3. Nf3 Nf6 4. Be2"] = "e5 | g6";
    book["1. e4 c5 2. c3 d6 3. Nf3 Nf6 4. h3"] = "Nc6";
    book["1. e4 c5 2. c3 d6 3. Nf3 Nf6 4. Bd3"] = "Bg4";
    book["1. e4 c5 2. c3 d6 3. Nf3 Nf6 4. Bc4"] = "Nxe4 | Nc6";
    book["1. e4 c5 2. c3 d6 3. Nf3 Nf6 4. d3"] = "g6 | e5";
    book["1. e4 c5 2. c3 d6 3. Nf3 Nf6 4. Qc2"] = "Qc7";
    book["1. e4 c5 2. c3 d6 3. Nf3 Nf6 4. Bb5+"] = "Bd7";
    book["1. e4 c5 2. c3 d6 3. Nf3 Nf6 4. Bb5+ Bd7 5. Bxd7+"] = "Qxd7";
    book["1. e4 c5 2. c3 d6 3. Nf3 Nf6 4. g3"] = "Nc6";
    book["1. e4 c5 2. c3 d6 3. Nf3 Nf6 4. e5"] = "dxe5";
    book["1. e4 c5 2. c3 d6 3. Nf3 Nf6 4. e5 dxe5 5. Nxe5"] = "Nbd7";
    book["1. e4 c5 2. c3 d6 3. Nf3 Nf6 4. d4"] = "Nxe4";
    book["1. e4 c5 2. c3 d6 3. g3"] = "d5 | Nf6"; 
    book["1. e4 c5 2. c3 d6 3. d3"] = "Nf6 | Nc6";
    book["1. e4 c5 2. c3 d6 3. f4"] = "Nf6";
    book["1. e4 c5 2. c3 d6 3. Bc4"] = "Nf6";
    book["1. e4 c5 2. c3 d6 3. Bb5+"] = "Bd7";
    book["1. e4 c5 2. c3 d6 3. Bb5+ Bd7 4. Bxd7+"] = "Qxd7 | Nxd7";



    // B22 Sicilian Defense: Alapin Variation -- WHITE
    book["1. e4 c5 2. c3 d6 3. d4 Nf6"] = "Bd3 | dxc5 | e5 | f3 | Nd2";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. Bd3 cxd4"] = "cxd4 | Nf3";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. Bd3 Nc6"] = "Nf3 | Ne2 | d5 | Be3";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. Bd3 g6"] = "Nf3 | Ne2 | f4 | h3";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. Bd3 e5"] = "d5 | Nf3 | dxe5 | Ne2 | dxc5";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. Bd3 e6"] = "Nf3 | f4 | Ne2";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. dxc5 Nc6"] = "cxd6 | f3 | Bc4";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. dxc5 Nxe4"] = "cxd6 | Qa4+";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. dxc5 dxc5"] = "Qxd8+";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. dxc5 dxc5 5. Qxd8+ Kxd8"] = "e5 | f3";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. dxc5 Qa5"] = "cxd6";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. dxc5 Qa5 5. cxd6 Nxe4"] = "dxe7 | Ne2";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. dxc5 Qa5 5. cxd6 exd6"] = "b4";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. e5 dxe5"] = "dxe5 | Bb5+ | dxc5";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. e5 Nd5"] = "Nf3 | exd6 | f4 | c4 | dxc5 | Bc4";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. f3 cxd4"] = "cxd4";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. f3 Nc6"] = "Be3 | d5";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. f3 g6"] = "Be3 | Bd3 | dxc5";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. f3 Nbd7"] = "Be3";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. f3 e6"] = "Be3 | Bd3 | Bg5";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. f3 e5"] = "d5 | dxe5 | Be3";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. f3 d5"] = "e5 | dxc5";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. Nd2 cxd4"] = "cxd4 | Qa4+";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. Nd2 g6"] = "Ngf3 | f4 | Bd3";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. Nd2 Nc6"] = "Ngf3";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. Nd2 e5"] = "d5 | Ngf3";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. Nd2 Nbd7"] = "Ngf3 | f4";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. Nd2 e6"] = "Bd3 | Ngf3";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. Nd2 e6 5. Ngf3 cxd4"] = "cxd4";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. Nd2 e6 5. Ngf3 Be7"] = "Bd3 | Bb5+";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. Nd2 e6 5. Ngf3 Nc6"] = "Bb5 | Bd3";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. Nd2 e6 5. Ngf3 Nc6 6. Bb5 Bd7"] = "0-0 | dxc5";
    book["1. e4 c5 2. c3 d6 3. d4 Nf6 4. Nd2 e6 5. Ngf3 Nc6 6. Bb5 Bd7 7. dxc5 dxc5"] = "0-0";


    book["1. e4 c5 2. c3 d6 3. d4 Nc6"] = "d5";
    book["1. e4 c5 2. c3 d6 3. d4 Nc6 4. d5 Nb8"] = "Bd3";
    book["1. e4 c5 2. c3 d6 3. d4 Nc6 4. d5 Ne5"] = "f4";

    book["1. e4 c5 2. c3 d5"] = "exd5";
    book["1. e4 c5 2. c3 d5 3. exd5"] = "Qxd5";


    // B22 Sicilian Defense: Alapin Variation, Barmen Defense -- WHITE
    book["1. e4 c5 2. c3 d5 3. exd5 Nf6"] = "Qa4+";
    book["1. e4 c5 2. c3 d5 3. exd5 Nf6 4. Qa4+ Qd7"] = "Bb5";
    book["1. e4 c5 2. c3 d5 3. exd5 Nf6 4. Qa4+ Bd7"] = "Qb3";
    book["1. e4 c5 2. c3 d5 3. exd5 Nf6 4. Qa4+ Nbd7"] = "Qb3";
    book["1. e4 c5 2. c3 d5 3. exd5 Qxd5"] = "d4";
    book["1. e4 c5 2. c3 d5 3. exd5 Qxd5 4. d4 Nf6"] = "Nf3 | Be3";
    book["1. e4 c5 2. c3 d5 3. exd5 Qxd5 4. d4 e6"] = "Nf3 | Na3";
    book["1. e4 c5 2. c3 d5 3. exd5 Qxd5 4. d4 g6"] = "Nf3 | dxc5 | Na3";
    book["1. e4 c5 2. c3 d5 3. exd5 Qxd5 4. d4 g6 5. dxc5 Qxc5"] = "Be3";
    book["1. e4 c5 2. c3 d5 3. exd5 Qxd5 4. d4 cxd4"] = "cxd4 | Nf3";
    book["1. e4 c5 2. c3 d5 3. exd5 Qxd5 4. d4 e5"] = "dxe5";
    book["1. e4 c5 2. c3 d5 3. exd5 Qxd5 4. d4 e5 5. dxe5 Qxd1+"] = "Kxd1";
    book["1. e4 c5 2. c3 d5 3. exd5 Qxd5 4. d4 e5 5. dxe5 Qxd1+ 6. Kxd1 Nc6"] = "Nf3";
    book["1. e4 c5 2. c3 d5 3. exd5 Qxd5 4. d4 e5 5. dxe5 Qxd1+ 6. Kxd1 Be6"] = "Nd2 | Nf3";
    book["1. e4 c5 2. c3 d5 3. exd5 Qxd5 4. d4 e5 5. dxe5 Qxd1+ 6. Kxd1 Bf5"] = "Nf3";
    book["1. e4 c5 2. c3 d5 3. exd5 Qxd5 4. d4 Nc6"] = "Nf3 | dxc5 | Be3";
    book["1. e4 c5 2. c3 d5 3. exd5 Qxd5 4. d4 Nc6 5. dxc5 Qxd1+"] = "Kxd1";
    book["1. e4 c5 2. c3 d5 3. exd5 Qxd5 4. d4 Nc6 5. dxc5 Qxd1+ 6. Kxd1 Bf5"] = "Be3";
    book["1. e4 c5 2. c3 d5 3. exd5 Qxd5 4. d4 Nc6 5. dxc5 Qxd1+ 6. Kxd1 e5"] = "b4";
    book["1. e4 c5 2. c3 d5 3. exd5 Qxd5 4. d4 Nc6 5. dxc5 Qxd1+ 6. Kxd1 Nf6"] = "Nf3";
    book["1. e4 c5 2. c3 d5 3. exd5 Qxd5 4. d4 Nc6 5. dxc5 Qxd1+ 6. Kxd1 Nf6 7. Nf3 g6"] = "Bb5 | Nbd2";
    book["1. e4 c5 2. c3 d5 3. exd5 Qxd5 4. d4 Nc6 5. dxc5 Qxd1+ 6. Kxd1 Nf6 7. Nf3 g6 8. Bb5 Bg7"] = "Re1 | Nbd2";
    book["1. e4 c5 2. c3 d5 3. exd5 Qxd5 4. d4 Nc6 5. dxc5 Qxd1+ 6. Kxd1 Nf6 7. Nf3 g6 8. Nbd2 Bg7"] = "Bb5";
    book["1. e4 c5 2. c3 d5 3. exd5 Qxd5 4. d4 Nc6 5. dxc5 Qxd1+ 6. Kxd1 Nf6 7. Nf3 Bg4"] = "Be3";
    book["1. e4 c5 2. c3 d5 3. exd5 Qxd5 4. d4 Nc6 5. dxc5 Qxd1+ 6. Kxd1 Nf6 7. Nf3 Bf5"] = "Be3";
    book["1. e4 c5 2. c3 d5 3. exd5 Qxd5 4. d4 Nc6 5. dxc5 Qxd1+ 6. Kxd1 Nf6 7. Nf3 e6"] = "b4";


    book["1. e4 c5 2. c3 d5 3. exd5 Nf6"] = "d4 | Bb5+";


    // B22 Sicilian, Alapin's variation (2.c3) -- WHITE
    book["1. e4 c5 2. c3 g6"] = "d4";
    book["1. e4 c5 2. c3 g6 3. d4 Bg7"] = "dxc5";
    book["1. e4 c5 2. c3 g6 3. d4 d5"] = "dxc5";
    book["1. e4 c5 2. c3 g6 3. d4 cxd4"] = "cxd4";
    book["1. e4 c5 2. c3 g6 3. d4 cxd4 4. cxd4 d5"] = "e5";
    book["1. e4 c5 2. c3 g6 3. d4 cxd4 4. cxd4 Bg7"] = "Nc3";
    book["1. e4 c5 2. c3 g6 3. d4 cxd4 4. cxd4 Bg7 5. Nc3 d6"] = "Nf3";
    book["1. e4 c5 2. c3 g6 3. d4 cxd4 4. cxd4 Bg7 5. Nc3 a6"] = "Nf3";
    book["1. e4 c5 2. c3 g6 3. d4 cxd4 4. cxd4 Bg7 5. Nc3 a6 6. Nf3 d6"] = "h3";
    book["1. e4 c5 2. c3 g6 3. d4 cxd4 4. cxd4 Bg7 5. Nc3 a6 6. Nf3 b5"] = "Bd3";
    book["1. e4 c5 2. c3 g6 3. d4 cxd4 4. cxd4 Bg7 5. Nc3 a6 6. Nf3 b5 7. Bd3 Nc6"] = "0-0";
    book["1. e4 c5 2. c3 g6 3. d4 cxd4 4. cxd4 Bg7 5. Nc3 a6 6. Nf3 b5 7. Bd3 Bb7"] = "0-0";
    book["1. e4 c5 2. c3 g6 3. d4 cxd4 4. cxd4 Bg7 5. Nc3 a6 6. Nf3 b5 7. Bd3 Bb7 8. 0-0 Nc6"] = "Be3";
    book["1. e4 c5 2. c3 g6 3. d4 cxd4 4. cxd4 Bg7 5. Nc3 a6 6. Nf3 b5 7. Bd3 Bb7 8. 0-0 Nf6"] = "e5";
    book["1. e4 c5 2. c3 g6 3. d4 cxd4 4. cxd4 Bg7 5. Nc3 a6 6. Nf3 b5 7. Bd3 Bb7 8. 0-0 Nf6 9. e5 Nd5"] = "Ng5";
    book["1. e4 c5 2. c3 g6 3. d4 cxd4 4. cxd4 Bg7 5. Nc3 a6 6. Nf3 b5 7. Bd3 Bb7 8. 0-0 Nf6 9. e5 Nd5 10. Ng5 Nxc3"] = "bxc3";


    book["1. e4 c5 2. g3"] = "Nc6";
    book["1. e4 c5 2. g3 Nc6 3. Bg2"] = "g6";

    book["1. e4 c5 2. Nf3 d6"] = "d4 | Bb5+ | c3";
    book["1. e4 c5 2. Nf3 Nc6"] = "d4 | Bb5 | Nc3 | c3";
    book["1. e4 c5 2. Nf3 e6"] = "d4 | Nc3 | c3 | d3 | b3";
    book["1. e4 c5 2. Nf3 g6"] = "d4 | c3 | c4";


    // B40 Sicilian Defense: French Variation, Westerinen Attack -- WHITE
    book["1. e4 c5 2. Nf3 e6 3. b3 b6"] = "Bb2 | Nc3";
    book["1. e4 c5 2. Nf3 e6 3. b3 Nc6"] = "Bb5 | Bb5";
    book["1. e4 c5 2. Nf3 e6 3. b3 a6"] = "Bb2 | Be2 | c4";
    book["1. e4 c5 2. Nf3 e6 3. b3 Nf6"] = "e5";
    book["1. e4 c5 2. Nf3 e6 3. b3 Nf6 4. e5 Ng8"] = "Bb2";
    book["1. e4 c5 2. Nf3 e6 3. b3 Nf6 4. e5 Nd5"] = "Bb2";
    book["1. e4 c5 2. Nf3 e6 3. b3 d5"] = "exd5 | Bb5+";
    book["1. e4 c5 2. Nf3 e6 3. b3 d5 4. exd5 exd5"] = "Bb5+ | Bb2";
    book["1. e4 c5 2. Nf3 e6 3. b3 d5 4. exd5 Qxd5"] = "Nc3 | Bb2";
    book["1. e4 c5 2. Nf3 e6 3. b3 d6"] = "Bb2";
    book["1. e4 c5 2. Nf3 e6 3. b3 d6 4. Bb2 Nf6"] = "e5";
    book["1. e4 c5 2. Nf3 e6 3. b3 d6 4. Bb2 Nf6 5. e5 dxe5"] = "Nxe5";
    book["1. e4 c5 2. Nf3 e6 3. b3 d6 4. Bb2 e5"] = "Bb5+";
    book["1. e4 c5 2. Nf3 e6 3. b3 d6 4. Bb2 Nc6"] = "d4";
    book["1. e4 c5 2. Nf3 e6 3. b3 d6 4. Bb2 Nc6 5. d4 cxd4"] = "Nxd4";
    book["1. e4 c5 2. Nf3 e6 3. b3 d6 4. Bb2 Nc6 5. d4 cxd4 6. Nxd4 Nf6"] = "Nxc6";
    book["1. e4 c5 2. Nf3 e6 3. b3 d6 4. Bb2 Nc6 5. d4 cxd4 6. Nxd4 Nf6 7. Nxc6 bxc6"] = "Bd3";
    book["1. e4 c5 2. Nf3 e6 3. b3 d6 4. Bb2 a6"] = "d4";
    book["1. e4 c5 2. Nf3 e6 3. b3 d6 4. Bb2 a6 5. d4 cxd4"] = "Qxd4";
    book["1. e4 c5 2. Nf3 e6 3. b3 d6 4. Bb2 a6 5. d4 cxd4 6. Qxd4 Nc6"] = "Qe3";


    // B27 Sicilian, Hungarian variation -- BLACK
    book["1. e4 c5 2. Nf3 g6 3. c3"] = "Bg7";
    book["1. e4 c5 2. Nf3 g6 3. c3 Bg7 4. d4"] = "cxd4";
    book["1. e4 c5 2. Nf3 g6 3. c3 Bg7 4. d4 cxd4 5. cxd4"] = "d5";
    book["1. e4 c5 2. Nf3 g6 3. c3 Bg7 4. d4 cxd4 5. cxd4 d5 6. e5"] = "a6";
    book["1. e4 c5 2. Nf3 g6 3. c3 Bg7 4. d4 cxd4 5. cxd4 d5 6. e5 a6 7. Bd3"] = "Nc6";


    book["1. e4 c5 2. Nf3 e6 3. d4"] = "cxd4";
    book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4"] = "Nc6";
    book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nc6 5. Nc3"] = "Nf6";
    book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nc6 5. Nb5"] = "d6";
    book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nc6 5. Be3"] = "Nf6";
    book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nc6 5. Nxc6"] = "bxc6";
    book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nc6 5. Be2"] = "Nf6";



    // B51 Sicilian Defense: Moscow Variation -- WHITE
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Nd7"] = "d4 | c4 | a4";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7"] = "Bxd7+ | c4 | Qe2";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. Bxd7+ Qxd7"] = "c4 | d3 | 0-0";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. Bxd7+ Nxd7"] = "0-0 | c4 | Qe2";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. Qe2 Bxb5"] = "Qxb5+";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. Qe2 Bxb5 5. Qxb5+ Qd7"] = "Qe2 | a4 | Qxd7+";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. Qe2 Bxb5 5. Qxb5+ Qd7 6. Qxd7+ Nxd7"] = "Nc3";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. Qe2 Bxb5 5. Qxb5+ Qd7 6. Qxd7+ Kxd7"] = "d4";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. Qe2 Bxb5 5. Qxb5+ Qd7 6. Qxd7+ Kxd7 7. d4 cxd4"] = "Nxd4";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. Qe2 Nf6"] = "0-0 | Bxd7+";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. Qe2 Nf6 5. Bxd7+ Nbxd7"] = "0-0";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. Qe2 Nf6 5. Bxd7+ Qxd7"] = "0-0";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. Qe2 e6"] = "d4 | 0-0";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. Qe2 a6"] = "Bxd7+";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. Qe2 a6 5. Bxd7+ Nxd7"] = "0-0";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. Qe2 a6 5. Bxd7+ Qxd7"] = "c3";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. Qe2 g6"] = "c3";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. Qe2 Nc6"] = "Bxc6 | c3 | 0-0";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. Qe2 Nc6 5. Bxc6 Bxc6"] = "d4";

    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Nc6"] = "0-0";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Nc6 4. 0-0 a6"] = "Bxc6+";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Nc6 4. 0-0 a6 5. Bxc6+ bxc6"] = "e5 | Re1";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Nc6 4. 0-0 Nf6"] = "e5";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Nc6 4. 0-0 e6"] = "c3 | Re1 | d4";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Nc6 4. 0-0 Bg4"] = "c3";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Nc6 4. 0-0 Bd7"] = "Re1 | Ba4 | a4";



    // B51 Sicilian Defense: Moscow Variation -- BLACK
    book["1. e4 c5 2. Nf3 d6 3. Bb5+"] = "Nd7 | Bd7";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. c4"] = "Nc6 | g6 | Nf6";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. Qe2"] = "Bxb5 | Nc6 | Nf6";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. Qe2 Bxb5 5. Qxb5+"] = "Qd7";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. Bxd7+"] = "Qxd7 | Nxd7";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. Bxd7+ Qxd7 5. c4"] = "Nf6 | Nc6 | e6";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. Bxd7+ Qxd7 5. d4"] = "cxd4 | Nf6";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. Bxd7+ Qxd7 5. d3"] = "Nc6 | Nf6 | g6";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. Bxd7+ Qxd7 5. 0-0"] = "Nc6 | Nf6 | e6";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. Bxd7+ Qxd7 5. 0-0 Nc6 6. c4"] = "Nf6 | g6";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. Bxd7+ Qxd7 5. 0-0 Nc6 6. d4"] = "cxd4";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. Bxd7+ Qxd7 5. 0-0 Nc6 6. d4 cxd4 7. Nxd4"] = "Nf6";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. Bxd7+ Qxd7 5. 0-0 Nc6 6. Re1"] = "e6 | Nf6 | a6";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. Bxd7+ Qxd7 5. 0-0 Nc6 6. c3"] = "Nf6 | d5";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. Bxd7+ Qxd7 5. 0-0 Nc6 6. c3 Nf6 7. Qe2"] = "e6 | h6";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. Bxd7+ Qxd7 5. 0-0 Nc6 6. c3 Nf6 7. d4"] = "Nxe4";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. Bxd7+ Qxd7 5. 0-0 Nc6 6. c3 Nf6 7. d4 Nxe4 8. d5"] = "Ne5";
    book["1. e4 c5 2. Nf3 d6 3. Bb5+ Bd7 4. Bxd7+ Qxd7 5. 0-0 Nc6 6. c3 Nf6 7. Re1"] = "e6 | Rc8";



    // B40 Sicilian defence -- WHITE
    book["1. e4 c5 2. Nf3 e6 3. d4 cxd4"] = "Nxd4";
    book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nc6"] = "Nc3";
    book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Nf6"] = "Nc3";
    book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Qb6"] = "Nb3";
    book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Bc5"] = "Be3";
    book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 d6"] = "c4";
    book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 Qc7"] = "Nb5";
    book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 g6"] = "Nc3";
    book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 a6"] = "Bd3";
    book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 a6 5. Bd3 Nc6"] = "Nxc6";
    book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 a6 5. Bd3 Nc6 6. Nxc6 bxc6"] = "0-0";
    book["1. e4 c5 2. Nf3 e6 3. d4 cxd4 4. Nxd4 a6 5. Bd3 Nc6 6. Nxc6 dxc6"] = "Nd2";


    // B27 Sicilian, Hungarian variation -- BLACK
    book["1. e4 c5 2. Nf3 g6 3. d4"] = "cxd4";
    book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. c3"] = "dxc3";
    book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. c3 dxc3 5. Bc4"] = "cxb2";
    book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. c3 dxc3 5. Bc4 cxb2 6. Bxb2"] = "Nf6";
    book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. c3 dxc3 5. Bc4 cxb2 6. Bxb2 Nf6 7. e5"] = "Nh5";
    book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. c3 dxc3 5. Bc4 cxb2 6. Bxb2 Nf6 7. e5 Nh5 8. 0-0"] = "Bg7";
    book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. c3 dxc3 5. Bc4 cxb2 6. Bxb2 Nf6 7. e5 Nh5 8. e6"] = "f6";
    book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. c3 dxc3 5. Nxc3"] = "Nc6";
    book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Qxd4"] = "Nf6";
    book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Qxd4 Nf6 5. e5"] = "Nc6";
    book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Qxd4 Nf6 5. Nc3"] = "Nc6";
    book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Qxd4 Nf6 5. Bb5"] = "a6";
    book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4"] = "Bg7";

    book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Bg7 5. Nc3"] = "Nc6";
    book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Bg7 5. Nc3 Nc6 6. Nxc6"] = "bxc6";
    book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Bg7 5. Nc3 Nc6 6. Nb3"] = "d6";
    book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Bg7 5. Nc3 Nc6 6. Be3"] = "Nf6";
    book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Bg7 5. Nc3 Nc6 6. Be3 Nf6 7. f3"] = "0-0";
    book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Bg7 5. Nc3 Nc6 6. Be3 Nf6 7. f3 0-0 8. Nb3"] = "d5";
    book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Bg7 5. Nc3 Nc6 6. Be3 Nf6 7. f3 0-0 8. Nxc6"] = "bxc6";
    book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Bg7 5. Nc3 Nc6 6. Be3 Nf6 7. f3 0-0 8. Bc4"] = "d5";
    book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Bg7 5. Nc3 Nc6 6. Be3 Nf6 7. Bc4"] = "Qb6";


    book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Bg7 5. c4"] = "Nc6";
    book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Bg7 5. c4 Nc6 6. Nb3"] = "b6 | d6";
    book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Bg7 5. c4 Nc6 6. Nc2"] = "d6";
    book["1. e4 c5 2. Nf3 g6 3. d4 cxd4 4. Nxd4 Bg7 5. c4 Nc6 6. Be3"] = "Qb6";



    // B40 Sicilian defence -- WHITE
    book["1. e4 c5 2. Nf3 e6 3. d3 Nc6"] = "g3";
    book["1. e4 c5 2. Nf3 e6 3. d3 Nc6 4. g3 g6"] = "Bg2";
    book["1. e4 c5 2. Nf3 e6 3. d3 Nc6 4. g3 d5"] = "Qe2";
    book["1. e4 c5 2. Nf3 e6 3. d3 Nc6 4. g3 d5 5. Qe2 Nge7"] = "Bg2";
    book["1. e4 c5 2. Nf3 e6 3. d3 Nc6 4. g3 d5 5. Qe2 Be7"] = "e5";
    book["1. e4 c5 2. Nf3 e6 3. d3 Nc6 4. g3 d5 5. Qe2 Be7 6. e5 b6"] = "Bg2";
    book["1. e4 c5 2. Nf3 e6 3. d3 Nc6 4. g3 Nge7"] = "Bg2";
    book["1. e4 c5 2. Nf3 e6 3. d3 Nc6 4. g3 Nf6"] = "Qe2";
    book["1. e4 c5 2. Nf3 e6 3. d3 Nc6 4. g3 Nf6 5. Qe2 d6"] = "Bg2";
    book["1. e4 c5 2. Nf3 e6 3. d3 Nc6 4. g3 Nf6 5. Qe2 d5"] = "exd5";
    book["1. e4 c5 2. Nf3 e6 3. d3 Nc6 4. g3 Nf6 5. Qe2 d5 6. exd5 Qxd5"] = "Nc3";
    book["1. e4 c5 2. Nf3 e6 3. d3 Nc6 4. g3 Nf6 5. Qe2 d5 6. exd5 Nxd5"] = "Bg2";
    book["1. e4 c5 2. Nf3 e6 3. d3 Nc6 4. g3 d6"] = "Bg2";


    // B40 Sicilian defence -- BLACK
    book["1. e4 c5 2. Nf3 e6 3. Nc3"] = "Nc6";
    book["1. e4 c5 2. Nf3 e6 3. Nc3 Nc6 4. d4"] = "cxd4";
    book["1. e4 c5 2. Nf3 e6 3. Nc3 Nc6 4. d4 cxd4 5. Nxd4"] = "Nf6";
    book["1. e4 c5 2. Nf3 e6 3. Nc3 Nc6 4. Bb5"] = "Nge7";
    book["1. e4 c5 2. Nf3 e6 3. Nc3 Nc6 4. g3"] = "d5";
    book["1. e4 c5 2. Nf3 e6 3. Nc3 Nc6 4. Be2"] = "Nf6";

    book["1. e4 c5 2. Nf3 e6 3. d3"] = "Nf6 | d5";
    book["1. e4 c5 2. Nf3 e6 3. d3 Nf6 4. e5"] = "Nd5";
    book["1. e4 c5 2. Nf3 e6 3. d3 Nf6 4. Be2"] = "Nc6 | d5";
    book["1. e4 c5 2. Nf3 e6 3. d3 Nf6 4. c3"] = "Nc6 | d6 | Be7";
    book["1. e4 c5 2. Nf3 e6 3. d3 Nf6 4. g3"] = "d5";
    book["1. e4 c5 2. Nf3 e6 3. d3 Nf6 4. g3 d5 5. e5"] = "Nfd7";
    book["1. e4 c5 2. Nf3 e6 3. d3 Nf6 4. g3 d5 5. e5 Nfd7 6. Bg2"] = "Nc6";
    book["1. e4 c5 2. Nf3 e6 3. d3 Nf6 4. g3 d5 5. Qe2"] = "Be7 | b5";
    book["1. e4 c5 2. Nf3 e6 3. d3 Nf6 4. g3 d5 5. Qe2 Be7 6. Bg2"] = "b5";
    book["1. e4 c5 2. Nf3 e6 3. d3 Nf6 4. g3 d5 5. Qe2 Be7 6. c4"] = "Nc6";
    book["1. e4 c5 2. Nf3 e6 3. d3 Nf6 4. g3 d5 5. Qe2 b5 6. Bg2"] = "Nc6";
    book["1. e4 c5 2. Nf3 e6 3. d3 Nf6 4. g3 d5 5. Bg2"] = "dxe4";
    book["1. e4 c5 2. Nf3 e6 3. d3 Nf6 4. g3 d5 5. Bg2 dxe4 6. Ne5"] = "Be7";
    book["1. e4 c5 2. Nf3 e6 3. d3 Nf6 4. Nbd2"] = "d5";
    book["1. e4 c5 2. Nf3 e6 3. d3 Nf6 4. Qe2"] = "Be7 | d5";
    book["1. e4 c5 2. Nf3 e6 3. d3 d5 4. exd5"] = "exd5";
    book["1. e4 c5 2. Nf3 e6 3. d3 d5 4. g3"] = "Be7";
    book["1. e4 c5 2. Nf3 e6 3. d3 d5 4. Nbd2"] = "Be7 | Nc6 | Nf6";
    book["1. e4 c5 2. Nf3 e6 3. d3 d5 4. Qe2"] = "Nf6 | Be7";
    book["1. e4 c5 2. Nf3 e6 3. d3 d5 4. Nc3"] = "d4";
    book["1. e4 c5 2. Nf3 e6 3. d3 d5 4. Nc3 d4 5. Nb1"] = "Nc6";


    // i1. e4 c5 2. Nf3 e6 3. Nc3 Nc6
    book["1. e4 c5 2. Nf3 e6 3. Nc3 a6"] = "d4";
    book["1. e4 c5 2. Nf3 e6 3. Nc3 a6 4. d4 cxd4"] = "Nxd4";
    book["1. e4 c5 2. Nf3 e6 3. Nc3 Nc6"] = "d4 | Bb5";
    book["1. e4 c5 2. Nf3 e6 3. Nc3 Nc6 4. d4 cxd4"] = "Nxd4";
    book["1. e4 c5 2. Nf3 e6 3. Nc3 d6"] = "d4";
    book["1. e4 c5 2. Nf3 e6 3. Nc3 d6 4. d4 cxd4"] = "Nxd4";
    book["1. e4 c5 2. Nf3 e6 3. Nc3 Nf6"] = "d4 | e5";
    book["1. e4 c5 2. Nf3 e6 3. Nc3 Nf6 4. d4 cxd4"] = "Nxd4";
    book["1. e4 c5 2. Nf3 e6 3. Nc3 d5"] = "exd5 | Bb5+";
    book["1. e4 c5 2. Nf3 e6 3. Nc3 d5 4. exd5 exd5"] = "Bb5+";
    book["1. e4 c5 2. Nf3 e6 3. Nc3 Qc7"] = "d4";
    book["1. e4 c5 2. Nf3 e6 3. Nc3 Qc7 4. d4 cxd4"] = "Nb5";
    book["1. e4 c5 2. Nf3 e6 3. Nc3 Qc7 4. d4 cxd4 5. Nb5 Qa5+"] = "Bd2";
    book["1. e4 c5 2. Nf3 e6 3. Nc3 Qc7 4. d4 cxd4 5. Nb5 Qa5+ 6. Bd2 Qb6"] = "Bf4";
    book["1. e4 c5 2. Nf3 e6 3. Nc3 Qc7 4. d4 a6"] = "d5";
    book["1. e4 c5 2. Nf3 e6 3. Nc3 Qb6"] = "d4";
    book["1. e4 c5 2. Nf3 e6 3. Nc3 Qb6 4. d4 cxd4"] = "Qxd4";
    book["1. e4 c5 2. Nf3 e6 3. Nc3 Qb6 4. d4 cxd4 5. Qxd4 Qxd4"] = "Nxd4";
    book["1. e4 c5 2. Nf3 e6 3. Nc3 Qb6 4. d4 cxd4 5. Qxd4 Qxd4 6. Nxd4 a6"] = "Be2";


    // Sicilian Defense (B32) -- BLACK
    book["1. e4 c5 2. Nf3 Nc6 3. d4"] = "cxd4";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4"] = "Nf6 | g6 | e5";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb5"] = "d6";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nb3"] = "Nf6";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nf3"] = "Nf6 | Bc5";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nf3 Nf6 6. Nc3"] = "Bb4";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nf3 Nf6 6. Nc3 Bb4 7. Bd3"] = "Bxc3+";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nf3 Nf6 6. Nc3 Bb4 7. Bd3 Bxc3+ 8.bxc3"] = "0-0";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nf3 Nf6 6. Nc3 Bb4 7. Bd2"] = "Bxc3";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nf3 Nf6 6. Nc3 Bb4 7. Bd2 Bxc3 8. Bxc3"] = "Nxe4";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5 5. Nf3 Nf6 6. Nc3 Bb4 7. Bc4"] = "Qe7";


    // Sicilian Defense (B32) -- WHITE
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4"] = "Nxd4";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6"] = "Nc3";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6"] = "c4";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e5"] = "Nb5";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e6"] = "Nc3";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 d6"] = "c4";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 a6"] = "Nc3";


    // B32 Sicilian Defense: Accelerated Dragon -- BLACK
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6 5. c4"] = "Nf6 | d6 | Bg7";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6 5. Be3"] = "Nf6 | d6 | Bg7";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6 5. Be2"] = "Bg7 | Nf6";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6 5. Nxc6"] = "bxc6";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6 5. Nc3"] = "Bg7";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6 5. Nc3 Bg7 6. Be3"] = "Nf6";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6 5. Nc3 Bg7 6. Nb3"] = "d6 | Nf6";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6 5. Nc3 Bg7 6. Nxc6"] = "bxc6";


    // B33 Sicilian defence -- BLACK
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3"] = "d6 | e6 | e5";

    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6 6. Ndb5"] = "d6 | Bb4";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6 6. Ndb5 Bb4 7. Bf4"] = "Nxe4";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6 6. Ndb5 Bb4 7. Nd6+"] = "Ke7";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6 6. Ndb5 Bb4 7. a3"] = "Bxc3+";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6 6. Ndb5 Bb4 7. a3 Bxc3+ 8. Nxc3"] = "d5";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6 6. Ndb5 Bb4 7. a3 Bxc3+ 8. Nxc3 d5 9. exd5"] = "exd5";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6 6. Ndb5 Bb4 7. a3 Bxc3+ 8. Nxc3 d5 9. exd5 exd5 10. Bd3"] = "0-0";


    // B40 Sicilian Defense: Four Knights Variation -- BLACK
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6 6. Be2"] = "Bb4 | a6 | Be7";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6 6. Be2 Bb4 7. 0-0"] = "Bxc3 | 0-0 | d5";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6 6. Be2 Bb4 7. 0-0 Bxc3 8. bxc3"] = "Nxe4";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6 6. Be2 Bb4 7. f3"] = "d5 | 0-0 | Qa5 | Qb6";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6 6. Be2 Bb4 7. Nxc6"] = "bxc6";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6 6. Be2 Bb4 7. Nxc6 bxc6 8. e5"] = "Nd5 | Ne4";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6 6. Be2 Bb4 7. Nxc6 bxc6 8. 0-0"] = "Bxc3 | d5 | 0-0";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6 6. Be2 Bb4 7. Nxc6 bxc6 8. 0-0 Bxc3 9. bxc3"] = "Nxe4 | Qc7";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6 6. Be2 Bb4 7. Nxc6 bxc6 8. Qd3"] = "d5 | 0-0 | a5";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6 6. Be2 Bb4 7. Nxc6 bxc6 8. Bd3"] = "d5 | 0-0 | Qa5 | Bxc3+";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6 6. Be2 Bb4 7. Nxc6 bxc6 8. Bd3 Bxc3+ 9. bxc3"] = "0-0 | d5 | Qa5";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6 6. Be2 Bb4 7. Nxc6 bxc6 8. Bd3 Bxc3+ 9. bxc3 Qa5 10. Bd2"] = "0-0 | Qc7 | d5";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6 6. Be2 Bb4 7. Nxc6 bxc6 8. Bd3 Bxc3+ 9. bxc3 Qa5 10. 0-0"] = "Qxc3 | 0-0";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6 6. Be2 Bb4 7. Nxc6 bxc6 8. Bd3 Bxc3+ 9. bxc3 Qa5 10. Bb2"] = "Rb8";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6 6. Be2 Bb4 7. Nxc6 bxc6 8. Bd3 Bxc3+ 9. bxc3 Qa5 10. Bb2 Rb8 11. Qc1"] = "0-0";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6 6. Be2 Bb4 7. Nxc6 bxc6 8. Bd3 Bxc3+ 9. bxc3 Qa5 10. Bb2 Rb8 11. Rb1"] = "Rxb2";


    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6 6. Qd3"] = "Bb4";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6 6. Nxc6"] = "bxc6";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6 6. Nxc6 bxc6 7. e5"] = "Nd5";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6 6. Nxc6 bxc6 7. Bd3"] = "e5";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6 6. Nxc6 bxc6 7. Bd3 e5 8. Qf3"] = "Be7";
    book["1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6 6. Nxc6 bxc6 7. Bd3 e5 8. 0-0"] = "Be7";



    // B30 Sicilian, Nimzovich-Rossolimo attack (without ...d6) -- BLACK
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5"] = "g6";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 g6 4. 0-0"] = "Bg7";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 g6 4. Bxc6"] = "bxc6";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5"] = "e6";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 e6 4. 0-0"] = "Nge7";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 e6 4. Bxc6"] = "bxc6";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5"] = "d6";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 d6 4. 0-0"] = "Bd7";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 d6 4. Bxc6+"] = "bxc6";

    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 d6 4. 0-0 Bd7 5. d3"] = "g6 | e6";


    // B30 Sicilian, Nimzovich-Rossolimo attack (without ...d6) -- BLACK
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 d6 4. 0-0 Bd7 5. d3 g6 6. Bxc6"] = "Bxc6";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 d6 4. 0-0 Bd7 5. d3 g6 6. Bxc6 Bxc6 7. c4"] = "Bg7";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 d6 4. 0-0 Bd7 5. d3 g6 6. Bxc6 Bxc6 7. Bd2"] = "Bg7";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 d6 4. 0-0 Bd7 5. d3 g6 6. Bxc6 Bxc6 7. Re1"] = "Bg7";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 d6 4. 0-0 Bd7 5. d3 g6 6. Bxc6 Bxc6 7. Nc3"] = "Bg7";


    // B30 Sicilian, Nimzovich-Rossolimo attack (without ...d6) -- WHITE
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 Nd4"] = "Nxd4";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 Nd4 4. Nxd4 cxd4"] = "0-0";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 Nd4 4. Nxd4 cxd4 5. 0-0 g6"] = "c3";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 Nd4 4. Nxd4 cxd4 5. 0-0 e6"] = "c3";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 Nd4 4. Nxd4 cxd4 5. 0-0 e5"] = "d3";

    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 Nd4 4. Nxd4 cxd4 5. 0-0 a6"] = "Bc4";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 Nd4 4. Nxd4 cxd4 5. 0-0 a6 6. Bc4 Qc7"] = "d3";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 Nd4 4. Nxd4 cxd4 5. 0-0 a6 6. Bc4 Nf6"] = "d3";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 Nd4 4. Nxd4 cxd4 5. 0-0 a6 6. Bc4 e6"] = "d3";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 Nd4 4. Nxd4 cxd4 5. 0-0 a6 6. Bc4 e6 7. d3 Bc5"] = "Qg4";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 Nd4 4. Nxd4 cxd4 5. 0-0 a6 6. Bc4 e6 7. d3 b5"] = "Bb3";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 Nd4 4. Nxd4 cxd4 5. 0-0 a6 6. Bc4 e6 7. d3 b5 8. Bb3 Bb7"] = "Nd2";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 Nd4 4. Nxd4 cxd4 5. 0-0 a6 6. Bc4 e6 7. d3 b5 8. Bb3 Nf6"] = "e5";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 Nd4 4. Nxd4 cxd4 5. 0-0 a6 6. Bc4 e6 7. d3 b5 8. Bb3 Nf6 9. e5 Ng8"] = "c3 | Qf3";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 Nd4 4. Nxd4 cxd4 5. 0-0 a6 6. Bc4 e6 7. d3 b5 8. Bb3 Nf6 9. e5 Nd5"] = "Bxd5";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 Nd4 4. Nxd4 cxd4 5. 0-0 a6 6. Bc4 e6 7. d3 b5 8. Bb3 Nf6 9. e5 Nd5 10. Bxd5 exd5"] = "Re1";



    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 Nd4 4. Nxd4 cxd4 5. 0-0 a6 6. Bc4 e6 7. d3 b5 8. Bb3 Nf6 9. e5 Nd5 10. Bxd5 exd5 11. Re1 a5"] = "Qg4";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 Nd4 4. Nxd4 cxd4 5. 0-0 a6 6. Bc4 e6 7. d3 b5 8. Bb3 Nf6 9. e5 Nd5 10. Bxd5 exd5 11. Re1 Qb6"] = "Qg4";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 Nd4 4. Nxd4 cxd4 5. 0-0 a6 6. Bc4 e6 7. d3 b5 8. Bb3 Nf6 9. e5 Nd5 10. Bxd5 exd5 11. Re1 Bb4"] = "Bd2";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 Nd4 4. Nxd4 cxd4 5. 0-0 a6 6. Bc4 e6 7. d3 b5 8. Bb3 Nf6 9. e5 Nd5 10. Bxd5 exd5 11. Re1 Bb4 12. Bd2 Bf8"] = "Qg4";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 Nd4 4. Nxd4 cxd4 5. 0-0 a6 6. Bc4 e6 7. d3 b5 8. Bb3 Nf6 9. e5 Nd5 10. Bxd5 exd5 11. Re1 Bb4 12. Bd2 Bc5"] = "Qg4";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 Nd4 4. Nxd4 cxd4 5. 0-0 a6 6. Bc4 e6 7. d3 b5 8. Bb3 Nf6 9. e5 Nd5 10. Bxd5 exd5 11. Re1 Bb4 12. Bd2 Bc5 13. Qg4 g6"] = "Bh6";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 Nd4 4. Nxd4 cxd4 5. 0-0 a6 6. Bc4 e6 7. d3 b5 8. Bb3 Nf6 9. e5 Nd5 10. Bxd5 exd5 11. Re1 Bb4 12. Bd2 Bc5 13. Qg4 Kf8"] = "Bg5";



    // B30 Sicilian, Nimzovich-Rossolimo attack (without ...d6) -- WHITE
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 e6"] = "0-0";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 e6 4. 0-0 Nge7"] = "Re1";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 e6 4. 0-0 a6"] = "Bxc6";
    book["1. e4 c5 2. Nf3 Nc6 3. Bb5 e6 4. 0-0 d6"] = "c3";

    book["1. e4 c5 2. Nf3 d6 3. c3"] = "Nf6 | Nc6 | g6";
    book["1. e4 c5 2. Nf3 d6 3. c3 Nf6"] = "Be2";
    book["1. e4 c5 2. Nf3 d6 3. c3 Nf6 4. Be2"] = "g6 | Nc6";

    book["1. e4 c5 2. Bc4"] = "e6 | Nc6 | d6";
    book["1. e4 c5 2. Bc4 Nc6"] = "Nf3"; 
    book["1. e4 c5 2. Bc4 Nc6 3. Nf3"] = "e6 | d6 | g6 | Nf6";

    book["1. e4 c5 2. Bc4 Nc6 3. d3"] = "e6";
    book["1. e4 c5 2. Bc4 Nc6 3. d3 e6 4. Nf3"] = "d5";
    book["1. e4 c5 2. Bc4 Nc6 3. d3 e6 4. Nc3"] = "Nf6 | a6";

    book["1. e4 c5 2. Bc4 Nc6 3. d3 e6 4. f4"] = "d5";
    book["1. e4 c5 2. Bc4 Nc6 3. d3 e6 4. f4 d5 5. Bb3"] = "dxe4";
    book["1. e4 c5 2. Bc4 Nc6 3. d3 e6 4. f4 d5 5. Bb5"] = "Qa5+";

    book["1. e4 c5 2. Bc4 e6 3. Ne2"] = "Nf6";




    book["1. e4 c5 2. Nf3 d6 3. c3 Nf6 4. d3"] = "Nc6 | g6";
    book["1. e4 c5 2. Nf3 d6 3. c3 Nf6 4. d3 Nc6 5. b3"] = "g6";


    // B50 Sicilian Defence
    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4"] = "Nxd4";
    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nc6"] = "Nc3 | c4 | Bb5 | Be3 | Bc4 | f4 | Nxc6";
    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 a6"] = "Nc3 | c4 | Bc4";
    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 e6"] = "Nc3 | c4 | Bd3 | Be2 | g3 | Bb5+";
    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 e5"] = "Bb5+ | Nb3 | Nf3";
    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 g6"] = "Nc3 | c4";
    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Qc7"] = "c4 | Nc3";
    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Qc7 5. Nc3 a6"] = "Be2";
    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6"] = "Nc3 | f3 | Bd3 | Bb5+ | Bc4";
    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 Nc6"] = "Bg5 | Bc4 | Be2";
    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 g6"] = "Be3 | Be2 | g3 | Bc4 | f4";
    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 e6"] = "g4 | Be2 | Be3 | g3 | f4";
    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6"] = "Be3 | Bg5";
    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Be3 Nc6"] = "f3";
    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Be3 e6"] = "f3 | Be2";
    book["1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Be3 e5"] = "Nb3 | Nf3";



    // Sicilian, Smith-Morra gambit (B21)
    book["1. e4 c5 2. d4 cxd4 3. Nf3"] = "Nc6 | d6 | e6";

    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4"] = "Nf6 | g6 | e5 | e6";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 Nf6 5. Nc3"] = "e5 | d6 | e6 | g6 | Qb6";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 Nf6 5. Nxc6"] = "bxc6";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 Nf6 5. f3"] = "Qb3 | d5";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 g6 5. c4"] = "Bg7 | Nf6 | d6";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 g6 5. Nc3"] = "Bg7";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 g6 5. Be2"] = "Bg7";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 g6 5. Be3"] = "Bg7 | Nf6";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 g6 5. Nxc6"] = "bxc6";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 g6 5. Nb3"] = "Bg7 | d6";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 g6 5. Bc4"] = "Bg7 | Qa5+";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e6 5. Nc3"] = "Qc7 | a6 | Nf6";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e6 5. Nb5"] = "d6";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e6 5. Nxc6"] = "bxc6";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e6 5. Be3"] = "Nf6";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e6 5. c4"] = "Nf6";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e6 5. g3"] = "d5 | Bc5 | Nf6";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e6 5. g3 d5 6. Bg2"] = "dxe4";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e6 5. g3 Bc5 6. Nb3"] = "Bb6";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e6 5. g3 Bc5 6. Be3"] = "Qb6";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e6 5. g3 Nf6 6. Bg2"] = "d5 | Bc5";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e6 5. Be2"] = "Nf6";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e5 5. Nb3"] = "Nf6 | Bb4+";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e5 5. Nb3 Nf6 6. Bg5"] = "Be7 | Bb4+";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e5 5. Nb3 Nf6 6. Nc3"] = "Bb4";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e5 5. Nb3 Bb4+ 6. Bd2"] = "a5";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e5 5. Nb3 Bb4+ 6. c3"] = "Be7";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e5 5. Nb3 Bb4+ 6. Nc3"] = "Nf6";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e5 5. Nf3"] = "Nf6 | Bc5";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e5 5. Nxc6"] = "bxc6";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e5 5. Nf5"] = "d5 | Nf6";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e5 5. Nb5"] = "d6 | a6";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e5 5. Nb5 d6 6. N1c3"] = "a6 | Nf6";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e5 5. Nb5 d6 6. c4"] = "g6 | a6 | Be7 | Nf6";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e5 5. Nb5 d6 6. a4"] = "Be6 | Be7";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e5 5. Nb5 d6 6. Be3"] = "Nf6 | a6";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e5 5. Nb5 d6 6. Bc4"] = "Be7 | Be6";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e5 5. Nb5 d6 6. g3"] = "Be7 | Nf6";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e5 5. Nb5 d6 6. Be2"] = "Be7 | Be6 | Nf6";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e5 5. Nb5 d6 6. Bd3"] = "a6 | Be7";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e5 5. Nb5 a6 6. Nd6+"] = "Bxd6";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e5 5. Nb5 a6 6. Nd6 Bxd6 7. Qxd6"] = "Qe7";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e5 5. Nb5 a6 6. Nd6 Bxd6 7. Qxd6 Qe7 8. Qd1"] = "Nf6 |d6";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e5 5. Nb5 a6 6. Nd6 Bxd6 7. Qxd6 Qe7 8. Qd2"] = "Nf6";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e5 5. Nb5 a6 6. Nd6 Bxd6 7. Qxd6 Qe7 8. Qd3"] = "Nf6";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e5 5. Nb5 a6 6. Nd6 Bxd6 7. Qxd6 Qe7 8. Qc7"] = "d5";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e5 5. Nb5 a6 6. Nd6 Bxd6 7. Qxd6 Qe7 8. Qc7 d5 9. Qxe7+"] = "Ngxe7";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e5 5. Nb5 a6 6. Nd6 Bxd6 7. Qxd6 Qe7 8. Qxe7"] = "Ngxe7";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e5 5. Nb5 a6 6. N5c3"] = "Bc5 | Nf6";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e5 5. Nb5 a6 6. N5a3"] = "Nf6";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 Nc6 4. Nxd4 e5 5. Nb5 a6 6. N5a3 Nf6 7. Nc3"] = "b5";




    book["1. e4 c5 2. d4 cxd4 3. Nf3 d6 4. Nxd4"] = "Nf6 | Nc6";
    book["1. e4 c5 2. d4 cxd4 3. Nf3 e6 4. Nxd4"] = "a6 | Nf6 | Nc6";

    book["1. e4 c5 2. d4 cxd4 3. c3"] = "dxc3 | Nf6 | d3 | d5";
    book["1. e4 c5 2. d4 cxd4 3. c3 dxc3 4. Nxc3"] = "Nc6 | e6 | d6";


    // Sicilian, Smith-Morra gambit (B21)
    book["1. e4 c5 2. d4 cxd4 3. c3 Nf6 4. e5"] = "Nd5";
    book["1. e4 c5 2. d4 cxd4 3. c3 d3 4. Bxd3"] = "Nc6 | d6 | g6";
    book["1. e4 c5 2. d4 cxd4 3. c3 d5 4. exd5"] = "Qxd5 | Nf6";

    book["1. e4 c5 2. d4 cxd4 3. c3 Nf6 4. e5 Nd5 5. Nf3"] = "Nc6 | e6 | d6";
    book["1. e4 c5 2. d4 cxd4 3. c3 Nf6 4. e5 Nd5 5. cxd4"] = "d6 | e6 | Nc6";
    book["1. e4 c5 2. d4 cxd4 3. c3 Nf6 4. e5 Nd5 5. Qxd4"] = "e6 | Nb6";


    // Sicilian closed (B23)
    book["1. e4 c5 2. Nc3 Nc6"] = "g3 | f4 | Nf3 | Bb5";


    // B23 Sicilian Defense: Grand Prix Attack -- WHITE
    book["1. e4 c5 2. Nc3 Nc6 3. f4 e6"] = "Nf3 | Bb5 | Bc4";
    book["1. e4 c5 2. Nc3 Nc6 3. f4 d6"] = "Nf3 | Bb5 | Bc4";
    book["1. e4 c5 2. Nc3 Nc6 3. f4 a6"] = "Nf3";
    book["1. e4 c5 2. Nc3 Nc6 3. f4 e5"] = "fxe5";
    book["1. e4 c5 2. Nc3 Nc6 3. f4 e5 4. fxe5 Nxe5"] = "d4";
    book["1. e4 c5 2. Nc3 Nc6 3. f4 e5 4. fxe5 d6"] = "Bb5 | Nf3";
    book["1. e4 c5 2. Nc3 Nc6 3. f4 e5 4. fxe5 Nge7"] = "Nf3 | Qh5";
    book["1. e4 c5 2. Nc3 Nc6 3. f4 Qc7"] = "Nf3 | Nge2";
    book["1. e4 c5 2. Nc3 Nc6 3. f4 g6"] = "Nf3 | Bb5";
    book["1. e4 c5 2. Nc3 Nc6 3. f4 g6 4. Bb5 Nd4"] = "Nf3 | d3 | a4";
    book["1. e4 c5 2. Nc3 Nc6 3. f4 g6 4. Bb5 Bg7"] = "Nf3 | Bxc6";
    book["1. e4 c5 2. Nc3 Nc6 3. f4 g6 4. Bb5 Bg7 5. Bxc6 dxc6"] = "Nf3";
    book["1. e4 c5 2. Nc3 Nc6 3. f4 g6 4. Bb5 Bg7 5. Bxc6 bxc6"] = "d3 | Nf3";
    book["1. e4 c5 2. Nc3 Nc6 3. f4 g6 4. Nf3 d6"] = "Bc4 | Bb5";
    book["1. e4 c5 2. Nc3 Nc6 3. f4 g6 4. Nf3 a6"] = "d4";

    book["1. e4 c5 2. Nc3 Nc6 3. f4 g6 4. Nf3 Bg7"] = "Bb5 | d3 | a4";

    book["1. e4 c5 2. Nc3 Nc6 3. f4 g6 4. Nf3 Bg7 5. Bb5 d6"] = "Bxc6+";
    book["1. e4 c5 2. Nc3 Nc6 3. f4 g6 4. Nf3 Bg7 5. Bb5 d6 6. Bxc6+ bxc6"] = "d3";
    book["1. e4 c5 2. Nc3 Nc6 3. f4 g6 4. Nf3 Bg7 5. Bb5 e6"] = "Bxc6";
    book["1. e4 c5 2. Nc3 Nc6 3. f4 g6 4. Nf3 Bg7 5. Bb5 e6 6. Bxc6 dxc6"] = "Qe2";
    book["1. e4 c5 2. Nc3 Nc6 3. f4 g6 4. Nf3 Bg7 5. Bb5 e6 6. Bxc6 bxc6"] = "d3";
    book["1. e4 c5 2. Nc3 Nc6 3. f4 g6 4. Nf3 Bg7 5. Bb5 a6"] = "Bxc6";
    book["1. e4 c5 2. Nc3 Nc6 3. f4 g6 4. Nf3 Bg7 5. Bb5 a6 6. Bxc6 dxc6"] = "0-0";
    book["1. e4 c5 2. Nc3 Nc6 3. f4 g6 4. Nf3 Bg7 5. Bb5 a6 6. Bxc6 bxc6"] = "d3";
    book["1. e4 c5 2. Nc3 Nc6 3. f4 g6 4. Nf3 Bg7 5. Bb5 Nd4"] = "0-0";
    book["1. e4 c5 2. Nc3 Nc6 3. f4 g6 4. Nf3 Bg7 5. Bb5 Nd4 6. 0-0 a6"] = "Be2";
    book["1. e4 c5 2. Nc3 Nc6 3. f4 g6 4. Nf3 Bg7 5. Bb5 Nd4 6. 0-0 a6 7. Be2 b5"] = "d3";


    book["1. e4 c5 2. Nc3 Nc6 3. Nf3"] = "g6 | d6 | e6 | e5 | Nf6";
    book["1. e4 c5 2. Nc3 Nc6 3. Nge2"] = "g6 | d6 | e6 | Nf6";

    book["1. e4 c5 2. Nc3 d6"] = "g3 | f4 | Nf3";
    book["1. e4 c5 2. Nc3 d6 3. g3"] = "Nc6 | g6";
    book["1. e4 c5 2. Nc3 d6 3. f4"] = "Nc6 | g6";
    book["1. e4 c5 2. Nc3 d6 3. Nf3"] = "Nf6 | Nc6";



    book["1. e4 c5 2. Nc3 d6 3. Nf3 Nf6"] = "d4 | Bb5+";



    book["1. e4 c5 2. Nc3 d6 3. Nf3 Nc6 4. Bc4"] = "Nf6";
    book["1. e4 c5 2. Nc3 d6 3. Nf3 Nc6 4. Bc4 Nf6 5. d3"] = "g6";
    book["1. e4 c5 2. Nc3 d6 3. Nf3 Nc6 4. Bc4 Nf6 5. d4"] = "cxd4";
    book["1. e4 c5 2. Nc3 d6 3. Nf3 Nc6 4. Bc4 Nf6 5. 0-0"] = "g6";

    book["1. e4 c5 2. Nc3 e6"] = "g3 | Nf3";
    book["1. e4 c5 2. Nc3 e6 3. g3"] = "d5 | Nc6";
    book["1. e4 c5 2. Nc3 e6 3. Nf3"] = "a6 | Nc6 | d6";


    book["1. e4 c5 2. Nc3 e6 3. Nf3 Nc6 4. Bb5"] = "Nge7 | Nd4 | Qc7";
    book["1. e4 c5 2. Nc3 e6 3. Nf3 Nc6 4. g3"] = "d5 | Nf6";
    book["1. e4 c5 2. Nc3 e6 3. Nf3 Nc6 4. Be2"] = "Nd4 | d5 | Nf6";
    book["1. e4 c5 2. Nc3 e6 3. Nf3 Nc6 4. Bc4"] = "Be7 | Nf6 | a6";
    book["1. e4 c5 2. Nc3 e6 3. Nf3 Nc6 4. d3"] = "d5 | Nf6";
    book["1. e4 c5 2. Nc3 e6 3. Nf3 Nc6 4. b3"] = "a6 | Nf6";
    book["1. e4 c5 2. Nc3 e6 3. Nf3 Nc6 4. d4"] = "cxd4";
    book["1. e4 c5 2. Nc3 e6 3. Nf3 Nc6 4. d4 cxd4 5. Nxd4"] = "Qc7 | a6 | d6 | Nf6";
    book["1. e4 c5 2. Nc3 e6 3. Nf3 Nc6 4. d4 cxd4 5. Nxd4 Nf6 6. Bf4"] = "Bb4";
    book["1. e4 c5 2. Nc3 e6 3. Nf3 Nc6 4. d4 cxd4 5. Nxd4 Nf6 6. Ndb5"] = "d6";
    book["1. e4 c5 2. Nc3 e6 3. Nf3 Nc6 4. d4 cxd4 5. Nxd4 Nf6 6. Nxc6"] = "bxc6";
    book["1. e4 c5 2. Nc3 e6 3. Nf3 Nc6 4. d4 cxd4 5. Nxd4 Nf6 6. Nxc6 bxc6 7. e5"] = "Nd5";
    book["1. e4 c5 2. Nc3 e6 3. Nf3 Nc6 4. d4 cxd4 5. Nxd4 Nf6 6. Nxc6 bxc6 7. Bd3"] = "d5";
    book["1. e4 c5 2. Nc3 e6 3. Nf3 Nc6 4. d4 cxd4 5. Nxd4 Nf6 6. Nxc6 bxc6 7. Be3"] = "d5";
    book["1. e4 c5 2. Nc3 e6 3. Nf3 Nc6 4. d4 cxd4 5. Nxd4 Nf6 6. Nxc6 bxc6 7. Bg5"] = "h6";
    book["1. e4 c5 2. Nc3 e6 3. Nf3 Nc6 4. d4 cxd4 5. Nxd4 Nf6 6. Nxc6 bxc6 7. Bg5 h6 8. Bh4"] = "Rb8";
    book["1. e4 c5 2. Nc3 e6 3. Nf3 Nc6 4. d4 cxd4 5. Nxd4 Nf6 6. Nxc6 bxc6 7. Bg5 h6 8. Bf4"] = "Qb6";
    book["1. e4 c5 2. Nc3 e6 3. Nf3 Nc6 4. d4 cxd4 5. Nxd4 Nf6 6. Nxc6 bxc6 7. Bg5 h6 8. Be3"] = "d5";
    book["1. e4 c5 2. Nc3 e6 3. Nf3 Nc6 4. d4 cxd4 5. Nxd4 Nf6 6. Nxc6 bxc6 7. Bg5 h6 8. Bd2"] = "d5";



    // B23 Sicilian Defense: Closed -- WHITE
    book["1. e4 c5 2. Nc3 e6 3. g3 d5"] = "exd5";
    book["1. e4 c5 2. Nc3 e6 3. g3 d5 4. exd5 exd5"] = "d4";
    book["1. e4 c5 2. Nc3 e6 3. g3 Nc6"] = "Bg2";
    book["1. e4 c5 2. Nc3 e6 3. g3 a6"] = "Bg2";
    book["1. e4 c5 2. Nc3 e6 3. g3 d6"] = "Bg2";
    book["1. e4 c5 2. Nc3 e6 3. g3 b6"] = "Bg2";
    book["1. e4 c5 2. Nc3 e6 3. g3 b6 4. Bg2 Bb7"] = "Nf3 | Nge2";
    book["1. e4 c5 2. Nc3 e6 3. g3 g6"] = "d4";
    book["1. e4 c5 2. Nc3 e6 3. g3 g6 4. d4 cxd4"] = "Qxd4";
    book["1. e4 c5 2. Nc3 e6 3. g3 g6 4. d4 Nf6"] = "Nf3";
    book["1. e4 c5 2. Nc3 e6 3. g3 g6 4. d4 Nf6 5. Nf3 d5"] = "exd5";
    book["1. e4 c5 2. Nc3 e6 3. g3 g6 4. d4 Bg7"] = "dxc5";

    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 Nf6"] = "Bb5";
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 a6"] = "Bxc6";
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 a6 5. Bxc6 dxc6"] = "d3";
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 a6 5. Bxc6 bxc6"] = "e5";
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 a6 5. Bxc6 bxc6 6. e5 Nd5"] = "Ne4";
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 g6"] = "e5";
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 g6 5. e5 Nh5"] = "0-0";
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 e5"] = "Bxc6";
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 e5 5. Bxc6 bxc6"] = "Nxe5";
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 e5 5. Bxc6 dxc6"] = "Nxe5";
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 e5 5. Bxc6 dxc6 6. Nxe5 Nxe4"] = "Nxe4";
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 e5 5. Bxc6 dxc6 6. Nxe5 Nxe4 7. Nxe4 Qd5"] = "0-0";
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 e5 5. Bxc6 dxc6 6. Nxe5 Nxe4 7. Nxe4 Qd4"] = "Qe2";
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Nd4"] = "e5";
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Nd4 5. e5 Nxb5"] = "Nxb5";
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Nd4 5. e5 Nxb5 6. Nxb5 Nd5"] = "0-0";
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 e6"] = "Bxc6";
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 e6 5. Bxc6 bxc6"] = "e5";
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 e6 5. Bxc6 bxc6 6. e5 Nd5"] = "Ne4";
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 e6 5. Bxc6 dxc6"] = "0-0";
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 d5"] = "exd5";
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 d5 5. exd5 Nxd5"] = "0-0";
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Qb6"] = "e5";
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Qb6 5. e5 Nd4"] = "Be2";
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Qb6 5. e5 Ng5"] = "Bxc6";
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 Nf6 4. Bb5 Qc7"] = "0-0";



    // B23 Sicilian, closed, 2...Nc6 -- WHITE
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 g6"] = "Bb5";
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 g6 4. Bb5 Nd4"] = "Ba4";
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 g6 4. Bb5 Bg7"] = "0-0";
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 g6 4. Bb5 Bg7 5. 0-0 d6"] = "d4";
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 g6 4. Bb5 Bg7 5. 0-0 d6 6. d4 cxd4"] = "Nxd4";
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 g6 4. Bb5 Bg7 5. 0-0 e5"] = "d3";
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 g6 4. Bb5 Bg7 5. 0-0 e5 6. d3 Nge7"] = "a3";
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 g6 4. Bb5 Bg7 5. 0-0 e5 6. d3 Nge7 7. a3 0-0"] = "Bc4";
    book["1. e4 c5 2. Nc3 Nc6 3. Nf3 g6 4. Bb5 Bg7 5. 0-0 e5 6. d3 Nge7 7. a3 d6"] = "Bc4";


    // B23 Sicilian, closed -- BLACK
    book["1. e4 c5 2. Nc3 e6 3. f4"] = "d5 | Nc6";
    book["1. e4 c5 2. Nc3 e6 3. f4 d5 4. Nf3"] = "dxe4";
    book["1. e4 c5 2. Nc3 e6 3. f4 d5 4. Nf3 5. dxe4 Nxe4"] = "Nc6";
    book["1. e4 c5 2. Nc3 e6 3. f4 d5 4. Bb5+"] = "Bd7";
    book["1. e4 c5 2. Nc3 e6 3. f4 d5 4. exd5"] = "exd5";
    book["1. e4 c5 2. Nc3 e6 3. f4 d5 4. d3"] = "Nc6";
    book["1. e4 c5 2. Nc3 e6 3. f4 d5 4. e5"] = "Nh6";
    book["1. e4 c5 2. Nc3 e6 3. f4 d5 4. Qe2"] = "Nc6";
    book["1. e4 c5 2. Nc3 e6 3. f4 d5 4. g3"] = "Nc6";


    // Sicilian closed (B24) 
    book["1. e4 c5 2. Nc3 Nc6 3. g3"] = "g6 | d6 | e6 | Nf6";
    book["1. e4 c5 2. Nc3 Nc6 3. g3 d6"] = "Bg2";
    book["1. e4 c5 2. Nc3 Nc6 3. g3 d6 4. Bg2"] = "g6";
    book["1. e4 c5 2. Nc3 Nc6 3. g3 d6 4. Bg2 g6"] = "d3 | Nge2";
    book["1. e4 c5 2. Nc3 Nc6 3. g3 g6"] = "Bg2 | d3";
    book["1. e4 c5 2. Nc3 Nc6 3. g3 e6"] = "Bg2";
    book["1. e4 c5 2. Nc3 Nc6 3. g3 e6 4. Bg2"] = "Nf6 | g6";
    book["1. e4 c5 2. Nc3 Nc6 3. g3 Nf6"] = "Bg2";
    book["1. e4 c5 2. Nc3 Nc6 3. g3 Nf6 4. Bg2"] = "e6 | d6 | g6";


    // Robatsch defense (B06)
    book["1. e4 g6"] = "d4 | Nc3 | Nf3";
    book["1. e4 g6 2. d4"] = "Bg7 | d6 | c6";
    book["1. e4 g6 2. Nc3"] = "Bg7 | c6";

    book["1. e4 g6 2. d4 d6"] = "c4 | Nc3";
    book["1. e4 g6 2. d4 d6 3. c4 Bg7"] = "Nc3";
    book["1. e4 g6 2. d4 d6 3. c4 e5"] = "Nc3";
    book["1. e4 g6 2. d4 d6 3. c4 Nf6"] = "Nc3";
    book["1. e4 g6 2. d4 d6 3. c4 Nf6 4. Nc3 Bg7"] = "Nf3";
    book["1. e4 g6 2. d4 d6 3. c4 Nd7"] = "Nc3";
    book["1. e4 g6 2. d4 d6 3. c4 c5"] = "d5";
    book["1. e4 g6 2. d4 d6 3. c4 c6"] = "Nc3";


    // Owen defense (B00)
    book["1. e4 b6"] = "d4 | Nf3 | Nc3";
    book["1. e4 b6 2. d4"] = "Bb7 | e6";
    book["1. e4 b6 2. d4 Bb7"] = "Bd3 | Nc3";
    book["1. e4 b6 2. d4 e6"] = "Nf3 | Nc3 | Bd3";


    // B00 Owen defence -- 	WHITE
    book["1. e4 b6 2. d4 Bb7 3. Nc3 e6"] = "Bd3";
    book["1. e4 b6 2. d4 Bb7 3. Nc3 g6"] = "h4";
    book["1. e4 b6 2. d4 Bb7 3. Nc3 g6 4. h4 Bg7"] = "h5";
    book["1. e4 b6 2. d4 Bb7 3. Nc3 g6 4. h4 Bg7 5. h5 gxh5"] = "Qxh5";
    book["1. e4 b6 2. d4 Bb7 3. Nc3 g6 4. h4 Bg7 5. h5 e5"] = "dxe5";
    book["1. e4 b6 2. d4 Bb7 3. Nc3 g6 4. h4 Bg7 5. h5 e5 6. dxe5 Bxe5"] = "Nd5";
    book["1. e4 b6 2. d4 Bb7 3. Nc3 g6 4. h4 Bg7 5. h5 e5 6. dxe5 Nc6"] = "f4";
    book["1. e4 b6 2. d4 Bb7 3. Nc3 g6 4. h4 h5"] = "Nf3";


    // C33 King's gambit -- BLACK
    book["1. e4 e5 2. f4"] = "exf4 | Bc5 | d5";
    book["1. e4 e5 2. f4 exf4 3. Bc4"] = "Qh4+";
    book["1. e4 e5 2. f4 exf4 3. Bc4 Qh4+ 4. Ke2"] = "f5";
    book["1. e4 e5 2. f4 exf4 3. Bc4 Qh4+ 4. Kf1"] = "Nf6";
    book["1. e4 e5 2. f4 exf4 3. Nc3"] = "Qh4+";
    book["1. e4 e5 2. f4 exf4 3. Nc3 Qh4+ 4. Ke2"] = "d6";
    book["1. e4 e5 2. f4 exf4 3. Nf3"] = "g5";
    book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. h4"] = "g4";
    book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. h3"] = "h6";
    book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. d4"] = "g4";
    book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. Nc3"] = "Bg7";
    book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. Bc4"] = "Bg7";
    book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. Bc4 Bg7 5. d4"] = "d6";
    book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. Bc4 Bg7 5. h4"] = "h6";
    book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. Bc4 Bg7 5. 0-0"] = "h6";
    book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. Bc4 Bg7 5. 0-0 h6 6. d4"] = "Nc6";


    // C31 King's Gambit Declined: Falkbeer Countergambit Accepted -- BLACK
    book["1. e4 e5 2. f4 d5 3. exd5"] = "exf4 | c6";
    book["1. e4 e5 2. f4 d5 3. exd5 exf4 4. Bb5+"] = "c6";
    book["1. e4 e5 2. f4 d5 3. exd5 exf4 4. Bb5+ c6 5. dxc6"] = "Nxc6";
    book["1. e4 e5 2. f4 d5 3. exd5 exf4 4. Qe2"] = "Be7";
    book["1. e4 e5 2. f4 d5 3. exd5 exf4 4. Nf3"] = "Nf6 | c6 | Bd6";
    book["1. e4 e5 2. f4 d5 3. exd5 exf4 4. Nf3 Nf6 5. c4"] = "c6";
    book["1. e4 e5 2. f4 d5 3. exd5 exf4 4. Nf3 Nf6 5. Bc4"] = "Nxd5 | c6 | Qe7";
    book["1. e4 e5 2. f4 d5 3. exd5 exf4 4. Nf3 Nf6 5. Bb5+"] = "c6 | Nbd7 | Bd7";
    book["1. e4 e5 2. f4 d5 3. exd5 exf4 4. Nf3 Nf6 5. Bb5+ Nbd7 6. 0-0"] = "Be7";
    book["1. e4 e5 2. f4 d5 3. exd5 exf4 4. Nf3 Nf6 5. Bb5+ Nbd7 6. Nc3"] = "Bd6";
    book["1. e4 e5 2. f4 d5 3. exd5 exf4 4. Nf3 Nf6 5. Bb5+ Nbd7 6. d4"] = "Nxd5";
    book["1. e4 e5 2. f4 d5 3. exd5 exf4 4. Nf3 Nf6 5. Bb5+ Nbd7 6. Qe2+"] = "Be7";
    book["1. e4 e5 2. f4 d5 3. exd5 exf4 4. Nf3 Nf6 5. Bb5+ Nbd7 6. Qe2+ Be7 7. d4"] = "0-0";
    book["1. e4 e5 2. f4 d5 3. exd5 exf4 4. Nf3 Nf6 5. Bb5+ Nbd7 6. Qe2+ Be7 7. d4 0-0 8. Nc3"] = "Nb6";
    book["1. e4 e5 2. f4 d5 3. exd5 exf4 4. Nf3 Nf6 5. Bb5+ Nbd7 6. Qe2+ Be7 7. Nc3"] = "0-0";
    book["1. e4 e5 2. f4 d5 3. exd5 exf4 4. Nf3 Nf6 5. Bb5+ Nbd7 6. Qe2+ Be7 7. Nc3 0-0 8. d4"] = "Nb6";
    book["1. e4 e5 2. f4 d5 3. exd5 exf4 4. Nf3 Nf6 5. Bb5+ Nbd7 6. Qe2+ Be7 7. Nc3 0-0 8. 0-0"] = "Nb6";
    book["1. e4 e5 2. f4 d5 3. exd5 exf4 4. Nf3 Nf6 5. Bb5+ Nbd7 6. Qe2+ Be7 7. Nc3 0-0 8. 0-0 Nb6 9. d4"] = "Nbxd5";
    book["1. e4 e5 2. f4 d5 3. exd5 exf4 4. Nf3 Nf6 5. Bb5+ Nbd7 6. Qe2+ Be7 7. Nc3 0-0 8. 0-0 Nb6 9. d4 Nbxd5 10. Nxd5"] = "Nxd5";
    book["1. e4 e5 2. f4 d5 3. exd5 exf4 4. Nf3 Nf6 5. Bb5+ Nbd7 6. Qe2+ Be7 7. Nc3 0-0 8. 0-0 Nb6 9. Bc4"] = "Re8";
    book["1. e4 e5 2. f4 d5 3. exd5 exf4 4. Nf3 Nf6 5. Bb5+ Nbd7 6. Qe2+ Be7 7. Nc3 0-0 8. 0-0 Nb6 9. Bc4 Re8 10. d4"] = "Bb4";
    book["1. e4 e5 2. f4 d5 3. exd5 exf4 4. Nf3 Nf6 5. Bb5+ Nbd7 6. Qe2+ Be7 7. Nc3 0-0 8. 0-0 Nb6 9. Bc4 Re8 10. d4 Bb4 11. Ne5"] = "Bxc3";
    book["1. e4 e5 2. f4 d5 3. exd5 exf4 4. Nf3 Nf6 5. Bb5+ Nbd7 6. Qe2+ Be7 7. Nc3 0-0 8. 0-0 Nb6 9. Bc4 Re8 10. d4 Bb4 11. Ne5 Bxc3 12. bxc3"] = "Nxc4";
    book["1. e4 e5 2. f4 d5 3. exd5 exf4 4. Nf3 Nf6 5. Bb5+ Nbd7 6. Qe2+ Be7 7. Nc3 0-0 8. 0-0 Nb6 9. Bc4 Re8 10. d4 Bb4 11. Ne5 Bxc3 12. bxc3 Nxc4 13. Qxc4"] = "Nxd5";


    // C33 King's gambit -- WHITE
    book["1. e4 e5 2. f4 Bc5"] = "Nf3";
    book["1. e4 e5 2. f4 Bc5 3. Nf3 d6"] = "c3";
    book["1. e4 e5 2. f4 Bc5 3. Nf3 d6 4. c3 Nc6"] = "fxe5 | b4";
    book["1. e4 e5 2. f4 Bc5 3. Nf3 d6 4. c3 Nc6 5. fxe5 dxe5"] = "Bb5";
    book["1. e4 e5 2. f4 Bc5 3. Nf3 d6 4. c3 Nc6 5. fxe5 Nxe5"] = "d4";
    book["1. e4 e5 2. f4 Bc5 3. Nf3 d6 4. c3 Nc6 5. b4 Bg6"] = "a4";
    book["1. e4 e5 2. f4 Bc5 3. Nf3 d6 4. c3 Nc6 5. b4 Bg6 6. a4 a6"] = "fxe5";
    book["1. e4 e5 2. f4 Bc5 3. Nf3 d6 4. c3 Nc6 5. b4 Bg6 6. a4 a6 7. fxe5 dxe5"] = "Bc4";

    book["1. e4 e5 2. f4 exf4"] = "Nf3 | Bc4";
    book["1. e4 e5 2. f4 exf4 3. Bc4 Nc6"] = "Nf3";
    book["1. e4 e5 2. f4 exf4 3. Bc4 Nc6 4. Nf3 g5"] = "d4";
    book["1. e4 e5 2. f4 exf4 3. Nf3 d6"] = "Bc4";
    book["1. e4 e5 2. f4 exf4 3. Nf3 Nf6"] = "Nc3";
    book["1. e4 e5 2. f4 exf4 3. Nf3 g5"] = "h4";
    book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. h4 d5"] = "d4";
    book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. h4 g4"] = "Ne5";
    book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. h4 g4 5. Ne5 d6"] = "Nxg4";
    book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. h4 g4 5. Ne5 d6 6. Nxg4 Nc6"] = "Nf2";
    book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. h4 g4 5. Ne5 d6 6. Nxg4 Be7"] = "Nf2";
    book["1. e4 e5 2. f4 exf4 3. Nf3 g5 4. h4 g4 5. Ne5 d6 6. Nxg4 Be7 7. Nf2 Bxh4"] = "d4";



    // King's pawn game (C20)
    book["1. e4 e5"] = "Nf3 | Nc3 | Bc4 | f4 | d4";
    book["1. e4 e5 2. d4"] = "exd4";
    book["1. e4 e5 2. d4 exd4"] = "Qxd4 | c3 | Nf3";
    book["1. e4 e5 2. d4 exd4 3. Qxd4"] = "Nc6";
    book["1. e4 e5 2. d4 exd4 3. Qxd4 Nc6"] = "Qe3";
    book["1. e4 e5 2. d4 exd4 3. Qxd4 Nc6 4.Qe3"] = "Nf6 | d6";


    // C21 Danish Gambit -- WHITE
    book["1. e4 e5 2. d4 exd4 3. c3 dxc3"] = "Nxc3";
    book["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Nxc3 d6"] = "Nge2 | Qb3 | Be3";
    book["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Nxc3 Bc5"] = "Nf3 | Bc4";
    book["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Nxc3 Nc6"] = "Nf3 | Bc4";
    book["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Nxc3 Bb4"] = "Nf3 | Qd4";
    book["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Nxc3 Bb4 5. Qd4 Bf8"] = "Bf4";
    book["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Nxc3 Bb4 5. Qd4 Bxc3+"] = "Qxc3";
    book["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Nxc3 Bb4 5. Qd4 Bxc3+ 6. Qxc3 Nf6"] = "Ne2";
    book["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Nxc3 Bb4 5. Qd4 Bxc3+ 6. Qxc3 Nf6 7. Ne2 0-0"] = "Bg5";



    // Danish gambit (C21)
    book["1. e4 e5 2. d4 exd4 3. c3"] = "dxc3 | d5";
    book["1. e4 e5 2. d4 exd4 3. Nf3"] = "Nc6 | Bb4+";
    book["1. e4 e5 2. d4 exd4 3. Nf3 Nc6"] = "Nxd4 | Bc4";
    book["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Bc4"] = "cxb2";
    book["1. e4 e5 2. d4 exd4 3. c3 dxc3 4. Bc4 cxb2 5. Bxb2"] = "Nf6";

    book["1. e4 e5 2. g3"] = "Nf6 | Nc6 | d5";


    // C21 Danish gambit, Soerensen defence -- BLACK
    book["1. e4 e5 2. d4 exd4 3. c3 d5 4. Qxd4"] = "Be6";
    book["1. e4 e5 2. d4 exd4 3. c3 d5 4. exd5"] = "Qxd5";
    book["1. e4 e5 2. d4 exd4 3. c3 d5 4. exd5 Qxd5 5. Qxd4"] = "Qxd4";
    book["1. e4 e5 2. d4 exd4 3. c3 d5 4. exd5 Qxd5 5. Qxd4 Qxd4 6. cxd4"] = "Nc6";
    book["1. e4 e5 2. d4 exd4 3. c3 d5 4. exd5 Qxd5 5. Qxd4 Qxd4 6. cxd4 Nc6 7. d5"] = "Nb4";
    book["1. e4 e5 2. d4 exd4 3. c3 d5 4. exd5 Qxd5 5. Qxd4 Qxd4 6. cxd4 Nc6 7. Nf3"] = "Be6";
    book["1. e4 e5 2. d4 exd4 3. c3 d5 4. exd5 Qxd5 5. cxd4"] = "Nc6";


    // C20 KP, Indian opening -- BLACK
    book["1. e4 e5 2. d3"] = "Nc6 | Nf6 | Bc5";
    book["1. e4 e5 2. d3 Nc6 3. Nc3"] = "Bb4";
    book["1. e4 e5 2. d3 Nc6 3. Nf3"] = "Nf6";
    book["1. e4 e5 2. d3 Nc6 3. f4"] = "exf4";
    book["1. e4 e5 2. d3 Nc6 3. f4 exf4 4. Bxf4"] = "Qf6";

    book["1. e4 e5 2. c4"] = "Bc5 | Nf6";

    book["1. e4 e5 2. Bc4"] = "Nf6 | Nc6";
    book["1. e4 e5 2. Bc4 Nc6 3. Nf3"] = "Bc5";
    book["1. e4 e5 2. Bc4 Nc6 3. Nf3 Bc5 4. d3"] = "Nf6";
    book["1. e4 e5 2. Bc4 Nc6 3. Nf3 Bc5 4. d3 Nf6 5. c3"] = "d6";
    book["1. e4 e5 2. Bc4 Nc6 3. Nf3 Bc5 4. d3 Nf6 5. 0-0"] = "d6";
    book["1. e4 e5 2. Bc4 Nc6 3. Nf3 Bc5 4. d3 Nf6 5. Nbd2"] = "0-0";

    book["1. e4 e5 2. Bc4 Nf6 3. d3"] = "Nc6 | c6 | Bc5";
    book["1. e4 e5 2. Bc4 Nf6 3. Nc3"] = "Nc6 | Nxe4 | Bc5";



    // C24 Bishop's Opening: Berlin Defense -- WHITE
    book["1. e4 e5 2. Bc4 Nf6 3. d3 d5"] = "exd5";
    book["1. e4 e5 2. Bc4 Nf6 3. d3 d5 4. exd5 Nxd5"] = "Nf3 | Qf3";
    book["1. e4 e5 2. Bc4 Nf6 3. d3 d5 4. exd5 Nxd5 5. Nf3 Nc6"] = "0-0";
    book["1. e4 e5 2. Bc4 Nf6 3. d3 d5 4. exd5 Nxd5 5. Nf3 Nb6"] = "Bb3";
    book["1. e4 e5 2. Bc4 Nf6 3. d3 d5 4. exd5 Nxd5 5. Nf3 Nb6 6. Bb3 f6"] = "a4";
    book["1. e4 e5 2. Bc4 Nf6 3. d3 d5 4. exd5 Nxd5 5. Nf3 Nb6 6. Bb3 f6 7. a4 a5"] = "Nc3";


    // C26 Vienna Game: Stanley Variation -- WHITE
    book["1. e4 e5 2. Bc4 Nf6 3. Nc3 Nc6"] = "d3 | Nf3";



    book["1. e4 e5 2. Bc4 Nf6 3. Nc3 Nc6 4. d3 Bc5"] = "Nf3 | h3";
    book["1. e4 e5 2. Bc4 Nf6 3. Nc3 Nc6 4. d3 Na5"] = "Nge2 | Bb3";
    book["1. e4 e5 2. Bc4 Nf6 3. Nc3 Nc6 4. d3 Be7"] = "a3 | Nf3 | f4";
    book["1. e4 e5 2. Bc4 Nf6 3. Nc3 Nc6 4. d3 Bb4"] = "Nf3 | Ne2";
    book["1. e4 e5 2. Bc4 Nf6 3. Nc3 Nc6 4. d3 Bb4 5. Ne2 0-0"] = "0-0";
    book["1. e4 e5 2. Bc4 Nf6 3. Nc3 Nc6 4. d3 Bb4 5. Ne2 Na5"] = "a3";
    book["1. e4 e5 2. Bc4 Nf6 3. Nc3 Nc6 4. d3 Bb4 5. Ne2 d6"] = "a3 | 0-0";
    book["1. e4 e5 2. Bc4 Nf6 3. Nc3 Nc6 4. d3 Bb4 5. Ne2 d5"] = "exd5";
    book["1. e4 e5 2. Bc4 Nf6 3. Nc3 Nc6 4. d3 Bb4 5. Ne2 d5 6. exd5 Nxd5"] = "Bd2 | a3";



    book["1. e4 e5 2. Bc4 Nf6 3. Nc3 Nxe4"] = "Qh5";
    book["1. e4 e5 2. Bc4 Nf6 3. Nc3 Nxe4 4. Qh5 Nd6"] = "Qxe5+";
    book["1. e4 e5 2. Bc4 Nf6 3. Nc3 Nxe4 4. Qh5 Nd6 5. Qxe5+ Qe7"] = "Qxe7+";
    book["1. e4 e5 2. Bc4 Nf6 3. Nc3 Nxe4 4. Qh5 Nd6 5. Qxe5+ Qe7 6. Qxe7+ Bxe7"] = "Be2";
    book["1. e4 e5 2. Bc4 Nf6 3. Nc3 Bb4"] = "Nd5 | a3";
    book["1. e4 e5 2. Bc4 Nf6 3. Nc3 c6"] = "Nf3 | d4";
    book["1. e4 e5 2. Bc4 Nf6 3. Nc3 c6 4. d4 exd4"] = "Qxd4";
    book["1. e4 e5 2. Bc4 Nf6 3. Nc3 c6 4. d4 exd4 5. Qxd4 Be7"] = "Nf3 | a4";
    book["1. e4 e5 2. Bc4 Nf6 3. Nc3 d6"] = "d3 | Nf3";
    book["1. e4 e5 2. Bc4 Nf6 3. Nc3 Be7"] = "d3 | Nf3";
    book["1. e4 e5 2. Bc4 Nf6 3. Nc3 Bc5"] = "d3 | Nf3";
    book["1. e4 e5 2. Bc4 Nf6 3. Nc3 Bc5 4. Nf3 Nc6"] = "d3";
    book["1. e4 e5 2. Bc4 Nf6 3. Nc3 Bc5 4. Nf3 Qe7"] = "0-0 | d3";
    book["1. e4 e5 2. Bc4 Nf6 3. Nc3 Bc5 4. Nf3 d6"] = "d3 | 0-0";
    book["1. e4 e5 2. Bc4 Nf6 3. Nc3 Bc5 4. Nf3 d6 5. 0-0 0-0"] = "d4";
    book["1. e4 e5 2. Bc4 Nf6 3. Nc3 Bc5 4. Nf3 d6 5. 0-0 0-0 6. d4 exd4"] = "Nxd4";
    book["1. e4 e5 2. Bc4 Nf6 3. Nc3 Bc5 4. Nf3 d6 5. 0-0 Bg4"] = "Na4";
    book["1. e4 e5 2. Bc4 Nf6 3. Nc3 Bc5 4. Nf3 d6 5. 0-0 Be6"] = "Bxe6";
    book["1. e4 e5 2. Bc4 Nf6 3. Nc3 Bc5 4. Nf3 d6 5. 0-0 Be6 6. Bxe6 fxe6"] = "Na4";
    book["1. e4 e5 2. Bc4 Nf6 3. Nc3 Bc5 4. Nf3 d6 5. 0-0 Be6 6. Bxe6 fxe6 7. Na4 Bb6"] = "d3";
    book["1. e4 e5 2. Bc4 Nf6 3. Nc3 Bc5 4. Nf3 d6 5. 0-0 Nc6"] = "Na4";
    book["1. e4 e5 2. Bc4 Nf6 3. Nc3 Bc5 4. Nf3 d6 5. 0-0 Nc6 6. Na4 Bb6"] = "d3";



    // C43 Bishop's Opening: Urusov Gambit -- BLACK
    book["1. e4 e5 2. Bc4 Nf6 3. d4"] = "exd4";
    book["1. e4 e5 2. Bc4 Nf6 3. d4 exd4 4. Qxd4"] = "Nc6";
    book["1. e4 e5 2. Bc4 Nf6 3. d4 exd4 4. Nf3"] = "Nxe4";
    book["1. e4 e5 2. Bc4 Nf6 3. d4 exd4 4. Nf3 Nxe4 5. 0-0"] = "d5 | Be7 | Bc5 | Nf6";
    book["1. e4 e5 2. Bc4 Nf6 3. d4 exd4 4. Nf3 Nxe4 5. Nxd4"] = "d5 | Bc5";
    book["1. e4 e5 2. Bc4 Nf6 3. d4 exd4 4. Nf3 Nxe4 5. c3"] = "d5";
    book["1. e4 e5 2. Bc4 Nf6 3. d4 exd4 4. Nf3 Nxe4 5. Qxd4"] = "Nf6";
    book["1. e4 e5 2. Bc4 Nf6 3. d4 exd4 4. Nf3 Nxe4 5. Qxd4 Nf6 6. Bg5"] = "Qe7+";
    book["1. e4 e5 2. Bc4 Nf6 3. d4 exd4 4. Nf3 Nxe4 5. Qxd4 Nf6 6. 0-0"] = "d5";
    book["1. e4 e5 2. Bc4 Nf6 3. d4 exd4 4. Nf3 Nxe4 5. Qxd4 Nf6 6. Ng5"] = "d5";
    book["1. e4 e5 2. Bc4 Nf6 3. d4 exd4 4. Nf3 Nxe4 5. Qxd4 Nf6 6. Ne5"] = "d5";
    book["1. e4 e5 2. Bc4 Nf6 3. d4 exd4 4. Nf3 Nxe4 5. Qxd4 Nf6 6. Nc3"] = "Be7 | Nc6";
    book["1. e4 e5 2. Bc4 Nf6 3. d4 exd4 4. Nf3 Nxe4 5. Qxd4 Nf6 6. Nc3 Nc6 7. Qh4"] = "Bb4";
    book["1. e4 e5 2. Bc4 Nf6 3. d4 exd4 4. Nf3 Nxe4 5. Qxd4 Nf6 6. Nc3 Nc6 7. Qh4 Bb4 8. 0-0"] = "Bxc3";
    book["1. e4 e5 2. Bc4 Nf6 3. d4 exd4 4. Nf3 Nxe4 5. Qxd4 Nf6 6. Nc3 Nc6 7. Qh4 Bb4 8. 0-0 Bxc3 9. bxc3"] = "0-0";
    book["1. e4 e5 2. Bc4 Nf6 3. d4 exd4 4. Nf3 Nxe4 5. Qxd4 Nf6 6. Nc3 Nc6 7. Qh4 Bb4 8. Bg5"] = "Qe7+";




    book["1. e4 e5 2. Bc4 Nf6 3. Qe2"] = "Bc5";
    book["1. e4 e5 2. Bc4 Nf6 3. Nf3"] = "Nxe4";
    book["1. e4 e5 2. Bc4 Nf6 3. Nf3 Nxe4 4. d3"] = "Nc5";
    book["1. e4 e5 2. Bc4 Nf6 3. Nf3 Nxe4 4. Nc3"] = "Nxc3";
    book["1. e4 e5 2. Bc4 Nf6 3. Nf3 Nxe4 4. Nxe5"] = "d5";
    book["1. e4 e5 2. Bc4 Nf6 3. Nf3 Nxe4 4. Nxe5 d5 5. d3"] = "dxc4";
    book["1. e4 e5 2. Bc4 Nf6 3. Nf3 Nxe4 4. Nxe5 d5 5. d3 dxc4 6. dxe4"] = "Qxd1+";
    book["1. e4 e5 2. Bc4 Nf6 3. Nf3 Nxe4 4. Nxe5 d5 5. d3 dxc4 6. dxe4 Qxd1+ 7. Kxd1"] = "Be6";
    book["1. e4 e5 2. Bc4 Nf6 3. Nf3 Nxe4 4. Nxe5 d5 5. Qf3"] = "Be6";


    // Vienna game (C25)
    book["1. e4 e5 2. Nc3"] = "Nf6 | Nc6 | Bc5";
    book["1. e4 e5 2. Nc3 Nf6"] = "f4 | Bc4 | Nf3 | g3";
    book["1. e4 e5 2. Nc3 Nc6"] = "f4 | Bc4 | g3";
    book["1. e4 e5 2. Nc3 Bc5"] = "f4 | Bc4 | g3 | Nf3";

    book["1. e4 e5 2. Nc3 Nf6 3. f4"] = "d5";
    book["1. e4 e5 2. Nc3 Nf6 3. f4 d5 4. fxe5"] = "Nxe4";
    book["1. e4 e5 2. Nc3 Nf6 3. f4 d5 4. exd5"] = "exf4 | e4";

    book["1. e4 e5 2. Nc3 Nf6 3. Nf3 d6"] = "d4";
    book["1. e4 e5 2. Nc3 Nf6 3. Nf3 d6 4. d4 exd4"] = "Nxd4";

    book["1. e4 e5 2. Nc3 Be7"] = "Bc4";
    book["1. e4 e5 2. Nc3 Be7 3. Bc4 d6"] = "d3";


    // C25 Vienna gambit -- WHITE
    book["1. e4 e5 2. Nc3 Nc6 3. f4 Bc5"] = "Nf3";
    book["1. e4 e5 2. Nc3 Nc6 3. f4 exf4"] = "Nf3";
    book["1. e4 e5 2. Nc3 Nc6 3. f4 exf4 4. Nf3 g5"] = "h3";
    book["1. e4 e5 2. Nc3 Nc6 3. f4 exf4 4. Nf3 Be7"] = "Bc4";
    book["1. e4 e5 2. Nc3 Nc6 3. f4 exf4 4. Nf3 Bb4"] = "Nd5";
    book["1. e4 e5 2. Nc3 Nc6 3. f4 exf4 4. Nf3 d6"] = "d4";
    book["1. e4 e5 2. Nc3 Nc6 3. f4 exf4 4. Nf3 Nf6"] = "Bc4";
    book["1. e4 e5 2. Nc3 Nc6 3. f4 exf4 4. Nf3 Nf6 5. Bc4 Na5"] = "d3";
    book["1. e4 e5 2. Nc3 Nc6 3. f4 exf4 4. Nf3 Nf6 5. Bc4 Be7"] = "d3";


    // C25 Vienna Game: Paulsen Variation -- BLACK
    book["1. e4 e5 2. Nc3 Nc6 3. g3"] = "a5 | Nf6 | a6 | Bc5";
    book["1. e4 e5 2. Nc3 Nc6 3. g3 Nf6 4. Nf3"] = "Bc5 | d5";
    book["1. e4 e5 2. Nc3 Nc6 3. g3 Nf6 4. d3"] = "Bc5 | d5 | a5";
    book["1. e4 e5 2. Nc3 Nc6 3. g3 Nf6 4. Bg2"] = "Bc5 | a5";
    book["1. e4 e5 2. Nc3 Nc6 3. g3 Nf6 4. Bg2 Bc5 5. Nf3"] = "d6";
    book["1. e4 e5 2. Nc3 Nc6 3. g3 Nf6 4. Bg2 Bc5 5. Na4"] = "Be7";
    book["1. e4 e5 2. Nc3 Nc6 3. g3 Nf6 4. Bg2 Bc5 5. d3"] = "a5 | 0-0";
    book["1. e4 e5 2. Nc3 Nc6 3. g3 Nf6 4. Bg2 Bc5 5. Nge2"] = "0-0 | a5";
    book["1. e4 e5 2. Nc3 Nc6 3. g3 Nf6 4. Bg2 Bc5 5. Nge2 0-0 6. Na4"] = "Be7";
    book["1. e4 e5 2. Nc3 Nc6 3. g3 Nf6 4. Bg2 Bc5 5. Nge2 0-0 6. d3"] = "a5 | Re8";
    book["1. e4 e5 2. Nc3 Nc6 3. g3 Nf6 4. Bg2 Bc5 5. Nge2 0-0 6. 0-0"] = "Re8 | a5";
    book["1. e4 e5 2. Nc3 Nc6 3. g3 Nf6 4. Bg2 Bc5 5. Nge2 0-0 6. 0-0 Re8 7. Na4"] = "Bf8";
    book["1. e4 e5 2. Nc3 Nc6 3. g3 Nf6 4. Bg2 Bc5 5. Nge2 0-0 6. 0-0 Re8 7. Nd5"] = "d6 | Nxd5";
    book["1. e4 e5 2. Nc3 Nc6 3. g3 Nf6 4. Bg2 Bc5 5. Nge2 0-0 6. 0-0 Re8 7. Nd5 Nxd5 8. exd5"] = "Ne7";
    book["1. e4 e5 2. Nc3 Nc6 3. g3 Nf6 4. Bg2 Bc5 5. Nge2 0-0 6. 0-0 Re8 7. d3"] = "a5";
    book["1. e4 e5 2. Nc3 Nc6 3. g3 Nf6 4. Bg2 Bc5 5. Nge2 0-0 6. 0-0 Re8 7. d3 a5 8. Kh1"] = "Ng4";
    book["1. e4 e5 2. Nc3 Nc6 3. g3 Nf6 4. Bg2 Bc5 5. Nge2 0-0 6. 0-0 Re8 7. d3 a5 8. Bg5"] = "h6";
    book["1. e4 e5 2. Nc3 Nc6 3. g3 Nf6 4. Bg2 Bc5 5. Nge2 0-0 6. 0-0 Re8 7. d3 a5 8. Bg5 h6 9. Bxf6"] = "Qxf6";
    book["1. e4 e5 2. Nc3 Nc6 3. g3 Nf6 4. Bg2 Bc5 5. Nge2 0-0 6. 0-0 Re8 7. d3 a5 8. Bg5 h6 9. Bh4"] = "g5";




    // Vienna game (C26)
    book["1. e4 e5 2. Nc3 Nf6 3. Bc4 c6"] = "Nf3";
    book["1. e4 e5 2. Nc3 Nf6 3. Bc4 c6 4. Nf3 b5"] = "Bb3";
    book["1. e4 e5 2. Nc3 Nf6 3. Bc4 c6 4. Nf3 b5 5. Bb3 Bb4"] = "Nxe5";
    book["1. e4 e5 2. Nc3 Nf6 3. Bc4 c6 4. Nf3 b5 5. Bb3 Bb4 6. Nxe5 0-0"] = "0-0";


    book["1. e4 e5 2. Nc3 Nf6 3. Bc4 Bc5"] = "d3";
    book["1. e4 e5 2. Nc3 Nf6 3. Bc4 Bc5 4. d3 d6"] = "Na4";
    book["1. e4 e5 2. Nc3 Nf6 3. Bc4 Bc5 4. d3 c6"] = "Nf3";
    book["1. e4 e5 2. Nc3 Nf6 3. Bc4 Bc5 4. d3 Nc6"] = "Nf3";
    book["1. e4 e5 2. Nc3 Nf6 3. Bc4 Bc5 4. d3 0-0"] = "Nf3";
    book["1. e4 e5 2. Nc3 Nf6 3. Bc4 Bc5 4. d3 h6"] = "Nf3";


    book["1. e4 e5 2. Nc3 Bc5 3. Nf3"] = "d6";
    book["1. e4 e5 2. Nc3 Bc5 3. Nf3 d6"] = "d4 | Na4 | Bc4";
    book["1. e4 e5 2. Nc3 Bc5 3. Nf3 Nc6"] = "Bc4 | Nxe5";

    book["1. e4 e5 2. Nc3 Bc5 3. f4"] = "d6";
    book["1. e4 e5 2. Nc3 Bc5 3. f4 d6"] = "Nf3 | fxe5";
    book["1. e4 e5 2. Nc3 Bc5 3. f4 d6 4. Nf3"] = "Nf6 | Nc6";
    book["1. e4 e5 2. Nc3 Bc5 3. f4 d6 4. fxe5"] = "dxe5";
    book["1. e4 e5 2. Nc3 Bc5 3. f4 d6 4. fxe5 dxe5"] = "Qh5";
    book["1. e4 e5 2. Nc3 Bc5 3. f4 d6 4. fxe5 dxe5 5. Qh5"] = "Nc6";
    book["1. e4 e5 2. Nc3 Bc5 3. f4 d6 4. fxe5 dxe5 5. Qh5 Nc6"] = "Bb5";

    book["1. e4 e5 2. Nc3 Bc5 3. f4 exf4"] = "Nf3";

    book["1. e4 e5 2. Nc3 Bb4"] = "Bc4 | Nf3 | Nd5";
    book["1. e4 e5 2. Nc3 Bb4 3. Bc4"] = "Nf6";
    book["1. e4 e5 2. Nc3 Bb4 3. Bc4 Nf6"] = "d3 | Nge2";
    book["1. e4 e5 2. Nc3 Bb4 3. Nf3"] = "Nc6";
    book["1. e4 e5 2. Nc3 Bb4 3. Nf3 Nc6"] = "Bc4 | Bb5 | Nd5";

    book["1. e4 e5 2. Nc3 Nc6 3. Bc4"] = "Nf6 | Bc5 | d6";
    book["1. e4 e5 2. Nc3 Nc6 3. Bc4 Nf6"] = "d3";
    book["1. e4 e5 2. Nc3 Nc6 3. Bc4 Nf6 4. d3"] = "Bb4 | Na5";
    book["1. e4 e5 2. Nc3 Nc6 3. Bc4 Bc5"] = "Qg4 | d3";
    book["1. e4 e5 2. Nc3 Nc6 3. Bc4 d6"] = "d3";
    book["1. e4 e5 2. Nc3 Nc6 3. Bc4 d6 4. d3"] = "Nf6 | Na5";

    book["1. e4 e5 2. Nc3 Nc6 3. Bc4 g6"] = "d3 | f4";

    book["1. e4 e5 2. Nc3 Bc5 3. Bc4"] = "Nf6 | d6";
    book["1. e4 e5 2. Nc3 Bc5 3. Bc4 Nf6 4. f4"] = "d6";

    book["1. e4 e5 2. Nc3 Bb4 3. Bc4 Bxc3"] = "dxc3";
    book["1. e4 e5 2. Nc3 Bb4 3. Bc4 Bxc3 4. dxc3 Nf6"] = "f3";

    book["1. e4 e5 2. Nc3 Nc6 3. Bc4 Nf6 4. d3 Na5"] = "Bb3";
    book["1. e4 e5 2. Nc3 Nc6 3. Bc4 Nf6 4. d3 Na5 5. Bb3 Nxb3"] = "axb3";
    book["1. e4 e5 2. Nc3 Nc6 3. Bc4 Nf6 4. d3 Na5 5. Bb3 Bc5"] = "f4";
    book["1. e4 e5 2. Nc3 Nc6 3. Bc4 Nf6 4. d3 Na5 5. Bb3 Be7"] = "f4";


    book["1. e4 e5 2. Nc3 Nc6 3. Bc4 Nf6 4. d3 Bb4 5. Bd2"] = "0-0 | Na5";
    book["1. e4 e5 2. Nc3 Nc6 3. Bc4 Nf6 4. d3 Bb4 5. Bd2 0-0 6. Nge2"] = "Na5";
    book["1. e4 e5 2. Nc3 Nc6 3. Bc4 Nf6 4. d3 Bb4 5. Bd2 0-0 6. Nf3"] = "d6";
    book["1. e4 e5 2. Nc3 Nc6 3. Bc4 Nf6 4. d3 Bb4 5. Bd2 Na5 6. Bb3"] = "0-0";
    book["1. e4 e5 2. Nc3 Nc6 3. Bc4 Nf6 4. d3 Bb4 5. Bd2 Na5 6. Qf3"] = "0-0";
    book["1. e4 e5 2. Nc3 Nc6 3. Bc4 Nf6 4. d3 Bb4 5. Bd2 Na5 6. Nf3"] = "Nxc4";
    book["1. e4 e5 2. Nc3 Nc6 3. Bc4 Nf6 4. d3 Bb4 5. Bd2 Na5 6. Nf3 Nxc4 7. dxc4"] = "d6";
    book["1. e4 e5 2. Nc3 Nc6 3. Bc4 Nf6 4. d3 Bb4 5. Bd2 Na5 6. Nge2"] = "Nxc4";
    book["1. e4 e5 2. Nc3 Nc6 3. Bc4 Nf6 4. d3 Bb4 5. Bd2 Na5 6. Nge2 Nxc4 7. dxc4"] = "d6";
    book["1. e4 e5 2. Nc3 Nc6 3. Bc4 Nf6 4. d3 Bb4 5. Bd2 Na5 6. Nb5"] = "Bxd2";
    book["1. e4 e5 2. Nc3 Nc6 3. Bc4 Nf6 4. d3 Bb4 5. Bd2 Na5 6. Nb5 Bxd2+ 7. Qxd2"] = "b6";
    book["1. e4 e5 2. Nc3 Nc6 3. Bc4 Nf6 4. d3 Bb4 5. Bd2 Na5 6. Nb5 Bxd2+ 7. Qxd2 b6 8. a3"] = "a6 | Nxc4";
    book["1. e4 e5 2. Nc3 Nc6 3. Bc4 Nf6 4. d3 Bb4 5. Bd2 Na5 6. Nb5 Bxd2+ 7. Qxd2 b6 8. a3 Nxc4 9. dxc4"] = "a6";


    // King’s knight opening C40)
    book["1. e4 e5 2. Nf3"] = "Nc6 | Nf6 | d6";


    // King's pawn game (C44)
    book["1. e4 e5 2. Nf3 Nc6"] = "Bb5 | Bc4 | d4 | Nc3";


    // King's pawn game (C50) -- WHITE
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 h6"] = "d4";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 h6 4. d4 exd4"] = "0-0";


    // Scotch opening (C44)
    book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4"] = "Nxd4";
    book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Bc5"] = "Be3";
    book["1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nf6"] = "Nxc6";

    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 d6"] = "d4 | Bb5";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 d6 4. Bb5 Bd7"] = "d4";


    // C46 Three knights game -- WHITE
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 d6 4. Bb5 Nge7"] = "d4";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 d6 4. Bb5 a6"] = "Bxc6+";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 d6 4. Bb5 a6 5. Bxc6+ bxc6"] = "d4";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 d6 4. Bb5 Nf6"] = "d4";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 d6 4. Bb5 Bg4"] = "d4";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 d6 4. Bb5 Bg4 5. d4 Bxf3"] = "Qxf3";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 d6 4. Bb5 Bg4 5. d4 Bxf3 6. Qxf3 exd4"] = "Ne2";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 d6 4. Bb5 Bg4 5. d4 exd4"] = "Qxd4";


    book["1. e4 e5 2. Nf3 Nc6 3. d4 Nf6"] = "dxe5 | d5";
    book["1. e4 e5 2. Nf3 Nc6 3. d4 Nf6 4. dxe5 Nxe4"] = "Bc4";
    book["1. e4 e5 2. Nf3 Nc6 3. d4 Nf6 4. d5 Ne7"] = "Nc3";
    book["1. e4 e5 2. Nf3 Nc6 3. d4 Nf6 4. d5 Nb4"] = "a3";



    // C46 Four knights game -- WHITE
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6"] = "Bb5 | h3 | d4";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4"] = "Nxd4";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4"] = "e5";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. e5 dxc3"] = "exf6";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. e5 dxc3 7. exf6 Qxf6"] = "dxc3";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. e5 dxc3 7. exf6 Qxf6 8. dxc3 Bc5"] = "Qe2+";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 d6"] = "d4";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 d6 5. d4 exd4"] = "Nxd4";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 d6 5. d4 exd4 6. Nxd4 Bd7"] = "0-0 | Bxc6";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 d6 5. d4 exd4 6. Nxd4 Bd7 7. Bxc6 bxc6"] = "Qf3";


    
    // C46 Four knights game -- BLACK
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3"] = "Nf6";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4"] = "exd4";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. d4 exd4 5. Nxd4"] = "Bb4";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bc4"] = "Nxe4";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bc4 Nxe4 5. Nxe4"] = "d5";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5"] = "Nd4";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Nxd4"] = "exd4";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. e5"] = "dxc3";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. e5 dxc3 7. exf6"] = "Qxf6";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Nxd4 exd4 6. e5 dxc3 7. exf6 Qxf6 8. dxc3"] = "Bc5";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Ba4"] = "c6";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Ba4 c6 6. Nxe5"] = "d6";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Ba4 c6 6. Nxe5 d6 7. Nf3"] = "Bg4";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Ba4 c6 6. d3"] = "Bc5";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Ba4 c6 6. 0-0"] = "a5";
    book["1. e4 e5 2. Nf3 Nc6 3. Nc3 Nf6 4. Bb5 Nd4 5. Ba4 c6 6. 0-0 a5 7. a3"] = "Bc5";



    // King's pawn game (C50)
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4"] = "Bc5 | Nf6 | Be7 | d6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Bc5"] = "c3 | d3 | 0-0";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6"] = "d3 | Ng5 | Nc3 | d4";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. 0-0"] = "Bc5 | Nxe4";


    // C55 Two knights defence (Modern bishop's opening) -- WHITE
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Be7"] = "0-0";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Qe7"] = "0-0";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 d5"] = "exd5";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 d5 5. exd5 Nxd5"] = "0-0";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 h6"] = "0-0";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5"] = "0-0";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. d3 Bc5 5. 0-0 d6"] = "Re1";


    // Fried Liver Attack (C58)
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5"] = "d5";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. Nxf7"] = "Kxf7";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. Nxf7 Kxf7 6. exd5"] = "b5";

    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5"] = "Na5";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+"] = "c6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6"] = "bxc6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Bd3"] = "Nd5";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Be2"] = "h6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Ba4"] = "h6";

    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Bd3 Nd5 9. Nf3"] = "Bd6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Bd3 Nd5 9. h4"] = "Nf4";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Be2 h6 9. Nf3"] = "e4";
    book["1. e4 e5 2. Nf3 Nc6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 Na5 6. Bb5+ c6 7. dxc6 bxc6 8. Ba4 h6 9. Nf3"] = "e4";


    // Spanish opening (C60)
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5"] = "a6 | Nf6 | f5";

    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Bc5"] = "0-0 | c3";

    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6"] = "Ba4 | Bxc6";

    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4"] = "Nf6 | d6 | b5 | Bc5";



    // Spanish opening, exchange variation (C68)
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Bxc6"] = "dxc6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Bxc6 dxc6"] = "0-0 | Nc3";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Bxc6 dxc6 5. 0-0"] = "f6 | Bg4";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Bxc6 dxc6 5. Nc3"] = "f6 | Bd6";

    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6"] = "0-0 | d3 | Nc3";

    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. d3"] = "Bc5 | d6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. d3 Bc5"] = "c3 | 0-0 | Bxc6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. d3 d6"] = "c3 | 0-0";

    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0"] = "Nxe4 | Bc5 | d6";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Nxe4"] = "d4 | Re1";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 Bc5"] = "c3 | Nxe5 | d3";
    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. 0-0 d6"] = "d4 | Re1";

    book["1. e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. Nc3"] = "Bb4 | Nd4 | d6 | Bc5";



    // Petrov's defense (C42)
    book["1. e4 e5 2. Nf3 Nf6"] = "Nxe5 | Nc3 | d4 | d3 | Bc4";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5"] = "d6 | Nxe4";
    book["1. e4 e5 2. Nf3 Nf6 3. Nc3"] = "Nc6 | Bb4 | d6 | Bc5";
    book["1. e4 e5 2. Nf3 Nf6 3. Nc3 Bb4"] = "Nxe5 | Bc4 | d3";
    book["1. e4 e5 2. Nf3 Nf6 3. Nc3 Bb4 4. Bc4"] = "0-0 | d6";
    book["1. e4 e5 2. Nf3 Nf6 3. Nc3 Nc6"] = "Bb5 | d4";
    book["1. e4 e5 2. Nf3 Nf6 3. Nc3 Nc6 4. Bc4"] = "Bc5 | Nxe4";
    book["1. e4 e5 2. Nf3 Nf6 3. Nc3 Nc6 4. Bc4 Bc5"] = "d3 | 0-0";
    book["1. e4 e5 2. Nf3 Nf6 3. d4"] = "Nxe4 | dxe4";
    book["1. e4 e5 2. Nf3 Nf6 3. d3"] = "Nc6";
    book["1. e4 e5 2. Nf3 Nf6 3. d3 Nc6"] = "Be2 | g3 | c3 | Nc3 | Bg5";
    book["1. e4 e5 2. Nf3 Nf6 3. Bc4"] = "Nc6 | Nxe4";

    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nd3"] = "Nxe4";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nd3 Nxe4 5. Qf3"] = "d5 | Nf6";


    // C42 Petrov's defence -- BLACK
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3"] = "Nxe4";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4"] = "d5";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. Nc3"] = "Nxc3";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. Nc3 Nxc3 6. dxc3"] = "Be7";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. Nc3 Nxc3 6. bxc3"] = "Be7";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. Qe2"] = "Qe7";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. c4"] = "Nc6";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d3"] = "Nf6";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. Bd3"] = "Nf6";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. Be2"] = "Be7";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. Be2 Be7 6. d3"] = "Nf6";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. Be2 Be7 6. d4"] = "0-0";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. Be2 Be7 6. 0-0"] = "0-0";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. Be2 Be7 6. 0-0 0-0 7. Re1"] = "d5";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. Be2 Be7 6. 0-0 0-0 7. d3"] = "Nf6";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. Be2 Be7 6. 0-0 0-0 7. d3 Nf6 8. Nc3"] = "Re8";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. Be2 Be7 6. 0-0 0-0 7. d3 Nf6 8. Re1"] = "h6";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. Be2 Be7 6. 0-0 0-0 7. d3 Nf6 8. Bg5"] = "h6";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. Be2 Be7 6. 0-0 0-0 7. d3 Nf6 8. b3"] = "d5";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. Be2 Be7 6. 0-0 0-0 7. d3 Nf6 8. d4"] = "d5";


    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3"] = "Be7";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Be7 7. 0-0"] = "Nc6";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Be7 7. 0-0 Nc6 8. c4"] = "Nb4";
    book["1. e4 e5 2. Nf3 Nf6 3. Nxe5 d6 4. Nf3 Nxe4 5. d4 d5 6. Bd3 Be7 7. 0-0 Nc6 8. Nbd2"] = "Nd6";


    book["1. e4 e5 2. Nf3 Nf6 3. Bc4 Nc6"] = "d3 | Ng5";
    book["1. e4 e5 2. Nf3 Nf6 3. Bc4 Nxe4"] = "Nc3";
    book["1. e4 e5 2. Nf3 Nf6 3. Bc4 Nxe4 4. Nc3"] = "Nxc3 | Nc6";

    book["1. e4 e5 2. Nf3 Nf6 3. d4 Nxe4 4. dxe5"] = "d5";
    book["1. e4 e5 2. Nf3 Nf6 3. d4 Nxe4 4. dxe5 d5"] = "Nbd2 | exd6";
    book["1. e4 e5 2. Nf3 Nf6 3. d4 Nxe4 4. dxe5 d5 5. Nbd2"] = "Nxd2";
    book["1. e4 e5 2. Nf3 Nf6 3. d4 Nxe4 4. dxe5 d5 5. Nbd2 Nxd2"] = "Qxd2 | Bxd2";

    book["1. e4 e5 2. Nf3 Nf6 3. d4 Nxe4 4. dxe5 d5 5. Nbd2 Nxd2 6. Bxd2"] = "Be7";
    book["1. e4 e5 2. Nf3 Nf6 3. d4 Nxe4 4. dxe5 d5 5. Nbd2 Nxd2 6. Bxd2 Be7 7. Bd3"] = "c5";
    book["1. e4 e5 2. Nf3 Nf6 3. d4 Nxe4 4. dxe5 d5 5. Nbd2 Nxd2 6. Bxd2 Be7 7. c3"] = "c5";
    book["1. e4 e5 2. Nf3 Nf6 3. d4 Nxe4 4. dxe5 d5 5. Nbd2 Nxd2 6. Bxd2 Be7 7. Bb5+"] = "c6";
    book["1. e4 e5 2. Nf3 Nf6 3. d4 Nxe4 4. dxe5 d5 5. Nbd2 Nxd2 6. Bxd2 Be7 7. Bb5+ c6 8. Bd3"] = "Nd7";
    book["1. e4 e5 2. Nf3 Nf6 3. d4 Nxe4 4. dxe5 d5 5. Nbd2 Nxd2 6. Bxd2 Be7 7. Bb5+ c6 8. Bd3 Nd7 9. c3"] = "Nc5";
    book["1. e4 e5 2. Nf3 Nf6 3. d4 Nxe4 4. dxe5 d5 5. Nbd2 Nxd2 6. Bxd2 Be7 7. Bb5+ c6 8. Bd3 Nd7 9. 0-0"] = "Nc5";
    book["1. e4 e5 2. Nf3 Nf6 3. d4 Nxe4 4. dxe5 d5 5. Nbd2 Nxd2 6. Bxd2 Be7 7. Bb5+ c6 8. Bd3 Nd7 9. 0-0 Nc5 10. Be2"] = "0-0";
    book["1. e4 e5 2. Nf3 Nf6 3. d4 Nxe4 4. dxe5 d5 5. Nbd2 Nxd2 6. Bxd2 Be7 7. Bb5+ c6 8. Bd3 Nd7 9. 0-0 Nc5 10. Be2 0-0 11. c3"] = "Qc7";
    book["1. e4 e5 2. Nf3 Nf6 3. d4 Nxe4 4. dxe5 d5 5. Nbd2 Nxd2 6. Bxd2 Be7 7. Bb5+ c6 8. Bd3 Nd7 9. 0-0 Nc5 10. Be2 0-0 11. Nd4"] = "Qb6";
    book["1. e4 e5 2. Nf3 Nf6 3. d4 Nxe4 4. dxe5 d5 5. Nbd2 Nxd2 6. Bxd2 Be7 7. Bb5+ c6 8. Bd3 Nd7 9. 0-0 Nc5 10. Be2 0-0 11. Nd4 Qb6 12. Rb1"] = "Ne4";
    book["1. e4 e5 2. Nf3 Nf6 3. d4 Nxe4 4. dxe5 d5 5. Nbd2 Nxd2 6. Bxd2 Be7 7. Bb5+ c6 8. Bd3 Nd7 9. 0-0 Nc5 10. Be2 0-0 11. Nd4 Qb6 12. Rb1 Ne4 13. Bf4"] = "Qc7 | Ne4";

    book["1. e4 e5 2. Nf3 Nf6 3. d4 Nxe4 4. dxe5 d5 5. exd6"] = "Bxd6";
    book["1. e4 e5 2. Nf3 Nf6 3. d4 Nxe4 4. dxe5 d5 5. exd6 Bxd6"] = "Bd3";
    book["1. e4 e5 2. Nf3 Nf6 3. d4 Nxe4 4. dxe5 d5 5. exd6 Bxd6 6. Bd3"] = "Nc5";
    book["1. e4 e5 2. Nf3 Nf6 3. d4 Nxe4 4. dxe5 d5 5. exd6 Bxd6 6. Bd3 Nc5"] = "0-0";
    book["1. e4 e5 2. Nf3 Nf6 3. d4 Nxe4 4. dxe5 d5 5. exd6 Bxd6 6. Bd3 Nc5 7. 0-0"] = "Nxd3";
    book["1. e4 e5 2. Nf3 Nf6 3. d4 Nxe4 4. dxe5 d5 5. exd6 Bxd6 6. Bd3 Nc5 7. 0-0 Nxd3"] = "Qxd3";
    book["1. e4 e5 2. Nf3 Nf6 3. d4 Nxe4 4. dxe5 d5 5. exd6 Bxd6 6. Bd3 Nc5 7. 0-0 Nxd3 8. Qxd3"] = "0-0";


    // Philidor's defense (C41)
    book["1. e4 e5 2. Nf3 d6"] = "d4 | Bc4 | Nc3";
    book["1. e4 e5 2. Nf3 d6 3. d4"] = "exd4 | Nf6";
    book["1. e4 e5 2. Nf3 d6 3. Bc4"] = "Be7 | Nf6";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Be7"] = "0-0 | d4";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Be7 4. 0-0"] = "Nf6 | c5 | Nc6";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Be7 4. 0-0 Nf6"] = "d3 | Re1";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Be7 4. d4"] = "exd4 | Nc6";
    book["1. e4 e5 2. Nf3 d6 3. Nc3"] = "Nf6 | Nc6 | d5";
    book["1. e4 e5 2. Nf3 d6 3. Nc3 Nf6"] = "d4";
    book["1. e4 e5 2. Nf3 d6 3. Nc3 Nf6 4. d4"] = "Nbd7 | exd4 | Nc6";

    book["1. e4 e5 2. Nf3 d6 3. Bc4 Be7 4. 0-0 Nf6 5. d3"] = "0-0";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Be7 4. 0-0 Nf6 5. d3 0-0 6. a4"] = "c6";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Be7 4. 0-0 Nf6 5. d3 0-0 6. h3"] = "c6";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Be7 4. 0-0 Nf6 5. d3 0-0 6. Re1"] = "c6";


    book["1. e4 e5 2. Nf3 d6 3. Bc4 Be7 4. d4 exd4"] = "Nxd4";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Be7 4. d4 exd4 5. Nxd4 Nf6"] = "Nc3";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Be7 4. d4 exd4 5. Nxd4 Nc6"] = "Nc3";


    // C41 Philidor Defense -- BLACK
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Be7 4. 0-0"] = "Nf6 | c5 | Nc6";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Be7 4. 0-0 Nf6 5. Nc3"] = "0-0 | c5";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Be7 4. 0-0 Nf6 5. Nc3 0-0 6. d3"] = "Be6";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Be7 4. 0-0 Nf6 5. Nc3 0-0 6. Re1"] = "Be6";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Be7 4. 0-0 Nf6 5. Nc3 0-0 6. Re1 Be6 7. Bxe6"] = "fxe6";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Be7 4. 0-0 Nf6 5. Nc3 0-0 6. Re1 Be6 7. Bxe6 8. fxe6 d4"] = "exd4";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Be7 4. 0-0 Nf6 5. Nc3 0-0 6. Re1 Be6 7. Bxe6 8. fxe6 d4 9. exd4 Qxd4"] = "Nc6";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Be7 4. 0-0 Nf6 5. Nc3 0-0 6. Re1 Be6 7. Bxe6 8. fxe6 d4 9. exd4 Nxd4"] = "Qd7";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Be7 4. 0-0 Nf6 5. Nc3 0-0 6. h3"] = "Be6 | Nc6";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Be7 4. 0-0 Nf6 5. Nc3 0-0 6. d4"] = "exd4";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Be7 4. 0-0 Nf6 5. Nc3 0-0 6. d4 exd4 7. Qxd4"] = "Bg4";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Be7 4. 0-0 Nf6 5. Nc3 0-0 6. d4 exd4 7. Nxd4"] = "c6";


    // C41 Philidor Defense -- BLACK
    book["1. e4 e5 2. Nf3 d6 3. Be2"] = "Nf6 | c5";
    book["1. e4 e5 2. Nf3 d6 3. Be2 Nf6 4. Nc3"] = "c5";
    book["1. e4 e5 2. Nf3 d6 3. Be2 Nf6 4. d4"] = "exd4";
    book["1. e4 e5 2. Nf3 d6 3. Be2 Nf6 4. d4 exd4 5. Nxd4"] = "Nxe4";
    book["1. e4 e5 2. Nf3 d6 3. Be2 Nf6 4. d4 exd4 5. Qxd4"] = "Nc6";
    book["1. e4 e5 2. Nf3 d6 3. Be2 Nf6 4. d3"] = "c5 | Be7";
    book["1. e4 e5 2. Nf3 d6 3. Be2 Nf6 4. d3 Be7 5. 0-0"] = "c5";
    book["1. e4 e5 2. Nf3 d6 3. Be2 Nf6 4. d3 Be7 5. Bd2"] = "c5";
    book["1. e4 e5 2. Nf3 d6 3. Be2 Nf6 4. d3 Be7 5. c4"] = "c5";
    book["1. e4 e5 2. Nf3 d6 3. Be2 Nf6 4. d3 Be7 5. c3"] = "0-0 | c5";
    book["1. e4 e5 2. Nf3 d6 3. Be2 Nf6 4. d3 Be7 5. h3"] = "c5";
    book["1. e4 e5 2. Nf3 d6 3. Be2 Nf6 4. d3 Be7 5. Bg5"] = "c5 | 0-0";
    book["1. e4 e5 2. Nf3 d6 3. Be2 Nf6 4. d3 Be7 5. Bg5 0-0 6. 0-0"] = "c5";
    book["1. e4 e5 2. Nf3 d6 3. Be2 Nf6 4. d3 Be7 5. Bg5 0-0 6. c4"] = "c5";
    book["1. e4 e5 2. Nf3 d6 3. Be2 Nf6 4. d3 Be7 5. Bg5 0-0 6. Bd2"] = "c5";
    book["1. e4 e5 2. Nf3 d6 3. Be2 Nf6 4. d3 Be7 5. Bg5 0-0 6. Bxf6"] = "Bxf6";
    book["1. e4 e5 2. Nf3 d6 3. Be2 Nf6 4. d3 Be7 5. Bg5 0-0 6. Bxf6 Bxf6 7. 0-0"] = "g6";
    book["1. e4 e5 2. Nf3 d6 3. Be2 Nf6 4. d3 Be7 5. Bg5 0-0 6. Bxf6 Bxf6 7. c3"] = "g6";
    book["1. e4 e5 2. Nf3 d6 3. Be2 Nf6 4. d3 Be7 5. Bg5 0-0 6. Bxf6 Bxf6 7. Nbd2"] = "g6";
    book["1. e4 e5 2. Nf3 d6 3. Be2 Nf6 4. d3 Be7 5. Bg5 0-0 6. Bxf6 Bxf6 7. Nc3"] = "c6";
    book["1. e4 e5 2. Nf3 d6 3. Be2 Nf6 4. d3 Be7 5. Bg5 0-0 6. Bxf6 Bxf6 7. Nc3 c6 8. Nb1"] = "a5";
    book["1. e4 e5 2. Nf3 d6 3. Be2 Nf6 4. d3 Be7 5. Bg5 0-0 6. Bxf6 Bxf6 7. Nc3 c6 8. h3"] = "d5 | g6";
    book["1. e4 e5 2. Nf3 d6 3. Be2 Nf6 4. d3 Be7 5. Bg5 0-0 6. Bxf6 Bxf6 7. Nc3 c6 8. h3 d5 9. 0-0"] = "g6";
    book["1. e4 e5 2. Nf3 d6 3. Be2 Nf6 4. d3 Be7 5. Bg5 0-0 6. Bxf6 Bxf6 7. Nc3 c6 8. h3 d5 9. exd5"] = "cxd5";
    book["1. e4 e5 2. Nf3 d6 3. Be2 Nf6 4. d3 Be7 5. Bg5 0-0 6. Bxf6 Bxf6 7. Nc3 c6 8. h3 d5 9. exd5 cxd5 10. 0-0"] = "Nc6";
    book["1. e4 e5 2. Nf3 d6 3. Be2 Nf6 4. d3 Be7 5. Bg5 0-0 6. Bxf6 Bxf6 7. Nc3 c6 8. h3 d5 9. exd5 cxd5 10. d4"] = "e4";
    book["1. e4 e5 2. Nf3 d6 3. Be2 Nf6 4. d3 Be7 5. Bg5 0-0 6. Bxf6 Bxf6 7. Nc3 c6 8. h3 d5 9. exd5 cxd5 10. d4 e4 11. Ne5"] = "Nc6";



    // C41 Philidor Defense -- BLACK
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Nf6 4. Nc3"] = "Be7 | Be6";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Nf6 4. Ng5"] = "d5";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Nf6 4. Ng5 d5 5. exd5"] = "h6";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 h6 6. Nf3"] = "e4";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 h6 6. Nf3 e4 7. Ne5"] = "Bd6";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 h6 6. Nf3 e4 7. Nd4"] = "c6";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Nf6 4. Ng5 d5 5. exd5 h6 6. Nf3 e4 7. Qe2"] = "Bb4";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Nf6 4. Qe2"] = "Be7";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Nf6 4. d4"] = "exd4";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Nf6 4. d4 exd4 5. Qxd4"] = "Nc6";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Nf6 4. d4 exd4 5. 0-0"] = "Be7";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Nf6 4. d3"] = "Be7 | h6";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Nf6 4. d3 Be7 5. c3"] = "c6 | Nbd7";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Nf6 4. d3 Be7 5. Nbd2"] = "0-0 | c6";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Nf6 4. d3 Be7 5. Bb3"] = "c5";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Nf6 4. d3 Be7 5. Nc3"] = "0-0 | h6";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Nf6 4. d3 Be7 5. 0-0"] = "0-0 | h6";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Nf6 4. d3 Be7 5. 0-0 0-0 6. c3"] = "c5";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Nf6 4. d3 Be7 5. 0-0 0-0 6. Bb3"] = "c5";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Nf6 4. d3 Be7 5. 0-0 0-0 6. Re1"] = "c5";


    // C41 Philidor Defence -- WHITE
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Be7 4. 0-0 Nf6 5. Re1 Bg4"] = "h3 | c3 | d3";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Be7 4. 0-0 Nf6 5. Re1 c6"] = "c3 | d4 | h3";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Be7 4. 0-0 Nf6 5. Re1 Nc6"] = "h3 | c3 | Bb3";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Be7 4. 0-0 Nf6 5. Re1 0-0"] = "c3 | h3 | d4";


    book["1. e4 e5 2. Nf3 d6 3. Bc4 Be7 4. 0-0 Nf6 5. d4 0-0"] = "dxe5 | Re1";
    book["1. e4 e5 2. Nf3 d6 3. Bc4 Be7 4. 0-0 Nf6 5. d4 exd4"] = "Qxd4 | Re1";


    book["1. e4 e5 2. Nf3 d6 3. Nc3 Nc6"] = "d4";

    book["1. e4 e5 2. Nf3 d6 3. d4 exd4"] = "Nxd4";
    book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Nxd4"] = "Nf6 | g6";
    book["1. e4 e5 2. Nf3 d6 3. d4 Nf6"] = "Nc3 | dxe5";

    book["1. e4 e5 2. Nf3 d6 3. d4 exd4 4. Bf4"] = "Nf6 | c5";

    book["1. e4 e5 2. Nf3 d6 3. d4 Nf6 4. Nc3"] = "exd4 | Nbd7";
    book["1. e4 e5 2. Nf3 d6 3. d4 Nf6 4. Nc3 exd4"] = "Nxd4";
    book["1. e4 e5 2. Nf3 d6 3. d4 Nf6 4. Nc3 Nbd7"] = "Bc4";
    book["1. e4 e5 2. Nf3 d6 3. d4 Nf6 4. dxe5"] = "Nxe4";
    book["1. e4 e5 2. Nf3 d6 3. d4 Nf6 4. dxe5 Nxe4"] = "Qd5 | Bc4";
    book["1. e4 e5 2. Nf3 d6 3. d4 Nf6 4. dxe5 Nxe4 5. Qd5"] = "Nc5";
    book["1. e4 e5 2. Nf3 d6 3. d4 Nf6 4. dxe5 Nxe4 5. Bc4"] = "c6";


    // C41 Philidor, Nimzovich (Jaenisch) variation -- BLACK
    book["1. e4 e5 2. Nf3 d6 3. d4 Nf6 4. Bg5"] = "exd4";
    book["1. e4 e5 2. Nf3 d6 3. d4 Nf6 4. Bg5 exd4 5. Nxd4"] = "Be7";
    book["1. e4 e5 2. Nf3 d6 3. d4 Nf6 4. Bg5 exd4 5. Qxd4"] = "Nc6";


    // Vienna game (C25)
    book["1. e4 e5 2. Nc3"] = "Nf6 | Nc6 | Bc5";
    book["1. e4 e5 2. Nc3 d6"] = "Bc4 | Nf3";
    book["1. e4 e5 2. Nc3 d6 3. Nf3"] = "Nf6 | Bg4 | Nc6";
    book["1. e4 e5 2. Nc3 d6 3. Nf3 Be6"] = "d4";
    book["1. e4 e5 2. Nc3 d6 3. Nf3 Be6 4. d4"] = "exd4 | Nd7";
    book["1. e4 e5 2. Nc3 d6 3. Nf3 Be6 4. d4 exd4"] = "Nxd4";
    book["1. e4 e5 2. Nc3 d6 3. Nf3 Be6 4. d4 exd4 5. Nxd4"] = "Nf6 | Bd7";
    book["1. e4 e5 2. Nc3 d6 3. Nf3 Be6 4. d4 Nd7"] = "h3";
    book["1. e4 e5 2. Nc3 d6 3. Nf3 Be6 4. d4 Nd7 5. h3"] = "c6 | a6";
    book["1. e4 e5 2. Nc3 d6 3. Bc4"] = "Nf6";
    book["1. e4 e5 2. Nc3 d6 3. Bc4 Nf6"] = "d3 | Nf3";


    // C00 French defense -- BLACK
    book["1. e4 e6"] = "d4";
    book["1. e4 e6 2. d4"] = "d5 | c5"; 

    book["1. e4 e6 2. d4 c5 3. d5"] = "exd5 | Nf6";
    book["1. e4 e6 2. d4 c5 3. d5 Nf6 4. Nc3"] = "d6";
    book["1. e4 e6 2. d4 c5 3. d5 Nf6 4. dxe6"] = "dxe6";
    book["1. e4 e6 2. d4 c5 3. d5 Nf6 4. dxe6 dxe6 5. Qxd8+"] = "Kxd8";
    book["1. e4 e6 2. d4 c5 3. d5 Nf6 4. dxe6 dxe6 5. Qxd8+ Kxd8 6. Nc3"] = "a6";
    book["1. e4 e6 2. d4 c5 3. d5 Nf6 4. dxe6 dxe6 5. Qxd8+ Kxd8 6. f3"] = "Bd6";
    book["1. e4 e6 2. d4 c5 3. d5 Nf6 4. dxe6 dxe6 5. Qxd8+ Kxd8 6. e5"] = "Nd5";


    book["1. e4 e6 2. d4 c5 3. Nf3"] = "cxd4";
    book["1. e4 e6 2. d4 c5 3. Nf3 cxd4 4. Qxd4"] = "Nc6";
    book["1. e4 e6 2. d4 c5 3. Nf3 cxd4 4. Nxd4"] = "Nc6 | Nf6";
    book["1. e4 e6 2. d4 c5 3. Nf3 cxd4 4. Nxd4 Nf6 5. Bd3"] = "Nc6";
    book["1. e4 e6 2. d4 c5 3. Nf3 cxd4 4. Nxd4 Nf6 5. Nd2"] = "d5 | e5";
    book["1. e4 e6 2. d4 c5 3. Nf3 cxd4 4. Nxd4 Nf6 5. f3"] = "Be7";
    book["1. e4 e6 2. d4 c5 3. Nf3 cxd4 4. Nxd4 Nf6 5. Nc3"] = "Nc6 | Bb4";
    book["1. e4 e6 2. d4 c5 3. Nf3 cxd4 4. Nxd4 Nf6 5. Nc3 Bb4 6. Nb5"] = "d5 | Nc6";
    book["1. e4 e6 2. d4 c5 3. Nf3 cxd4 4. Nxd4 Nf6 5. Nc3 Bb4 6. Bd3"] = "d6 | Nc6";
    book["1. e4 e6 2. d4 c5 3. Nf3 cxd4 4. Nxd4 Nf6 5. Nc3 Bb4 6. e5"] = "Nd5";
    book["1. e4 e6 2. d4 c5 3. Nf3 cxd4 4. Nxd4 Nf6 5. Nc3 Bb4 6. e5 Nd5 7. Bd2"] = "Nxc3";
    book["1. e4 e6 2. d4 c5 3. Nf3 cxd4 4. Nxd4 Nf6 5. Nc3 Bb4 6. e5 Nd5 7. Bd2 Nxc3 8. Bxc3"] = "Bxc3+";
    book["1. e4 e6 2. d4 c5 3. Nf3 cxd4 4. Nxd4 Nf6 5. Nc3 Bb4 6. e5 Nd5 7. Bd2 Nxc3 8. Bxc3 Bxc3+ 9. bxc3"] = "Qc7";
    book["1. e4 e6 2. d4 c5 3. Nf3 cxd4 4. Nxd4 Nf6 5. Nc3 Bb4 6. e5 Nd5 7. Bd2 Nxc3 8. bxc3"] = "Bf8";
    book["1. e4 e6 2. d4 c5 3. Nf3 cxd4 4. Nxd4 Nf6 5. Nc3 Bb4 6. e5 Nd5 7. Qg4"] = "Kf8";


    book["1. e4 e6 2. d4 c5 3. c3"] = "d5 | a6 | cxd4";
    book["1. e4 e6 2. d4 c5 3. c3 cxd4 4. cxd4"] = "d5 | Nc6";
    book["1. e4 e6 2. d4 c5 3. c3 d5 4. dxc5"] = "Bxc5";
    book["1. e4 e6 2. d4 c5 3. c3 d5 4. e5"] = "Nc6 | Ne7 | Qb6";
    book["1. e4 e6 2. d4 c5 3. c3 d5 4. exd5"] = "Qxd5 | exd5";
    book["1. e4 e6 2. d4 c5 3. c3 d5 4. exd5 Qxd5 5. Na3"] = "cxd4 | Bd7";
    book["1. e4 e6 2. d4 c5 3. c3 d5 4. exd5 Qxd5 5. Be3"] = "Nf6 | cxd4";
    book["1. e4 e6 2. d4 c5 3. c3 d5 4. exd5 Qxd5 5. Nf3"] = "Nf6 | Nc6 | cxd4";
    book["1. e4 e6 2. d4 c5 3. c3 d5 4. exd5 Qxd5 5. Nf3 Nc6 6. Bd3"] = "Bd7";
    book["1. e4 e6 2. d4 c5 3. c3 d5 4. exd5 Qxd5 5. Nf3 Nc6 6. Na3"] = "Nf6 | Bd7";
    book["1. e4 e6 2. d4 c5 3. c3 d5 4. exd5 Qxd5 5. Nf3 Nc6 6. Be3"] = "cxd4";
    book["1. e4 e6 2. d4 c5 3. c3 d5 4. exd5 Qxd5 5. Nf3 Nc6 6. Be2"] = "Nf6 | cxd4";



    // C00 Queen's Pawn Game: Franco-Sicilian Defense -- BLACK
    book["1. e4 e6 2. d4 c5 3. dxc5"] = "Bxc5";
    book["1. e4 e6 2. d4 c5 3. dxc5 Bxc5 4. Nf3"] = "Nf6 | d6 | Nc6";
    book["1. e4 e6 2. d4 c5 3. dxc5 Bxc5 4. Nc3"] = "Nc6 | d6";
    book["1. e4 e6 2. d4 c5 3. dxc5 Bxc5 4. Bd3"] = "Ne7 | Nc6 | d6";
    book["1. e4 e6 2. d4 c5 3. dxc5 Bxc5 4. c4"] = "Nf6 | Qb6";
    book["1. e4 e6 2. d4 c5 3. dxc5 Bxc5 4. Bc4"] = "d5";
    book["1. e4 e6 2. d4 c5 3. dxc5 Bxc5 4. Bc4 d5 5. Bb5+"] = "Nc6";
    book["1. e4 e6 2. d4 c5 3. dxc5 Bxc5 4. Bc4 d5 5. exd5"] = "Bxf2+";
    book["1. e4 e6 2. d4 c5 3. dxc5 Bxc5 4. Bc4 d5 5. exd5 Bxf2+ 6. Kxf2"] = "Qh4";
    book["1. e4 e6 2. d4 c5 3. dxc5 Bxc5 4. Bc4 d5 5. exd5 Bxf2+ 6. Kxf2 Qh4+ 7. g3"] = "Qxc4";



    book["1. e4 e6 2. Nf3"] = "c5 | d5"; 
    book["1. e4 e6 2. Nf3 d5"] = "Nc3 | e5 | exd5";

    book["1. e4 e6 2. d3"] = "d5 | c5";

    book["1. e4 e6 2. Nc3"] = "d5 | c5 | b6 | c6 | d6";
    book["1. e4 e6 2. Nc3 d5 3. exd5"] = "exd5";
    book["1. e4 e6 2. Nc3 d5 3. exd5 exd5 4. d4"] = "Nf6";
    book["1. e4 e6 2. Nc3 d5 3. exd5 exd5 4. d4 Nf6 5. Qe2+"] = "Be7";
    book["1. e4 e6 2. Nc3 d5 3. exd5 exd5 4. d4 Nf6 5. Qe2+ Be7 6. Nf3"] = "0-0";
    book["1. e4 e6 2. Nc3 d5 3. exd5 exd5 4. d4 Nf6 5. Qe2+ Be7 6. Nf3 0-0 7. Ne5"] = "c5";

    book["1. e4 e6 2. Nc3 d5 3. Nf3"] = "Nf6 | d4 | dxe4";
    book["1. e4 e6 2. Nc3 d5 3. d3"] = "Nf6 | dxe4 | d4 | c5 | Bb4";
    book["1. e4 e6 2. Nc3 d5 3. f4"] = "dxe4 | d4 | Nf6 | c5";
    book["1. e4 e6 2. Nc3 d5 3. e5"] = "c5 | d4";
    book["1. e4 e6 2. Nc3 d5 3. g3"] = "Nf6 | d4 | dxe4 | c5 | c6 | Bb4";
    book["1. e4 e6 2. Nc3 d5 3. d4"] = "Nf6 | Bb4 | dxe4";
    book["1. e4 e6 2. Nc3 d5 3. d4 Nf6 4. e5"] = "Nfd7 | Ne4";
    book["1. e4 e6 2. Nc3 d5 3. d4 Nf6 4. Bg5"] = "Be7 | dxe4 | Bb4";
    book["1. e4 e6 2. Nc3 d5 3. d4 Nf6 4. exd5"] = "exd5 | Nxd5";
    book["1. e4 e6 2. Nc3 d5 3. d4 Nf6 4. Bd3"] = "c5 | dxe4 | Bb4";
    book["1. e4 e6 2. Nc3 d5 3. d4 Bb4 4. e5"] = "c5 | Ne7 | b6";
    book["1. e4 e6 2. Nc3 d5 3. d4 Bb4 4. exd5"] = "exd5 | Qxd5 | Bxc3+ | c5";
    book["1. e4 e6 2. Nc3 d5 3. d4 Bb4 4. Ne2"] = "dxe4 | Nf6";
    book["1. e4 e6 2. Nc3 d5 3. d4 Bb4 4. Bd3"] = "dxe4 | c5 | Nf6";
    book["1. e4 e6 2. Nc3 d5 3. d4 Bb4 4. a3"] = "Bxc3+ | Ba5 | Be7";
    book["1. e4 e6 2. Nc3 d5 3. d4 Bb4 4. Bd2"] = "Bxc3 | dxe4 | c5 | Nf6 | Ne7";
    book["1. e4 e6 2. Nc3 d5 3. d4 dxe4 4. f3"] = "exf3 | Nf6 | Nd7 | e3";
    book["1. e4 e6 2. Nc3 d5 3. d4 dxe4 4. Be3"] = "Nf6 | f5 | Bb4";
    book["1. e4 e6 2. Nc3 d5 3. d4 dxe4 4. Nxe4"] = "Nd7 | Nf6 | Bd7 | Be7";


    // C00 French Defense: Queen's Knight -- BLACK
    book["1. e4 e6 2. Nc3 d5 3. exd5 exd5 4. d4 Nf6 5. Bg5"] = "Be7 | c6 | Bb4";
    book["1. e4 e6 2. Nc3 d5 3. exd5 exd5 4. d4 Nf6 5. Bd3"] = "Bd6 | c6 | Be7 | Bb4 | c5 | Nc6";
    book["1. e4 e6 2. Nc3 d5 3. exd5 exd5 4. d4 Nf6 5. Be3"] = "Bd6 | c6 | Be7 | Bb4 | c5 | Be6";
    book["1. e4 e6 2. Nc3 d5 3. exd5 exd5 4. d4 Nf6 5. Bf4"] = "Bd6 | c6 | Be7 | Bb4 | c5 | a6";
    book["1. e4 e6 2. Nc3 d5 3. exd5 exd5 4. d4 Nf6 5. h3"] = "Bd6 | Bb4 | Be7 | Bf5 | c5 | c6";
    book["1. e4 e6 2. Nc3 d5 3. exd5 exd5 4. d4 Nf6 5. Bb5+"] = "c6";
    book["1. e4 e6 2. Nc3 d5 3. exd5 exd5 4. d4 Nf6 5. Be2"] = "Bd6 | Be7 | Bb4 | c6 | c5";
    book["1. e4 e6 2. Nc3 d5 3. exd5 exd5 4. d4 Nf6 5. Nf3"] = "Bd6 | Be7 | Bb4 | c6 | Bg4 | c5 | Nc6";
    book["1. e4 e6 2. Nc3 d5 3. exd5 exd5 4. d4 Nf6 5. Nf3"] = "Bd6 | Be7 | Bb4 | c6 | Bg4 | c5 | Nc6 | Be6";
    book["1. e4 e6 2. Nc3 d5 3. exd5 exd5 4. d4 Nf6 5. Nf3 Bb4 6. Bd3"] = "0-0 | Bxc3+ | Bg4";
    book["1. e4 e6 2. Nc3 d5 3. exd5 exd5 4. d4 Nf6 5. Nf3 Bb4 6. Bd3 Bxc3+ 7. bxc3"] = "0-0 | Bg4";
    book["1. e4 e6 2. Nc3 d5 3. exd5 exd5 4. d4 Nf6 5. Nf3 Bb4 6. Bd2"] = "0-0 | Bg4";



    book["1. e4 e6 2. f4"] = "d5";

    book["1. e4 e6 2. f4 d5 3. e5"] = "c5";
    book["1. e4 e6 2. f4 d5 3. e5 c5 4. Nf3"] = "Nc6";
    book["1. e4 e6 2. f4 d5 3. e5 c5 4. Nf3 Nc6 5. g3"] = "Be7";
    book["1. e4 e6 2. f4 d5 3. e5 c5 4. Nf3 Nc6 5. c4"] = "Nh6";
    book["1. e4 e6 2. f4 d5 3. e5 c5 4. Nf3 Nc6 5. c3"] = "Bd7";

    book["1. e4 e6 2. f4 d5 3. exd5"] = "exd5";
    book["1. e4 e6 2. f4 d5 3. exd5 exd5 4. Nf3"] = "Nf6";

    book["1. e4 e6 2. e5"] = "d5";
    book["1. e4 e6 2. Bc4"] = "d5";
    book["1. e4 e6 2. Bc4 d5 3. exd5"] = "exd5";
    book["1. e4 e6 2. Bc4 d5 3. exd5 exd5"] = "c6";


    // C00 French defence -- BLACK
    book["1. e4 e6 2. Bc4 d5 3. exd5 exd5 4. Be2"] = "Bd6";
    book["1. e4 e6 2. Bc4 d5 3. exd5 exd5 4. Bb3"] = "Nf6";
    book["1. e4 e6 2. Bc4 d5 3. exd5 exd5 4. Bb3 Nf6 5. d4"] = "Bd6";


    book["1. e4 e6 2. Nf3 d5 3. exd5"] = "exd5";
    book["1. e4 e6 2. Nf3 d5 3. exd5 exd5"] = "d4";
    book["1. e4 e6 2. Nf3 d5 3. exd5 exd5 4. d4"] = "Bd6 | Nf6 | Bg4 | Nc6";
    book["1. e4 e6 2. Nf3 d5 3. exd5 exd5 4. Nc3"] = "Nf6";
    book["1. e4 e6 2. Nf3 d5 3. exd5 exd5 4. Nc3 Nf6"] = "d4";
    book["1. e4 e6 2. Nf3 d5 3. exd5 exd5 4. Nc3 Nf6 5. d4"] = "Bd6 | Bg4 | Be7 | Bb4";

    book["1. e4 e6 2. Nf3 d5 3. Nc3"] = "Nf6 | d4";
    book["1. e4 e6 2. Nf3 d5 3. Nc3 Nf6"] = "e5";
    book["1. e4 e6 2. Nf3 d5 3. Nc3 Nf6 4. e5"] = "Nfd7";
    book["1. e4 e6 2. Nf3 d5 3. Nc3 Nf6 4. e5 Nfd7"] = "d4";
    book["1. e4 e6 2. Nf3 d5 3. Nc3 Nf6 4. e5 Nfd7 5. d4"] = "c5";
    book["1. e4 e6 2. Nf3 d5 3. Nc3 Nf6 4. e5 Nfd7 5. d4 c5"] = "dxc5";
    book["1. e4 e6 2. Nf3 d5 3. Nc3 Nf6 4. e5 Nfd7 5. d4 c5 6. dxc5"] = "Nc6";
    book["1. e4 e6 2. Nf3 d5 3. Nc3 d4"] = "Ne2";
    book["1. e4 e6 2. Nf3 d5 3. Nc3 d4 4. Ne2"] = "c5";
    book["1. e4 e6 2. Nf3 d5 3. Nc3 d4 4. Ne2 c5"] = "c3";
    book["1. e4 e6 2. Nf3 d5 3. Nc3 d4 4. Ne2 c5 5. c3"] = "Nc6 | Nf6";


    // C00 French, Two knights variation -- BLACK
    book["1. e4 e6 2. Nf3 d5 3. Nc3 d4 4. Ne2 c5 5. c3"] = "Nf6";
    book["1. e4 e6 2. Nf3 d5 3. Nc3 d4 4. Ne2 c5 5. d3"] = "Nc6";
    book["1. e4 e6 2. Nf3 d5 3. Nc3 d4 4. Ne2 c5 5. Ng3"] = "Nc6";
    book["1. e4 e6 2. Nf3 d5 3. Nc3 d4 4. Ne2 c5 5. Ng3 Nc6 6. Bc4"] = "Nf6";
    book["1. e4 e6 2. Nf3 d5 3. Nc3 d4 4. Ne2 c5 5. Ng3 Nc6 6. Bb5"] = "Ne7";



    book["1. e4 e6 2. Nf3 d5 3. e5"] = "c5";
    book["1. e4 e6 2. Nf3 d5 3. e5 c5"] = "b4";
    book["1. e4 e6 2. Nf3 d5 3. e5 c5 4. b4"] = "cxb4 | b6";

    book["1. e4 e6 2. Nf3 d5 3. e5 c5 4. d4"] = "Nc6 | cxd4";
    book["1. e4 e6 2. Nf3 d5 3. e5 c5 4. d4 Nc6 5. c3"] = "Qb6 | Bd7";

    book["1. e4 e6 2. Nf3 d5 3. Bd3"] = "c5 | Nf6 | dxe4";
    book["1. e4 e6 2. Nf3 d5 3. Bd3 dxe4 4. Bxe4"] = "Nf6";
    book["1. e4 e6 2. Nf3 d5 3. Bd3 dxe4 4. Bxe4 Nf6 5. Nc3"] = "Bb4";
    book["1. e4 e6 2. Nf3 d5 3. Bd3 dxe4 4. Bxe4 Nf6 5. Bd3"] = "Bd7";

    book["1. e4 e6 2. d4 c6"] = "Nf3 | Nc3 | c4";
    book["1. e4 e6 2. d4 c6 3. Nc3 g6"] = "Nf3";
    book["1. e4 e6 2. d4 c6 3. Nc3 g6 4. Nf3 g5"] = "Bd3";
    book["1. e4 e6 2. d4 c6 3. Nc3 g6 4. Nf3 g5 5. Bd3 a5"] = "0-0";


    // French defense, Paulsen variation (C10)
    book["1. e4 e6 2. d4 d5"] = "Nc3 | Nd2 | e5 | exd5";
    book["1. e4 e6 2. d4 d5 3. Nc3"] = "Bb4 | Nf6 | dxe4";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4"] = "e5 | exd5";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5"] = "c5 | Ne7";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 c5"] = "a3 | Bd2";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 Ne7"] = "a3 | Bd2";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 c5 5. a3"] = "Bxc3+ | Ba5";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 c5 5. Bd2"] = "Ne7";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 c5 5. Bd2 Ne7"] = "Nb5 | a3";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 Ne7 5. a3"] = "Bxc3+";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 Ne7 5. a3 Bxc3+"] = "bxc3";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 Ne7 5. a3 Bxc3+ 6. bxc3"] = "c5";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 Ne7 5. Bd2"] = "c5 | b6";

    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5"] = "Bd3 | Nf3";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nc6"] = "a3 | Nf3";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Ne7"] = "Qh5 | Nf3";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6"] = "a3 | Ne2 | Bg5";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 c6"] = "Ng3 | 0-0";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 Bg4"] = "Bf4 | f3";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 Nc6"] = "0-0 | a3";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 0-0"] = "0-0 | a3";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 0-0 7. 0-0 c6"] = "Ng3 | a3";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 0-0 7. 0-0 Re8"] = "Bg5 | a3 | h3";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 0-0 7. 0-0 Bg4"] = "f3";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 0-0 7. 0-0 h6"] = "a3 | h3 | Ng3";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 0-0 7. 0-0 Bd6"] = "Bg5";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. exd5 exd5 5. Bd3 Nf6 6. Ne2 0-0 7. 0-0 Nc6"] = "a3";


    // C10 French, Paulsen variation -- WHITE
    book["1. e4 e6 2. d4 d5 3. Nc3 a6"] = "Nf3 | Bd3";
    book["1. e4 e6 2. d4 d5 3. Nc3 a6 4. Bd3 Bb4"] = "exd5";
    book["1. e4 e6 2. d4 d5 3. Nc3 a6 4. Bd3 Bb4 5. exd5 exd5"] = "Nf3";


    // C16 French, Winawer, advance variation -- BLACK
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 Ne7 5. a3 Bxc3+ 6. bxc3 c5 7. Qg4"] = "0-0";
    book["1. e4 e6 2. d4 d5 3. Nc3 Bb4 4. e5 Ne7 5. a3 Bxc3+ 6. bxc3 c5 7. Qg4 0-0 8. Bd3"] = "Nbc6";


    book["1. d4 e6 2. e4"] = "d5 | c5";
    book["1. d4 e6 2. e4 c5 3. Nf3"] = "cxd4";
    book["1. d4 e6 2. e4 c5 3. Nf3 cxd4 4. Nxd4"] = "Nc6";
    book["1. d4 e6 2. e4 c5 3. Nf3 cxd4 4. Nxd4 Nc6 5. Nc3"] = "Qc7";


    book["1. d4 e6 2. e4 d5"] = "Nc3 | Nd2 | e5 | exd5";
    book["1. d4 e6 2. e4 c6"] = "Nf3 | Nc3";
    book["1. d4 e6 2. e4 b6"] = "Nf3 | Bd3";


    // C00 French defence -- BLACK
    book["1. d4 e6 2. e4 d5 3. Nc3"] = "Bb4 | Nf6";
    book["1. d4 e6 2. e4 d5 3. Nd2"] = "Nf6 | c5";
    book["1. d4 e6 2. e4 d5 3. Nd2 c5 4. exd5"] = "exd5";
    book["1. d4 e6 2. e4 d5 3. Nd2 c5 4. Ngf3"] = "cxd4 | Nc6";
    book["1. d4 e6 2. e4 d5 3. exd5"] = "exd5";
    book["1. d4 e6 2. e4 d5 3. e5"] = "c5";
    book["1. d4 e6 2. e4 d5 3. e5 c5 4. Nf3"] = "cxd4 | Nc6";
    book["1. d4 e6 2. e4 d5 3. e5 c5 4. c3"] = "Bd7 | Nc6";
    book["1. d4 e6 2. e4 d5 3. e5 c5 4. c3 Nc6 5. Nf3"] = "Nge7";

    book["1. d4 e6 2. e4 d5 3. Nd2"] = "Nf6 | c5 | Nd7 | a6";
    book["1. d4 e6 2. e4 d5 3. Nd2 Nf6 4. exd5"] = "exd5";
    book["1. d4 e6 2. e4 d5 3. Nd2 Nf6 4. Bd3"] = "Nxe4 | dxe4 | c5";
    book["1. d4 e6 2. e4 d5 3. Nd2 Nf6 4. e5"] = "Nfd7";
    book["1. d4 e6 2. e4 d5 3. Nd2 Nf6 4. e5 Nfd7 5. Bd3"] = "c5";
    book["1. d4 e6 2. e4 d5 3. Nd2 Nf6 4. e5 Nfd7 5. f4"] = "c5 | Be7";
    book["1. d4 e6 2. e4 d5 3. Nd2 Nf6 4. e5 Nfd7 5. c3"] = "c5";
    book["1. d4 e6 2. e4 d5 3. Nd2 Nf6 4. e5 Nfd7 5. c3 c5 6. f4"] = "Qb6 | Nc6 | cxd4";
    book["1. d4 e6 2. e4 d5 3. Nd2 Nf6 4. e5 Nfd7 5. c3 c5 6. Ngf3"] = "Qb6 | Nc6";
    book["1. d4 e6 2. e4 d5 3. Nd2 Nf6 4. e5 Nfd7 5. c3 c5 6. Nb3"] = "Nc6";
    book["1. d4 e6 2. e4 d5 3. Nd2 Nf6 4. e5 Nfd7 5. c3 c5 6. Bd3"] = "Nc6 | b5";
    book["1. d4 e6 2. e4 d5 3. Nd2 Nf6 4. e5 Nfd7 5. c3 c5 6. Bd3 Nc6 7. Ndf3"] = "Qa5 | cxd4";
    book["1. d4 e6 2. e4 d5 3. Nd2 Nf6 4. e5 Nfd7 5. c3 c5 6. Bd3 Nc6 7. Ngf3"] = "a5 | Qb6";
    book["1. d4 e6 2. e4 d5 3. Nd2 Nf6 4. e5 Nfd7 5. c3 c5 6. Bd3 Nc6 7. Ne2"] = "cxd4";
    book["1. d4 e6 2. e4 d5 3. Nd2 Nf6 4. e5 Nfd7 5. c3 c5 6. Bd3 Nc6 7. Ne2 cxd4 8. Nxd4"] = "Ndxe5";
    book["1. d4 e6 2. e4 d5 3. Nd2 Nf6 4. e5 Nfd7 5. c3 c5 6. Bd3 Nc6 7. Ne2 cxd4 8. cxd4"] = "f6";
    book["1. d4 e6 2. e4 d5 3. Nd2 Nf6 4. e5 Nfd7 5. c3 c5 6. Bd3 Nc6 7. Ne2 cxd4 8. cxd4 f6 9. exf6"] = "Nxf6";
    book["1. d4 e6 2. e4 d5 3. Nd2 Nf6 4. e5 Nfd7 5. c3 c5 6. Bd3 Nc6 7. Ne2 cxd4 8. cxd4 f6 9. exf6 Nxf6 10. 0-0"] = "Bd6";


    // C00 French, Schlechter variation -- BLACK
    book["1. e4 e6 2. d4 d5 3. Bd3"] = "dxe4 | c5";
    book["1. e4 e6 2. d4 d5 3. Bd3 dxe4 4. Bxe4"] = "Nf6";
    book["1. e4 e6 2. d4 d5 3. Bd3 dxe4 4. Bxe4 Nf6 5. Bd3"] = "c5";
    book["1. e4 e6 2. d4 d5 3. Bd3 dxe4 4. Bxe4 Nf6 5. Bf3"] = "c5";



    // French defense, Exchange variation (C01)
    book["1. e4 e6 2. d4 d5 3. exd5"] = "exd5";
    book["1. e4 e6 2. d4 d5 3. exd5 exd5"] = "Bd3 | Nf3 | c4";


    // C01 French, exchange variation -- BLACK
    book["1. e4 e6 2. d4 d5 3. exd5 exd5 4. Nf3"] = "Nf6 | Nc6 | Bd6";
    book["1. e4 e6 2. d4 d5 3. exd5 exd5 4. c4"] = "Nf6 | Bb4+";
    book["1. e4 e6 2. d4 d5 3. exd5 exd5 4. Bd3"] = "Bd6 | Nc6 | c5";
    book["1. e4 e6 2. d4 d5 3. exd5 exd5 4. Bd3 Nf6 5. Nf3"] = "Bd6";
    book["1. e4 e6 2. d4 d5 3. exd5 exd5 4. Bd3 Nf6 5. Bg5"] = "h6";
    book["1. e4 e6 2. d4 d5 3. exd5 exd5 4. Bd3 Nf6 5. Bg5 h6 6. Bh4"] = "c5";


    // French defense (C11) -- WHITE
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6"] = "Bg5 | e5 | exd5";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5"] = "Be7 | dxe4 | Bb4";


    // C12 French Defence: MacCutcheon Variation -- BLACK
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Bb4 5. exd5"] = "Qxd5";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Bb4 5. Ne2"] = "h6";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Bb4 5. Bxf6"] = "Qxf6";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Bb4 5. a3"] = "Bxc3+";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Bb4 5. a3 Bxc3+ 6. bxc3"] = "dxe4";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Bb4 5. Bd3"] = "h6";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Bb4 5. e5"] = "h6 | Bxc3+";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Bb4 5. e5 Bxc3+ 6. bxc3"] = "h6";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Bb4 5. e5 h6 6. exf6"] = "hxg5";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Bb4 5. e5 h6 6. exf6 hxg5 7. fxg7"] = "Rg8";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Bb4 5. e5 h6 6. Bd2"] = "Bxc3";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Bb4 5. e5 h6 6. Bd2 Bxc3 7. bxc3"] = "Ne4";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Bb4 5. e5 h6 6. Bd2 Bxc3 7. Bxc3"] = "Ne4";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Bb4 5. e5 h6 6. Bd2 Bxc3 7. Bxc3 Ne4 8. Bd3"] = "Nxc3";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Bb4 5. e5 h6 6. Bd2 Bxc3 7. Bxc3 Ne4 8. Bd3 Nxc3 9. bxc3"] = "c5";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Bb4 5. e5 h6 6. Bd2 Bxc3 7. Bxc3 Ne4 8. Bd2"] = "c5";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Bb4 5. e5 h6 6. Bd2 Bxc3 7. Bxc3 Ne4 8. Qg4"] = "g6";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. Bg5 Bb4 5. e5 h6 6. Bd2 Bxc3 7. Bxc3 Ne4 8. Bb4"] = "c5";



    // French defense, Steinitz variation (C11)
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. e5"] = "Nfd7";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. e5 Nfd7"] = "f4 | Nf3";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. e5 Nfd7 5. f4"] = "c5";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. e5 Nfd7 5. f4 c5"] = "Nf3";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. e5 Nfd7 5. f4 c5 6. Nf3"] = "Nc6";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. e5 Nfd7 5. f4 c5 6. Nf3 Nc6"] = "Be3";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. e5 Nfd7 5. f4 c5 6. Nf3 Nc6 7. Be3"] = "cxd4 | a6";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. e5 Nfd7 5. Nf3"] = "c5";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. e5 Nfd7 5. Nf3 c5"] = "dxc5";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. e5 Nfd7 5. Nf3 c5 6. dxc5"] = "Nc6 | Bxc5";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. e5 Nfd7 5. Nf3 c5 6. dxc5 Nc6"] = "Bf4";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. e5 Nfd7 5. Nf3 c5 6. dxc5 Nc6 7. Bf4"] = "Bxc5 | Nxc5";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. e5 Nfd7 5. Nf3 c5 6. dxc5 Bxc5"] = "Bf4";
    book["1. e4 e6 2. d4 d5 3. Nc3 Nf6 4. e5 Nfd7 5. Nf3 c5 6. dxc5 Bxc5 7. Bf4"] = "Nc6";


    // French defense, advance variation (C02)
    book["1. e4 e6 2. d4 d5 3. e5"] = "c5 | Bd7";
    book["1. e4 e6 2. d4 d5 3. e5 c5"] = "c3 | Nf3";

    book["1. e4 e6 2. d4 d5 3. e5 c5 4. c3"] = "Nc6 | Qb6";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. Nf3"] = "Nc6 | cxd4";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. Nf3 Nc6"] = "Bd3 | c3";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. Nf3 cxd4"] = "Nxd4 | Bd3";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. Nf3 cxd4 5. Bd3"] = "Nc6 | Ne7";

    book["1. e4 e6 2. d4 d5 3. e5 c5 4. Nf3 cxd4 5. Bd3 Nc6"] = "0-0";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. Nf3 cxd4 5. Bd3 Nc6 6. 0-0 Nge7"] = "Bf4";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. Nf3 cxd4 5. Bd3 Nc6 6. 0-0 f6"] = "Bb5";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. Nf3 cxd4 5. Bd3 Nc6 6. 0-0 Bd7"] = "Re1";

    book["1. e4 e6 2. d4 d5 3. e5 c5 4. Nf3 cxd4 5. Nxd4"] = "Ne7 | Nc6";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. Nf3 cxd4 5. Nxd4 Nc6 6. Bb5"] = "Bd7";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. Nf3 cxd4 5. Nxd4 Nc6 6. Nxc6"] = "bxc6";


    book["1. e4 e6 2. d4 d5 3. e5 c5 4. c3 Nc6 5. Nf3"] = "Bd7";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. c3 Nc6 5. Nf3 Bd7 6. Be2"] = "Nge7";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. c3 Nc6 5. Nf3 Bd7 6. a3"] = "f6";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. c3 Nc6 5. Nf3 Bd7 6. Bd3"] = "cxd4";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. c3 Nc6 5. Nf3 Bd7 6. Bd3 cxd4 7.  cxd4"] = "Qb6";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. c3 Nc6 5. Nf3 Bd7 6. dxc5"] = "Bxc5";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. c3 Nc6 5. Nf3 Bd7 6. Be3"] = "Qb6";


    book["1. e4 e6 2. d4 d5 3. e5 c5 4. c3 Nc6 5. Be3"] = "Qb6 | Nge7";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. c3 Nc6 5. Be3 Qb6 6. Qd2"] = "Bd7";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. c3 Nc6 5. Be3 Qb6 6. Qb3"] = "Qxb3";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. c3 Nc6 5. Be3 Qb6 6. Qb3 Qxb3 7. axb3"] = "cxd4";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. c3 Nc6 5. Be3 Qb6 6. Qb3 Qxb3 7. axb3 cxd4 8. cxd4"] = "Nge7";


    book["1. e4 e6 2. d4 d5 3. e5 c5 4. c3 Nc6 5. Bb5"] = "Bd7 | Qa5";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. c3 Nc6 5. Bb5 Bd7 6. Bxc6"] = "Bxc6";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. c3 Nc6 5. Bb5 Bd7 6. Nf3"] = "Nxe5";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. c3 Nc6 5. Bb5 Bd7 6. Nf3 Nxe5 7. Bxd7+"] = "Nxd7";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. c3 Nc6 5. Bb5 Bd7 6. Nf3 Nxe5 7. Nxe5"] = "Bxb5";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. c3 Nc6 5. Bb5 Bd7 6. Nf3 Nxe5 7. Bd3"] = "Nxd3";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. c3 Nc6 5. Bb5 Bd7 6. Nf3 Nxe5 7. Bd3 Nxd3 8. Qxd3"] = "Qb6";


    book["1. e4 e6 2. d4 d5 3. e5 c5 4. Nf3 Nc6 5. Bd3"] = "cxd4";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. Nf3 Nc6 5. Bd3 cxd4"] = "0-0";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. Nf3 Nc6 5. Bd3 cxd4 6. 0-0"] = "Nge7 | f6";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. Nf3 Nc6 5. c3"] = "Qb6 | Bd7 | Nge7 | cxd4";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. Nf3 Nc6 5. c3 Qb6"] = "a3 | Be2 | Bd3";


    book["1. e4 e6 2. d4 d5 3. e5 c5 4. Nf3 Nc6 5. c3 Bd7"] = "Be2 | a3";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. Nf3 Nc6 5. c3 Bd7 6. Be2"] = "Nge7 | f6 | cxd4";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. Nf3 Nc6 5. c3 Bd7 6. Be2 cxd4"] = "cxd4";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. Nf3 Nc6 5. c3 Bd7 6. Be2 cxd4 7. cxd4"] = "Nge7";

    book["1. e4 e6 2. d4 d5 3. e5 c5 4. Nf3 Nc6 5. c3 Nge7"] = "Bd3 | Na3";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. Nf3 Nc6 5. c3 cxd4"] = "cxd4";
    book["1. e4 e6 2. d4 d5 3. e5 c5 4. Nf3 Nc6 5. c3 cxd4 6. cxd4"] = "Bb4+ | Qb6 | Nge7";



    // French defense, Tarrasch (C03)
    book["1. e4 e6 2. d4 d5 3. Nd2"] = "Nf6 | c5 | dxe4 | Nc6 | Be7";


    // C05 French Defence: Tarrasch Variation, Closed -- WHITE
    book["1. e4 e6 2. d4 d5 3. Nd2 Nf6 4. e5 Ne4"] = "Bd3 | Nxe4";
    book["1. e4 e6 2. d4 d5 3. Nd2 Nf6 4. e5 Ng8"] = "Bd3 | f4";
    book["1. e4 e6 2. d4 d5 3. Nd2 Nf6 4. e5 Nfd7"] = "Bd3 | f4 | c3";
    book["1. e4 e6 2. d4 d5 3. Nd2 Nf6 4. e5 Nfd7 5. c3 Be7"] = "Bd3 | f4";
    book["1. e4 e6 2. d4 d5 3. Nd2 Nf6 4. e5 Nfd7 5. c3 c5"] = "Bd3 | f4";


    book["1. e4 e6 2. d4 d5 3. Nd2 c5"] = "exd5 | Ngf3";


    book["1. e4 e6 2. d4 d5 3. Nd2 c5 4. Ngf3 cxd4"] = "exd5";
    book["1. e4 e6 2. d4 d5 3. Nd2 c5 4. Ngf3 cxd4 5. exd5 Qxd5"] = "Bc4";
    book["1. e4 e6 2. d4 d5 3. Nd2 c5 4. Ngf3 cxd4 5. exd5 Qxd5 6. Bc4 Qd6"] = "0-0";
    book["1. e4 e6 2. d4 d5 3. Nd2 c5 4. Ngf3 cxd4 5. exd5 Qxd5 6. Bc4 Qd7"] = "0-0";
    book["1. e4 e6 2. d4 d5 3. Nd2 c5 4. Ngf3 Nc6"] = "exd5";
    book["1. e4 e6 2. d4 d5 3. Nd2 c5 4. Ngf3 Nc6 5. exd5 exd5"] = "Bb5";
    book["1. e4 e6 2. d4 d5 3. Nd2 c5 4. Ngf3 Nf6"] = "e5";
    book["1. e4 e6 2. d4 d5 3. Nd2 c5 4. Ngf3 Nf6 5. e5 Nfd7"] = "c3";
    book["1. e4 e6 2. d4 d5 3. Nd2 c5 4. Ngf3 a6"] = "dxc5";
    book["1. e4 e6 2. d4 d5 3. Nd2 c5 4. Ngf3 a6 5. dxc5 Bxc5"] = "Bd3";
    book["1. e4 e6 2. d4 d5 3. Nd2 c5 4. Ngf3 c4"] = "a4";
    book["1. e4 e6 2. d4 d5 3. Nd2 c5 4. Ngf3 dxe4"] = "Nxe4";
    book["1. e4 e6 2. d4 d5 3. Nd2 c5 4. Ngf3 dxe4 5. Nxe4 cxd4"] = "Qxd4";
    book["1. e4 e6 2. d4 d5 3. Nd2 c5 4. Ngf3 dxe4 5. Nxe4 cxd4 6. Qxd4 Qxd4"] = "Nxd4";
    book["1. e4 e6 2. d4 d5 3. Nd2 c5 4. Ngf3 Be7"] = "exd5";
    book["1. e4 e6 2. d4 d5 3. Nd2 c5 4. Ngf3 Be7 5. exd5 exd5"] = "dxc5";
    book["1. e4 e6 2. d4 d5 3. Nd2 c5 4. Ngf3 Be7 5. exd5 exd5 6. dxc5 Bxc5"] = "Nb3";


    book["1. e4 e6 2. d4 d5 3. Nd2 dxe4"] = "Nxe4";
    book["1. e4 e6 2. d4 d5 3. Nd2 Nc6"] = "Ngf3 | c3";
    book["1. e4 e6 2. d4 d5 3. Nd2 c5"] = "exd5 | Ngf3 | c3";



    // C03 French Defense: Tarrasch Variation -- BLACK
    book["1. e4 e6 2. d4 d5 3. Nd2 dxe4 4. Nxe4"] = "Nd7 | Bd7 | Nf6 | Be7";

    book["1. e4 e6 2. d4 d5 3. Nd2 dxe4 4. Nxe4 Nf6 5. Nxf6+"] = "Qxf6 | gxf6";
    book["1. e4 e6 2. d4 d5 3. Nd2 dxe4 4. Nxe4 Nf6 5. Bg5"] = "Be7 | Nbd7";
    book["1. e4 e6 2. d4 d5 3. Nd2 dxe4 4. Nxe4 Nf6 5. Bd3"] = "Nbd7 | Nxe4";
    book["1. e4 e6 2. d4 d5 3. Nd2 dxe4 4. Nxe4 Nf6 5. Ng3"] = "c5";

    book["1. e4 e6 2. d4 d5 3. Nd2 dxe4 4. Nxe4 Bd7 5. Nf3"] = "Bc6";
    book["1. e4 e6 2. d4 d5 3. Nd2 dxe4 4. Nxe4 Bd7 5. Bd3"] = "Bc6 | Nf6";
    book["1. e4 e6 2. d4 d5 3. Nd2 dxe4 4. Nxe4 Bd7 5. c4"] = "Bb4+ | Nf6";
    book["1. e4 e6 2. d4 d5 3. Nd2 dxe4 4. Nxe4 Bd7 5. Bg5"] = "Be7";
    book["1. e4 e6 2. d4 d5 3. Nd2 dxe4 4. Nxe4 Bd7 5. Bg5 Be7 6. Bxe7"] = "Nxe7";

    book["1. e4 e6 2. d4 d5 3. Nd2 dxe4 4. Nxe4 Nd7 5. Nf3"] = "Ngf6";
    book["1. e4 e6 2. d4 d5 3. Nd2 dxe4 4. Nxe4 Nd7 5. Nf3 Ngf6 6. Nxf6+"] = "Nxf6";
    book["1. e4 e6 2. d4 d5 3. Nd2 dxe4 4. Nxe4 Nd7 5. Bd3"] = "Ngf6 | c5";
    book["1. e4 e6 2. d4 d5 3. Nd2 dxe4 4. Nxe4 Nd7 5. g3"] = "Ngf6 | b6 | Be7";
    book["1. e4 e6 2. d4 d5 3. Nd2 dxe4 4. Nxe4 Nd7 5. c4"] = "Ngf6";
    book["1. e4 e6 2. d4 d5 3. Nd2 dxe4 4. Nxe4 Nd7 5. g4"] = "Ngf6 | Ndf6";

    book["1. e4 e6 2. d4 d5 3. Nd2 dxe4 4. Nxe4 Be7 5. Nf3"] = "Nf6 | Nd7";
    book["1. e4 e6 2. d4 d5 3. Nd2 dxe4 4. Nxe4 Be7 5. Bd3"] = "Nf6 | Nd7";
    book["1. e4 e6 2. d4 d5 3. Nd2 dxe4 4. Nxe4 Be7 5. g3"] = "Nf6 | Nd7";
    book["1. e4 e6 2. d4 d5 3. Nd2 dxe4 4. Nxe4 Be7 5. c3"] = "Nf6 | Nd7";




    book["1. e4 e6 2. d4 d5 3. Nd2 Be7"] = "Ngf3 | Bd3 | e5";
    book["1. e4 e6 2. d4 d5 3. Nd2 Be7 4. Ngf3"] = "Nf6";
    book["1. e4 e6 2. d4 d5 3. Nd2 Be7 4. Ngf3 Nf6"] = "e5";
    book["1. e4 e6 2. d4 d5 3. Nd2 Be7 4. Ngf3 Nf6 5. e5"] = "Nfd7";
    book["1. e4 e6 2. d4 d5 3. Nd2 Be7 4. Ngf3 Nf6 5. e5 Nfd7"] = "Bd3";
    book["1. e4 e6 2. d4 d5 3. Nd2 Be7 4. Ngf3 Nf6 5. e5 Nfd7 6. Bd3"] = "c5";
    book["1. e4 e6 2. d4 d5 3. Nd2 Be7 4. Ngf3 Nf6 5. e5 Nfd7 6. Bd3 c5"] = "c3";
    book["1. e4 e6 2. d4 d5 3. Nd2 Be7 4. Ngf3 Nf6 5. e5 Nfd7 6. Bd3 c5 7. c3"] = "Nc6 | b6";
    book["1. e4 e6 2. d4 d5 3. Nd2 Be7 4. Bd3"] = "c5";
    book["1. e4 e6 2. d4 d5 3. Nd2 Be7 4. Bd3 c5"] = "dxc5";

    book["1. e4 e6 2. d4 d5 3. Nd2 Be7 4. Bd3 c5 5. dxc5"] = "Nf6 | Nd7";

    book["1. e4 e6 2. d4 d5 3. Nd2 Be7 4. Bd3 c5 5. dxc5 Nd7 6. b4"] = "a5";
    book["1. e4 e6 2. d4 d5 3. Nd2 Be7 4. Bd3 c5 5. dxc5 Nd7 6. Ngf3"] = "Nxc5";
    book["1. e4 e6 2. d4 d5 3. Nd2 Be7 4. Bd3 c5 5. dxc5 Nd7 6. Qe2"] = "Nxc5";
    book["1. e4 e6 2. d4 d5 3. Nd2 Be7 4. Bd3 c5 5. dxc5 Nd7 6. Nb3"] = "dxe4";
    book["1. e4 e6 2. d4 d5 3. Nd2 Be7 4. Bd3 c5 5. dxc5 Nd7 6. Nb3 dxe4 7. Bxe4"] = "Ngf6";
    book["1. e4 e6 2. d4 d5 3. Nd2 Be7 4. Bd3 c5 5. dxc5 Nd7 6. Bb5"] = "dxe4";
    book["1. e4 e6 2. d4 d5 3. Nd2 Be7 4. Bd3 c5 5. dxc5 Nd7 6. Bb5 dxe4 7. Nxe4"] = "Qa5+";
    book["1. e4 e6 2. d4 d5 3. Nd2 Be7 4. Bd3 c5 5. dxc5 Nd7 6. Bb5 dxe4 7. Nxe4 Qa5+ 8. Nc3"] = "Nf6 | a6";
    book["1. e4 e6 2. d4 d5 3. Nd2 Be7 4. Bd3 c5 5. dxc5 Nd7 6. exd5"] = "exd5";
    book["1. e4 e6 2. d4 d5 3. Nd2 Be7 4. Bd3 c5 5. dxc5 Nd7 6. exd5 exd5 7. Nb3"] = "Nxc5";
    book["1. e4 e6 2. d4 d5 3. Nd2 Be7 4. Bd3 c5 5. dxc5 Nd7 6. exd5 exd5 7. Nb3 Nxc5 8. Nxc5"] = "Bxc5";
    book["1. e4 e6 2. d4 d5 3. Nd2 Be7 4. Bd3 c5 5. dxc5 Nd7 6. exd5 exd5 7. Nb3 Nxc5 8. Nxc5 Bxc5 9. Nf3"] = "Nf6";
    book["1. e4 e6 2. d4 d5 3. Nd2 Be7 4. Bd3 c5 5. dxc5 Nd7 6. exd5 exd5 7. b4"] = "a5";
    book["1. e4 e6 2. d4 d5 3. Nd2 Be7 4. Bd3 c5 5. dxc5 Nd7 6. exd5 exd5 7. Ngf3"] = "Nxc5";
    book["1. e4 e6 2. d4 d5 3. Nd2 Be7 4. Bd3 c5 5. dxc5 Nd7 6. exd5 exd5 7. Ngf3 Nxc5 8. Nb3"] = "Nxd3+";
    book["1. e4 e6 2. d4 d5 3. Nd2 Be7 4. Bd3 c5 5. dxc5 Nd7 6. exd5 exd5 7. Ngf3 Nxc5 8. Nb3 Nxd3+ 9. Qxd3"] = "Nf6";


    book["1. e4 e6 2. d4 d5 3. Nd2 Be7 4. e5"] = "c5";
    book["1. e4 e6 2. d4 d5 3. Nd2 Be7 4. e5 c5"] = "Qg4";
    book["1. e4 e6 2. d4 d5 3. Nd2 Be7 4. e5 c5 5. Qg4"] = "Kf8 | g6";


    // Caro-Kann defense (B10)
    book["1. e4 c6"] = "d4 | Nc3 | c4 | d3 | Nf3";
    book["1. e4 c6 2. d4"] = "d5 | g6 | d6";
    book["1. e4 c6 2. Nf3"] = "d5 | g6";
    book["1. e4 c6 2. Nf3 d5"] = "Nc3 | e5 | exd5";
    book["1. e4 c6 2. Nf3 d5 3. Nc3"] = "Bg4 | Nf6";
    book["1. e4 c6 2. Nf3 g6"] = "d4 | c4";
    book["1. e4 c6 2. Nf3 g6 3. d4"] = "Bg7 | d5";
    book["1. e4 c6 2. Nf3 d5 3. exd5"] = "cxd5";
    book["1. e4 c6 2. Nf3 d5 3. exd5 cxd5"] = "d4 | Ne5 | Bb5+";
    book["1. e4 c6 2. Nf3 d5 3. exd5 cxd5 4. d4"] = "Nf6 | Nc6";
    book["1. e4 c6 2. Nf3 d5 3. exd5 cxd5 4. Ne5"] = "Nf6 | Nc6";
    book["1. e4 c6 2. Nf3 d5 3. exd5 cxd5 4. Bb5+"] = "Bd7";
    book["1. e4 c6 2. Nf3 d5 3. exd5 cxd5 4. Bb5+ Bd7"] = "Bxd7";
    book["1. e4 c6 2. Nf3 d5 3. exd5 cxd5 4. Bb5+ Bd7 5. Bxd7"] = "Nxd7";
    book["1. e4 c6 2. Nf3 d5 3. exd5 cxd5 4. Bb5+ Bd7 5. Bxd7 Nxd7"] = "Nc3";
    book["1. e4 c6 2. Nf3 d5 3. exd5 cxd5 4. Bb5+ Bd7 5. Bxd7 Nxd7 6. Nc3"] = "Ngf6 | e6";

    book["1. e4 c6 2. Nf3 g6 3. Be2"] = "d5";
    book["1. e4 c6 2. Nf3 g6 3. Be2 d5 4. exd5"] = "cxd5";
    book["1. e4 c6 2. Nf3 g6 3. Be2 d5 4. exd5 cxd5 5. d4"] = "Nf6";
    book["1. e4 c6 2. Nf3 g6 3. Be2 d5 4. exd5 cxd5 5. h3"] = "d4";
    book["1. e4 c6 2. Nf3 g6 3. Be2 d5 4. exd5 cxd5 5. h3 d4 6. Bb5+"] = "Nc6";
    book["1. e4 c6 2. Nf3 g6 3. Be2 d5 4. exd5 cxd5 5. h3 d4 6. Ne5"] = "Bg7";
    book["1. e4 c6 2. Nf3 g6 3. Be2 d5 4. exd5 cxd5 5. h3 d4 6. Ne5 Bg7 7. Nf3"] = "Nf6";
    book["1. e4 c6 2. Nf3 g6 3. Be2 d5 4. exd5 cxd5 5. h3 d4 6. Ne5 Bg7 7. Bb5+"] = "Nd7";

    book["1. e4 c6 2. Nf3 g6 3. Be2 d5 4. e5"] = "c5";
    book["1. e4 c6 2. Nf3 g6 3. Be2 d5 4. e5 c5 5. 0-0"] = "Nc6";
    book["1. e4 c6 2. Nf3 g6 3. Be2 d5 4. e5 c5 5. 0-0 Nc6 6. h3"] = "e6";



    book["1. e4 c6 2. Nf3 d5 3. exd5 cxd5 4. d4 Nf6 5. Ne5"] = "Nc6 | Bg4";
    book["1. e4 c6 2. Nf3 d5 3. exd5 cxd5 4. d4 Nf6 5. Bf4"] = "Nc6";
    book["1. e4 c6 2. Nf3 d5 3. exd5 cxd5 4. d4 Nf6 5. Bd3"] = "g6 | Bf5 | Nc6";
    book["1. e4 c6 2. Nf3 d5 3. exd5 cxd5 4. d4 Nf6 5. c3"] = "Nc6 | g6 | Bf5";


    book["1. e4 c6 2. c4"] = "d5 | e5";


    book["1. e4 c6 2. Nf3 d5 3. e5"] = "Bg4 | Bf5";

    book["1. e4 c6 2. Nf3 g6 3. d4 d5"] = "e5 | Nc3";
    book["1. e4 c6 2. Nf3 g6 3. d4 d5 4. e5"] = "Bg4 | Bg7";
    book["1. e4 c6 2. Nf3 g6 3. d4 d5 4. Nc3"] = "Bg7 | Bg4";

    book["1. e4 c6 2. Nf3 g6 3. d4 d5 4. e5 Bg4 5. h3"] = "Bxf3";
    book["1. e4 c6 2. Nf3 g6 3. d4 d5 4. e5 Bg4 5. h3 Bxf3 6. Qxf3"] = "e6";
    book["1. e4 c6 2. Nf3 g6 3. d4 d5 4. e5 Bg4 5. Be2"] = "Bxf3";
    book["1. e4 c6 2. Nf3 g6 3. d4 d5 4. e5 Bg4 5. Be2 Bxf3 6. Bxf3"] = "e6";
    book["1. e4 c6 2. Nf3 g6 3. d4 d5 4. e5 Bg4 5. Nbd2"] = "e6";
    book["1. e4 c6 2. Nf3 g6 3. d4 d5 4. e5 Bg4 5. Bd3"] = "c5";

    book["1. e4 c6 2. Nf3 g6 3. d4 Bg7"] = "Nc3 | Bd3 | c3";
    book["1. e4 c6 2. Nf3 g6 3. d4 Bg7 4. Nc3"] = "d5 | d6";
    book["1. e4 c6 2. Nf3 g6 3. d4 Bg7 4. Bd3"] = "d5 | d6";
    book["1. e4 c6 2. Nf3 g6 3. d4 Bg7 4. c3"] = "d5 | d6";

    book["1. e4 c6 2. Nf3 g6 3. Bc4"] = "d5";
    book["1. e4 c6 2. Nf3 g6 3. Bc4 d5 4. exd5"] = "cxd5";
    book["1. e4 c6 2. Nf3 g6 3. Bc4 d5 4. exd5 cxd5 5. Bb5+"] = "Bd7";

    book["1. e4 c6 2. Nc3"] = "d5 | g6";
    book["1. e4 c6 2. Nc3 d5"] = "Nf3 | d4";
    book["1. e4 c6 2. Nc3 g6"] = "d4 | Bc4 | Nf3";

    book["1. e4 c6 2. d4 d5"] = "Nc3 | exd5 | e5";
    book["1. e4 c6 2. d4 d5 3. Nc3"] = "dxe4 | g6";

    book["1. e4 c6 2. d4 d5 3. Nc3 g6 4. exd5"] = "cxd5";


    // B10 Caro-Kann, anti-Caro-Kann defence -- WHITE
    book["1. e4 c6 2. c4 e5"] = "Nf3 | Nc3";
    book["1. e4 c6 2. c4 g6"] = "d4 | Nc3";
    book["1. e4 c6 2. c4 g6 3. d4 Bg7"] = "Nf3 | Nc3";
    book["1. e4 c6 2. c4 e6"] = "Nc3 | d4";
    book["1. e4 c6 2. c4 d6"] = "d4 | Nc3";
    book["1. e4 c6 2. c4 d5"] = "exd5 | cxd5";
    book["1. e4 c6 2. c4 d5 3. exd5 Nf6"] = "d4 | Nf3 | Nc3";
    book["1. e4 c6 2. c4 d5 3. exd5 cxd5"] = "cxd5";
    book["1. e4 c6 2. c4 d5 3. exd5 cxd5 4. cxd5 Nf6"] = "Bb5+";
    book["1. e4 c6 2. c4 d5 3. exd5 cxd5 4. cxd5 Nf6 5. Bb5+ Bd7"] = "Bc4";
    book["1. e4 c6 2. c4 d5 3. exd5 cxd5 4. cxd5 Nf6 5. Bb5+ Bd7 6. Bc4 Na6"] = "Nc3";
    book["1. e4 c6 2. c4 d5 3. exd5 cxd5 4. cxd5 Nf6 5. Bb5+ Bd7 6. Bc4 Qc7"] = "d3";
    book["1. e4 c6 2. c4 d5 3. exd5 cxd5 4. cxd5 Nf6 5. Bb5+ Bd7 6. Bc4 b5"] = "Bb3";
    book["1. e4 c6 2. c4 d5 3. exd5 cxd5 4. cxd5 Nf6 5. Bb5+ Nbd7"] = "d4";
    book["1. e4 c6 2. c4 d5 3. exd5 cxd5 4. cxd5 Qxd5"] = "Nc3";


    book["1. e4 c6 2. c4 d5 3. cxd5 cxd5"] = "exd5 | e5";
    book["1. e4 c6 2. c4 d5 3. cxd5 cxd5 4. exd5 a6"] = "Nc3";
    book["1. e4 c6 2. c4 d5 3. cxd5 cxd5 4. exd5 Qxd5"] = "d4 | Nf3";
    book["1. e4 c6 2. c4 d5 3. cxd5 cxd5 4. exd5 Nf6"] = "Nf3 | Nc3 | d4";



    // B10 Caro-Kann, anti-Caro-Kann defence -- BLACK
    book["1. e4 c6 2. c4 d5 3. exd5"] = "cxd5";
    book["1. e4 c6 2. c4 d5 3. exd5 cxd5 4. d4"] = "Nf6";
    book["1. e4 c6 2. c4 d5 3. exd5 cxd5 4. d4 Nf6 5. cxd5"] = "Nxd5";
    book["1. e4 c6 2. c4 d5 3. exd5 cxd5 4. d4 Nf6 5. Nc3"] = "Nc6";
    book["1. e4 c6 2. c4 d5 3. exd5 cxd5 4. d4 Nf6 5. Nc3 Nc6 6. Nf3"] = "Bg4";
    book["1. e4 c6 2. c4 d5 3. exd5 cxd5 4. d4 Nf6 5. Nc3 Nc6 6. cxd5"] = "Nxd5";
    book["1. e4 c6 2. c4 d5 3. exd5 cxd5 4. d4 Nf6 5. Nc3 Nc6 6. Bg5"] = "cxd4";
    book["1. e4 c6 2. c4 d5 3. exd5 cxd5 4. d4 Nf6 5. Nc3 Nc6 6. Bg5 cxd4 7. Bxc4"] = "h6";
    book["1. e4 c6 2. c4 d5 3. exd5 cxd5 4. d4 Nf6 5. Nc3 Nc6 6. Bg5 cxd4 7. d5"] = "Ne5";
    book["1. e4 c6 2. c4 d5 3. exd5 cxd5 4. d4 Nf6 5. Nc3 Nc6 6. Bg5 cxd4 7. d5 Ne5 8. Nf3"] = "Bg4";
    book["1. e4 c6 2. c4 d5 3. exd5 cxd5 4. d4 Nf6 5. Nc3 Nc6 6. Bg5 cxd4 7. d5 Ne5 8. Qd4"] = "h6";
    book["1. e4 c6 2. c4 d5 3. exd5 cxd5 4. d4 Nf6 5. Nc3 Nc6 6. Bg5 cxd4 7. d5 Ne5 8. Qd4 h6 9. Bf4"] = "Ng6";



    // Caro-Kann, advance variation (B12)
    book["1. e4 c6 2. d4 d5 3. e5"] = "Bf5 | c5";
    book["1. e4 c6 2. d4 d5 3. e5 Bf5"] = "Nf3 | Nc3";
    book["1. e4 c6 2. d4 d5 3. e5 c5"] = "dxc5";
    book["1. e4 c6 2. d4 d5 3. e5 c5 4. dxc5"] = "Nc6 | e6";

    book["1. e4 c6 2. d4 d5 3. e5 Bf5 4. Nf3"] = "e6";
    book["1. e4 c6 2. d4 d5 3. e5 Bf5 4. Nc3"] = "e6";

    book["1. e4 c6 2. d4 d5 3. e5 Bf5 4. Bf4"] = "Qb6";
    book["1. e4 c6 2. d4 d5 3. e5 Bf5 4. Bf4 Qb6 5. b3"] = "e6";
    book["1. e4 c6 2. d4 d5 3. e5 Bf5 4. Bf4 Qb6 5. Bc1"] = "e6";
    
    book["1. e4 c6 2. d4 d6"] = "Nc3 | Nf3 | f4 | c4";


    // B06 Rat Defense: Accelerated Gurgenidze -- BLACK
    book["1. e4 c6 2. d4 d6 3. Nc3"] = "Nf6 | g6";

    book["1. e4 c6 2. d4 d6 3. Nc3 Nf6 4. f4"] = "Qa5 | g6";
    book["1. e4 c6 2. d4 d6 3. Nc3 Nf6 4. Nf3"] = "Bg4 | g6";

    book["1. e4 c6 2. d4 d6 3. Nc3 g6 4. f4"] = "d5 | Bg7";
    book["1. e4 c6 2. d4 d6 3. Nc3 g6 4. Nf3"] = "Bg7 | Nf6";
    book["1. e4 c6 2. d4 d6 3. Nc3 g6 4. a4"] = "Bg7 | Nf6";
    book["1. e4 c6 2. d4 d6 3. Nc3 g6 4. Bc4"] = "Nf6 | Bg7";
    book["1. e4 c6 2. d4 d6 3. Nc3 g6 4. g3"] = "Bg7";
    book["1. e4 c6 2. d4 d6 3. Nc3 g6 4. Be2"] = "Bg7";
    book["1. e4 c6 2. d4 d6 3. Nc3 g6 4. Be3"] = "Bg7 | Nf6";


    book["1. e4 c6 2. d4 d6 3. Nf3"] = "Bg4 | Nf6";
    book["1. e4 c6 2. d4 d6 3. f4"] = "g6 | Nf6";
    book["1. e4 c6 2. d4 d6 3. c4"] = "Nf6 | g6 | e5 | Nd7";

    book["1. e4 c6 2. d4 d6 3. Nf3 Nf6 4.Bd3"] = "Bg4";



    // Caro-Kann, exchange variation (B13)
    book["1. e4 c6 2. d4 d5 3. exd5"] = "cxd5";
    book["1. e4 c6 2. d4 d5 3. exd5 cxd5"] = "c4 | c3 | Nf3 | Bd3";

    book["1. e4 c6 2. d4 d5 3. exd5 cxd5 4. c4"] = "Nf6";
    book["1. e4 c6 2. d4 d5 3. exd5 cxd5 4. c4 Nf6 5. Nf3"] = "Nc6";
    book["1. e4 c6 2. d4 d5 3. exd5 cxd5 4. c4 Nf6 5. Nc3"] = "Nc6";
    book["1. e4 c6 2. d4 d5 3. exd5 cxd5 4. c4 Nf6 5. Nc3 Nc6 6. Nf3"] = "Bg4";
    book["1. e4 c6 2. d4 d5 3. exd5 cxd5 4. c4 Nf6 5. Nc3 Nc6 6. Qb3"] = "Nxd4";
    book["1. e4 c6 2. d4 d5 3. exd5 cxd5 4. c4 Nf6 5. Nc3 Nc6 6. Qb3 Nxd4 7. Qa4+"] = "Bd7";
    book["1. e4 c6 2. d4 d5 3. exd5 cxd5 4. c4 Nf6 5. Nc3 Nc6 6. Qb3 Nxd4 7. Qa4+ Bd7 8. Qd1"] = "e5";

    book["1. e4 c6 2. d3"] = "d5 | e5 | g6";
    book["1. e4 c6 2. d3 d5"] = "Nd2";
    book["1. e4 c6 2. d3 d5 3. Nd2"] = "e5 | g6";
    book["1. e4 c6 2. d3 e5"] = "Nf3 | g3";
    book["1. e4 c6 2. d3 g6"] = "g3 | Nf3";

    book["1. e4 c6 2. d3 d5 3. Nd2 c5"] = "exd5";
    book["1. e4 c6 2. d3 d5 3. Nd2 c5 4. exd5 Qxd5"] = "Ne2";
    book["1. e4 c6 2. d3 d5 3. Nd2 c5 4. exd5 Nf6"] = "c4";

    book["1. e4 c6 2. d3 g6 3. c4"] = "d5";
    book["1. e4 c6 2. d3 g6 3. c4 d5 4. Nd2"] = "Bg7";


    // B13 Caro-Kann Defense: Exchange Variation -- WHITE
    book["1. e4 c6 2. d4 d5 3. exd5 cxd5 4. Nf3 Nc6"] = "c4 | Bf4";
    book["1. e4 c6 2. d4 d5 3. exd5 cxd5 4. Nf3 Nc6 5. c4 Nf6"] = "c5 | Nc3 | h3";
    book["1. e4 c6 2. d4 d5 3. exd5 cxd5 4. Nf3 Nc6 5. c4 e6"] = "Nc3 | c5 | cxd5";
    book["1. e4 c6 2. d4 d5 3. exd5 cxd5 4. Nf3 Nc6 5. c4 Bg4"] = "cxd5 | Be3";
    book["1. e4 c6 2. d4 d5 3. exd5 cxd5 4. Nf3 Nc6 5. Bf4 Bg4"] = "c3 | Nbd2 | Be2";
    book["1. e4 c6 2. d4 d5 3. exd5 cxd5 4. Nf3 Nc6 5. Bf4 Bf5"] = "c4 | c3 | Bd3";
    book["1. e4 c6 2. d4 d5 3. exd5 cxd5 4. Nf3 Nc6 5. Bf4 Nf6"] = "c3 | Nbd2 | Bd3";


    // Caro-Kann, closed variation (B10)
    book["1. e4 c6 2. d3 g6 3. g3"] = "Bg7";
    book["1. e4 c6 2. d3 g6 3. g3 Bg7"] = "Bg2";
    book["1. e4 c6 2. d3 g6 3. g3 Bg7 4. Bg2"] = "d5 | d6 | e5";
    book["1. e4 c6 2. d3 g6 3. Nf3"] = "Bg7";
    book["1. e4 c6 2. d3 g6 3. Nf3 Bg7"] = "g3 | Nbd2 | Be2";

    book["1. e4 c6 2. d3 d5 3. Nd2 e5"] = "Ngf3 | g3";
    book["1. e4 c6 2. d3 d5 3. Nd2 e5 4. Ngf3"] = "Bd6 | Nd7";
    book["1. e4 c6 2. d3 d5 3. Nd2 e5 4. g3"] = "Nf6";
    book["1. e4 c6 2. d3 d5 3. Nd2 e5 4. g3 Nf6"] = "Bg2 | Ngf3";

    book["1. e4 c6 2. d3 d5 3. Nd2 g6"] = "Ngf3 | g3";
    book["1. e4 c6 2. d3 d5 3. Nd2 g6 4. Ngf3"] = "Bg7";
    book["1. e4 c6 2. d3 d5 3. Nd2 g6 4. Ngf3 Bg7"] = "g3 | Be2";
    book["1. e4 c6 2. d3 d5 3. Nd2 g6 4. g3"] = "Bg7";
    book["1. e4 c6 2. d3 d5 3. Nd2 g6 4. g3 Bg7"] = "Bg2";
    book["1. e4 c6 2. d3 d5 3. Nd2 g6 4. g3 Bg7 5. Bg2"] = "e5 | Nf6 | dxe4";


    // Caro-Kann two-knights (B11)
    book["1. e4 c6 2. Nf3 d5 3. Nc3 Bg4"] = "h3 | Be2 | d4";
    book["1. e4 c6 2. Nf3 d5 3. Nc3 Bg4 4. h3"] = "Bxf3";
    book["1. e4 c6 2. Nf3 d5 3. Nc3 Bg4 4. h3 Bxf3"] = "Qxf3";
    book["1. e4 c6 2. Nf3 d5 3. Nc3 Bg4 4. h3 Bxf3 5. Qxf3"] = "e6 | Nf6";
    book["1. e4 c6 2. Nf3 d5 3. Nc3 Bg4 4. Be2"] = "e6 | Nf6";
    book["1. e4 c6 2. Nf3 d5 3. Nc3 Bg4 4. d4"] = "e6 | Nf6";

    book["1. e4 c6 2. Nf3 d5 3. Nc3 Bg4 4. d4 e6"] = "h3 | Be2";
    book["1. e4 c6 2. Nf3 d5 3. Nc3 Bg4 4. d4 Nf6"] = "e5";
    book["1. e4 c6 2. Nf3 d5 3. Nc3 Bg4 4. d4 Nf6 5. e5"] = "Ne4";
    book["1. e4 c6 2. Nf3 d5 3. Nc3 Bg4 4. d4 Nf6 5. e5 Ne4"] = "Bd3 | h3";

    book["1. e4 c6 2. Nf3 d5 3. Nc3 Bg4 4. Be2 Nf6"] = "e5 | h3";
    book["1. e4 c6 2. Nf3 d5 3. Nc3 Bg4 4. Be2 Nf6 5. e5"] = "Nfd7";
    book["1. e4 c6 2. Nf3 d5 3. Nc3 Bg4 4. Be2 Nf6 5. e5 Nfd7"] = "d4";
    book["1. e4 c6 2. Nf3 d5 3. Nc3 Bg4 4. Be2 Nf6 5. e5 Nfd7 6. d4"] = "e6";
    book["1. e4 c6 2. Nf3 d5 3. Nc3 Bg4 4. Be2 Nf6 5. e5 Nfd7 6. d4 e6"] = "Ng5 | 0-0";
    book["1. e4 c6 2. Nf3 d5 3. Nc3 Bg4 4. Be2 Nf6 5. h3"] = "Bxf3 | Bh5";


    // Caro-Kann defense (B12)
    book["1. e4 c6 2. d4 g6"] = "Nf3 | Nc3 | c4";
    book["1. e4 c6 2. d4 g6 3. Nc3"] = "d5 | Bg7";
    book["1. e4 c6 2. d4 g6 3. Nc3 d5"] = "Nf3 | h3 | e5";
    book["1. e4 c6 2. d4 g6 3. Nc3 Bg7"] = "Nf3 | f4 | Bc4 | Be3";

    book["1. e4 c6 2. d4 g6 3. Bf4"] = "Bg7";

    book["1. e4 c6 2. Bc4"] = "d5";
    book["1. e4 c6 2. Bc4 d5"] = "exd5 | Bb3";
    book["1. e4 c6 2. Bc4 d5 3. exd5"] = "cxd5";
    book["1. e4 c6 2. Bc4 d5 3. exd5 cxd5"] = "Bb3 | Bb5+";
    book["1. e4 c6 2. Bc4 d5 3. exd5 cxd5 4. Bb3"] = "Nf6";
    book["1. e4 c6 2. Bc4 d5 3. exd5 cxd5 4. Bb5+"] = "Bd7 | Nc6";
    book["1. e4 c6 2. Bc4 d5 3. Bb3"] = "dxe4";
    book["1. e4 c6 2. Bc4 d5 3. Bb3 dxe4"] = "Qh5";
    book["1. e4 c6 2. Bc4 d5 3. Bb3 dxe4 4. Qh5"] = "g6";

    book["1. e4 c6 2. d4 g6 3. e5"] = "d6 | Bg7";
    book["1. e4 c6 2. d4 g6 3. e5 d6 4. Nf3"] = "dxe5";
    book["1. e4 c6 2. d4 g6 3. e5 d6 4. Nf3 dxe5 5. Nxe5"] = "Nd7";
    book["1. e4 c6 2. d4 g6 3. e5 d6 4. Nf3 dxe5 5. Nxe5 Nd7 6. Nxf7"] = "Kxf7";
    book["1. e4 c6 2. d4 g6 3. e5 d6 4. Nf3 dxe5 5. Nxe5 Nd7 6. Nxf7 Kxf7 7. Qf3"] = "Ngf6";
    book["1. e4 c6 2. d4 g6 3. e5 d6 4. Nf3 dxe5 5. Nxe5 Nd7 6. Nxf7 Kxf7 7. Bc4"] = "Kg7";

    book["1. e4 c6 2. d4 g6 3. Nf3"] = "Bg7";
    book["1. e4 c6 2. d4 g6 3. Nf3 Bg7 Nc3"] = "d6";
    book["1. e4 c6 2. d4 g6 3. Nf3 Bg7 h3"] = "d5";
    book["1. e4 c6 2. d4 g6 3. Nf3 Bg7 c3"] = "d5";
    book["1. e4 c6 2. d4 g6 3. Nf3 Bg7 Bd3"] = "d6";




    // Queen's pawn game (A45)
    book["1. d4 Nf6"] = "c4 | Nf3 | Bg5 | Nc3";

    book["1. d4 Nf6 2. e3"] = "g6 | d5 | e6";

    book["1. d4 Nf6 2. e3 e6 3. c4"] = "b6 | d5";

    book["1. d4 Nf6 2. c3"] = "g6 | d5 | e6 | d6 | b6";
    book["1. d4 Nf6 2. c3 d5 3. Bg5"] = "c5 | Ne4 | Nbd7 | Nc6 | e6";

    book["1. d4 Nf6 2. c4 e5"] = "dxe5";
    book["1. d4 Nf6 2. c4 e5 3. dxe5 Ng4"] = "e4";
    book["1. d4 Nf6 2. c4 e5 3. dxe5 Ng4 4. e4 Nxe5"] = "f4";
    book["1. d4 Nf6 2. c4 e5 3. dxe5 Ng4 4. e4 Nxe5 5. f4 Ng6"] = "Nc3";
    book["1. d4 Nf6 2. c4 e5 3. dxe5 Ng4 4. e4 Nxe5 5. f4 Nec6"] = "Nc3";

    book["1. d4 Nf6 2. c4 e5 3. dxe5 Ng4 4. e4 Nxe5 5. f4 Nec6 6. Nc3 Bc5"] = "Na4";
    book["1. d4 Nf6 2. c4 e5 3. dxe5 Ng4 4. e4 Nxe5 5. f4 Nec6 6. Nc3 Bc5 7. Na4 Bb4+"] = "Bd2";
    book["1. d4 Nf6 2. c4 e5 3. dxe5 Ng4 4. e4 Nxe5 5. f4 Nec6 6. Nc3 Bc5 7. Na4 b6"] = "Nxc5";
    book["1. d4 Nf6 2. c4 e5 3. dxe5 Ng4 4. e4 Nxe5 5. f4 Nec6 6. Nc3 Bc5 7. Na4 b6 8. Nxc5 bxc5"] = "Nf3 | Bd3";

    book["1. d4 Nf6 2. c4 e5 3. dxe5 Ng4 4. e4 Nxe5 5. f4 Nec6 6. Nc3 Bc5 7. Na4 Bxg1"] = "Rxg1";
    book["1. d4 Nf6 2. c4 e5 3. dxe5 Ng4 4. e4 Nxe5 5. f4 Nec6 6. Nc3 Bc5 7. Na4 Bxg1 8. Rxg1 d6"] = "Nc3";
    book["1. d4 Nf6 2. c4 e5 3. dxe5 Ng4 4. e4 Nxe5 5. f4 Nec6 6. Nc3 Bc5 7. Na4 Bxg1 8. Rxg1 a5"] = "Be3";
    book["1. d4 Nf6 2. c4 e5 3. dxe5 Ng4 4. e4 Nxe5 5. f4 Nec6 6. Nc3 Bc5 7. Na4 Bxg1 8. Rxg1 Na6"] = "Nc3 | Be3";
    book["1. d4 Nf6 2. c4 e5 3. dxe5 Ng4 4. e4 Nxe5 5. f4 Nec6 6. Nc3 Bc5 7. Na4 Bxg1 8. Rxg1 0-0"] = "Be3";
    book["1. d4 Nf6 2. c4 e5 3. dxe5 Ng4 4. e4 Nxe5 5. f4 Nec6 6. Nc3 Bc5 7. Na4 Bxg1 8. Rxg1 Qh4+"] = "g3";
    book["1. d4 Nf6 2. c4 e5 3. dxe5 Ng4 4. e4 Nxe5 5. f4 Nec6 6. Nc3 Bc5 7. Na4 Bxg1 8. Rxg1 Qh4+ 9. g3 Qe7"] = "Nc3";
    book["1. d4 Nf6 2. c4 e5 3. dxe5 Ng4 4. e4 Nxe5 5. f4 Nec6 6. Nc3 Bc5 7. Na4 Bxg1 8. Rxg1 Qh4+ 9. g3 Qxh2"] = "Rg2";
    book["1. d4 Nf6 2. c4 e5 3. dxe5 Ng4 4. e4 Nxe5 5. f4 Nec6 6. Nc3 Bc5 7. Na4 Bxg1 8. Rxg1 Qh4+ 9. g3 Qxh2 10. Rg2 Qh1"] = "Be3 | Nc3";
    book["1. d4 Nf6 2. c4 e5 3. dxe5 Ng4 4. e4 Nxe5 5. f4 Nec6 6. Nc3 Bc5 7. Na4 Bxg1 8. Rxg1 Qh4+ 9. g3 Qxh2 10. Rg2 Qh6"] = "Nc3";
    book["1. d4 Nf6 2. c4 e5 3. dxe5 Ng4 4. e4 Nxe5 5. f4 Nec6 6. Nc3 Bc5 7. Na4 Bxg1 8. Rxg1 Qh4+ 9. g3 Qxh2 10. Rg2 Qh3"] = "Nc3";
    book["1. d4 Nf6 2. c4 e5 3. dxe5 Ng4 4. e4 Nxe5 5. f4 Nec6 6. Nc3 Bc5 7. Na4 Bxg1 8. Rxg1 Qh4+ 9. g3 Qxh2 10. Rg2 Qh3 11. Nc3 d6"] = "f5";
    book["1. d4 Nf6 2. c4 e5 3. dxe5 Ng4 4. e4 Nxe5 5. f4 Nec6 6. Nc3 Bc5 7. Na4 Bxg1 8. Rxg1 Qh4+ 9. g3 Qxh2 10. Rg2 Qh3 11. Nc3 d6 12. f5 0-0"] = "Bf4";
    book["1. d4 Nf6 2. c4 e5 3. dxe5 Ng4 4. e4 Nxe5 5. f4 Nec6 6. Nc3 Bc5 7. Na4 Bxg1 8. Rxg1 Qh4+ 9. g3 Qxh2 10. Rg2 Qh3 11. Nc3 d6 12. f5 Ne5"] = "Bf4";
    book["1. d4 Nf6 2. c4 e5 3. dxe5 Ng4 4. e4 Nxe5 5. f4 Nec6 6. Nc3 Bc5 7. Na4 Bxg1 8. Rxg1 Qh4+ 9. g3 Qxh2 10. Rg2 Qh3 11. Nc3 d6 12. f5 0-0 13. Bf4 Re8"] = "Kf2";
    book["1. d4 Nf6 2. c4 e5 3. dxe5 Ng4 4. e4 Nxe5 5. f4 Nec6 6. Nc3 Bc5 7. Na4 Bxg1 8. Rxg1 Qh4+ 9. g3 Qxh2 10. Rg2 Qh3 11. Nc3 d6 12. f5 0-0 13. Bf4 Re8 14. Kf2 Bxf5"] = "exf5";
    book["1. d4 Nf6 2. c4 e5 3. dxe5 Ng4 4. e4 Nxe5 5. f4 Nec6 6. Nc3 Bc5 7. Na4 Bxg1 8. Rxg1 Qh4+ 9. g3 Qxh2 10. Rg2 Qh3 11. Nc3 d6 12. f5 0-0 13. Bf4 Re8 14. Kf2 Bxf5 15. exf5 Qxf5"] = "Nd5";
    book["1. d4 Nf6 2. c4 e5 3. dxe5 Ng4 4. e4 Nxe5 5. f4 Nec6 6. Nc3 Bc5 7. Na4 Bxg1 8. Rxg1 Qh4+ 9. g3 Qxh2 10. Rg2 Qh3 11. Nc3 d6 12. f5 0-0 13. Bf4 Re8 14. Kf2 Ne5"] = "Kg1";
    book["1. d4 Nf6 2. c4 e5 3. dxe5 Ng4 4. e4 Nxe5 5. f4 Nec6 6. Nc3 Bc5 7. Na4 Bxg1 8. Rxg1 Qh4+ 9. g3 Qxh2 10. Rg2 Qh3 11. Nc3 d6 12. f5 0-0 13. Bf4 Re8 14. Kf2 Ne5 15. Kg1 Bxf5"] = "Rf2";
    book["1. d4 Nf6 2. c4 e5 3. dxe5 Ng4 4. e4 Nxe5 5. f4 Nec6 6. Nc3 Bc5 7. Na4 Bxg1 8. Rxg1 Qh4+ 9. g3 Qxh2 10. Rg2 Qh3 11. Nc3 d6 12. f5 0-0 13. Bf4 Re8 14. Kf2 Ne5 15. Kg1 Ng4"] = "Be2";
    book["1. d4 Nf6 2. c4 e5 3. dxe5 Ng4 4. e4 Nxe5 5. f4 Nec6 6. Nc3 Bc5 7. Na4 Bxg1 8. Rxg1 Qh4+ 9. g3 Qxh2 10. Rg2 Qh3 11. Nc3 d6 12. f5 0-0 13. Bf4 Re8 14. Kf2 Ne5 15. Kg1 Ng4 16. Be2 Bxf5"] = "exf5";
    book["1. d4 Nf6 2. c4 e5 3. dxe5 Ng4 4. e4 Nxe5 5. f4 Nec6 6. Nc3 Bc5 7. Na4 Bxg1 8. Rxg1 Qh4+ 9. g3 Qxh2 10. Rg2 Qh3 11. Nc3 d6 12. f5 0-0 13. Bf4 Re8 14. Kf2 Ne5 15. Kg1 Ng4 16. Be2 Bxf5 17. exf5 Nf6"] = "g4";



    // Queen's pawn game (A50)
    book["1. d4 Nf6 2. c4"] = "e6 | g6 | c5 | d6 | c6";
    book["1. d4 Nf6 2. c4 e6"] = "Nc3 | Nf3 | g3";
    book["1. d4 Nf6 2. c4 g6"] = "Nc3 | Nf3 | g3 | f3";
    book["1. d4 Nf6 2. c4 g6 3. Nf3"] = "Bg7 | c5";
    book["1. d4 Nf6 2. c4 g6 3. g3"] = "Bg7 | c6";
    book["1. d4 Nf6 2. c4 g6 3. f3"] = "Bg7 | d5";
    book["1. d4 Nf6 2. c4 g6 3. Nc3"] = "Bg7 | d5";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 Bg7"] = "e4 | Nf3 | g3 | Bg5";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5"] = "cxd5 | Nf3 | Bf4 | Bg5 | e3";



    // E60 King's Indian Defense: Normal Variation, King's Knight Variation -- BLACK
    book["1. d4 Nf6 2. c4 g6 3. Nf3 Bg7 4. Nc3"] = "d5";
    book["1. d4 Nf6 2. c4 g6 3. Nf3 Bg7 4. e3"] = "0-0 | a6";
    book["1. d4 Nf6 2. c4 g6 3. Nf3 Bg7 4. b4"] = "a5 | 0-0";
    book["1. d4 Nf6 2. c4 g6 3. Nf3 Bg7 4. Bf4"] = "c5";
    book["1. d4 Nf6 2. c4 g6 3. Nf3 Bg7 4. g3"] = "0-0 | c6";
    book["1. d4 Nf6 2. c4 g6 3. Nf3 Bg7 4. g3 0-0 5. Nc3"] = "d5 | c6";
    book["1. d4 Nf6 2. c4 g6 3. Nf3 Bg7 4. g3 0-0 5. b3"] = "c5 | d5";
    book["1. d4 Nf6 2. c4 g6 3. Nf3 Bg7 4. g3 0-0 5. Bg2"] = "c6 | c5";




    // King's Indian (E70)
    book["1. d4 Nf6 2. c4 g6 3. Nc3 Bg7 4. e4"] = "d6 | 0-0";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 Bg7 4. e4 0-0 5. Nf3"] = "d6";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 Bg7 4. e4 0-0 5. Be2"] = "d6";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 Bg7 4. e4 0-0 5. f3"] = "d6";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 Bg7 4. e4 0-0 5. Be3"] = "d6";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 Bg7 4. e4 0-0 5. Bd3"] = "d6";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 Bg7 4. e4 0-0 5. e5"] = "Ne8";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 Bg7 4. e4 0-0 5. e5 Ne8 6. Nf3"] = "d6";


    // Grünfeld Defense (D85)
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. cxd5 Nxd5"] = "e4";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. cxd5 Nxd5 5. e4 Nxc3"] = "bxc3";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. cxd5 Nxd5 5. e4 Nxc3 6. bxc3 Bg7"] = "Bc4 | Nf3";

    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. Nf3"] = "Bg7";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. Nf3 Bg7 5. cxd5"] = "Nxd5";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. Nf3 Bg7 5. Bg5"] = "Ne4";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. Nf3 Bg7 5. Qb3"] = "dxc4";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. Nf3 Bg7 5. Qb3 dxc4 6. Qxc4"] = "0-0";


    // D96 Grünfeld Defense -- BLACK
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. Nf3 Bg7 5. Qb3"] = "dxc4";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. Nf3 Bg7 5. Qb3 dxc4 6. Qxc4"] = "a6 | 0-0";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. Nf3 Bg7 5. cxd5"] = "Nxd5";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. Nf3 Bg7 5. cxd5 Nxd5 6. e3"] = "0-0 | c5";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. Nf3 Bg7 5. cxd5 Nxd5 6. e4"] = "Nxc3";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. Nf3 Bg7 5. cxd5 Nxd5 6. e4 Nxc3 7. bxc3"] = "c5";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. Nf3 Bg7 5. cxd5 Nxd5 6. e4 Nxc3 7. bxc3 c5 8. Rb1"] = "0-0";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. Nf3 Bg7 5. cxd5 Nxd5 6. e4 Nxc3 7. bxc3 c5 8. Be3"] = "Bg4";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. Nf3 Bg7 5. cxd5 Nxd5 6. e4 Nxc3 7. bxc3 c5 8. Bb5+"] = "Nc6";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. Nf3 Bg7 5. cxd5 Nxd5 6. e4 Nxc3 7. bxc3 c5 8. Be2"] = "Nc6";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. Nf3 Bg7 5. Bg5"] = "Ne4";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. Nf3 Bg7 5. Bg5 Ne4 6. cxd5"] = "Nxg5";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. Nf3 Bg7 5. Bg5 Ne4 6. cxd5 Nxg5 7. Nxg5"] = "e6 | 0-0";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. Nf3 Bg7 5. Bg5 Ne4 6. Bh4"] = "Nxc3";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. Nf3 Bg7 5. Bg5 Ne4 6. Bh4 Nxc3 7. bxc3"] = "dxc4";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. Nf3 Bg7 5. Bg5 Ne4 6. Bf4"] = "0-0 | Nxc3";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. Nf3 Bg7 5. Qa4+"] = "Bd7";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. Nf3 Bg7 5. Qa4+ Bd7 6. Qb3"] = "dxc4";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. Nf3 Bg7 5. Qa4+ Bd7 6. Qb3 dxc4 7. Qxc4"] = "0-0";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. Nf3 Bg7 5. Bf4"] = "0-0";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. Nf3 Bg7 5. e3"] = "0-0 | e6";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. Nf3 Bg7 5. e3 0-0 6. Be2"] = "c5 | dxc4";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. Nf3 Bg7 5. e3 0-0 6. cxd5"] = "Nxd5";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. Nf3 Bg7 5. e3 0-0 6. Qb3"] = "e6";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. Nf3 Bg7 5. e3 0-0 6. Qb3 e6 7. Bd2"] = "dxc4 | b6";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. Nf3 Bg7 5. e3 0-0 6. Qb3 e6 7. Be2"] = "Nc6 | b6";




    // E20 Nimzo-Indian Defense -- WHITE
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4"] = "e3 | Nf3 | Qc2";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 0-0"] = "Bd2 | Bd3 | Nf3";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 c6"] = "Nf3";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 d5"] = "Qa4+";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 d5 5. Qa4+ Nc6"] = "Nf3";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 b6"] = "Ne2";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 c5"] = "Ne2 | Nf3 | Bd3";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 c5 5. Nf3 d5"] = "dxc5 | Bd2";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 c5 5. Nf3 Nc6"] = "Bd3";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 c5 5. Nf3 0-0"] = "Bd3 | Be2 | Bd2";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 c5 5. Nf3 0-0 6. Bd3 cxd4"] = "exd4";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 c5 5. Nf3 0-0 6. Bd3 cxd4 7. exd4 d5"] = "cxd5";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 c5 5. Nf3 0-0 6. Bd3 cxd4 7. exd4 d5 8. cxd5 Nxd5"] = "0-0";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 c5 5. Nf3 0-0 6. Bd3 cxd4 7. exd4 d5 8. cxd5 Qxd5"] = "0-0";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 c5 5. Nf3 0-0 6. Bd3 cxd4 7. exd4 d5 8. cxd5 exd5"] = "0-0";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 c5 5. Nf3 0-0 6. Bd3 b6"] = "0-0";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 c5 5. Nf3 0-0 6. Bd3 Nc6"] = "0-0 | dxc5";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 c5 5. Nf3 0-0 6. Bd3 d5"] = "0-0 | cxd5";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 c5 5. Nf3 0-0 6. Bd3 d5 7. 0-0 cxd4"] = "exd4";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 c5 5. Nf3 0-0 6. Bd3 d5 7. 0-0 cxd4 8. exd4 dxc4"] = "Bxc4";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 c5 5. Nf3 0-0 6. Bd3 d5 7. 0-0 dxc4"] = "Bxc4";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 c5 5. Nf3 0-0 6. Bd3 d5 7. 0-0 dxc4 8. Bxc4 cxd4"] = "exd4";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 c5 5. Nf3 0-0 6. Bd3 d5 7. 0-0 Nbd7"] = "a3";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 c5 5. Nf3 0-0 6. Bd3 d5 7. 0-0 Nbd7 8. a3 Bxc3"] = "bxc3";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 c5 5. Nf3 0-0 6. Bd3 d5 7. 0-0 Nbd7 8. a3 Ba5"] = "cxd5";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 c5 5. Nf3 0-0 6. Bd3 d5 7. 0-0 Nbd7 8. a3 Ba5 9. cxd5 Nxd5"] = "Qc2";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 c5 5. Nf3 0-0 6. Bd3 d5 7. 0-0 Nbd7 8. a3 Ba5 9. cxd5 exd5"] = "Bd2";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 c5 5. Nf3 0-0 6. Bd3 d5 7. 0-0 Nc6"] = "cxd5";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 c5 5. Nf3 0-0 6. Bd3 d5 7. 0-0 Nc6 8. cxd5 exd5"] = "dxc5";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 c5 5. Nf3 0-0 6. Bd3 d5 7. 0-0 Nc6 8. cxd5 exd5 9. dxc5 Bxc5"] = "h3";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 c5 5. Nf3 0-0 6. Bd3 d5 7. 0-0 Nc6 8. cxd5 exd5 9. dxc5 Bg4"] = "Na4";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 c5 5. Nf3 0-0 6. Bd3 d5 7. 0-0 Nc6 8. cxd5 Nxd5"] = "Nxd5";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 c5 5. Nf3 0-0 6. Bd3 d5 7. 0-0 Nc6 8. cxd5 Nxd5 9. Nxd5 Qxd5"] = "Qc2";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 c5 5. Nf3 0-0 6. Bd3 d5 7. 0-0 Nc6 8. cxd5 Nxd5 9. Nxd5 exd5"] = "a3";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 c5 5. Nf3 0-0 6. Bd3 d5 7. 0-0 Nc6 8. cxd5 cxd4"] = "dxc6";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3 c5 5. Nf3 0-0 6. Bd3 d5 7. 0-0 Nc6 8. cxd5 cxd4 9. dxc6 dxc3"] = "bxc3";


    // D85 Gruenfeld, exchange variation -- BLACK
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. cxd5"] = "Nxd5";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. cxd5 Nxd5 5. e4"] = "Nxc3";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. cxd5 Nxd5 5. e4 Nxc3 6. bxc3"] = "Bg7";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. cxd5 Nxd5 5. e4 Nxc3 6. bxc3 Bg7 7. Be3"] = "c5";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. cxd5 Nxd5 5. e4 Nxc3 6. bxc3 Bg7 7. Bc4"] = "c5";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. cxd5 Nxd5 5. e4 Nxc3 6. bxc3 Bg7 7. Nf3"] = "c5";
    book["1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. cxd5 Nxd5 5. Bd2"] = "Bg7";


    book["1. d4 Nf6 2. c4 g6 3. g3 Bg7"] = "Bg2";
    book["1. d4 Nf6 2. c4 g6 3. g3 Bg7 4. Bg2"] = "0-0 | d5 | d6 | c5";
    book["1. d4 Nf6 2. c4 g6 3. g3 c6"] = "Bg2 | Nf3";
    book["1. d4 Nf6 2. c4 g6 3. g3 c6 4. Bg2"] = "d5 | Bg7";
    book["1. d4 Nf6 2. c4 g6 3. g3 c6 4. Nf3"] = "Bg7 | d5";

    book["1. d4 Nf6 2. c4 e6 3. Nc3"] = "Bb4 | d5";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. e3"] = "0-0";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Nf3"] = "c5 | b6";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Qc2"] = "0-0";


    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Qb3"] = "Nc6 | c5";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Qb3 c5 5. dxc5"] = "Nc6";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Qb3 c5 5. Nf3"] = "0-0";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Qb3 c5 5. a3"] = "Bxc3+";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Qb3 c5 5. a3 Bxc3+ 6. bxc3"] = "b6";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Qb3 c5 5. a3 Bxc3+ 6. Qxc3"] = "cxd4";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Qb3 c5 5. a3 Bxc3+ 6. Qxc3 cxd4 7. Qxd4"] = "d6";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 Bb4 4. Qb3 c5 5. e3"] = "0-0 | b6";


    book["1. d4 Nf6 2. c4 g6 3. Nf3 c6"] = "Nc3";
    book["1. d4 Nf6 2. c4 g6 3. Nf3 c6 4. Nc3 d5"] = "e3 | cxd5";
    book["1. d4 Nf6 2. c4 g6 3. Nf3 c6 4. Nc3 Bg7"] = "e4";
    book["1. d4 Nf6 2. c4 g6 3. Nf3 c6 4. Nc3 d6"] = "e4";


    // A50 Indian Game: Normal Variation -- BLACK
    book["1. d4 Nf6 2. c4 g6 3. a3"] = "Bg7 | d5 | c5";
    book["1. d4 Nf6 2. c4 g6 3. a3 d5 4. Nc3"] = "Be7 | c6 | c5";
    book["1. d4 Nf6 2. c4 g6 3. a3 d5 4. Nf3"] = "dxc4";
    book["1. d4 Nf6 2. c4 g6 3. a3 d5 4. Nf3 dxc4 5. e3"] = "b5";
    book["1. d4 Nf6 2. c4 g6 3. a3 d5 4. e3"] = "Be7 | Nbd7";
    book["1. d4 Nf6 2. c4 g6 3. a3 d5 4. cxd5"] = "exd5";
    book["1. d4 Nf6 2. c4 g6 3. a3 d5 4. Bg5"] = "dxc4";
    book["1. d4 Nf6 2. c4 g6 3. a3 c5 4. e3"] = "d5 | b6";
    book["1. d4 Nf6 2. c4 g6 3. a3 c5 4. Nf3"] = "cxd4";
    book["1. d4 Nf6 2. c4 g6 3. a3 c5 4. Nf3 cxd4 5. Nxd4"] = "Be7";
    book["1. d4 Nf6 2. c4 g6 3. a3 c5 4. d5"] = "exd5 | g6";
    book["1. d4 Nf6 2. c4 g6 3. a3 c5 4. dxc5"] = "Bxc5";




    // D35 Queen's Gambit Declined, 3...Nf6 -- BLACK
    book["1. d4 Nf6 2. c4 e6 3. Nc3 d5 4. cxd5"] = "exd5";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 d5 4. Bg5"] = "Be7";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 d5 4. Nf3"] = "Be7";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 d5 4. Bf4"] = "Bb4";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 d5 4. e3"] = "Bd6";

    book["1. d4 Nf6 2. c4 e6 3. Nc3 d5 4. Bg5 Be7 5. Nf3"] = "h6";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 d5 4. Bg5 Be7 5. Nf3 h6 6. Bxf6"] = "Bxf6";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 d5 4. Bg5 Be7 5. Nf3 h6 6. Bh4"] = "0-0";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 d5 4. Bg5 Be7 5. Nf3 h6 6. Bf4"] = "0-0";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 d5 4. Bg5 Be7 5. e3"] = "h6";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 d5 4. Bg5 Be7 5. e3 h6 6. Bxf6"] = "Bxf6";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 d5 4. Bg5 Be7 5. e3 h6 6. Bf4"] = "0-0";
    book["1. d4 Nf6 2. c4 e6 3. Nc3 d5 4. Bg5 Be7 5. e3 h6 6. Bh4"] = "0-0";


    // E00 Queen's pawn game -- BLACK
    book["1. d4 Nf6 2. c4 e6 3. e3"] = "b6 | d5 | c5";
    book["1. d4 Nf6 2. c4 e6 3. e3 d5 4. Nf3"] = "Be7 | b6";
    book["1. d4 Nf6 2. c4 e6 3. e3 d5 4. Nf3 b6 5. Nc3"] = "Bb7";
    book["1. d4 Nf6 2. c4 e6 3. e3 d5 4. Nf3 b6 5. Bd3"] = "Bb7";
    book["1. d4 Nf6 2. c4 e6 3. e3 d5 4. Nc3"] = "Be7 | b6";
    book["1. d4 Nf6 2. c4 e6 3. e3 d5 4. Nc3 b6 5. Bd3"] = "Bb7";
    book["1. d4 Nf6 2. c4 e6 3. e3 d5 4. Nc3 b6 5. Qb3"] = "Bb7";
    book["1. d4 Nf6 2. c4 e6 3. e3 d5 4. Nc3 b6 5. Nf3"] = "Bb7";


    // King's Indian (E60)
    book["1. d4 Nf6 2. c4 g6 3. g3 Bg7 4. Bg2 0-0"] = "Nc3 | Nf3";
    book["1. d4 Nf6 2. c4 g6 3. g3 Bg7 4. Bg2 d5"] = "cxd5 | Nf3";
    book["1. d4 Nf6 2. c4 g6 3. g3 Bg7 4. Bg2 d6"] = "Nf3 | Nc3";
    book["1. d4 Nf6 2. c4 g6 3. g3 Bg7 4. Bg2 c5"] = "d5 | Nf3";

    // Neo-Grünfeld (D70)
    book["1. d4 Nf6 2. c4 g6 3. f3 Bg7"] = "e4 | Nc3";
    book["1. d4 Nf6 2. c4 g6 3. f3 d5"] = "cxd5";
    book["1. d4 Nf6 2. c4 g6 3. f3 d5 4. cxd5"] = "Nxd5";
    book["1. d4 Nf6 2. c4 g6 3. f3 d5 4. cxd5 Nxd5"] = "e4";
    book["1. d4 Nf6 2. c4 g6 3. f3 d5 4. cxd5 Nxd5 5. e4"] = "Nb6 | Nf6";


    // Queen's pawn game (D02)
    book["1. d4 Nf6 2. Nf3"] = "e6 | g6 | d5";
    book["1. d4 Nf6 2. Nf3 e6"] = "c4 | Bg5 | e3 | g3";
    book["1. d4 Nf6 2. Nf3 g6"] = "c4 | g3 | Bg5";
    book["1. d4 Nf6 2. Nf3 d5"] = "c4 | e3 | Bf4";


    // D02 Queen's pawn game -- BLACK
    book["1. d4 Nf6 2. Nf3 d5 3. c4 e6"] = "Nc3 | g3 | Bg5";
    book["1. d4 Nf6 2. Nf3 d5 3. c4 e6 4. Nc3 Be7"] = "Bg5 | Bf4 | cxd5";
    book["1. d4 Nf6 2. Nf3 d5 3. c4 e6 4. Nc3 Bb4"] = "Bg5 | cxd5 | Qa4+";
    book["1. d4 Nf6 2. Nf3 d5 3. c4 e6 4. Nc3 c6"] = "Bg5 | e3 | cxd5";
    book["1. d4 Nf6 2. Nf3 d5 3. c4 e6 4. Nc3 dxc4"] = "e4 | e3 | Qa4+";
    book["1. d4 Nf6 2. Nf3 d5 3. c4 e6 4. Nc3 Nbd7"] = "Bg5 | cxd5 | Bf4";
    book["1. d4 Nf6 2. Nf3 d5 3. c4 e6 4. Nc3 c5"] = "cxd5 | e3";
    book["1. d4 Nf6 2. Nf3 d5 3. c4 e6 4. Nc3 c5 5. cxd5 Nxd5"] = "e4";
    book["1. d4 Nf6 2. Nf3 d5 3. c4 e6 4. Nc3 c5 5. cxd5 exd5"] = "Bg5";
    book["1. d4 Nf6 2. Nf3 d5 3. c4 e6 4. Nc3 c5 5. cxd5 cxd4"] = "Qxd4";

    book["1. d4 Nf6 2. Nf3 d5 3. c4 Bg4"] = "Ne5 | cxd5";
    book["1. d4 Nf6 2. Nf3 d5 3. c4 Bg4 4. Ne5 Bf5"] = "Nc3 | cxd5";
    book["1. d4 Nf6 2. Nf3 d5 3. c4 Bg4 4. Ne5 Bh5"] = "cxd5 | Qb3";
    book["1. d4 Nf6 2. Nf3 d5 3. c4 Bg4 4. cxd5 Bxf3"] = "gxf3";
    book["1. d4 Nf6 2. Nf3 d5 3. c4 Bg4 4. cxd5 Bxf3"] = "gxf3";
    book["1. d4 Nf6 2. Nf3 d5 3. c4 Bg4 4. cxd5 Bxf3 5. gxf3 Nxd5"] = "e4";
    book["1. d4 Nf6 2. Nf3 d5 3. c4 Bg4 4. cxd5 Bxf3 5. gxf3 Nxd5 6. e4 Nf6"] = "Qb3";
    book["1. d4 Nf6 2. Nf3 d5 3. c4 Bg4 4. cxd5 Bxf3 5. gxf3 Nxd5 6. e4 Nb6"] = "Be3";
    book["1. d4 Nf6 2. Nf3 d5 3. c4 Bg4 4. cxd5 Nxd5"] = "Ne5";
    book["1. d4 Nf6 2. Nf3 d5 3. c4 Bg4 4. cxd5 Nxd5 5. Ne5 Bh5"] = "Qb3 | g4 | Nc3";
    book["1. d4 Nf6 2. Nf3 d5 3. c4 Bg4 4. cxd5 Nxd5 5. Ne5 Bh5 6. g4 Bg6"] = "Bg2";
    book["1. d4 Nf6 2. Nf3 d5 3. c4 Bg4 4. cxd5 Nxd5 5. Ne5 Bf5"] = "Qb3";
    book["1. d4 Nf6 2. Nf3 d5 3. c4 Bg4 4. cxd5 c6"] = "Ne5";
    book["1. d4 Nf6 2. Nf3 d5 3. c4 Bg4 4. cxd5 c6 5. Ne5 cxd5"] = "Nxg4";
    book["1. d4 Nf6 2. Nf3 d5 3. c4 Bg4 4. cxd5 c6 5. Ne5 cxd5 6. Nxg4 Nxg4"] = "e4";
    book["1. d4 Nf6 2. Nf3 d5 3. c4 Bg4 4. cxd5 c6 5. Ne5 cxd5 6. Nxg4 Nxg4 7. e4 Nf6"] = "e5";
    book["1. d4 Nf6 2. Nf3 d5 3. c4 Bg4 4. cxd5 c6 5. Ne5 cxd5 6. Nxg4 Nxg4 7. e4 Nf6 8. e5 Nfd7"] = "Be3";

    book["1. d4 Nf6 2. Nf3 e6 3. c4 b6"] = "g3 | a3 | Nc3 | e3";
    book["1. d4 Nf6 2. Nf3 e6 3. c4 b6 4. g3 Bb7"] = "Bg2";
    book["1. d4 Nf6 2. Nf3 e6 3. c4 d5"] = "Nc3 | g3 | Bg5 | e3";
    book["1. d4 Nf6 2. Nf3 e6 3. c4 c5"] = "d5 | e3 | Nc3";
    book["1. d4 Nf6 2. Nf3 e6 3. c4 Bb4+"] = "Bd2 | Nbd2";
    book["1. d4 Nf6 2. Nf3 e6 3. c4 Bb4+ 4. Bd2 Qe7"] = "g3";
    book["1. d4 Nf6 2. Nf3 e6 3. c4 Bb4+ 4. Bd2 Qe7 5. g3 Bxd2+"] = "Qxd2";
    book["1. d4 Nf6 2. Nf3 e6 3. c4 Bb4+ 4. Bd2 Qe7 5. g3 0-0"] = "Bg2";
    book["1. d4 Nf6 2. Nf3 e6 3. c4 Bb4+ 4. Bd2 a5"] = "a3";
    book["1. d4 Nf6 2. Nf3 e6 3. c4 Bb4+ 4. Bd2 a5 5. a3 Bxd2+"] = "Qxd2";
    book["1. d4 Nf6 2. Nf3 e6 3. c4 Bb4+ 4. Bd2 c5"] = "Bxb4";
    book["1. d4 Nf6 2. Nf3 e6 3. c4 Bb4+ 4. Bd2 c5 5. Bxb4 cxb4"] = "e3";
    book["1. d4 Nf6 2. Nf3 e6 3. c4 Bb4+ 4. Bd2 Bxd2+"] = "Qxd2";


    book["1. d4 Nf6 2. Nf3 e6 3. Bg5 b6"] = "e4";
    book["1. d4 Nf6 2. Nf3 e6 3. Bg5 b6 4. e4 Bb7"] = "e5 | Bd3";
    book["1. d4 Nf6 2. Nf3 e6 3. Bg5 b6 4. e4 Be7"] = "Bd3 | e5 | Nc3";





    // A46 Torre Attack -- WHITE
    book["1. d4 Nf6 2. Nf3 e6 3. Bg5 c5"] = "e3 | d5 | c3 | Nc3";
    book["1. d4 Nf6 2. Nf3 e6 3. Bg5 c5 4. Nc3 cxd4"] = "Qxd4 | Nxd4";
    book["1. d4 Nf6 2. Nf3 e6 3. Bg5 c5 4. Nc3 h6"] = "Bxf6";
    book["1. d4 Nf6 2. Nf3 e6 3. Bg5 c5 4. Nc3 h6 5. Bxf6 Qxf6"] = "d5";
    book["1. d4 Nf6 2. Nf3 e6 3. Bg5 c5 4. Nc3 Nc6"] = "d5";
    book["1. d4 Nf6 2. Nf3 e6 3. Bg5 c5 4. Nc3 Nc6 5. d5 exd5"] = "Bxf6";
    book["1. d4 Nf6 2. Nf3 e6 3. Bg5 c5 4. Nc3 Nc6 5. d5 exd5 6. Bxf6 Qxf6"] = "Nxd5";
    book["1. d4 Nf6 2. Nf3 e6 3. Bg5 c5 4. Nc3 Nc6 5. d5 Nb5"] = "e4";
    book["1. d4 Nf6 2. Nf3 e6 3. Bg5 c5 4. Nc3 Nc6 5. d5 Nb5 6. e4 h6"] = "Bxf6";
    book["1. d4 Nf6 2. Nf3 e6 3. Bg5 c5 4. Nc3 Nc6 5. d5 Nb5 6. e4 h6 7. Bxf6 Qxf6"] = "a3";
    book["1. d4 Nf6 2. Nf3 e6 3. Bg5 c5 4. Nc3 Nc6 5. d5 Nb5 6. e4 h6 7. Bxf6 Qxf6 8. a3 Na6"] = "e5";
    book["1. d4 Nf6 2. Nf3 e6 3. Bg5 c5 4. Nc3 Nc6 5. d5 Nb5 6. e4 h6 7. Bxf6 gxf6"] = "a3";
    book["1. d4 Nf6 2. Nf3 e6 3. Bg5 c5 4. Nc3 Nc6 5. d5 Nb5 6. e4 h6 7. Bxf6 gxf6 8. a3 Na6"] = "Qd2";



    // A46 Torre Attack -- BLACK
    book["1. d4 Nf6 2. Nf3 e6 3. Bg5"] = "c5 | h6 | d5";



    
    // D02 Queen's Pawn Game: Symmetrical Variation -- BLACK
    book["1. d4 Nf6 2. Nf3 d5 3. Nbd2"] = "Bf5 | c5 | e6";
    book["1. d4 Nf6 2. Nf3 d5 3. Nbd2 e6 4. e3"] = "c5 | Be7";

    book["1. d4 Nf6 2. Nf3 g6 3. Bg5"] = "Bg7";
    book["1. d4 Nf6 2. Nf3 g6 3. Bg5 Bg7"] = "Nbd2 | e3 | c3";


    // E60 King's Indian Defense: Normal Variation -- BLACK
    book["1. d4 Nf6 2. Nf3 g6 3. c4"] = "Bg7 | d5 | c5 | d6 | c6 | e6 | b6";
    book["1. d4 Nf6 2. Nf3 g6 3. c4 Bg7 4. g3"] = "0-0 | d6 | d5";
    book["1. d4 Nf6 2. Nf3 g6 3. c4 Bg7 4. e3"] = "0-0 | d6";
    book["1. d4 Nf6 2. Nf3 g6 3. c4 Bg7 4. Bf4"] = "0-0 | d6 | d5";
    book["1. d4 Nf6 2. Nf3 g6 3. c4 Bg7 4. Bg5"] = "0-0 | d6 | d5 | Ne4";
    book["1. d4 Nf6 2. Nf3 g6 3. c4 Bg7 4. Nc3"] = "0-0 | d6 | d5";
    book["1. d4 Nf6 2. Nf3 g6 3. c4 Bg7 4. Nc3 0-0 5. e4"] = "d6";
    book["1. d4 Nf6 2. Nf3 g6 3. c4 Bg7 4. Nc3 0-0 5. Bg5"] = "d6 | h6 | c5";
    book["1. d4 Nf6 2. Nf3 g6 3. c4 Bg7 4. Nc3 0-0 5. g3"] = "d6 | d5 | c5";
    book["1. d4 Nf6 2. Nf3 g6 3. c4 Bg7 4. Nc3 0-0 5. Bf4"] = "d6 | c5 | d5";
    book["1. d4 Nf6 2. Nf3 g6 3. c4 Bg7 4. Nc3 0-0 5. e3"] = "d6 | d5 | c5";
    book["1. d4 Nf6 2. Nf3 g6 3. c4 Bg7 4. Nc3 d6 5. e4"] = "0-0 | Bg4 | Nbd7 | Nc6";
    book["1. d4 Nf6 2. Nf3 g6 3. c4 Bg7 4. Nc3 d6 5. Bg5"] = "0-0 | h6 | Nbd7";
    book["1. d4 Nf6 2. Nf3 g6 3. c4 Bg7 4. Nc3 d6 5. g3"] = "0-0 | Nbd7";
    book["1. d4 Nf6 2. Nf3 g6 3. c4 Bg7 4. Nc3 d6 5. e3"] = "0-0 | Bg4";
    book["1. d4 Nf6 2. Nf3 g6 3. c4 Bg7 4. Nc3 d6 5. Bf4"] = "0-0 | Bf5";
    book["1. d4 Nf6 2. Nf3 g6 3. c4 Bg7 4. Nc3 d5 5. Bg5"] = "Ne4 | c6";
    book["1. d4 Nf6 2. Nf3 g6 3. c4 Bg7 4. Nc3 d5 5. cxd5"] = "Nxd5";
    book["1. d4 Nf6 2. Nf3 g6 3. c4 Bg7 4. Nc3 d5 5. cxd5 Nxd5 6. e4"] = "Nxc3";
    book["1. d4 Nf6 2. Nf3 g6 3. c4 Bg7 4. Nc3 d5 5. cxd5 Nxd5 6. e4 Nxc3 7. bxc3"] = "c5";
    book["1. d4 Nf6 2. Nf3 g6 3. c4 Bg7 4. Nc3 d5 5. cxd5 Nxd5 6. e4 Nxc3 7. bxc3 c5 8. Be3"]= "0-0";
    book["1. d4 Nf6 2. Nf3 g6 3. c4 Bg7 4. Nc3 d5 5. e3"] = "0-0 | c5 | c6"; 
    book["1. d4 Nf6 2. Nf3 g6 3. c4 Bg7 4. Nc3 d5 5. Bf4"] = "0-0 | c6 | c5";
    book["1. d4 Nf6 2. Nf3 g6 3. c4 Bg7 4. Nc3 d5 5. Qb3"] = "dxc4 | c6";
    book["1. d4 Nf6 2. Nf3 g6 3. c4 Bg7 4. Nc3 d5 5. g3"] = "0-0 | dxc4";
    book["1. d4 Nf6 2. Nf3 g6 3. c4 Bg7 4. Nc3 d5 5. g3 0-0 6. Bg2"] = "dxc4";
    book["1. d4 Nf6 2. Nf3 g6 3. c4 Bg7 4. Nc3 d5 5. g3 0-0 6. cxd5"] = "Nxd5";
    book["1. d4 Nf6 2. Nf3 g6 3. c4 Bg7 4. Nc3 d5 5. g3 0-0 6. cxd5 Nxd5 7. Bg2"] = "c5";
    book["1. d4 Nf6 2. Nf3 g6 3. c4 Bg7 4. Nc3 d5 5. g3 dxc4 6. Bg2"] = "c6";
    book["1. d4 Nf6 2. Nf3 g6 3. c4 Bg7 4. Nc3 d5 5. g3 dxc4 6. Qa4+"] = "Nc6";



    book["1. Nf3 Nf6 2. d4 e6"] = "c4 | Bg5 | e3 | g3";
    book["1. Nf3 Nf6 2. d4 e6 3. c4"] = "b6 | d5 | Bb4";
    book["1. Nf3 Nf6 2. d4 e6 3. Bg5"] = "c5 | h6";
    book["1. Nf3 Nf6 2. d4 e6 3. e3"] = "b6 | c5";
    book["1. Nf3 Nf6 2. d4 e6 3. g3"] = "b6 | c5 | d5";


    // A46 Indian Defense: Knights Variation -- WHITE
    book["1. Nf3 Nf6 2. d4 e6 3. g3 b5"] = "Bg2";
    book["1. Nf3 Nf6 2. d4 e6 3. g3 c5"] = "c4 | Bg2 | dxc5";
    book["1. Nf3 Nf6 2. d4 e6 3. g3 c5 dxc5 4. Bxc5"] = "c4 | Bg2";
    book["1. Nf3 Nf6 2. d4 e6 3. g3 b6"] = "Bg2 | c4";
    book["1. Nf3 Nf6 2. d4 e6 3. g3 Be7"] = "Bg2";
    book["1. Nf3 Nf6 2. d4 e6 3. g3 Be7 4. Bg2 0-0"] = "c4";
    book["1. Nf3 Nf6 2. d4 e6 3. g3 Be7 4. Bg2 b5"] = "Ne5 | a4";
    book["1. Nf3 Nf6 2. d4 e6 3. g3 Be7 4. Bg2 d5"] = "0-0 | c4";
    book["1. Nf3 Nf6 2. d4 e6 3. g3 d5"] = "Bg2 | c4";
    book["1. Nf3 Nf6 2. d4 e6 3. g3 d5 4. Bg2 Be7"] = "0-0 | c4";
    book["1. Nf3 Nf6 2. d4 e6 3. g3 d5 4. Bg2 b5"] = "0-0 | a4";
    book["1. Nf3 Nf6 2. d4 e6 3. g3 d5 4. Bg2 Bb4+"] = "c3";
    book["1. Nf3 Nf6 2. d4 e6 3. g3 d5 4. Bg2 c5"] = "c4";
    book["1. Nf3 Nf6 2. d4 e6 3. g3 d5 4. Bg2 Nbd7"] = "0-0";
    book["1. Nf3 Nf6 2. d4 e6 3. g3 d5 4. Bg2 c6"] = "0-0 | c4 | b3";
    book["1. Nf3 Nf6 2. d4 e6 3. g3 d5 4. c4 dxc4"] = "Bg2";
    book["1. Nf3 Nf6 2. d4 e6 3. g3 d5 4. c4 Be7"] = "Bg2 | Nc3";
    book["1. Nf3 Nf6 2. d4 e6 3. g3 d5 4. c4 Bb4+"] = "Bd2 | Nc3";
    book["1. Nf3 Nf6 2. d4 e6 3. g3 d5 4. c4 Nbd7"] = "Bg2";
    book["1. Nf3 Nf6 2. d4 e6 3. g3 d5 4. c4 c6"] = "Bg2 | Qd3";


    // A47 Queen's Indian defence -- WHITE
    book["1. d4 Nf6 2. Nf3 b6"] = "c4 | g3 | Bg5";
    book["1. d4 Nf6 2. Nf3 b6 3. c4 e6"] = "g3 | a3 | Nc3";
    book["1. d4 Nf6 2. Nf3 b6 3. c4 e6 4. g3 Ba6"] = "b3 | Qa4";
    book["1. d4 Nf6 2. Nf3 b6 3. c4 e6 4. g3 Bb7"] = "Bg2";
    book["1. d4 Nf6 2. Nf3 b6 3. c4 e6 4. g3 Bb4+"] = "Bd2";
    book["1. d4 Nf6 2. Nf3 b6 3. c4 Bb7"] = "g3";
    book["1. d4 Nf6 2. Nf3 b6 3. c4 Bb7 4. g3 e6"] = "Bg2";
    book["1. d4 Nf6 2. Nf3 b6 3. c4 Bb7 4. g3 g6"] = "Bg2";
    book["1. d4 Nf6 2. Nf3 b6 3. c4 Bb7 4. g3 c5"] = "d5";
    book["1. d4 Nf6 2. Nf3 b6 3. c4 Bb7 4. g3 Bxf3"] = "exf3";


    // A46 Queen's pawn, Yusupov-Rubinstein system -- WHITE
    book["1. d4 Nf6 2. Nf3 e6 3. e3 b6"] = "Bd3 | b3 | c4";
    book["1. d4 Nf6 2. Nf3 e6 3. e3 b6 4. Bd3 Bb7"] = "0-0";
    book["1. d4 Nf6 2. Nf3 e6 3. e3 c5"] = "Bd3";
    book["1. d4 Nf6 2. Nf3 e6 3. e3 g6"] = "c4 | Bd3";
    book["1. d4 Nf6 2. Nf3 e6 3. e3 d5"] = "Bd3 | b3 | c4";



    // D02 Queen's bishop game -- WHITE
    book["1. d4 Nf6 2. Nf3 d5 3. Bf4 c5"] = "e3 | c3";
    book["1. d4 Nf6 2. Nf3 d5 3. Bf4 e6"] = "e3 | Nbd2";
    book["1. d4 Nf6 2. Nf3 d5 3. Bf4 c6"] = "e3 | c3 | Nbd2";
    book["1. d4 Nf6 2. Nf3 d5 3. Bf4 Bf5"] = "e3 | c4";


    // D02 Queen's bishop game -- BLACK
    book["1. d4 Nf6 2. Nf3 d5 3. Bf4"] = "c5 | e6";
    book["1. d4 Nf6 2. Nf3 d5 3. Bf4 e6 4. Nbd2"] = "c5 | Bd6";
    book["1. d4 Nf6 2. Nf3 d5 3. Bf4 e6 4. e3"] = "c5 | Bd6";
    book["1. d4 Nf6 2. Nf3 d5 3. Bf4 e6 4. e3 Bd6 5. Bg3"] = "c5 | 0-0";
    book["1. d4 Nf6 2. Nf3 d5 3. Bf4 e6 4. e3 Bd6 5. Nbd2"] = "0-0";
    book["1. d4 Nf6 2. Nf3 d5 3. Bf4 e6 4. e3 Bd6 5. Bxd6"] = "Qxd6";
    book["1. d4 Nf6 2. Nf3 d5 3. Bf4 e6 4. e3 Bd6 5. Ne5"] = "0-0";
    book["1. d4 Nf6 2. Nf3 d5 3. Bf4 e6 4. e3 Bd6 5. Bb5+"] = "c6 | Bd7";
    book["1. d4 Nf6 2. Nf3 d5 3. Bf4 e6 4. e3 Bd6 5. Bb5+ c6 6. Bxd6"] = "Qxd6";
    book["1. d4 Nf6 2. Nf3 d5 3. Bf4 e6 4. e3 Bd6 5. Bb5+ c6 6. Bd3"] = "Bxf4";
    book["1. d4 Nf6 2. Nf3 d5 3. Bf4 e6 4. e3 Bd6 5. Bb5+ c6 6. Bd3 Bxf4 7. exf4"] = "Qd6";


    // A45 Trompovsky attack (Ruth, Opovcensky opening) -- WHITE
    book["1. d4 Nf6 2. Bg5 b6"] = "Nf3 | Bxf6 | Nd2";
    book["1. d4 Nf6 2. Bg5 b6 3. Nf3 Bb7"] = "Nbd2";
    book["1. d4 Nf6 2. Bg5 b6 3. Nf3 Bb7 4. Nbd2 d6"] = "Bxf6";
    book["1. d4 Nf6 2. Bg5 b6 3. Nf3 Bb7 4. Nbd2 g6"] = "e3";
    book["1. d4 Nf6 2. Bg5 b6 3. Nf3 Bb7 4. Nbd2 g6 5. e3 Bg7"] = "Bd3";


    // Trompovsky attack (A45)
    book["1. d4 Nf6 2. Bg5"] = "Ne4 | e6 | d5";

    book["1. d4 Nf6 2. Bg5 Ne4"] = "Bf4";
    book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4"] = "c5 | d5";
    book["1. d4 Nf6 2. Bg5 e6"] = "e4 | Nd2 | e3 | Nf3 | Nc3";
    book["1. d4 Nf6 2. Bg5 d5"] = "Bxf6 | e3 | Nd2 | Nf3 | Nc3";


    book["1. d4 Nf6 2. Bg5 e6 3. Nf3 Be7"] = "Nbd2";
    book["1. d4 Nf6 2. Bg5 e6 3. Nf3 Be7 4. Nbd2 h6"] = "Bxf6";
    book["1. d4 Nf6 2. Bg5 e6 3. Nf3 Be7 4. Nbd2 h6 5. Bxf6 Bxf6"] = "e4";
    book["1. d4 Nf6 2. Bg5 e6 3. Nf3 Be7 4. Nbd2 d5"] = "e3 | c3";


    book["1. d4 Nf6 2. Bg5 d5 3. Nf3 Ne4"] = "Bf4";

    book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 d5"] = "e3";
    book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 d5 4. e3"] = "Nc6";
    book["1. d4 Nf6 2. Bg5 Ne4 3. Bf4 d5 4. e3 Nc6"] = "Bd3 | Bb5";


    // A45 Trompovsky attack (Ruth, Opovcensky opening) -- WHITE
    book["1. d4 Nf6 2. Bg5 e6 3. Nd2 h6"] = "Bh4";
    book["1. d4 Nf6 2. Bg5 e6 3. Nd2 c5"] = "e3";
    book["1. d4 Nf6 2. Bg5 e6 3. Nd2 Be7"] = "e4";
    book["1. d4 Nf6 2. Bg5 e6 3. Nd2 d6"] = "Ngf3";
    book["1. d4 Nf6 2. Bg5 e6 3. Nd2 d5"] = "e4";


    // D03 Torre attack (Tartakower variation) -- WHITE
    book["1. d4 Nf6 2. Bg5 d5 3. Nf3 c5"] = "e3 | Bxf6";
    book["1. d4 Nf6 2. Bg5 d5 3. Nf3 c5 4. e3 Ne4"] = "Bf4";
    book["1. d4 Nf6 2. Bg5 d5 3. Nf3 c5 4. e3 Nc6"] = "Bxf6 | dxc5";


    // A45 Trompowsky Attack -- BLACK
    book["1. d4 Nf6 2. Bg5 d5 3. e3"] = "c5";
    book["1. d4 Nf6 2. Bg5 d5 3. e3 c5 4. Bxf6"] = "gxf6";
    book["1. d4 Nf6 2. Bg5 d5 3. Nd2"] = "c5";
    book["1. d4 Nf6 2. Bg5 d5 3. Nd2 c5 4. Bxf6"] = "gxf6";
    book["1. d4 Nf6 2. Bg5 d5 3. Nc3"] = "Nbd7 | h6";
    book["1. d4 Nf6 2. Bg5 d5 3. Nc3 Nbd7 4. Nf3"] = "h6";
    book["1. d4 Nf6 2. Bg5 d5 3. Nc3 h6 4. Bxf6"] = "exf6";
    book["1. d4 Nf6 2. Bg5 d5 3. Nf3"] = "Ne4 | c5";
    book["1. d4 Nf6 2. Bg5 d5 3. c4"] = "Ne4";
    book["1. d4 Nf6 2. Bg5 d5 3. c4 Ne4 4. Bf4"] = "e5";
    book["1. d4 Nf6 2. Bg5 d5 3. c4 Ne4 4. Bf4 e5 5. dxe5"] = "Bc5";
    book["1. d4 Nf6 2. Bg5 d5 3. c4 Ne4 4. Bf4 e5 5. Bxe5"] = "Bb4+";
    book["1. d4 Nf6 2. Bg5 d5 3. c4 Ne4 4. Bh4"] = "g5";
    book["1. d4 Nf6 2. Bg5 d5 3. c4 Ne4 4. Bh4 g5 5. Bg3"] = "e5";
    book["1. d4 Nf6 2. Bg5 d5 3. c4 Ne4 4. Bh4 g5 5. Bg3 e5 6. dxe5"] = "Bb4+";
    book["1. d4 Nf6 2. Bg5 d5 3. c4 Ne4 4. Bh4 g5 5. Bg3 e5 6. Bxe5"] = "Bb4+";
    book["1. d4 Nf6 2. Bg5 d5 3. c4 Ne4 4. Bh4 g5 5. Bg3 e5 6. Nc3"] = "Bb4";
    book["1. d4 Nf6 2. Bg5 d5 3. c4 Ne4 4. Nf3"] = "e5";
    book["1. d4 Nf6 2. Bg5 d5 3. c3"] = "c5 | Nc6";
    book["1. d4 Nf6 2. Bg5 d5 3. Bxf6"] = "exf6";
    book["1. d4 Nf6 2. Bg5 d5 3. Bxf6 exf6 4. g3"] = "Bd6 | c6";
    book["1. d4 Nf6 2. Bg5 d5 3. Bxf6 exf6 4. g3 Bd6 5. Bg2"] = "c6";
    book["1. d4 Nf6 2. Bg5 d5 3. Bxf6 exf6 4. g3 c6 5. Bg2"] = "Bd6";
    book["1. d4 Nf6 2. Bg5 d5 3. Bxf6 exf6 4. c3"] = "Bd6";
    book["1. d4 Nf6 2. Bg5 d5 3. Bxf6 exf6 4. Nc3"] = "c6";
    book["1. d4 Nf6 2. Bg5 d5 3. Bxf6 exf6 4. c4"] = "dxc4";
    book["1. d4 Nf6 2. Bg5 d5 3. Bxf6 exf6 4. e3"] = "Nd7";


    // Queen's pawn game (A45)
    book["1. d4 Nf6 2. Nc3"] = "d5 | c5 | g6 | d6";
    book["1. d4 Nf6 2. Nc3 d5"] = "Bg5 | Bf4";
    book["1. d4 Nf6 2. Nc3 g6"] = "e4";
    book["1. d4 Nf6 2. Nc3 g6 3. e4"] = "d6 | d5";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 d6"] = "Nf3 | f4 | Be3";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 d5"] = "e5 | Bd3";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 d5"] = "e5 | Bd3";


    book["1. d4 Nf6 2. Nc3 g6 3. e4 d6"] = "Be3 | Nf3 | f4";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 d5"] = "e5";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 c5"] = "dxc5 | d5";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 Nc6"] = "e5 | d5";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 Nc6 4. d5 Nb8"] = "e5";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 Nc6 4. d5 Nb8 5. e5 Ng8"] = "f4";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 Nc6 4. e5 Ng8"] = "d5";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 Nc6 4. e5 Ng8 5. d5 Nb8"] = "f4";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 Nc6 4. d5 Nb4"] = "e5 | a3";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 Nc6 4. d5 Nb4 5. e5 Ng8"] = "a3";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 Nc6 4. d5 Nb4 5. e5 Ng8 6. a3 Na6"] = "Bb5";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 Nc6 4. d5 Nb4 5. a3 Na6"] = "e5";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 Nc6 4. d5 Nb4 5. a3 Na6 6. e5 Ng8"] = "Bb5";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 Nc6 4. d5 Nb4 5. a3 Na6 6. e5 Ng8 7. Bb5 Bg7"] = "Nf3";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 Nc6 4. d5 Nb4 5. a3 Na6 6. e5 Ng8 7. Bb5 c6"] = "Bxa6";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 Nc6 4. d5 Nb4 5. a3 Na6 6. e5 Ng8 7. Bb5 c6 8. Bxa6 bxa6"] = "d6";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 Nc6 4. d5 Ne5"] = "f4";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 Nc6 4. d5 Ne5 5. f4 Nge4"] = "e5";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 Nc6 4. d5 Ne5 5. f4 Nge4 6. e5 d6"] = "Bb5+";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 Nc6 4. d5 Ne5 5. f4 Nge4 6. e5 d6 7. Bb5+ Bd7"] = "Bxd7+";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 Nc6 4. d5 Ne5 5. f4 Nge4 6. e5 d6 7. Bb5+ Bd7 8. Bxd7+ Qxd7"] = "exf6";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 Nc6 4. d5 Ne5 5. f4 Nge4 6. e5 d6 7. Bb5+ Bd7 8. Bxd7+ Qxd7 9. exf6 Nxf6"] = "Nf3";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 Nc6 4. d5 Ne5 5. f4 Nge4 6. e5 d6 7. Bb5+ Bd7 8. Bxd7+ Qxd7 9. exf6 Nxf6 10. Nf3 Bg7"] = "0-0";


    // A45 Queen's pawn game -- WHITE
    book["1. d4 Nf6 2. Nc3 c5"] = "d5";
    book["1. d4 Nf6 2. Nc3 c5 3. d5 g6"] = "e4 | Nf3";
    book["1. d4 Nf6 2. Nc3 c5 3. d5 d6"] = "e4 | Nf3";
    book["1. d4 Nf6 2. Nc3 c5 3. d5 Qa5"] = "Bd2";
    book["1. d4 Nf6 2. Nc3 c5 3. d5 e5"] = "e4 | Nf3";
    book["1. d4 Nf6 2. Nc3 c5 3. d5 a6"] = "a4 | e4";
    book["1. d4 Nf6 2. Nc3 c5 3. d5 e6"] = "e4";


    // A45 Queen's pawn game -- WHITE
    book["1. d4 Nf6 2. Nc3 g6 3. e4 d6 4. Nf3 c6"] = "Be2";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 d6 4. Nf3 Bg4"] = "h3";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 d6 4. Nf3 Bg7"] = "Be2";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 d6 4. Nf3 Bg7 5. Be2 0-0"] = "0-0";


    // B08 Pirc, classical (two knights) system -- BLACK
    book["1. d4 Nf6 2. Nc3 g6 3. e4 d6 4. Nf3"] = "Bg7";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 d6 4. Nf3 Bg7 5. Be2"] = "0-0";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 d6 4. Nf3 Bg7 5. Be2 0-0 6. 0-0"] = "c5";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 d6 4. Nf3 Bg7 5. h3"] = "0-0";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 d6 4. Nf3 Bg7 5. Be3"] = "0-0";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 d6 4. Nf3 Bg7 5. Bf4"] = "0-0";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 d6 4. Nf3 Bg7 5. Bc4"] = "0-0";
    book["1. d4 Nf6 2. Nc3 g6 3. e4 d6 4. Nf3 Bg7 5. Bd3"] = "Bg4";


    // Ritcher-Veresov attack (D01)
    book["1. d4 Nf6 2. Nc3 d5 3. Bg5"] = "Nbd7 | Bf5 | e6 | c6";
    book["1. d4 Nf6 2. Nc3 d5 3. Bg5 h6"] = "Bxf6";
    book["1. d4 Nf6 2. Nc3 d5 3. Bg5 h6 4. Bxf6 exf6"] = "e3 | e4";
    book["1. d4 Nf6 2. Nc3 d5 3. Bg5 h6 4. Bxf6 gxf6"] = "e3";

    book["1. d4 Nf6 2. Nc3 d5 3. Bg5 Nbd7"] = "Nf3 | Bh4 | Qd3";
    book["1. d4 Nf6 2. Nc3 d5 3. Bg5 Nbd7 4. Nf3 e6"] = "e3 | e4";
    book["1. d4 Nf6 2. Nc3 d5 3. Bg5 Nbd7 4. Nf3 e6 5. e4 h6"] = "Bxf6";
    book["1. d4 Nf6 2. Nc3 d5 3. Bg5 Nbd7 4. Nf3 e6 5. e4 h6 6. Bxf6 Nxf6"] = "Bd3";

    book["1. d4 Nf6 2. Nc3 d5 3. Bg5 Bf5"] = "e3 | Bxf6";
    book["1. d4 Nf6 2. Nc3 d5 3. Bg5 Bf5 4. e3 c6"] = "Nf3 | Bd3";
    book["1. d4 Nf6 2. Nc3 d5 3. Bg5 Bf5 4. e3 Nbd7"] = "Bd3";
    book["1. d4 Nf6 2. Nc3 d5 3. Bg5 Bf5 4. e3 e6"] = "Bd3 | Nf3";
    book["1. d4 Nf6 2. Nc3 d5 3. Bg5 Bf5 4. e3 e6 5. Bd3 Bg6"] = "e4";
    book["1. d4 Nf6 2. Nc3 d5 3. Bg5 Bf5 4. e3 e6 5. Bd3 Bg6 6. e4 dxe4"] = "Bxe4";
    book["1. d4 Nf6 2. Nc3 d5 3. Bg5 Bf5 4. e3 e6 5. Bd3 Bg6 6. e4 dxe4 7. Bxe4 Bxe4"] = "Nxe4";
    book["1. d4 Nf6 2. Nc3 d5 3. Bg5 Bf5 4. e3 e6 5. Bd3 Bg6 6. e4 dxe4 7. Bxe4 Bxe4 8. Nxe4 Qd5"] = "Nxf6+";
    book["1. d4 Nf6 2. Nc3 d5 3. Bg5 Bf5 4. e3 e6 5. Bd3 Bg6 6. e4 dxe4 7. Bxe4 Bxe4 8. Nxe4 Qd5 9. Nxf6+ gxf6"] = "Bxf6";
    book["1. d4 Nf6 2. Nc3 d5 3. Bg5 Bf5 4. e3 e6 5. Bd3 Bg6 6. e4 dxe4 7. Bxe4 Bxe4 8. Nxe4 Qd5 9. Nxf6+ gxf6 10. Bxf6 Qxg2"] = "Qf3";
    book["1. d4 Nf6 2. Nc3 d5 3. Bg5 Bf5 4. e3 e6 5. Bd3 Bg6 6. e4 dxe4 7. Bxe4 Bxe4 8. Nxe4 Qd5 9. Nxf6+ gxf6 10. Bxf6 Qxg2 11. Qf3 Rg8"] = "0-0-0";
    book["1. d4 Nf6 2. Nc3 d5 3. Bg5 Bf5 4. e3 e6 5. Bd3 h6"] = "Bf4";
    book["1. d4 Nf6 2. Nc3 d5 3. Bg5 Bf5 4. e3 e6 5. Bd3 Bxd3"] = "cxd3";
    book["1. d4 Nf6 2. Nc3 d5 3. Bg5 Bf5 4. e3 e6 5. Bd3 Bxd3 6. cxd3 h6"] = "Bf4";


    // Queen's pawn game (D00)
    book["1. d4 d5"] = "c4 | Nf3 | Nc3 | Bg5 | e3 | Bf4";


    // Queen's gambit (D06)
    book["1. d4 d5 2. c4"] = "c6 | e6 | dxc4 | Nc6 | e5";
    book["1. d4 d5 2. c4 c6 3. c5"] = "Nf6 | e5";
    book["1. d4 d5 2. c4 c6 3. c5 Nf6 4. e3"] = "e6 | e5";


    // D10 Queen's Gambit Declined Slav defence -- BLACK
    book["1. d4 d5 2. c4 c6 3. Nc3"] = "Nf6 | dxc4 | e6 | e5";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. e3"] = "e6";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. Nf3"] = "e6";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. cxd5"] = "cxd5";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. Bg5"] = "dxc4";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. Bg5 dxc4 5. e3"] = "b5";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. Bg5 dxc4 5. e4"] = "b5";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. Bg5 dxc4 5. a4"] = "Qb6";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. Bf4"] = "dxc4";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. Bf4 dxc4 5. a4"] = "Nd5";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. Bf4 dxc4 5. e4"] = "b5";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. Bf4 dxc4 5. e3"] = "b5";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. Qb3"] = "dxc4";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. Qb3 dxc4 5. Qxc4"] = "b5";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. g3"] = "dxc4";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. g3 dxc4 5. Bg2"] = "g6";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. g3 dxc4 5. Nf3"] = "g6";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. g3 dxc4 5. e3"] = "b5";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. g3 dxc4 5. e4"] = "e5";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. g3 dxc4 5. a4"] = "e5";


    // D31 Queen's Gambit Declined, semi-Slav -- WHITE
    book["1. d4 d5 2. c4 c6 3. Nc3 e6"] = "e3 | e4 | Nf3";
    book["1. d4 d5 2. c4 c6 3. Nc3 e6 4. e3 Nf6"] = "Nf3";
    book["1. d4 d5 2. c4 c6 3. Nc3 e6 4. e3 Bd6"] = "e4 | Nf3";
    book["1. d4 d5 2. c4 c6 3. Nc3 e6 4. e3 f5"] = "f4 | Bd3 | c5";
    book["1. d4 d5 2. c4 c6 3. Nc3 e6 4. e3 Nd7"] = "Nf3 | Qc2";
    book["1. d4 d5 2. c4 c6 3. Nc3 e6 4. e3 Be7"] = "b3 | Nf3";


    // D11 Queen's Gambit Declined Slav, 3.Nf3 -- BLACK
    book["1. d4 d5 2. c4 c6 3. Nf3"] = "Nf6 | e6 | dxc4";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3"] = "e6 | dxc4 |  a6";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. e3"] = "Bf5 | e6 | Bg4 | a6";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. cxd5"] = "cxd5";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Qc2"] = "dxc4 | g6";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Qb3"] = "dxc4";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Qb3 dxc4 5. Qxc4"] = "Bf5";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. g3"] = "Bf5 | dxc4 | g6";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nbd2"] = "Bf5 | g6 | e6 | a6";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Bg5"] = "dxc4";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Bf4"] = "dxc4";


    // D15 Slav Defense: Three Knights Variation -- WHITE
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6"] = "Bg5 | e3 | Bf4 | cxd5";

    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. Bg5 h6"] = "Bh4 | Bxf6";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. Bg5 h6 6. Bxf6 Qxf6"] = "e3";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. Bg5 dxc4"] = "e4";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. Bg5 Nbd7"] = "e3 | cxd5 | Qb3";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. Bg5 Be7"] = "e3";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. Bg5 Bb4"] = "e3 | Qb3";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. Bg5 Qb6"] = "Qc2";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. Bg5 Qa5"] = "Bxf6";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. Bg5 Qa5 6. Bxf6 gxf6"] = "e3";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. Bg5 a6"] = "e3 | e4";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. Bf4 dxc4"] = "a4";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. Bf4 Nbd7"] = "e3";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. Bf4 Bb4"] = "e3 | Qb3";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. Bf4 Bd6"] = "Bxd6";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. Bf4 Bd6 6. Bxd6 Qxd6"] = "e3";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. cxd5 exd5"] = "Qc2";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. cxd5 cxd5"] = "Bf4 | Bg5";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. cxd5 Nxd5"] = "e4";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. cxd5 Nxd5 6. e4 Nxc3"] = "bxc3";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. cxd5 Nxd5 6. e4 Nxc3 7. bxc3 c5"] = "Bd3";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. e3 a6"] = "b3 | Be2";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. e3 Bd6"] = "Bd3";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. e3 Be7"] = "Bd3 | Qc2";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. e3 Ne4"] = "Bd3 | Nxe4";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. e3 Ne4 6. Nxe4 dxe4"] = "Nd2";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. e3 Ne4 6. Bd3 f5"] = "Ne5";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. e3 Bb4"] = "Bd3 | Qc2";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. e3 g6"] = "Bd3";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. e3 g6 6. Bd3 Bg7"] = "b3";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. e3 dxc4"] = "Bxc4";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. e3 dxc4 6. Bxc4 c5"] = "0-0";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. e3 dxc4 6. Bxc4 b5"] = "Bd3";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. e3 Nbd7"] = "Bd3 | Qc2";



    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 Bf5"] = "cxd5 | Bg5 | Bf4 | e3";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 dxc4"] = "a4 | e4 | e3 | Bg5";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 Bg4"] = "Ne5 | Bg5";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 Nbd7"] = "Bg5 | Bf4 | e3";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 g6"] = "Bg5 | Bf4 | cxd5";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 a6"] = "e3 | cxd5 | Bg5 | c5 | a4 | Bf4";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 a6 5. cxd5 Nxd5"] = "e4";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 a6 5. cxd5 Nxd5 6. e4 Nxc3"] = "bxc3";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 a6 5. cxd5 Nxd5 6. e4 Nf6"] = "h3 | Bc4";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 a6 5. cxd5 cxd5"] = "Bf4 | Bg5 | e3 | a3 | g3 | a4 | Qb3";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 a6 5. cxd5 cxd5 6. Qb3 e6"] = "Bg5 | Bf4";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 a6 5. cxd5 cxd5 6. Qb3 b5"] = "Bg5 | Bf4";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 a6 5. cxd5 cxd5 6. Qb3 Nc6"] = "Bg5 | Bf4";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 a6 5. cxd5 cxd5 6. Qb3 Nc6 7. Bf4 Na5"] = "Qc2";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 a6 5. cxd5 cxd5 6. Qb3 Nc6 7. Bf4 b5"] = "e3";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 a6 5. cxd5 cxd5 6. Qb3 Nc6 7. Bf4 e6"] = "e3";


    // D11 Queen's Gambit Declined Slav, 3.Nf3 -- WHITE
    book["1. d4 d5 2. c4 c6 3. Nf3 Bf5"] = "cxd5 | Nc3";
    book["1. d4 d5 2. c4 c6 3. Nf3 Bf5 4. cxd5 cxd5"] = "Qb3";
    book["1. d4 d5 2. c4 c6 3. Nf3 Bf5 4. cxd5 cxd5 5. Qb3 Nf6"] = "Qxb7";
    book["1. d4 d5 2. c4 c6 3. Nf3 Bf5 4. cxd5 cxd5 5. Qb3 Nf6 6. Qxb7 Nbd7"] = "Nc3";
    book["1. d4 d5 2. c4 c6 3. Nf3 Bf5 4. cxd5 cxd5 5. Qb3 Nc6"] = "Nc3";
    book["1. d4 d5 2. c4 c6 3. Nf3 Bf5 4. cxd5 cxd5 5. Qb3 Bc8"] = "e4";
    book["1. d4 d5 2. c4 c6 3. Nf3 Bf5 4. cxd5 cxd5 5. Qb3 Qb6"] = "Qxd5";
    book["1. d4 d5 2. c4 c6 3. Nf3 Bf5 4. cxd5 cxd5 5. Qb3 Qb6 6. Qxd5 e6"] = "Qb3";
    book["1. d4 d5 2. c4 c6 3. Nf3 Bf5 4. cxd5 cxd5 5. Qb3 Qb6 6. Qxd5 e6 7. Qb3 Qxb3"] = "axb3";



    // D10 Queen's Gambit Declined Slav defence -- WHITE
    book["1. d4 d5 2. c4 c6"] = "Nf3 | Nc3 | cxd5 | e3 | Qc2";
    book["1. d4 d5 2. c4 c6 3. Nf3 Nf6"] = "Nc3";
    book["1. d4 d5 2. c4 c6 3. Nf3 e6"] = "Qc2 | e3";
    book["1. d4 d5 2. c4 c6 3. Nf3 dxc4"] = "e3";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6"] = "e3 | Nf3 | cxd5";
    book["1. d4 d5 2. c4 c6 3. Nc3 dxc4"] = "e4";


    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. Nf3 e6"] = "e3 | Bg5";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. Nf3 e6 5. e3 Bd6"] = "Qc2 | Bd3";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. Nf3 e6 5. e3 a6"] = "Bb4 | Qc2";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. Nf3 e6 5. e3 Nbd7"] = "Qc2 | Be2 | Bd3 | a3";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. Nf3 e6 5. e3 Nbd7 6. Bd3 dxc4"] = "Bxc4";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. Nf3 e6 5. e3 Nbd7 6. Bd3 dxc4 7. Bxc4 c5"] = "0-0";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. Nf3 e6 5. e3 Nbd7 6. Bd3 dxc4 7. Bxc4 a6"] = "a4 | e4 | Bb3";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. Nf3 e6 5. e3 Nbd7 6. Bd3 dxc4 7. Bxc4 Bd6"] = "e4";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. Nf3 e6 5. e3 Nbd7 6. Bd3 dxc4 7. Bxc4 b5"] = "Bd3";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. Nf3 e6 5. e3 Nbd7 6. Bd3 dxc4 7. Bxc4 b5 8. Bd3 b4"] = "Ne4";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. Nf3 e6 5. e3 Nbd7 6. Bd3 dxc4 7. Bxc4 b5 8. Bd3 b4 9. Ne4 Nxe4"] = "Bxe4";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. Nf3 e6 5. e3 Nbd7 6. Bd3 dxc4 7. Bxc4 b5 8. Bd3 b4 9. Ne4 Nxe4 10. Bxe4 Bb7"] = "0-0";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. Nf3 e6 5. e3 Nbd7 6. Bd3 dxc4 7. Bxc4 b5 8. Bd3 a6"] = "e4";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. Nf3 e6 5. e3 Nbd7 6. Bd3 dxc4 7. Bxc4 b5 8. Bd3 Bd6"] = "0-0 | Qc2";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. Nf3 e6 5. e3 Nbd7 6. Bd3 dxc4 7. Bxc4 b5 8. Bd3 Bb7"] = "0-0 | e4 | a3";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. Nf3 e6 5. e3 Nbd7 6. Bd3 dxc4 7. Bxc4 b5 8. Bd3 Bb7 9. 0-0 b4"] = "Na4";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. Nf3 e6 5. e3 Nbd7 6. Bd3 dxc4 7. Bxc4 b5 8. Bd3 Bb7 9. 0-0 Be7"] = "e4";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. Nf3 e6 5. e3 Nbd7 6. Bd3 dxc4 7. Bxc4 b5 8. Bd3 Bb7 9. 0-0 a6"] = "e4";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. Nf3 e6 5. e3 Nbd7 6. Bd3 dxc4 7. Bxc4 b5 8. Bd3 Bb7 9. 0-0 a6 10. e4 c5"] = "e5 | d5";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. Nf3 e6 5. e3 Nbd7 6. Bd3 dxc4 7. Bxc4 b5 8. Bd3 Bb7 9. 0-0 a6 10. e4 c5 11. e5 Nd5"] = "Ng5";
    book["1. d4 d5 2. c4 c6 3. Nc3 Nf6 4. Nf3 e6 5. e3 Nbd7 6. Bd3 dxc4 7. Bxc4 b5 8. Bd3 Bb7 9. 0-0 a6 10. e4 c5 11. e5 Nd5 12. Ng5 Be7"] = "Qh5";


    // D10 Slav Defense: Exchange Variation -- WHITE
    book["1. d4 d5 2. c4 c6 3. cxd5 cxd5"] = "Nc3 | Nf3";
    book["1. d4 d5 2. c4 c6 3. cxd5 cxd5 4. Nc3 Nf6"] = "Bf4 | Nf3";
    book["1. d4 d5 2. c4 c6 3. cxd5 cxd5 4. Nc3 Nc6"] = "Bf4 | e4";



    book["1. d4 d5 2. c4 c5"] = "cxd5 | dxc5";
    book["1. d4 d5 2. c4 c5 3. dxc5 d4 4. Nf3 Nc6"] = "e3";
    book["1. d4 d5 2. c4 c5 3. dxc5 d4 4. Nf3 Nc6 5. e3 e5"] = "exd4";
    book["1. d4 d5 2. c4 c5 3. dxc5 d4 4. Nf3 Nc6 5. e3 e5 6. exd4 exd4"] = "Bd3";


    // D20 Queen's gambit accepted -- BLACK
    book["1. d4 d5 2. c4 dxc4 3. Nf3"] = "a6 | e6 | Nf6";


    // D20 Queen's gambit accepted -- WHITE
    book["1. d4 d5 2. c4 dxc4"] = "Nf3 | e4 | e3";
    book["1. d4 d5 2. c4 dxc4 3. Nf3 Nf6"] = "e3 | Nc3 | Qa4+";
    book["1. d4 d5 2. c4 dxc4 3. Nf3 a6"] = "e3 | a4";
    book["1. d4 d5 2. c4 dxc4 3. Nf3 e6"] = "e3 | Qa4+| e4";
    book["1. d4 d5 2. c4 dxc4 3. Nf3 c5"] = "e3 | e4 | d5";
    book["1. d4 d5 2. c4 dxc4 3. Nf3 c6"] = "e3 | a4 | Nc3";


    // Queen's gambit declined (D07)
    book["1. d4 d5 2. c4 Nc6"] = "Nf3 | Nc3 | cxd5 | e3";
    book["1. d4 d5 2. c4 Nc6 3. Nf3"] = "Bg4 | e6 | e5";
    book["1. d4 d5 2. c4 Nc6 3. Nc3"] = "dxc4 | Nf6";
    book["1. d4 d5 2. c4 Nc6 3. cxd5"] = "Qxd5";
    book["1. d4 d5 2. c4 Nc6 3. cxd5 Qxd5"] = "e3 | Nf3";
    book["1. d4 d5 2. c4 Nc6 3. e3"] = "e5 | Nf6 | e6";

    book["1. d4 d5 2. c4 Nc6 3. c5"] = "e5";
    book["1. d4 d5 2. c4 Nc6 3. c5 e5 4. Nf3"] = "e4";


    // Queen's gambit declined (D30)
    book["1. d4 d5 2. c4 e6"] = "Nc3 | Nf3 | cxd5";

    book["1. d4 d5 2. c4 e6 3. Nc3 Nf6"] = "cxd5 | Bg5 | Nf3 | Bf4";
    book["1. d4 d5 2. c4 e6 3. Nc3 c6"] = "e3 | Nf3 | e4";
    book["1. d4 d5 2. c4 e6 3. Nc3 Be7"] = "Nf3 | cxd5 | Bf4";
    book["1. d4 d5 2. c4 e6 3. Nc3 c5"] = "cxd5 | e3 | Nf3";
    book["1. d4 d5 2. c4 e6 3. Nc3 Bb4"] = "Nf3 | e3 | cxd5 | a3";
    book["1. d4 d5 2. c4 e6 3. Nc3 a6"] = "cxd5";
    book["1. d4 d5 2. c4 e6 3. Nc3 a6 4. cxd5 exd5"] = "Nf3 | Bf4 | Qb3";
    book["1. d4 d5 2. c4 e6 3. Nc3 f5"] = "Nf3 | Bf4";
    book["1. d4 d5 2. c4 e6 3. Nc3 dxc4"] = "e4 | e3 | Nf3";
    book["1. d4 d5 2. c4 e6 3. Nc3 Nc6"] = "Nf3";


    book["1. d4 d5 2. c4 e6 3. Nf3 a6"] = "cxd5";
    book["1. d4 d5 2. c4 e6 3. Nf3 a6 4. cxd5 exd5"] = "Nc3";
    book["1. d4 d5 2. c4 e6 3. Nf3 a6 4. cxd5 Qxd5"] = "Nc3";


    // D30 Queen's gambit declined -- BLACK
    book["1. d4 d5 2. c4 e6 3. Nf3"] = "Nf6 | c6 | c5 | dxc4 | Be7";
    book["1. d4 d5 2. c4 e6 3. Nf3 Nf6 4. Nc3"] = "Be7 | c6 | Bb4";
    book["1. d4 d5 2. c4 e6 3. Nf3 Nf6 4. g3"] = "Be7 | dxc4 | Bb4+";
    book["1. d4 d5 2. c4 e6 3. Nf3 Nf6 4. Bg5"] = "dxc4 | Be7 | h6 | Bb4+";
    book["1. d4 d5 2. c4 e6 3. Nf3 Nf6 4. e3"] = "Be7 | c5 | a6 | c6";
    book["1. d4 d5 2. c4 e6 3. Nf3 Nf6 4. cxd5"] = "exd5";
    book["1. d4 d5 2. c4 e6 3. Nf3 Nf6 4. Qc2"] = "dxc4 | Be7 | c5";
    book["1. d4 d5 2. c4 e6 3. Nf3 Nf6 4. Nbd2"] = "c5";


    // Queen's gambit declined, Albin's counter-gambit (D08)
    book["1. d4 d5 2. c4 e5"] = "dxe5 | e3 | cxd5 | Nc3";
    book["1. d4 d5 2. c4 e5 3. Nc3"] = "dxc4";
    book["1. d4 d5 2. c4 e5 3. Nc3 dxc4"] = "d5 | e3 | Nf3 | dxe5";
    book["1. d4 d5 2. c4 e5 3. Nc3 dxc4 4. exd4"] = "exd4";


    // Queen's pawn, Mason variation (D00)
    book["1. d4 d5 2. Bf4 Bf5 3. e3"] = "e6 | Nf6";
    book["1. d4 d5 2. Bf4 Bf5 3. Nf3"] = "e6 | Nf6";
    book["1. d4 d5 2. Bf4 Bf5 3. Nc3"] = "e6 | c6 | Nf6";

    book["1. d4 d5 2. Bf4 Bf5 3. Nf3 Nc6"] = "e3 | c3";


    book["1. d4 d5 2. Bf4 Bf5 3. Nf3 Nf6 4. e3"] = "e6";
    book["1. d4 d5 2. Bf4 Bf5 3. Nf3 Nf6 4. e3 e6 5. c4"] = "Bxb1";
    book["1. d4 d5 2. Bf4 Bf5 3. Nf3 Nf6 4. e3 e6 5. c4 Bxb1 6. Rxb1"] = "Bb4+";
    book["1. d4 d5 2. Bf4 Bf5 3. Nf3 Nf6 4. e3 e6 5. c4 Bxb1 6. Rxb1 Bb4+ 7. Ke2"] = "dxc4";
    book["1. d4 d5 2. Bf4 Bf5 3. Nf3 Nf6 4. e3 e6 5. Nbd2"] = "Nbd7";

    book["1. d4 d5 2. Bf4 Bf5 3. Nf3 Nf6 4. Nbd2"] = "e6";
    book["1. d4 d5 2. Bf4 Bf5 3. Nf3 Nf6 4. Nbd2 e6 5. e3"] = "Nbd7";
    book["1. d4 d5 2. Bf4 Bf5 3. Nf3 Nf6 4. Nbd2 e6 5. e3 Nbd7 6. Be2"] = "Be7";
    book["1. d4 d5 2. Bf4 Bf5 3. Nf3 Nf6 4. Nbd2 e6 5. e3 Nbd7 6. Be2 Be7 7. c4"] = "0-0";
    book["1. d4 d5 2. Bf4 Bf5 3. Nf3 Nf6 4. Nbd2 e6 5. e3 Nbd7 6. Be2 Be7 7. Nh4"] = "Be4";
    book["1. d4 d5 2. Bf4 Bf5 3. Nf3 Nf6 4. Nbd2 e6 5. e3 Nbd7 6. Be2 Be7 7. 0-0"] = "Nh5 | c5";


    // Queen's pawn game, Chigorin variation (D00)
    book["1. d4 d5 2. Nc3"] = "Nf6 | Bf5 | c6";
    book["1. d4 d5 2. Nc3 Nf6"] = "Bg5 | Bf4";

    book["1. d4 d5 2. Nc3 Nf6 3. Bg5"] = "Nbd7 | Bf5 | e6 | c6 | c5";
    book["1. d4 d5 2. Nc3 Nf6 3. Bf4"] = "Bf5 | c6 | e6";

    book["1. d4 d5 2. Nc3 Nf6 3. Bf4 e6"] = "e3 | Nb5 | Nf3";

    book["1. d4 d5 2. Nc3 g6"] = "e4 | Bf4";
    book["1. d4 d5 2. Nc3 g6 3. e4 dxe4"] = "Nxe4";
    book["1. d4 d5 2. Nc3 g6 3. e4 dxe4 4. Nxe4 Bg7"] = "Nf3";
    book["1. d4 d5 2. Nc3 g6 3. Bf4 Bg7"] = "Qd2 | e3";



    // D00 Queen's Pawn Game: Chigorin Variation -- WHITE
    book["1. d4 d5 2. Nc3 e6"] = "e4 | Bf4";


    // Richter-Veresov attack (D01)
    book["1. d4 d5 2. Nc3 Nf6 3. Bg5 Nbd7"] = "Nf3 | f3 | e3";
    book["1. d4 d5 2. Nc3 Nf6 3. Bg5 Bf5"] = "f3 | Bxf6 | e3";
    book["1. d4 d5 2. Nc3 Nf6 3. Bg5 e6"] = "e4 | Nf3";
    book["1. d4 d5 2. Nc3 Nf6 3. Bg5 c6"] = "e3";
    book["1. d4 d5 2. Nc3 Nf6 3. Bg5 c6 4. e3"] = "Bf5 | Nbd7 | Qb6";
    book["1. d4 d5 2. Nc3 Nf6 3. Bg5 c5"] = "Bxf6";
    book["1. d4 d5 2. Nc3 Nf6 3. Bg5 c5 4. Bxf6"] = "gxf6";
    book["1. d4 d5 2. Nc3 Nf6 3. Bg5 c5 4. Bxf6 gxf6"] = "e3 | e4";

    book["1. d4 d5 2. Bg5"] = "h6 | c6";

    book["1. d4 d5 2. Bg5 Nf6"] = "Bxf6 | e3";


    book["1. d4 d5 2. Nc3 Nf6 3. Bg5 Nc6"] = "e3";
    book["1. d4 d5 2. Nc3 Nf6 3. Bg5 Nc6 4. e3 h6"] = "Bxf6";
    book["1. d4 d5 2. Nc3 Nf6 3. Bg5 Nc6 4. e3 h6 5. Bxf6 exf6"] = "a3";
    book["1. d4 d5 2. Nc3 Nf6 3. Bg5 Nc6 4. e3 h6 5. Bxf6 gxf6"] = "Nge2 | Qh5";
    book["1. d4 d5 2. Nc3 Nf6 3. Bg5 Nc6 4. e3 Bf5"] = "Bb5";


    // D00 Levitsky attack (Queen's bishop attack) -- BLACK
    book["1. d4 d5 2. Bg5 h6 3. Bh4"] = "c6 | c5";
    book["1. d4 d5 2. Bg5 h6 3. Bf4"] = "Nf6 | c5";
    book["1. d4 d5 2. Bg5 h6 3. Bd2"] = "Nf6 | c5";


    // D00 Levitsky attack (Queen's bishop attack) -- BLACK
    book["1. d4 d5 2. Bg5 c6 3. e3"] = "Qb6 | Bf5 | Nf6";
    book["1. d4 d5 2. Bg5 c6 3. e3 Qb6 4. Qc1"] = "Bf5";
    book["1. d4 d5 2. Bg5 c6 3. e3 Qb6 4. b3"] = "Bf5";
    book["1. d4 d5 2. Bg5 c6 3. e3 Qb6 4. b3 Bf5 5. Bd3"] = "Bxd3";
    book["1. d4 d5 2. Bg5 c6 3. e3 Qb6 4. b3 Bf5 5. Bd3 Bxd3 6. Qxd3"] = "Qa6";
    book["1. d4 d5 2. Bg5 c6 3. e3 Qb6 4. b3 Bf5 5. Nf3"] = "e6";


    book["1. d4 d5 2. Bg5 Nc6"] = "e3 | Nf3";
    book["1. d4 d5 2. Bg5 Nc6 3. e3"] = "f6";
    book["1. d4 d5 2. Bg5 Nc6 3. e3 f6"] = "Bh4 | Bf4";
    book["1. d4 d5 2. Bg5 Nc6 3. Nf3"] = "Bg4 | f6";

    book["1. d4 d5 2. Bg5 h6"] = "Bh4";
    book["1. d4 d5 2. Bg5 h6 3. Bh4"] = "c6 | c5 | Nf6";

    book["1. d4 d5 2. Bg5 h6 3. Bh4 g5"] = "Bg3";
    book["1. d4 d5 2. Bg5 h6 3. Bh4 g5 4. Bg3 Bg7"] = "e3";
    book["1. d4 d5 2. Bg5 h6 3. Bh4 g5 4. Bg3 Bg7 5. e3 Nf6"] = "Bd3";
    book["1. d4 d5 2. Bg5 h6 3. Bh4 g5 4. Bg3 Bg7 5. e3 c5"] = "Nf3";
    book["1. d4 d5 2. Bg5 h6 3. Bh4 g5 4. Bg3 Bg7 5. e3 Bf5"] = "Bd3";

    book["1. d4 d5 2. e3"] = "Nf6 | Bf5";
    book["1. d4 d5 2. e3 Nf6"] = "Nf3 | c4";
    book["1. d4 d5 2. e3 Nf6 3. c4"] = "c6";
    book["1. d4 d5 2. e3 e6"] = "Nf3";
    book["1. d4 d5 2. e3 Nc6"] = "c4";

    book["1. d4 d5 2. e3 Bf5"] = "c4 | Nf3 | Bd3";
    book["1. d4 d5 2. e3 Bf5 3. c4 c6"] = "Qb3";
    book["1. d4 d5 2. e3 Bf5 3. c4 e6"] = "Qb3";


    // D00 Queen's Pawn Game -- WHITE
    book["1. d4 d5 2. e3 Nf6"] = "Nf3 | c4";
    book["1. d4 d5 2. e3 Nf6 3. c4 c5"] = "cxd5";
    book["1. d4 d5 2. e3 Nf6 3. c4 c5 4. cxd5 Nxd5"] = "dxc5 | Nc3";
    book["1. d4 d5 2. e3 Nf6 3. c4 c6"] = "Nc3 | Nf3 | Qc2";
    book["1. d4 d5 2. e3 Nf6 3. c4 dxc4"] = "Bxc4 | Nf3";
    book["1. d4 d5 2. e3 Nf6 3. c4 e6"] = "a3 | Nf3 | Be2";
    book["1. d4 d5 2. e3 Nf6 3. c4 e6 4. Nf3 b6"] = "b3 | Nc3 | Bd3";
    book["1. d4 d5 2. e3 Nf6 3. c4 e6 4. Nf3 Be7"] = "Bd3 | Be2 | b3";
    book["1. d4 d5 2. e3 Nf6 3. c4 e6 4. Nf3 Nbd7"] = "Qc2 | b3 | Nc3";
    book["1. d4 d5 2. e3 Nf6 3. c4 e6 4. Nf3 c5"] = "cxd5 | Nc3";
    book["1. d4 d5 2. e3 Nf6 3. c4 e6 4. Nf3 c5 5. cxd5 Nxd5"] = "e4";
    book["1. d4 d5 2. e3 Nf6 3. c4 e6 4. Nf3 c5 5. cxd5 Nxd5 6. e4 Nf6"] = "Nc3";
    book["1. d4 d5 2. e3 Nf6 3. c4 e6 4. Nf3 c5 5. cxd5 Qxd5"] = "Nc3";
    book["1. d4 d5 2. e3 Nf6 3. c4 e6 4. Nf3 c5 5. cxd5 Qxd5 6. Nc3 Qd8"] = "g3";
    book["1. d4 d5 2. e3 Nf6 3. c4 e6 4. Nf3 c5 5. cxd5 exd5"] = "Bb5+";
    book["1. d4 d5 2. e3 Nf6 3. c4 e6 4. Nf3 c5 5. cxd5 exd5 6. Bb5+ Nbd7"] = "Nc3";
    book["1. d4 d5 2. e3 Nf6 3. c4 e6 4. Nf3 c5 5. cxd5 exd5 6. Bb5+ Bd7"] = "Bxd7+";
    book["1. d4 d5 2. e3 Nf6 3. c4 e6 4. Nf3 c5 5. cxd5 exd5 6. Bb5+ Bd7 7. Bxd7+ Qxd7"] = "0-0";
    book["1. d4 d5 2. e3 Nf6 3. c4 e6 4. Nf3 c5 5. cxd5 exd5 6. Bb5+ Bd7 7. Bxd7+ Nbxd7"] = "dxc5";
    book["1. d4 d5 2. e3 Nf6 3. c4 e6 4. Nf3 c5 5. cxd5 exd5 6. Bb5+ Bd7 7. Bxd7+ Nbxd7 8. dxc5 g6"] = "Nc3";
    book["1. d4 d5 2. e3 Nf6 3. c4 e6 4. Nf3 c5 5. cxd5 exd5 6. Bb5+ Bd7 7. Bxd7+ Nbxd7 8. dxc5 g6 9. Nc3 Nxc5"] = "b4";
    book["1. d4 d5 2. e3 Nf6 3. c4 e6 4. Nf3 c5 5. cxd5 exd5 6. Bb5+ Bd7 7. Bxd7+ Nbxd7 8. dxc5 g6 9. Nc3 Nxc5 10. b4 Nce4"] = "Bb2";
    book["1. d4 d5 2. e3 Nf6 3. c4 e6 4. Nf3 c5 5. cxd5 exd5 6. Bb5+ Bd7 7. Bxd7+ Nbxd7 8. dxc5 Nxc5"] = "0-0";




    // D00 Queen's pawn game -- WHITE
    book["1. d4 d5 2. e3 c5"] = "Nf3 | c4";
    book["1. d4 d5 2. e3 c5 3. Nf3 Nf6"] = "c4 | Be2";
    book["1. d4 d5 2. e3 c5 3. Nf3 Nf6 4. Nbd2 Nc6"] = "Bb5";
    book["1. d4 d5 2. e3 c5 3. Nf3 Nf6 4. Nbd2 e6"] = "b3";
    book["1. d4 d5 2. e3 c5 3. Nf3 Nc6"] = "dxc5 | c4 | Bb5";
    book["1. d4 d5 2. e3 c5 3. Nf3 Nc6 4. dxc5 e6"] = "c4";


    // D00 Queen's pawn game -- WHITE
    book["1. d4 d5 2. e3 c6"] = "Bd3 | c4";


    // D00 Queen's pawn game -- BLACK
    book["1. d4 d5 2. e3 Nc6 3. f4"] = "Bf5";
    book["1. d4 d5 2. e3 Nc6 3. f4 Bf5 4. Nf3"] = "Nb4";
    book["1. d4 d5 2. e3 Nc6 3. f4 Bf5 4. Nc3"] = "Nf6";
    book["1. d4 d5 2. e3 Nc6 3. f4 Bf5 4. Bd3"] = "e6";
    book["1. d4 d5 2. e3 Nc6 3. f4 Bf5 4. Nbd2"] = "Nb4";
    book["1. d4 d5 2. e3 Nc6 3. f4 Bf5 4. c3"] = "Nf6";
    book["1. d4 d5 2. e3 Nc6 3. f4 Bf5 4. Bb5"] = "e6";

    book["1. d4 d5 2. e3 Nc6 3. Nf3"] = "Bg4 | Nf6";
    book["1. d4 d5 2. e3 Nc6 3. Nf3 Bg4"] = "Be2 | c4 | Bb5";
    book["1. d4 d5 2. e3 Nc6 3. Nf3 Nf6"] = "c4 | Bd3 | c3";

    book["1. d4 d5 2. e3 Nc6 3. c4"] = "e5 | Nf6 | e6";
    book["1. d4 d5 2. e3 Nc6 3. c4 e5"] = "dxe5 | cxd5";
    book["1. d4 d5 2. e3 Nc6 3. c4 e5 4. dxe5"] = "d4";
    book["1. d4 d5 2. e3 Nc6 3. c4 e5 4. dxe5 d4"] = "a3 | exd4";
    book["1. d4 d5 2. e3 Nc6 3. c4 e5 4. cxd5"] = "Qxd5";
    book["1. d4 d5 2. e3 Nc6 3. c4 e5 4. cxd5 Qxd5"] = "Nc3";
    book["1. d4 d5 2. e3 Nc6 3. c4 e5 4. cxd5 Qxd5 5. Nc3"] = "Bb4";
    book["1. d4 d5 2. e3 Nc6 3. c4 e5 4. cxd5 Qxd5 5. Nc3 Bb4"] = "Bd2";
    book["1. d4 d5 2. e3 Nc6 3. c4 e5 4. cxd5 Qxd5 5. Nc3 Bb4 6. Bd2"] = "Bxc3";
    book["1. d4 d5 2. e3 Nc6 3. c4 e5 4. cxd5 Qxd5 5. Nc3 Bb4 6. Bd2 Bxc3"] = "bxc3 | Bxc3";
    book["1. d4 d5 2. e3 Nc6 3. c4 Nf6"] = "Nc3 | Nf3";
    book["1. d4 d5 2. e3 Nc6 3. c4 e6"] = "Nf3 | Nc3";

    book["1. d4 d5 2. Bf4"] = "Nf6 | e6 | c5 | Bf5 | Nc6";
    book["1. d4 d5 2. Bf4 Nf6"] = "e3 | Nf3";
    book["1. d4 d5 2. Bf4 c5"] = "e3";
    book["1. d4 d5 2. Bf4 c5 3. e3"] = "Nc6";
    book["1. d4 d5 2. Bf4 c5 3. e3 Nc6"] = "c3 | Nf3";
    book["1. d4 d5 2. Bf4 Bf5"] = "e3 | Nf3 | Nc3";
    book["1. d4 d5 2. Bf4 Nc6"] = "e3 | Nf3 | Nc3";
    book["1. d4 d5 2. Bf4 e6"] = "e3 | Nf3";
    book["1. d4 d5 2. Bf4 e6 3. e3"] = "Bd6 | Nf6 | c5";
    book["1. d4 d5 2. Bf4 e6 3. Nf3"] = "Nf6 | c5 | Bd6";

    book["1. d4 d5 2. Bf4 e6 3. e3 Nf6"] = "Nf3 | Nd2 | Bd3";

    book["1. d4 d5 2. Bf4 e6 3. e3 Ne7"] = "c4";

    book["1. d4 d5 2. Bf4 e6 3. Nf3 h6"] = "e3";
    book["1. d4 d5 2. Bf4 e6 3. Nf3 h6 4. e3 Nf6"] = "c4";

    book["1. d4 d5 2. Bf4 e6 3. Nf3 Bb4"] = "c3";
    book["1. d4 d5 2. Bf4 e6 3. Nf3 Bb4 4. c3 Bd6"] = "Bg3";
    book["1. d4 d5 2. Bf4 e6 3. Nf3 Bb4 4. c3 Ba5"] = "e3";

    book["1. d4 d5 2. Bf4 Nc6 3. e3"] = "Nf6 | Bf5";
    book["1. d4 d5 2. Bf4 Nc6 3. Nf3"] = "Bg4 | Nf6";
    book["1. d4 d5 2. Bf4 Nc6 3. Nc3"] = "Nf6";
    book["1. d4 d5 2. Bf4 Nc6 3. Nc3 Nf6"] = "Nb5";
    book["1. d4 d5 2. Bf4 Nc6 3. Nc3 Nf6 4. Nb5"] = "e5";
    book["1. d4 d5 2. Bf4 Nc6 3. Nc3 Nf6 4. Nb5 e5"] = "dxe5";
    book["1. d4 d5 2. Bf4 Nc6 3. Nc3 Nf6 4. Nb5 e5 5. dxe5"] = "Nh5 | Ne4";

    book["1. d4 d5 2. Bf4 Nc6 3. Nf3 Bg4"] = "e3 | Nbd2";
    book["1. d4 d5 2. Bf4 Nc6 3. Nf3 Nf6"] = "e3";
    book["1. d4 d5 2. Bf4 Nc6 3. Nf3 Nf6 4. e3"] = "Bg4 | e6 | Bf5";
    book["1. d4 d5 2. Bf4 Nc6 3. Nf3 Bf5"] = "e3";

    book["1. d4 d5 2. Bf4 c5 3. e3 Nc6 4. c3"] = "Nf6 | Qb6";
    book["1. d4 d5 2. Bf4 c5 3. e3 Nc6 4. Nf3"] = "Nf6 | Bg4";


    // D00 Queen's pawn, Mason variation -- WHITE
    book["1. d4 d5 2. Bf4 Nc6 3. Nf3 Nf6 4. e3 Bf5"] = "Bb5";
    book["1. d4 d5 2. Bf4 Nc6 3. Nf3 Nf6 4. e3 Bf5 5. Bb5 a6"] = "Bxc6+";
    book["1. d4 d5 2. Bf4 Nc6 3. Nf3 Nf6 4. e3 Bf5 5. Bb5 a6 6. Bxc6+ bxc6"] = "c4";
    book["1. d4 d5 2. Bf4 Nc6 3. Nf3 Nf6 4. e3 Bf5 5. Bb5 e6"] = "Ne5";



    // Queen's pawn, Mason variation (D00)
    book["1. d4 d5 2. Bf4 c5 3. e3 Nc6 4. Nf3 Nf6"] = "c3 | Be2";
    book["1. d4 d5 2. Bf4 c5 3. e3 Nc6 4. Nf3 Bg4"] = "Be2";
    book["1. d4 d5 2. Bf4 c5 3. e3 Nc6 4. Nf3 Bg4 5. Be2"] = "e6 | Nf6";


    // Queen's bishop game (D02)
    book["1. d4 d5 2. Bf4 Nf6 3. Nf3"] = "e6 | c5 | Bf5 | c6 | g6";
    book["1. d4 d5 2. Bf4 Nf6 3. Nf3 e6"] = "e3 | Nbd2";
    book["1. d4 d5 2. Bf4 Nf6 3. Nf3 c5"] = "e3 | c3";
    book["1. d4 d5 2. Bf4 Nf6 3. Nf3 Bf5"] = "e3 | c4 | c3 | Nbd2";
    book["1. d4 d5 2. Bf4 Nf6 3. Nf3 c6"] = "e3 | c3 | Nbd2";
    book["1. d4 d5 2. Bf4 Nf6 3. Nf3 g6"] = "e3";
    book["1. d4 d5 2. Bf4 Nf6 3. Nf3 g6 4. e3"] = "Bg7";
    book["1. d4 d5 2. Bf4 Nf6 3. Nf3 g6 4. e3 Bg7"] = "h3 | Bd3 | Be2 | c4";




    // Queen's pawn game (D02)
    book["1. d4 d5 2. Nf3"] = "Nf6 | c6 | e6";

    book["1. d4 d5 2. Nf3 Nf6"] = "c4 | e3 | Bf4";

    book["1. d4 d5 2. Nf3 Nf6 3. e3"] = "e6 | c5";

    book["1. d4 d5 2. Nf3 Nf6 3. e3 e6 4. Bd3"] = "b6";
    book["1. d4 d5 2. Nf3 Nf6 3. e3 e6 4. c3"] = "Nbd7";
    book["1. d4 d5 2. Nf3 Nf6 3. e3 e6 4. b3"] = "Be7";
    book["1. d4 d5 2. Nf3 Nf6 3. e3 c5 4. Be2"] = "b6";


    book["1. d4 d5 2. Nf3 Nf6 3. e3 c5 4. dxc5"] = "e6";
    book["1. d4 d5 2. Nf3 Nf6 3. e3 c5 4. dxc5 e6 5. b4"] = "a5";
    book["1. d4 d5 2. Nf3 Nf6 3. e3 c5 4. dxc5 e6 5. b4 a5 6. c3"] = "axb4";
    book["1. d4 d5 2. Nf3 Nf6 3. e3 c5 4. dxc5 e6 5. b4 a5 6. c3 axb4 7. cxb4"] = "b6";
    book["1. d4 d5 2. Nf3 Nf6 3. e3 c5 4. dxc5 e6 5. c4"] = "Bxc5";
    book["1. d4 d5 2. Nf3 Nf6 3. e3 c5 4. dxc5 e6 5. c4 Bxc5 6. Qc2"] = "dxc4";
    book["1. d4 d5 2. Nf3 Nf6 3. e3 c5 4. dxc5 e6 5. c4 Bxc5 6. Qc2 dxc4 7. Bxc4"] = "Nbd7";
    book["1. d4 d5 2. Nf3 Nf6 3. e3 c5 4. dxc5 e6 5. c4 Bxc5 6. a3"] = "0-0";
    book["1. d4 d5 2. Nf3 Nf6 3. e3 c5 4. dxc5 e6 5. a3"] = "Bxc5";
    book["1. d4 d5 2. Nf3 Nf6 3. e3 c5 4. dxc5 e6 5. a3 Bxc5 6. c4"] = "0-0";
    book["1. d4 d5 2. Nf3 Nf6 3. e3 c5 4. dxc5 e6 5. a3 Bxc5 6. Nbd2"] = "0-0";
    book["1. d4 d5 2. Nf3 Nf6 3. e3 c5 4. dxc5 e6 5. a3 Bxc5 6. Nbd2 0-0 7. c4"] = "a5";



    // D00 Queen's Pawn Game: Veresov Attack -- WHITE
    book["1. d4 d5 2. Nf3 Bf5"] = "Bf4 | c4 | e3";


    book["1. d4 d5 2. Nf3 c6 3. e3"] = "Nf6 | Bf5 | Bg4";

    book["1. d4 d5 2. Nf3 c6 3. Nc3"] = "Nf6";

    book["1. d4 d5 2. Nf3 c6 3. e3 Bf5"] = "Bd3";
    book["1. d4 d5 2. Nf3 c6 3. e3 Bg4"] = "c4";
    book["1. d4 d5 2. Nf3 c6 3. e3 e6"] = "Bd3";
    book["1. d4 d5 2. Nf3 c6 3. e3 Nf6"] = "c4";
    book["1. d4 d5 2. Nf3 c6 3. e3 Nf6 4. c4 Bf5"] = "Nc3";
    book["1. d4 d5 2. Nf3 c6 3. e3 Nf6 4. c4 Bg4"] = "Nc3";
    book["1. d4 d5 2. Nf3 c6 3. e3 Nf6 4. c4 e6"] = "Nbd2";
    book["1. d4 d5 2. Nf3 c6 3. e3 Nf6 4. c4 a6"] = "Be2";


    book["1. d4 d5 2. Nf3 Nf6 3. c4 Nc6"] = "cxd5";
    book["1. d4 d5 2. Nf3 Nf6 3. c4 Nc6 4. cxd5 Qxd5"] = "Nc3";
    book["1. d4 d5 2. Nf3 Nf6 3. c4 Nc6 4. cxd5 Qxd5 5. Nc3 Qa5"] = "Bd2";
    book["1. d4 d5 2. Nf3 Nf6 3. c4 Nc6 4. cxd5 Nxd5"] = "e4";


    // Queen's pawn (A40)
    book["1. d4 e6"] = "c4 | Nf3 | e4";
    book["1. d4 e6 2. e3"] = "d5 | Nf6";
    book["1. d4 e6 2. e3 d5"] = "Bd3 | Nf3 | c4";
    book["1. d4 e6 2. e3 d5 3. a3"] = "Nf6";
    book["1. d4 e6 2. e3 d5 3. a3 Nf6"] = "Nf3";
    book["1. d4 e6 2. e3 d5 3. a3 Nf6 4. Nf3"] = "c5";

    book["1. d4 e6 2. c4"] = "Nf6 | d5";
    book["1. d4 e6 2. c4 Nf6"] = "Nc3 | Nf3 | g3";



    // D02 Queen's Pawn Game: Symmetrical Variation -- BLACK
    book["1. d4 d5 2. Nf3 Nf6 3. c4"] = "c6 | e6";


    // Queen's pawn, Keres defense (A40) -- WHITE
    book["1. d4 e6 2. c4 b6"] = "e4 | Nc3";
    book["1. d4 e6 2. c4 b6 3. e4 Bb7"] = "Bd3";
    book["1. d4 e6 2. c4 b6 3. e4 Bb4+"] = "Bd2";


    book["1. d4 e6 2. c4 Nf6 3. Bd2"] = "c5";

    book["1. d4 e6 2. c3"] = "d5 | Nf6";

    book["1. d4 e6 2. Nf3"] = "Nf6 | c5";
    book["1. d4 e6 2. Nf3 Nf6"] = "c4 | Bg5 | e3 | g3";
    book["1. d4 e6 2. Nf3 c5"] = "e3 | g3";


    // Queen's pawn, Keres defense (A40) -- BLACK
    book["1. d4 e6 2. Nf3 c5 3. c4"] = "cxd4";
    book["1. d4 e6 2. Nf3 c5 3. c4 cxd4 4. Qxd4"] = "Nc6";
    book["1. d4 e6 2. Nf3 c5 3. c4 cxd4 4. Nxd4"] = "Nf6";
    book["1. d4 e6 2. Nf3 c5 3. c4 cxd4 4. Nxd4 Nf6 5. Nc3"] = "d5";
    book["1. d4 e6 2. Nf3 c5 3. c4 cxd4 4. Nxd4 Nf6 5. g3"] = "d5";
    book["1. d4 e6 2. Nf3 c5 3. c4 cxd4 4. Nxd4 Nf6 5. e3"] = "Bc5";
    book["1. d4 e6 2. Nf3 c5 3. c4 cxd4 4. Nxd4 Nf6 5. a3"] = "Be7";
    book["1. d4 e6 2. Nf3 c5 3. c4 cxd4 4. Nxd4 Nf6 5. Nb5"] = "d5";

    book["1. d4 e6 2. Nf3 Nf6 3. c4"] = "b6 | d5";
    book["1. d4 e6 2. Nf3 Nf6 3. c4 b6 4. g3"] = "Ba6 | Bb7";
    book["1. d4 e6 2. Nf3 Nf6 3. c4 b6 4. a3"] = "Bb7";
    book["1. d4 e6 2. Nf3 Nf6 3. c4 d5 4. Nc3"] = "Be7 | Bb4";
    book["1. d4 e6 2. Nf3 Nf6 3. c4 d5 4. Nc3 Bb4 5. cxd5"] = "exd5";
    book["1. d4 e6 2. Nf3 Nf6 3. c4 d5 4. Nc3 Bb4 5. Bg5"] = "dxc4";

    book["1. d4 e6 2. Nf3 Nf6 3. Bf4"] = "c5";
    book["1. d4 e6 2. Nf3 Nf6 3. Bf4 c5 4. e3"] = "Nc6";
    book["1. d4 e6 2. Nf3 Nf6 3. Bf4 c5 4. c3"] = "Nc6";
    book["1. d4 e6 2. Nf3 Nf6 3. Bf4 c5 4. dxc5"] = "Bxc5";


    // A40 Queen's pawn -- WHITE
    book["1. d4 e6 2. Nf3 d5"] = "c4";
    book["1. d4 e6 2. Nf3 d5 3. c4 Nf6"] = "Nc3";
    book["1. d4 e6 2. Nf3 d5 3. c4 d6"] = "e3";
    book["1. d4 e6 2. Nf3 d5 3. c4 c5"] = "cxd5";
    book["1. d4 e6 2. Nf3 d5 3. c4 c5 4. cxd5 exc5"] = "Nc3";
    book["1. d4 e6 2. Nf3 d5 3. c4 dxc4"] = "e3";


    //  A46 Queen's pawn, Yusupov-Rubinstein system -- BLACK
    book["1. d4 e6 2. Nf3 Nf6 3. e3"] = "b6";
    book["1. d4 e6 2. Nf3 Nf6 3. e3 b6 4. Bd3"] = "Bb7";
    book["1. d4 e6 2. Nf3 Nf6 3. e3 b6 4. c4"] = "Bb7";
    book["1. d4 e6 2. Nf3 Nf6 3. e3 b6 4. Nbd2"] = "Bb7";
    book["1. d4 e6 2. Nf3 Nf6 3. e3 b6 4. b3"] = "Bb7";
    

    // Queen's gambit declined (D30)
    book["1. d4 e6 2. c4 d5 3. Nf3"] = "Nf6 | c6";

    book["1. d4 e6 2. c4 d5"] = "cxd5";
    book["1. d4 e6 2. c4 d5 3. cxd5"] = "exd5";
    book["1. d4 e6 2. c4 d5 3. cxd5 exd5"] = "Nc3";
    book["1. d4 e6 2. c4 d5 3. cxd5 exd5 4. Nc3"] = "Nf6 | c6 | c5 | Be7";

    book["1. d4 e6 2. c4 d5 3. cxd5 exd5 4. Nc3 c6"] = "Bf4";

    book["1. d4 e6 2. c4 d5 3. cxd5 exd5 4. Nc3 Nf6"] = "Bg5";
    book["1. d4 e6 2. c4 d5 3. cxd5 exd5 4. Nc3 Nf6 5. Bg5 Be7"] = "e3";


    book["1. d4 e6 2. c4 d5 3. cxd5 exd5 4. Nc3 Nf6"] = "Bg5";
    book["1. d4 e6 2. c4 d5 3. cxd5 exd5 4. Nc3 Nf6 5. Bg5"] = "Be7 | Nbd7";
    book["1. d4 e6 2. c4 d5 3. cxd5 exd5 4. Nc3 c6"] = "Nf3 | Bf4";
    book["1. d4 e6 2. c4 d5 3. cxd5 exd5 4. Nc3 c5"] = "Nf3 | dxc5";
    book["1. d4 e6 2. c4 d5 3. cxd5 exd5 4. Nc3 Be7"] = "Bf4 | Nf3";



    // Queen's gambit declined (D32)
    book["1. d4 e6 2. c4 d5 3. cxd5 exd5 4. Nc3 c5 5. Nf3"] = "Nc6 | Nf6";

    book["1. d4 e6 2. c4 d5 3. cxd5 exd5 4. Nc3 c5 5. Nf3 Nc6 6. dxc5"] = "d4";
    book["1. d4 e6 2. c4 d5 3. cxd5 exd5 4. Nc3 c5 5. Nf3 Nc6 6. dxc5 d4 7. Na4"] = "Bxc5";
    book["1. d4 e6 2. c4 d5 3. cxd5 exd5 4. Nc3 c5 5. Nf3 Nc6 6. Bg5"] = "Be7 | f6";
    book["1. d4 e6 2. c4 d5 3. cxd5 exd5 4. Nc3 c5 5. Nf3 Nc6 6. e3"] = "Nf6 | cxd4";
    book["1. d4 e6 2. c4 d5 3. cxd5 exd5 4. Nc3 c5 5. Nf3 Nc6 6. Bf4"] = "Nf6 | c4";
    book["1. d4 e6 2. c4 d5 3. cxd5 exd5 4. Nc3 c5 5. Nf3 Nc6 6. g3"] = "Nf6 | Be7";
    book["1. d4 e6 2. c4 d5 3. cxd5 exd5 4. Nc3 c5 5. Nf3 Nc6 6. g3 Nf6 7. Bg2"] = "Be7 | c4 | cxd4";
    book["1. d4 e6 2. c4 d5 3. cxd5 exd5 4. Nc3 c5 5. Nf3 Nc6 6. g3 Nf6 7. Bg2 Be7 8. dxc5"] = "Bxc5";
    book["1. d4 e6 2. c4 d5 3. cxd5 exd5 4. Nc3 c5 5. Nf3 Nc6 6. g3 Nf6 7. Bg2 Be7 8. 0-0"] = "0-0";
    book["1. d4 e6 2. c4 d5 3. cxd5 exd5 4. Nc3 c5 5. Nf3 Nc6 6. g3 Nf6 7. Bg2 Be7 8. 0-0 0-0 9. Bg5"] = "c4";
    book["1. d4 e6 2. c4 d5 3. cxd5 exd5 4. Nc3 c5 5. Nf3 Nc6 6. g3 Nf6 7. Bg2 Be7 8. 0-0 0-0 9. Bg5 c4 10. Ne5"] = "Be6";
    book["1. d4 e6 2. c4 d5 3. cxd5 exd5 4. Nc3 c5 5. Nf3 Nc6 6. g3 Nf6 7. Bg2 Be7 8. 0-0 0-0 9. dxc5"] = "Bxc5";
    book["1. d4 e6 2. c4 d5 3. cxd5 exd5 4. Nc3 c5 5. Nf3 Nc6 6. g3 Nf6 7. Bg2 Be7 8. 0-0 0-0 9. dxc5 Bxc5 10. Na4"] = "Be7";
    book["1. d4 e6 2. c4 d5 3. cxd5 exd5 4. Nc3 c5 5. Nf3 Nc6 6. g3 Nf6 7. Bg2 Be7 8. 0-0 0-0 9. dxc5 Bxc5 10. a3"] = "Ne4";
    book["1. d4 e6 2. c4 d5 3. cxd5 exd5 4. Nc3 c5 5. Nf3 Nc6 6. g3 Nf6 7. Bg2 Be7 8. 0-0 0-0 9. dxc5 Bxc5 10. a3 Ne4 11. Qd3"] = "Nxc3";
    book["1. d4 e6 2. c4 d5 3. cxd5 exd5 4. Nc3 c5 5. Nf3 Nc6 6. g3 Nf6 7. Bg2 Be7 8. 0-0 0-0 9. dxc5 Bxc5 10. a3 Ne4 11. Qd3 Nxc3 12. Qxc3"] = "Be7";


    book["1. d4 e6 2. c4 d5 3. cxd5 exd5 4. Nc3 c5 5. Nf3 Nc6"] = "g3 | e3";
    book["1. d4 e6 2. c4 d5 3. cxd5 exd5 4. Nc3 c5 5. dxc5"] = "d4 | Nf6";

    book["1. d4 e6 2. c4 Nf6 3. Nf3"] = "b6 | d5 | Bb4";
    book["1. d4 e6 2. c4 Nf6 3. Nf3 b6"] = "g3 | a3 | Nc3 | e3";

    book["1. d4 e6 2. c4 Nf6 3. Nf3 d5"] = "Nc3 | g3 | Bg5 | e3";


    // E10 Indian Defense: Anti-Nimzo-Indian -- BLACK
    book["1. d4 e6 2. c4 Nf6 3. Nf3 d5 4. e3"] = "b6 | Be7";

    book["1. d4 e6 2. c4 Nf6 3. Nf3 d5 4. e3 b6 5. Nc3"] = "Bb7 | Bd6";
    book["1. d4 e6 2. c4 Nf6 3. Nf3 d5 4. e3 b6 5. Bd3"] = "Bb7 | dxc4 | Bd6";
    book["1. d4 e6 2. c4 Nf6 3. Nf3 d5 4. e3 b6 5. cxd5"] = "exd5";
    book["1. d4 e6 2. c4 Nf6 3. Nf3 d5 4. e3 b6 5. Nbd2"] = "Bb7 | Nbd7";
    book["1. d4 e6 2. c4 Nf6 3. Nf3 d5 4. e3 b6 5. b3"] = "Bb7 | Nbd7";

    book["1. d4 e6 2. c4 Nf6 3. Nf3 d5 4. e3 Be7 5. Nc3"] = "0-0";
    book["1. d4 e6 2. c4 Nf6 3. Nf3 d5 4. e3 Be7 5. b3"] = "c5 | 0-0";
    book["1. d4 e6 2. c4 Nf6 3. Nf3 d5 4. e3 Be7 5. Nbd2"] = "Nbd7 | 0-0";
    book["1. d4 e6 2. c4 Nf6 3. Nf3 d5 4. e3 Be7 5. Bd3"] = "0-0 | dxc4";
    book["1. d4 e6 2. c4 Nf6 3. Nf3 d5 4. e3 Be7 5. Bd3 dxc4 6. Bxc4"] = "a6";
    book["1. d4 e6 2. c4 Nf6 3. Nf3 d5 4. e3 Be7 5. Bd3 dxc4 6. Bxc4 a6 7. 0-0"] = "0-0";
    book["1. d4 e6 2. c4 Nf6 3. Nf3 d5 4. e3 Be7 5. Be2"] = "dxc4 | 0-0";
    book["1. d4 e6 2. c4 Nf6 3. Nf3 d5 4. e3 Be7 5. Be2 dxc4 6. Bxc4"] = "a6";
    book["1. d4 e6 2. c4 Nf6 3. Nf3 d5 4. e3 Be7 5. Be2 dxc4 6. Bxc4 a6 7. 0-0"] = "0-0";




    book["1. d4 e6 2. c4 Nf6 3. Nf3 d5 4. g3"] = "Bb4+";
    book["1. d4 e6 2. c4 Nf6 3. Nf3 d5 4. g3 Bb4+ 5. Bd2"] = "Be7";
    book["1. d4 e6 2. c4 Nf6 3. Nf3 d5 4. g3 Bb4+ 5. Bd2 Be7 6. Bg2"] = "c6";


    book["1. d4 e6 2. c4 Nf6 3. Nf3 Bb4+"] = "Bd2 | Nbd2";

    book["1. d4 e6 2. c4 Nf6 3. Nf3 b6 4. a3"] = "Bb7 | Ba6";
    book["1. d4 e6 2. c4 Nf6 3. Nf3 b6 4. a3 Bb7"] = "Nc3";
    book["1. d4 e6 2. c4 Nf6 3. Nf3 b6 4. a3 Bb7 4. Nc3"] = "d5";
    book["1. d4 e6 2. c4 Nf6 3. Nf3 b6 4. a3 Bb7 4. Nc3 d5"] = "cxd5 | Bg5";

    book["1. d4 e6 2. c4 d5 3. e3"] = "Nf6";

    book["1. d4 e6 2. c4 d5 3. e3 Nf6 4. Bd3"] = "dxc4";
    book["1. d4 e6 2. c4 d5 3. e3 Nf6 4. Bd3 dxc4 5. Bxc4"] = "c5";

    book["1. d4 e6 2. c4 Nf6 3. Nc3"] = "Bb4 | d5";

    book["1. d4 e6 2. c4 Nf6 3. Nc3 Bb4 4. e3"] = "0-0";
    book["1. d4 e6 2. c4 Nf6 3. Nc3 Bb4 4. Qc2"] = "0-0";
    book["1. d4 e6 2. c4 Nf6 3. Nc3 Bb4 4. Nf3"] = "c5 | b6";
    book["1. d4 e6 2. c4 Nf6 3. Nc3 Bb4 4. Bg5"] = "h6 | c5";
    book["1. d4 e6 2. c4 Nf6 3. Nc3 Bb4 4. Bd2"] = "0-0";
    book["1. d4 e6 2. c4 Nf6 3. Nc3 Bb4 4. a3"] = "Bxc3+";
    book["1. d4 e6 2. c4 Nf6 3. Nc3 Bb4 4. a3 Bxc3+ 5. bxc3"] = "0-0";

    book["1. d4 e6 2. c4 Nf6 3. Nc3 d5 4. Bg5"] = "Be7 | Nbd7";
    book["1. d4 e6 2. c4 Nf6 3. Nc3 d5 4. cxd5"] = "exd5";
    book["1. d4 e6 2. c4 Nf6 3. Nc3 d5 4. Nf3"] = "Be7 | c6 | Bb4";
    book["1. d4 e6 2. c4 Nf6 3. Nc3 d5 4. e3"] = "Be7 | c6 | c5";
    book["1. d4 e6 2. c4 Nf6 3. Nc3 d5 4. Bf4"] = "c6 | Be7";


    // 15 Queen's Indian Defense: Fianchetto Variation, Nimzowitsch -- WHITE
    book["1. d4 e6 2. c4 Nf6 3. Nf3 b6 4. g3 Ba6"] = "Qc2 | Nbd2 | b3";
    book["1. d4 e6 2. c4 Nf6 3. Nf3 b6 4. g3 Ba6 5. Nbd2 Bb7"] = "Bg2";
    book["1. d4 e6 2. c4 Nf6 3. Nf3 b6 4. g3 Ba6 5. Nbd2 d5"] = "Bg2";
    book["1. d4 e6 2. c4 Nf6 3. Nf3 b6 4. g3 Ba6 5. Nbd2 c5"] = "e4";
    book["1. d4 e6 2. c4 Nf6 3. Nf3 b6 4. g3 Ba6 5. Nbd2 Bb4"] = "Qc2 | Qa4";


    // D51 Queen's Gambit Declined, 4.Bg5 Nbd7 -- BLACK
    book["1. d4 e6 2. c4 Nf6 3. Nc3 d5 4. Bg5 Nbd7 5. e3"] = "Be7";
    book["1. d4 e6 2. c4 Nf6 3. Nc3 d5 4. Bg5 Nbd7 5. e3 Be7 6. Nf3"] = "0-0";
    book["1. d4 e6 2. c4 Nf6 3. Nc3 d5 4. Bg5 Nbd7 5. e3 Be7 6. Nf3 0-0 7. cxd5"] = "Nxd5";
    book["1. d4 e6 2. c4 Nf6 3. Nc3 d5 4. Bg5 Nbd7 5. e3 Be7 6. Nf3 0-0 7. Bd3"] = "h6";
    book["1. d4 e6 2. c4 Nf6 3. Nc3 d5 4. Bg5 Nbd7 5. e3 Be7 6. Nf3 0-0 7. Bd3 h6 8. Bh4"] = "b6";


    // Queen's gambit declined (D31) -- BLACK
    book["1. d4 e6 2. c4 d5 3. Nc3"] = "Nf6 | c6";
    book["1. d4 e6 2. c4 d5 3. Nc3 c6 4. e3"] = "Nf6";
    book["1. d4 e6 2. c4 d5 3. Nc3 c6 4. e4"] = "dxe4";
    book["1. d4 e6 2. c4 d5 3. Nc3 c6 4. e4 dxe4 5. Nxe4"] = "Bb4+";
    book["1. d4 e6 2. c4 d5 3. Nc3 c6 4. cxd5"] = "exd5";
    book["1. d4 e6 2. c4 d5 3. Nc3 c6 4. Bf4"] = "dxc4";
    book["1. d4 e6 2. c4 d5 3. Nc3 c6 4. Nf3"] = "Nf6";
    book["1. d4 e6 2. c4 d5 3. Nc3 c6 4. Nf3 Nf6 5. e3"] = "Nbd7";
    book["1. d4 e6 2. c4 d5 3. Nc3 c6 4. Nf3 Nf6 5. Bg5"] = "dxc4";
    book["1. d4 e6 2. c4 d5 3. Nc3 c6 4. Nf3 Nf6 5. cxd5"] = "exd5";
    book["1. d4 e6 2. c4 d5 3. Nc3 c6 4. Nf3 Nf6 5. Qd3"] = "dxc4";
    book["1. d4 e6 2. c4 d5 3. Nc3 c6 4. Nf3 Nf6 5. Qd3 dxc4 6. Qxc4"] = "b5";
    book["1. d4 e6 2. c4 d5 3. Nc3 c6 4. Nf3 Nf6 5. Qd3 dxc4 6. Qxc4 b5 7.  Qd3"] = "Ba6";


    // Reti opening (A05)
    book["1. Nf3 Nf6"] = "c4 | g3 | d4";
    book["1. Nf3 Nf6 2. c4"] = "g6 | e6 | c5";
    book["1. Nf3 Nf6 2. g3"] = "g6 | d5";
    book["1. Nf3 Nf6 2. d4"] = "g6 | e6 | d5";

    book["1. Nf3 Nf6 2. g3 d5"] = "Bg2 | c4";
    book["1. Nf3 Nf6 2. g3 d5 3. Bg2"] = "c6 | e6 | Bf5 | g6 | c5";
    book["1. Nf3 Nf6 2. g3 d5 3. c4"] = "c6 | e6 | dxc4";

    book["1. Nf3 Nf6 2. g3 d5 3. Bg2 g6"] = "0-0 | c4";
    book["1. Nf3 Nf6 2. g3 d5 3. Bg2 g6 4. 0-0"] = "Bg7";
    book["1. Nf3 Nf6 2. g3 d5 3. Bg2 g6 4. 0-0 Bg7"] = "d3 | d4 | c4";
    book["1. Nf3 Nf6 2. g3 d5 3. Bg2 g6 4. c4"] = "c6 | Bg7 | dxc4";


    // A05 King's Indian Attack -- WHITE
    book["1. Nf3 Nf6 2. g3 d5 3. c4 c6"] = "d4 | Bg2";
    book["1. Nf3 Nf6 2. g3 d5 3. c4 e6"] = "d4 | Bg2";
    book["1. Nf3 Nf6 2. g3 d5 3. c4 d4"] = "b4 | Bg2";
    book["1. Nf3 Nf6 2. g3 d5 3. c4 dxc4"] = "Bg2 | Qa4+";
    book["1. Nf3 Nf6 2. g3 d5 3. c4 dxc4 4.Qa4+ Nbd7"] = "Bg2 | Qxc4";
    book["1. Nf3 Nf6 2. g3 d5 3. c4 dxc4 4.Qa4+ c6"] = "Qxc4";
    book["1. Nf3 Nf6 2. g3 d5 3. c4 dxc4 4.Qa4+ c6 5. Qxc4 b5"]  ="Qb3";
    book["1. Nf3 Nf6 2. g3 d5 3. c4 dxc4 4.Qa4+ c6 5. Qxc4 b5 6. Qb3 Bb7"] = "Bg2";
    book["1. Nf3 Nf6 2. g3 d5 3. c4 dxc4 4.Qa4+ c6 5. Qxc4 b5 6. Qb3 e6"] = "Bg2";
    book["1. Nf3 Nf6 2. g3 d5 3. c4 dxc4 4.Qa4+ Bd7"] = "Qxc4";
    book["1. Nf3 Nf6 2. g3 d5 3. c4 dxc4 4.Qa4+ Bd7 5. Qxc4 c5"] = "Ne5";
    book["1. Nf3 Nf6 2. g3 d5 3. c4 dxc4 4.Qa4+ Nc6"] = "Bg2";
    book["1. Nf3 Nf6 2. g3 d5 3. c4 dxc4 4.Qa4+ Nc6 5. Bg2 Nd7"] = "Qxc4";
    book["1. Nf3 Nf6 2. g3 d5 3. c4 dxc4 4.Qa4+ Nc6 5. Bg2 Bd7"] = "Qxc4";


    // King's Indian, Torre attack (A48)
    book["1. Nf3 Nf6 2. d4 g6"] = "c4 | g3 | Bg5";
    book["1. Nf3 Nf6 2. d4 g6 3. c4"] = "Bg7 | c5 | d6 | d5";
    book["1. Nf3 Nf6 2. d4 g6 3. g3"] = "Bg7 | d5 | c5";
    book["1. Nf3 Nf6 2. d4 g6 3. Bg5"] = "Bg7 | Ne4";

    book["1. Nf3 Nf6 2. d4 g6 3. Bg5 c6"] = "Nbd2";


    // E60 King's Indian Defense: Normal Variation, King's Knight Variation -- WHITE
    book["1. Nf3 Nf6 2. d4 g6 3. c4 Bg7"] = "g3 | Nc3 | a3 | e3";
    book["1. Nf3 Nf6 2. d4 g6 3. c4 Bg7 4. Nc3 0-0"] = "e4";
    book["1. Nf3 Nf6 2. d4 g6 3. c4 Bg7 4. Nc3 d6"] = "e4 | h3 | g3";
    book["1. Nf3 Nf6 2. d4 g6 3. c4 Bg7 4. Nc3 d5"] = "Bg5 | cxd5 | Qb3";
    book["1. Nf3 Nf6 2. d4 g6 3. c4 Bg7 4. Nc3 d5 5. Bg5 c5"] = "dxc5 | Bxf6";
    book["1. Nf3 Nf6 2. d4 g6 3. c4 Bg7 4. Nc3 d5 5. Bg5 c6"] = "cxd5 | e3";
    book["1. Nf3 Nf6 2. d4 g6 3. c4 Bg7 4. Nc3 d5 5. Bg5 dxc4"] = "e4";
    book["1. Nf3 Nf6 2. d4 g6 3. c4 Bg7 4. Nc3 d5 5. Bg5 Ne4"] = "Bf4";
    book["1. Nf3 Nf6 2. d4 g6 3. c4 Bg7 4. Nc3 d5 5. Bg5 Ne4 6. Bf4 0-0"] = "e3 | Nxd5";
    book["1. Nf3 Nf6 2. d4 g6 3. c4 Bg7 4. Nc3 d5 5. Bg5 Ne4 6. Bf4 Nc3"] = "bxc3";
    book["1. Nf3 Nf6 2. d4 g6 3. c4 Bg7 4. Nc3 d5 5. Bg5 Ne4 6. Bf4 c5"] = "e3";



    // A15 English Opening: Anglo-Indian Defense, King's Knight Variation -- WHITE
    book["1. Nf3 Nf6 2. c4 c5"] = "Nc3 | d4";
    book["1. Nf3 Nf6 2. c4 c5 3. Nc3 d5"] = "cxd5";
    book["1. Nf3 Nf6 2. c4 c5 3. Nc3 d5 4. cxd5 Nxd5"] = "d4";
    book["1. Nf3 Nf6 2. c4 c5 3. Nc3 e6"] = "g3 | e4 | e3";
    book["1. Nf3 Nf6 2. c4 c5 3. Nc3 Nc6"] = "g3 | d4 | e3";

    book["1. Nf3 Nf6 2. c4 c5 3. d4 e6"] = "d5";
    book["1. Nf3 Nf6 2. c4 c5 3. d4 e6 4. d5 d6"] = "Nc3 | h3";
    book["1. Nf3 Nf6 2. c4 c5 3. d4 e6 4. d5 g6"] = "h3 | Nc3 | dxe6";
    book["1. Nf3 Nf6 2. c4 c5 3. d4 e6 4. d5 g6 5. dxe6 fxe6"] = "g3";
    book["1. Nf3 Nf6 2. c4 c5 3. d4 e6 4. d5 g6 5. dxe6 fxe6 6. g3 Bg7"] = "Bg2";
    book["1. Nf3 Nf6 2. c4 c5 3. d4 e6 4. d5 g6 5. dxe6 dxe6"] = "Qxd8+";
    book["1. Nf3 Nf6 2. c4 c5 3. d4 e6 4. d5 g6 5. dxe6 dxe6 6. Qxd8+ Kxd8"] = "Bf4";
    book["1. Nf3 Nf6 2. c4 c5 3. d4 e6 4. d5 b5"] = "Bf4 | dxe6";
    book["1. Nf3 Nf6 2. c4 c5 3. d4 e6 4. d5 exd5"] = "cxd5";


    // English opening (A15)
    book["1. Nf3 Nf6 2. c4 e6"] = "g3 | Nc3 | d4";
    book["1. Nf3 Nf6 2. c4 e6 3. g3"] = "d5 | b6";
    book["1. Nf3 Nf6 2. c4 e6 3. Nc3"] = "d5 | Bb4 | c5";
    book["1. Nf3 Nf6 2. c4 e6 3. d4"] = "b6 | d5 | Bb4 | c5";


    book["1. Nf3 Nf6 2. g3 e5"] = "Nxe5";
    book["1. Nf3 Nf6 2. g3 e5 3. Nxe5"] = "d6";
    book["1. Nf3 Nf6 2. g3 e5 3. Nxe5 d6"] = "Nf3";
    book["1. Nf3 Nf6 2. g3 e5 3. Nxe5 d6 4. Nf3"] = "Bf5";
    book["1. Nf3 Nf6 2. g3 e5 3. Nxe5 d6 4. Nf3 Bf5"] = "d3";
    book["1. Nf3 Nf6 2. g3 e5 3. Nxe5 d6 4. Nf3 Bf5 5. d3"] = "Be6";
    book["1. Nf3 Nf6 2. g3 e5 3. Nxe5 d6 4. Nf3 Bf5 5. d3 Be6"] = "Bg2";

    book["1. Nf3 Nf6 2. c4 Nc6"] = "d4 | Nc3";

    book["1. Nf3 Nf6 2. c4 Nc6 3. d4 e6"] = "a3";
    book["1. Nf3 Nf6 2. c4 Nc6 3. d4 e6 5. a3 d6"] = "e3";
    book["1. Nf3 Nf6 2. c4 Nc6 3. d4 e6 5. a3 g6"] = "Nc3";
    book["1. Nf3 Nf6 2. c4 Nc6 3. d4 e6 5. a3 g6 6. Nc3 Bg7"] = "e4";
    book["1. Nf3 Nf6 2. c4 Nc6 3. d4 e6 5. a3 Be7"] = "d5";


    book["1. Nf3 Nf6 2. c4 Nc6 3. Nc3 e5"] = "g3 | e3 | d4";
    book["1. Nf3 Nf6 2. c4 Nc6 3. Nc3 e5 4. d4 exd4"] = "Nxd4";
    book["1. Nf3 Nf6 2. c4 Nc6 3. Nc3 e5 4. d4 exd4 5. Nxd4 Bb4"] = "Bg5";
    book["1. Nf3 Nf6 2. c4 Nc6 3. Nc3 e5 4. d4 exd4 5. Nxd4 Bc5"] = "Nxc6";

    book["1. Nf3 Nf6 2. c4 Nc6 3. Nc3 e5 4. d4 exd4 5. Nxd4 Nxd4"] = "Qxd4";
    book["1. Nf3 Nf6 2. c4 Nc6 3. Nc3 e5 4. d4 exd4 5. Nxd4 Nxd4 6. Qxd4 Be7"] = "e4";
    book["1. Nf3 Nf6 2. c4 Nc6 3. Nc3 e5 4. d4 exd4 5. Nxd4 Nxd4 6. Qxd4 d6"] = "Bg5";

    book["1. Nf3 Nf6 2. g3 g6"] = "Bg2";
    book["1. Nf3 Nf6 2. g3 g6 3. Bg2"] = "Bg7 | d5";



    // A05 King's Indian Attack: Symmetrical Defense -- WHITE
    book["1. Nf3 Nf6 2. g3 g6 3. Bg2 Bg7"] = "0-0 | c4 | d4";
    book["1. Nf3 Nf6 2. g3 g6 3. Bg2 Bg7 4. d4 0-0"] = "0-0 | c4 | b3";
    book["1. Nf3 Nf6 2. g3 g6 3. Bg2 Bg7 4. d4 d5"] = "0-0 | c4";
    book["1. Nf3 Nf6 2. g3 g6 3. Bg2 Bg7 4. d4 c5"] = "0-0 | c4";
    book["1. Nf3 Nf6 2. g3 g6 3. Bg2 Bg7 4. d4 d6"] = "0-0 | c4";
    book["1. Nf3 Nf6 2. g3 g6 3. Bg2 Bg7 4. d4 c6"] = "0-0 | c4";
    book["1. Nf3 Nf6 2. g3 g6 3. Bg2 Bg7 4. d4 b6"] = "0-0 | c4";


    book["1. Nf3 Nf6 2. g3 g6 3. Bg2 d5"] ="0-0 | c4";


    // A15 English Opening: Anglo-Indian Defense, King's Indian -- WHITE
    book["1. Nf3 Nf6 2. c4 g6"] = "Nc3 | g3 | d4";
    book["1. Nf3 Nf6 2. c4 g6 3. Nc3 Bg7"] = "e4 | g3 | d4";
    book["1. Nf3 Nf6 2. c4 g6 3. Nc3 d5"] = "cxd5 | Qa4+ | d4";
    book["1. Nf3 Nf6 2. c4 g6 3. Nc3 d5 4. d4 Bg7"] = "Qb3 | cxd5";
    book["1. Nf3 Nf6 2. c4 g6 3. Nc3 c5"] = "d4 | e4";
    book["1. Nf3 Nf6 2. c4 g6 3. Nc3 d6"] = "d4 | g3 | e4";
    book["1. Nf3 Nf6 2. c4 g6 3. Nc3 d6 4. d4 Bg7"] = "e4 | g3 | Bg5";
    book["1. Nf3 Nf6 2. c4 g6 3. Nc3 d6 4. g3 Bg7"] = "Bg2";
    book["1. Nf3 Nf6 2. c4 g6 3. Nc3 d6 4. e4 Bg7"] = "d4 | Be2";
    book["1. Nf3 Nf6 2. c4 g6 3. g3 Bg7"] = "Bg2 | d4";
    book["1. Nf3 Nf6 2. c4 g6 3. g3 c6"] = "Bg2 | b3";
    book["1. Nf3 Nf6 2. c4 g6 3. g3 c6 4. Bg2 Bg7"] = "b3";
    book["1. Nf3 Nf6 2. c4 g6 3. g3 c6 4. b3 Bg7"] = "Bb2 | Bg2";
    book["1. Nf3 Nf6 2. c4 g6 3. g3 c5"] = "Bg2 | b3 | d4";
    book["1. Nf3 Nf6 2. c4 g6 3. g3 c5 4. d4 Bg7"] = "Nc3 | d5 | Bg2";
    book["1. Nf3 Nf6 2. c4 g6 3. g3 c5 4. b3 Bg7"] = "Bb2";
    book["1. Nf3 Nf6 2. c4 g6 3. g3 c5 4. Bg2 Bg7"] = "d4 | Nc3";
    book["1. Nf3 Nf6 2. c4 g6 3. g3 b6"] = "Bg2 | d4";
    book["1. Nf3 Nf6 2. c4 g6 3. g3 b6 4. Bg2 Bg7"] = "d4";
    book["1. Nf3 Nf6 2. c4 g6 3. g3 b6 4. Bg2 Bb7"] = "d4";
    book["1. Nf3 Nf6 2. c4 g6 3. g3 b6 4. d4 Bg7"] = "Nc3 | Bg2";
    book["1. Nf3 Nf6 2. c4 g6 3. g3 d5"] = "cxd5";
    book["1. Nf3 Nf6 2. c4 g6 3. g3 d5 4. cxd5 Nxd5"] = "Bg2";
    book["1. Nf3 Nf6 2. c4 g6 3. g3 d6"] = "Bg2 | d4";
    book["1. Nf3 Nf6 2. c4 g6 3. g3 d6 4. Bg2 Bg7"] = "d4 | Nc3";
    book["1. Nf3 Nf6 2. c4 g6 3. g3 d6 4. d4 Bg7"] = "Bg2";
    book["1. Nf3 Nf6 2. c4 g6 3. d4 Bg7"] = "Nc3 | g3 | e3";
    book["1. Nf3 Nf6 2. c4 g6 3. d4 Bg7 4. Nc3 0-0"] = "e4";
    book["1. Nf3 Nf6 2. c4 g6 3. d4 Bg7 4. g3 0-0"] = "Bg2 | Nc3";
    book["1. Nf3 Nf6 2. c4 g6 3. d4 Bg7 4. e3 0-0"] = "Be2";
    book["1. Nf3 Nf6 2. c4 g6 3. d4 c5"] = "Nc3 | d5 | g3";
    book["1. Nf3 Nf6 2. c4 g6 3. d4 d6"] = "Nc3 | g3";
    book["1. Nf3 Nf6 2. c4 g6 3. d4 d6 4. Nc3 Bg7"] = "e4";
    book["1. Nf3 Nf6 2. c4 g6 3. d4 d6 4. g3 Bg7"] = "Bg2";
    book["1. Nf3 Nf6 2. c4 g6 3. d4 d5"] = "cxd5";
    book["1. Nf3 Nf6 2. c4 g6 3. d4 d5 4. cxd5 Bg7"] = "Qa4+";
    book["1. Nf3 Nf6 2. c4 g6 3. d4 d5 4. cxd5 Bg7 5. Qa4+ Bd7"] = "Qb3";
    book["1. Nf3 Nf6 2. c4 g6 3. d4 d5 4. cxd5 Bg7 5. Qa4+ Nbd7"] = "Nc3";
    book["1. Nf3 Nf6 2. c4 g6 3. d4 d5 4. cxd5 Bg7 5. Qa4+ Qd7"] = "Qxd7+";
    book["1. Nf3 Nf6 2. c4 g6 3. d4 d5 4. cxd5 Bg7 5. Qa4+ Qd7 6. Qxd7+ Bxd7"] = "Nc3";
    book["1. Nf3 Nf6 2. c4 g6 3. d4 d5 4. cxd5 Bg7 5. Qa4+ c6"] = "dxc6";
    book["1. Nf3 Nf6 2. c4 g6 3. d4 d5 4. cxd5 Bg7 5. Qa4+ c6 6. dxc6 Nxc6"] = "Nc3";
    book["1. Nf3 Nf6 2. c4 g6 3. d4 d5 4. cxd5 Nxd5"] = "e4";
    book["1. Nf3 Nf6 2. c4 g6 3. d4 d5 4. cxd5 Nxd5 5. e4 Nb6"] = "h3";
    book["1. Nf3 Nf6 2. c4 g6 3. d4 c6"] = "Nc3";
    book["1. Nf3 Nf6 2. c4 g6 3. d4 c6 4. Nc3 Bg7"] = "e4";
    book["1. Nf3 Nf6 2. c4 g6 3. d4 c6 4. Nc3 d5"] = "cxd5";
    book["1. Nf3 Nf6 2. c4 g6 3. d4 c6 4. Nc3 d5 5. cxd5 cxd5"] = "Bf4";
    book["1. Nf3 Nf6 2. c4 g6 3. d4 c6 4. Nc3 d5 5. cxd5 Nxd5"] = "e4";
    book["1. Nf3 Nf6 2. c4 g6 3. d4 b6"] = "Nc3";
    book["1. Nf3 Nf6 2. c4 g6 3. d4 b6 4. Nc3 Bg7"] = "e4";
    book["1. Nf3 Nf6 2. c4 g6 3. d4 b6 4. Nc3 Bb7"] = "Qc2";


    // Reti opening (A06)
    book["1. Nf3 d5"] = "g3 | d4 | c4";

    book["1. Nf3 d5 2. d4"] = "Nf6 | c6 | e6 | Nc6";
    book["1. Nf3 d5 2. d4 Nf6"] = "c4 | e3 | Bf4 | Bg5 | g3";
    book["1. Nf3 d5 2. d4 c6"] = "c4 | e3 | Bf4 | g3";
    book["1. Nf3 d5 2. d4 e6"] = "c4 | e3 | Bf4 | g3";
    book["1. Nf3 d5 2. d4 Nc6"] = "Bf4 | c4 | g3 | e3";

    book["1. Nf3 d5 2. d4 Nc6 3. Bf4 Nf6"] = "e3";
    book["1. Nf3 d5 2. d4 Nc6 3. Bf4 Nf6 4. e3 Bg4"] = "Be2 | Nbd2";
    book["1. Nf3 d5 2. d4 Nc6 3. Bf4 Nf6 4. e3 e6"] = "Nbd2 | c4";
    book["1. Nf3 d5 2. d4 Nc6 3. Bf4 Nf6 4. e3 Bf5"] = "c4";

    book["1. Nf3 d5 2. g3 Bg4"] = "Bg2 | Ne5";
    book["1. Nf3 d5 2. g3 Bg4 3. Bg2"] = "Nd7 | c6 | e6";
    book["1. Nf3 d5 2. g3 Bg4 3. Ne5"] = "Bf5";
    book["1. Nf3 d5 2. g3 Bg4 3. Ne5 Bf5"] = "c4 | Bg2";

    book["1. Nf3 d5 2. g3 Bg4 3. Bg2 Bxf3"] = "Bxf3";
    book["1. Nf3 d5 2. g3 Bg4 3. Bg2 Bxf3 4. Bxf3 c6"] = "0-0";
    book["1. Nf3 d5 2. g3 Bg4 3. Bg2 Bxf3 4. Bxf3 e6"] = "d4";
    book["1. Nf3 d5 2. g3 Bg4 3. Bg2 Bxf3 4. Bxf3 Nf6"] = "0-0";
    book["1. Nf3 d5 2. g3 Bg4 3. Bg2 Bxf3 4. Bxf3 Nc6"] = "c4";
    book["1. Nf3 d5 2. g3 Bg4 3. Bg2 Bxf3 4. Bxf3 e5"] = "c4";
    book["1. Nf3 d5 2. g3 Bg4 3. Bg2 Bxf3 4. Bxf3 e5 5. c4 c6"] = "Qb3";
    book["1. Nf3 d5 2. g3 Bg4 3. Bg2 Bxf3 4. Bxf3 e5 5. c4 e4"] = "Bg2";

    book["1. Nf3 d5 2. c4"] = "c6 | e6 | d4 | dxc4";
    book["1. Nf3 d5 2. c4 c6"] = "e3 | b3 | d4 | g3";
    book["1. Nf3 d5 2. c4 c6 3. e3"] = "Nf6 | e6";
    book["1. Nf3 d5 2. c4 c6 3. b3"] = "Nf6 | Bg4 | Bf5";
    book["1. Nf3 d5 2. c4 c6 3. d4"] = "Nf6 | e6 | dxc4";

    book["1. Nf3 d5 2. d5 c4"] = "b4 | g3";

    book["1. Nf3 d5 2. c4 e6"] = "g3 | d4";
    book["1. Nf3 d5 2. c4 e6 3. g3"] = "Nf6 | dxc4 | c6";
    book["1. Nf3 d5 2. c4 e6 3. d4"] = "Nf6 | c6 | c5";
    book["1. Nf3 d5 2. c4 e6 3. cxd5"] = "exd5"; 
    book["1. Nf3 d5 2. c4 e6 3. cxd5 exd5 4. Nc3"] = "Nf6";



    // A07 King's Indian Attack: Sicilian Variation -- WHITE
    book["1. Nf3 d5 2. g3 c5"] = "Bg2 | Ne5";
    book["1. Nf3 d5 2. g3 c5 3. Bg2 Nf6"] = "0-0";
    book["1. Nf3 d5 2. g3 c5 3. Bg2 g6"] = "c4 | d4";
    book["1. Nf3 d5 2. g3 c5 3. Bg2 e6"] = "0-0 | d3 | c4";
    book["1. Nf3 d5 2. g3 c5 3. Bg2 Nc6"] = "d4";
    book["1. Nf3 d5 2. g3 c5 3. Bg2 Nc6 4. d4 e6"] = "0-0";
    book["1. Nf3 d5 2. g3 c5 3. Bg2 Nc6 4. d4 Nf6"] = "0-0 | dxc5";
    book["1. Nf3 d5 2. g3 c5 3. Bg2 Nc6 4. d4 cxd4"] = "Nxd4";
    book["1. Nf3 d5 2. g3 c5 3. Bg2 Nc6 4. d4 cxd4 5. Nxd4 Nf6"] = "c4";
    book["1. Nf3 d5 2. g3 c5 3. Bg2 Nc6 4. d4 cxd4 5. Nxd4 e6"] = "0-0 | c4";
    book["1. Nf3 d5 2. g3 c5 3. Bg2 Nc6 4. d4 cxd4 5. Nxd4 e5"] = "Nxc6";
    book["1. Nf3 d5 2. g3 c5 3. Bg2 Nc6 4. d4 cxd4 5. Nxd4 e5 6. Nxc6 bxc6"] = "c4";



    // D02 Queen's Pawn Game: Zukertort Variation -- BLACK
    book["1. Nf3 d5 2. d4 e6 3. Bf4"] = "Nf6 | c5 | Bd6";
    book["1. Nf3 d5 2. d4 e6 3. Bf4 Nf6 4. Nbd2"] = "Bd6 | b6 | Be7";
    book["1. Nf3 d5 2. d4 e6 3. Bf4 Nf6 4. h3"] = "c5 | Bd6 | Nc6";
    book["1. Nf3 d5 2. d4 e6 3. Bf4 Nf6 4. c3"] = "Bd6 | c5";
    book["1. Nf3 d5 2. d4 e6 3. Bf4 Nf6 4. e3"] = "Be7 | c5 | Bd6";
    book["1. Nf3 d5 2. d4 e6 3. Bf4 Nf6 4. e3 Bd6 5. Bxd6"] = "Qxd6";
    book["1. Nf3 d5 2. d4 e6 3. Bf4 Nf6 4. e3 Bd6 5. Bg3"] = "0-0 | c5";
    book["1. Nf3 d5 2. d4 e6 3. Bf4 Nf6 4. e3 Bd6 5. a3"] = "Bxf4 | 0-0";
    book["1. Nf3 d5 2. d4 e6 3. Bf4 Nf6 4. e3 Bd6 5. Bb5+"] = "c6 | Bd7";
    book["1. Nf3 d5 2. d4 e6 3. Bf4 Nf6 4. e3 Bd6 5. Bb5+ c6 6. Be2"] = "Bxf4";
    book["1. Nf3 d5 2. d4 e6 3. Bf4 Nf6 4. e3 Bd6 5. Bb5+ c6 6. Be2 Bxf4 7. exf4"] = "Qd6";
    book["1. Nf3 d5 2. d4 e6 3. Bf4 Nf6 4. e3 Bd6 5. Bb5+ c6 6. Bd3"] = "Bxf4";
    book["1. Nf3 d5 2. d4 e6 3. Bf4 Nf6 4. e3 Bd6 5. Bb5+ c6 6. Bd3 Bxf4 7. exf4"] = "Qd6";
    book["1. Nf3 d5 2. d4 e6 3. Bf4 Nf6 4. e3 Bd6 5. Bb5+ c6 6. Bxd6"] = "Qxd6";
    book["1. Nf3 d5 2. d4 e6 3. Bf4 Nf6 4. e3 Bd6 5. Bb5+ c6 6. Bxd6 Qxd6 7. Bf1"] = "Qb4+";
    book["1. Nf3 d5 2. d4 e6 3. Bf4 Nf6 4. e3 Bd6 5. Bb5+ c6 6. Bxd6 Qxd6 7. Bf1 Qb4+ 8. Nbd2"] = "Qxb2";
    book["1. Nf3 d5 2. d4 e6 3. Bf4 Nf6 4. e3 Bd6 5. Bb5+ c6 6. Bxd6 Qxd6 7. Be2"] = "Qb4+";
    book["1. Nf3 d5 2. d4 e6 3. Bf4 Nf6 4. e3 Bd6 5. Bb5+ c6 6. Bxd6 Qxd6 7. Be2 Qb4+ 8. Nbd2"] = "Qxb2";
    book["1. Nf3 d5 2. d4 e6 3. Bf4 Nf6 4. e3 Bd6 5. Bb5+ c6 6. Bxd6 Qxd6 7. Bd3"] = "Qb4+";
    book["1. Nf3 d5 2. d4 e6 3. Bf4 Nf6 4. e3 Bd6 5. Bb5+ c6 6. Bxd6 Qxd6 7. Bd3 Qb4+ 8. Nbd2"] = "Qxb2";
    book["1. Nf3 d5 2. d4 e6 3. Bf4 Nf6 4. e3 Bd6 5. Bb5+ c6 6. Bxd6 Qxd6 7. Bd3 Qb4+ 8. Nbd2 Qxb2 9. 0-0"] = "0-0";
    book["1. Nf3 d5 2. d4 e6 3. Bf4 Nf6 4. e3 Bd6 5. Bb5+ c6 6. Bxd6 Qxd6 7. Bd3 Qb4+ 8. Nbd2 Qxb2 9. 0-0 0-0 10. e4"] = "dxe4";
    book["1. Nf3 d5 2. d4 e6 3. Bf4 Nf6 4. e3 Bd6 5. Bb5+ c6 6. Bxd6 Qxd6 7. Bd3 Qb4+ 8. Nbd2 Qxb2 9. 0-0 0-0 10. e4 dxe4 11. Nxe4"] = "Nbd7";
    book["1. Nf3 d5 2. d4 e6 3. Bf4 Nf6 4. e3 Bd6 5. Bb5+ c6 6. Bxd6 Qxd6 7. Bd3 Qb4+ 8. Nbd2 Qxb2 9. 0-0 0-0 10. e4 dxe4 11. Bxe4"] = "Nbd7";
    book["1. Nf3 d5 2. d4 e6 3. Bf4 Nf6 4. e3 Bd6 5. Bb5+ c6 6. Bxd6 Qxd6 7. Bd3 Qb4+ 8. Nbd2 Qxb2 9. 0-0 0-0 10. c4"] = "Qa3";
    book["1. Nf3 d5 2. d4 e6 3. Bf4 Nf6 4. e3 Bd6 5. Bb5+ c6 6. Bxd6 Qxd6 7. Bd3 Qb4+ 8. Nbd2 Qxb2 9. 0-0 0-0 10. c4 Qa3 12. Qb3"] = "Qxb3";
    book["1. Nf3 d5 2. d4 e6 3. Bf4 Nf6 4. e3 Bd6 5. Bb5+ c6 6. Bxd6 Qxd6 7. Bd3 Qb4+ 8. Nbd2 Qxb2 9. 0-0 0-0 10. c4 Qa3 12. Qb3 Qxb3 13. axb3"] = "Re8";
    book["1. Nf3 d5 2. d4 e6 3. Bf4 Nf6 4. e3 Bd6 5. Bb5+ c6 6. Bxd6 Qxd6 7. Bd3 Qb4+ 8. Nbd2 Qxb2 9. 0-0 0-0 10. c4 Qa3 12. Qb3 Qxb3 13. axb3 Re8 14. Be2"] = "Nbd7";
    book["1. Nf3 d5 2. d4 e6 3. Bf4 Nf6 4. e3 Bd6 5. Bb5+ c6 6. Bxd6 Qxd6 7. Bd3 Qb4+ 8. Nbd2 Qxb2 9. 0-0 0-0 10. c4 Qa3 12. Qb3 Qxb3 13. axb3 Re8 14. h3"] = "Nbd7";



    // D02 Queen's Pawn Game: Chigorin Variation -- BLACK
    book["1. Nf3 d5 2. d4 Nc6 3. c4"] = "dxc4 | e6";



    // Queen's pawn game (D02)
    book["1. Nf3 d5 2. d4 Nf6 3. c4 e6"] = "Nc3";
    book["1. Nf3 d5 2. d4 Nf6 3. c4 c6"] = "Nc3 | e3";
    book["1. Nf3 d5 2. d4 Nf6 3. c4 dxc4"] = "e3";
    book["1. Nf3 d5 2. d4 Nf6 3. c4 c5"] = "cxd5";
    book["1. Nf3 d5 2. d4 Nf6 3. c4 g6"] = "cxd5";
    book["1. Nf3 d5 2. d4 Nf6 3. c4 g6 4. cxd5 Nxd5"] = "e4";
    book["1. Nf3 d5 2. d4 Nf6 3. c4 g6 4. cxd5 Bg7"] = "Qa4+";
    book["1. Nf3 d5 2. d4 Nf6 3. c4 g6 4. cxd5 Qxd5"] = "Nc3";
    book["1. Nf3 d5 2. d4 Nf6 3. c4 g6 4. cxd5 Qxd5 5. Nc3 Qa5"] = "Bd2";
    book["1. Nf3 d5 2. d4 Nf6 3. c4 g6 4. cxd5 Qxd5 5. Nc3 Qd8"] = "e4";
    book["1. Nf3 d5 2. d4 Nf6 3. c4 g6 4. cxd5 Qxd5 5. Nc3 Qd8 6. e4 Bg7"] = "Qa4+";


    // D13 Queen's Gambit Declined Slav, exchange variation -- BLACK
    book["1. Nf3 d5 2. d4 Nf6 3. c4 c6 4. cxd5"] = "cxd5";
    book["1. Nf3 d5 2. d4 Nf6 3. c4 c6 4. cxd5 cxd5 5. e3"] = "Nc6";
    book["1. Nf3 d5 2. d4 Nf6 3. c4 c6 4. cxd5 cxd5 5. Bf4"] = "Qb6";
    book["1. Nf3 d5 2. d4 Nf6 3. c4 c6 4. cxd5 cxd5 5. g3"] = "Bf5";
    book["1. Nf3 d5 2. d4 Nf6 3. c4 c6 4. cxd5 cxd5 5. Bg5"] = "Ne4";
    book["1. Nf3 d5 2. d4 Nf6 3. c4 c6 4. cxd5 cxd5 5. Qb3"] = "Nc6";
    book["1. Nf3 d5 2. d4 Nf6 3. c4 c6 4. cxd5 cxd5 5. Nc3"] = "Nc6";
    book["1. Nf3 d5 2. d4 Nf6 3. c4 c6 4. cxd5 cxd5 5. Nc3 Nc6 6. e3"] = "a6";
    book["1. Nf3 d5 2. d4 Nf6 3. c4 c6 4. cxd5 cxd5 5. Nc3 Nc6 6. g3"] = "Bf5";
    book["1. Nf3 d5 2. d4 Nf6 3. c4 c6 4. cxd5 cxd5 5. Nc3 Nc6 6. Bf4"] = "Nh5";



    // Torre attack (D03)
    book["1. Nf3 d5 2. d4 Nf6 3. c4"] = "e6 | c6 | dxc4";
    book["1. Nf3 d5 2. d4 Nf6 3. e3"] = "e6 | Bf5 | Bg4 | c6 | c5 | g6";
    book["1. Nf3 d5 2. d4 Nf6 3. Bf4"] = "e6 | c5 | Bf5 | c6 | g6";
    book["1. Nf3 d5 2. d4 Nf6 3. Bg5"] = "e6 | Ne4";
    book["1. Nf3 d5 2. d4 Nf6 3. g3"] = "e6 | c6 | Bf5 | g6";
    book["1. Nf3 d5 2. d4 Nf6 3. g3 Bg4"] = "Bg2";

    book["1. Nf3 d5 2. d4 Nf6 3. g3 e6"] = "Bg2";

    book["1. Nf3 d5 2. d4 Nf6 3. g3 e6 4. Bg2 Be7"] = "0-0";
    book["1. Nf3 d5 2. d4 Nf6 3. g3 e6 4. Bg2 c5"] = "0-0";

    book["1. Nf3 d5 2. d4 Nf6 3. Bg5 e6 4. Nbd2"] = "Nbd7 | Be7 | c5";
    book["1. Nf3 d5 2. d4 Nf6 3. Bg5 e6 4. Bh4"] = "c5";
    book["1. Nf3 d5 2. d4 Nf6 3. Bg5 e6 4. c4"] = "dxc4 | h6 | c6";
    book["1. Nf3 d5 2. d4 Nf6 3. Bg5 e6 4. e3"] = "c5 | h6 | Be7";
    book["1. Nf3 d5 2. d4 Nf6 3. Bg5 e6 4. e3 Be7 5. c3"] = "h6";
    book["1. Nf3 d5 2. d4 Nf6 3. Bg5 e6 4. e3 Be7 5. Nbd2"] = "c5";
    book["1. Nf3 d5 2. d4 Nf6 3. Bg5 e6 4. e3 Be7 5. c4"] = "0-0 | dxc4 | h6"; 
    book["1. Nf3 d5 2. d4 Nf6 3. Bg5 e6 4. e3 Be7 5. Bd3"] = "h6";
    book["1. Nf3 d5 2. d4 Nf6 3. Bg5 e6 4. e3 Be7 5. Bd3 h6 6. Bh4"] = "Nbd7";
    book["1. Nf3 d5 2. d4 Nf6 3. Bg5 e6 4. e3 Be7 5. Bd3 h6 6. Bf4"] = "c5";


    // Queen's bishop game (D02)
    book["1. Nf3 d5 2. d4 Nf6 3. Bf4 e6"] = "e3 | Nbd2";
    book["1. Nf3 d5 2. d4 Nf6 3. Bf4 c5"] = "e3 | c3 | dxc5";
    book["1. Nf3 d5 2. d4 Nf6 3. Bf4 Bf5"] = "e3 | c4 | c3";
    book["1. Nf3 d5 2. d4 Nf6 3. Bf4 c6"] = "e3 | c3 | Nbd2";
    book["1. Nf3 d5 2. d4 Nf6 3. Bf4 g6"] = "e3";
    book["1. Nf3 d5 2. d4 Nf6 3. Bf4 g6 e3"] = "Bg7";
    book["1. Nf3 d5 2. d4 Nf6 3. Bf4 g6 e3 4. Bg7"] = "h3 | Bd3 | Be2 | c4";


    // Reti opening (A07)
    book["1. Nf3 d5 2. g3 e6"] = "Bg2";
    book["1. Nf3 d5 2. g3 e6 3. Bg2"] = "Nf6 | c5";


    // Reti accepted (A09)
    book["1. Nf3 d5 2. c4 dxc4"] = "e3";
    book["1. Nf3 d5 2. c4 dxc4 3. e3"] = "Nf6 | Be6";
    book["1. Nf3 d5 2. c4 dxc4 3. e3 Nf6"] = "Bxc4";
    book["1. Nf3 d5 2. c4 dxc4 3. e3 Nf6 4. Bxc4"] = "e6";
    book["1. Nf3 d5 2. c4 dxc4 3. e3 Nf6 4. Bxc4 e6"] = "0-0 | d4";
    book["1. Nf3 d5 2. c4 dxc4 3. e3 Be6"] = "Na3 | Ng5";

    book["1. Nf3 d5 2. c4 dxc4 3. e3 Nf6 4. Bxc4 e6 5. 0-0"] = "c5 | a6";
    book["1. Nf3 d5 2. c4 dxc4 3. e3 Nf6 4. Bxc4 e6 5. d4"] = "c5 | a6";

    book["1. Nf3 d5 2. c4 dxc4 3. e3 Nf6 4. Bxc4 e6 5. 0-0 c5"] = "d4 | Qe2";
    book["1. Nf3 d5 2. c4 dxc4 3. e3 Nf6 4. Bxc4 e6 5. 0-0 a6"] = "d4";
    book["1. Nf3 d5 2. c4 dxc4 3. e3 Nf6 4. Bxc4 e6 5. 0-0 a6 6. d4"] = "c5 | b5";

    book["1. Nf3 d5 2. c4 c6 3. g3"] = "Nf6 | Bg4 | dxc4";

    book["1. Nf3 d5 2. c4 c6 3. g3 Bg4"] = "Bg2"; 
    book["1. Nf3 d5 2. c4 c6 3. g3 Bg4 4. Bg2"] = "e6 | Nf6 | Nd7";

    book["1. Nf3 d5 2. c4 c6 3. g3 Bg4 4. Bg2 e6"] = "0-0 | cxd5";
    book["1. Nf3 d5 2. c4 c6 3. g3 Bg4 4. Bg2 Nf6"] = "Ne5 | cxd5 | 0-0";
    book["1. Nf3 d5 2. c4 c6 3. g3 Bg4 4. Bg2 Nd7"] = "cxd5";
    book["1. Nf3 d5 2. c4 c6 3. g3 Bg4 4. Bg2 Nd7 5. cxd5"] = "cxd5";
    book["1. Nf3 d5 2. c4 c6 3. g3 Bg4 4. Bg2 Nd7 5. cxd5 cxd5"] = "Nc3 | Qa4 | Qb3";

    // Reti opening (A09)
    book["1. Nf3 d5 2. c4 Nf6"] = "cxd5 | g3 | d4";


    // A07 Reti, King's Indian attack (Barcza system) -- WHITE
    book["1. Nf3 d5 2. g3 c6 3. Bg2 Nf6"] = "0-0";
    book["1. Nf3 d5 2. g3 c6 3. Bg2 Nf6 4. 0-0 Bg4"] = "d3";
    book["1. Nf3 d5 2. g3 c6 3. Bg2 Nf6 4. 0-0 Bf5"] = "d3";
    book["1. Nf3 d5 2. g3 c6 3. Bg2 Nf6 4. 0-0 g6"] = "d3";
    book["1. Nf3 d5 2. g3 c6 3. Bg2 Nf6 4. 0-0 g6 5. d3 Bg7"] = "Nbd2";
    book["1. Nf3 d5 2. g3 c6 3. Bg2 Nf6 4. 0-0 Nbd7"] = "d4";
    book["1. Nf3 d5 2. g3 c6 3. Bg2 Nf6 4. 0-0 h6"] = "d3";
    book["1. Nf3 d5 2. g3 c6 3. Bg2 Nf6 4. 0-0 e6"] = "b3";
    book["1. Nf3 d5 2. g3 c6 3. Bg2 Nf6 4. 0-0 e6 5. b3 Bd6"] = "Bb2";
    book["1. Nf3 d5 2. g3 c6 3. Bg2 Nf6 4. 0-0 e6 5. b3 Be7"] = "Bb2";


    // Reti opening, King's Indian attack (A07)
    book["1. Nf3 d5 2. g3"] = "Nf6 | c6";
    book["1. Nf3 d5 2. g3 Nf6"] = "Bg2";
    book["1. Nf3 d5 2. g3 Nf6 3. Bg2"] = "c6 | e6 | Bf5 | g6";
    book["1. Nf3 d5 2. g3 c6"] = "Bg2";
    book["1. Nf3 d5 2. g3 c6 3. Bg2"] = "Bg4 | Nf6 | Bf5";
    book["1. Nf3 d5 2. g3 Nf6 3. Bg2 g6"] = "0-0 | c4";
    book["1. Nf3 d5 2. g3 Nf6 3. Bg2 g6 4. 0-0"] = "Bg7";
    book["1. Nf3 d5 2. g3 Nf6 3. Bg2 g6 4. 0-0 Bg7"] = "d3 | d4 | c4";
    book["1. Nf3 d5 2. g3 Nf6 3. Bg2 g6 4. c4"] = "c6 | Bg7 | dxc4";

    book["1. Nf3 d5 2. g3 Nf6 3. Bg2 g6 4. c4 c6"] = "b3 | 0-0 | cxd5";
    book["1. Nf3 d5 2. g3 Nf6 3. Bg2 g6 4. c4 Bg7"] = "cxd5 | 0-0 | d4";
    book["1. Nf3 d5 2. g3 Nf6 3. Bg2 g6 4. c4 dxc4"] = "Qa4+ | Na3";

    book["1. Nf3 d5 2. g3 Nf6 3. Bg2 g6 4. 0-0 Bg7 5. d3"] = "0-0";
    book["1. Nf3 d5 2. g3 Nf6 3. Bg2 g6 4. 0-0 Bg7 5. d3 0-0"] = "Nbd2 | c3 | Nc3";
    book["1. Nf3 d5 2. g3 Nf6 3. Bg2 g6 4. 0-0 Bg7 5. d4"] = "0-0 | c6";
    book["1. Nf3 d5 2. g3 Nf6 3. Bg2 g6 4. 0-0 Bg7 5. c4"] = "0-0";
    book["1. Nf3 d5 2. g3 Nf6 3. Bg2 g6 4. 0-0 Bg7 5. c4 0-0"] = "cxd5 | d4";

    book["1. Nf3 d5 2. g3 Nf6 3. Bg2 g6 4. 0-0 Bg7 5. d4 0-0"] = "c4 | Nbd2";
    book["1. Nf3 d5 2. g3 Nf6 3. Bg2 g6 4. 0-0 Bg7 5. d4 c6"] = "c4 | Nbd2";

    book["1. Nf3 d5 2. g3 Nf6 3. Bg2 g6 4. 0-0 Bg7 5. d3 0-0 6. Nbd2"] = "c5 | Nc6";
    book["1. Nf3 d5 2. g3 Nf6 3. Bg2 g6 4. 0-0 Bg7 5. d3 0-0 6. c3"] = "c5 | c6 | Nc6";
    book["1. Nf3 d5 2. g3 Nf6 3. Bg2 g6 4. 0-0 Bg7 5. d3 0-0 6. Nc3"] = "c5 | d4 | Nc6";

    book["1. Nf3 d5 2. g3 Nf6 3. Bg2 Bf5"] = "0-0 | d3 | c4";
    book["1. Nf3 d5 2. g3 Nf6 3. Bg2 Bf5 4. 0-0"] = "e6 | c6";
    book["1. Nf3 d5 2. g3 Nf6 3. Bg2 Bf5 4. d3"] = "e6";
    book["1. Nf3 d5 2. g3 Nf6 3. Bg2 Bf5 4. d3 e6"] = "0-0 | Nbd2";
    book["1. Nf3 d5 2. g3 Nf6 3. Bg2 Bf5 4. c4"] = "c6 | e6";

    book["1. Nf3 d5 2. g3 Nf6 3. Bg2 Bg4"] = "0-0";
    book["1. Nf3 d5 2. g3 Nf6 3. Bg2 Bg4 4. 0-0 e6"] = "d3";


    // A05 King's Indian Attack -- BLACK
    book["1. Nf3 d5 2. g3 Nf6 3. Bg2 e6 4. 0-0"] = "c5 | c6 | Bd6";


    // Reti opening (A04)
    book["1. Nf3 c5"] = "c4 | g3 | e4 | b3";
    book["1. Nf3 c5 2. c4"] = "Nc6 | Nf6 | g6 | b6 | e6";
    book["1. Nf3 c5 2. g3"] = "Nc6 | g6 | b6 | d5";
    book["1. Nf3 c5 2. e4"] = "d6 | Nc6 | e6 | g6";
    book["1. Nf3 c5 2. b3"] = "Nc6 | Nf6 | d5 | d6";


    book["1. Nf3 c5 2. c4 Nf6"] = "Nc3 | g3 | d4";
    book["1. Nf3 c5 2. c4 g6"] = "d4";
    book["1. Nf3 c5 2. c4 b6"] = "g3 | d4 | Nc3";
    book["1. Nf3 c5 2. c4 e6"] = "g3 | Nc3";
    book["1. Nf3 c5 2. c4 d6"] = "d4 | Nc3";
    book["1. Nf3 c5 2. c4 d5"] = "cxd5";
    book["1. Nf3 c5 2. c4 Nc6"] = "Nc3 | d4 | b3 | g3";
    book["1. Nf3 c5 2. c4 Nc6 3. Nc3 g6"] = "e3 | g3";
    book["1. Nf3 c5 2. c4 Nc6 3. Nc3 e5"] = "g3 | e3 | d3";
    book["1. Nf3 c5 2. c4 Nc6 3. Nc3 e6"] = "g3 | e3";
    book["1. Nf3 c5 2. c4 Nc6 3. Nc3 Nd4"] = "h3 | g3 | e3";
    book["1. Nf3 c5 2. c4 Nc6 3. Nc3 Nf6"] = "g3 | d4";


    // A04 Zukertort Opening: Sicilian Invitation -- BLACK
    book["1. Nf3 c5 2. c4 e6 3. Nc3"] = "Nf6 | Nc6";
    book["1. Nf3 c5 2. c4 e6 3. Nc3 Nf6 4. e3"] = "Nc6 | Be7";
    book["1. Nf3 c5 2. c4 e6 3. Nc3 Nf6 4. e4"] = "Nc6";
    book["1. Nf3 c5 2. c4 e6 3. Nc3 Nf6 4. d4"] = "cxd4";
    book["1. Nf3 c5 2. c4 e6 3. Nc3 Nf6 4. d4 cxd4 5. Qxd4"] = "Nc6";
    book["1. Nf3 c5 2. c4 e6 3. Nc3 Nf6 4. d4 cxd4 5. Nxd4"] = "Nc6 | Bb4 | d5";
    book["1. Nf3 c5 2. c4 e6 3. Nc3 Nf6 4. g3"] = "d5 | Be7 | Qb6";
    book["1. Nf3 c5 2. c4 e6 3. Nc3 Nf6 4. g3 d5 5. cxd5"] = "exd5 | Nxd5";
    book["1. Nf3 c5 2. c4 e6 3. Nc3 Nf6 4. g3 d5 5. Bg2"] = "d4";
    book["1. Nf3 c5 2. c4 e6 3. Nc3 Nf6 4. g3 Be7 5. Bg2"] = "d5 | 0-0";
    book["1. Nf3 c5 2. c4 e6 3. Nc3 Nf6 4. g3 Be7 5. d4"] = "cxd4";
    book["1. Nf3 c5 2. c4 e6 3. Nc3 Nf6 4. g3 Be7 5. d4 cxd4 6. Nxd4"] = "d5";
    book["1. Nf3 c5 2. c4 e6 3. Nc3 Nf6 4. g3 Be7 5. d4 cxd4 6. Qxd4"] = "Nc6";
    book["1. Nf3 c5 2. c4 e6 3. Nc3 Nf6 4. g3 Qb6 5. Bg2"] = "Nc6";
    book["1. Nf3 c5 2. c4 e6 3. Nc3 Nf6 4. g3 Qb6 5. e4"] = "Nc6";
    book["1. Nf3 c5 2. c4 e6 3. Nc3 Nf6 4. g3 Qb6 5. b3"] = "Be7 | Nc6";
    book["1. Nf3 c5 2. c4 e6 3. Nc3 Nf6 4. g3 Qb6 5. b3 Be7 6. Bg2"] = "Nc6";
    book["1. Nf3 c5 2. c4 e6 3. Nc3 Nf6 4. g3 Qb6 5. b3 Nc6 6. Bg2"] = "Be7";


    book["1. Nf3 c5 2. d4"] = "cxd4";
    book["1. Nf3 c5 2. d4 cxd4 3. Qxd4"] = "Nc6";
    book["1. Nf3 c5 2. d4 cxd4 3. Nxd4"] = "d5";
    book["1. Nf3 c5 2. d4 cxd4 3. c3"] = "dxc3";
    book["1. Nf3 c5 2. d4 cxd4 3. c3 dxc3 4. Nxc3"] = "d6";
    book["1. Nf3 c5 2. d4 cxd4 3. e4"] = "dxe3";
    book["1. Nf3 c5 2. d4 cxd4 3. e4 dxe3 4. Bxe3"] = "Nc6";


    book["1. Nf3 c5 2. g3 b6 3. e4"] = "Bb7";
    book["1. Nf3 c5 2. g3 b6 3. e4 Bb7 4. Bg2"] = "Bxe4";
    book["1. Nf3 c5 2. g3 b6 3. e4 Bb7 4. d3"] = "e6";
    book["1. Nf3 c5 2. g3 b6 3. e4 Bb7 4. Nc3"] = "Nf6";
    book["1. Nf3 c5 2. g3 b6 3. e4 Bb7 4. Qe2"] = "Nc6";
    book["1. Nf3 c5 2. g3 b6 3. c4"] = "Bb7";
    book["1. Nf3 c5 2. g3 b6 3. b3"] = "Bb7";
    book["1. Nf3 c5 2. g3 b6 3. Bg2"] = "Bb7";


    book["1. Nf3 c5 2. b3 Nc6"] = "Bb2";
    book["1. Nf3 c5 2. b3 Nc6 3. Bb2"] = "d6 | d5 | Nf6";
    book["1. Nf3 c5 2. b3 Nf6"] = "Bb2";
    book["1. Nf3 c5 2. b3 Nf6 3. Bb2"] = "e6 | Nc6 | g6";
    book["1. Nf3 c5 2. b3 Nf6 3. Bb2 g6"] = "d6 | d5";
    book["1. Nf3 c5 2. b3 Nf6 3. Bb2 g6 4. d6"] = "Ne4";
    book["1. Nf3 c5 2. b3 Nf6 3. Bb2 g6 4. d5"] = "e3";


    book["1. Nf3 c5 2. b3 d5"] = "e3 | Bb2";
    book["1. Nf3 c5 2. b3 d6"] = "Bb2";
    book["1. Nf3 c5 2. b3 d6 3. Bb2"] = "e5";
    book["1. Nf3 c5 2. b3 d6 3. Bb2 e5"] = "e4";
    book["1. Nf3 c5 2. b3 d6 3. Bb2 e5 4. e4"] = "Nf6 | Nc6";

    book["1. Nf3 c5 2. g3 Nc6"] = "Bg2 | d4 | c4";
    book["1. Nf3 c5 2. g3 Nc6 3. Bg2"] = "g6 | d5 | e5 | Nf6";
    book["1. Nf3 c5 2. g3 Nc6 3. d4"] = "cxd4 | e6";
    book["1. Nf3 c5 2. g3 Nc6 3. c4"]= "g6 | e5 | Nf6";

    book["1. Nf3 c5 2. g3 g6"] = "Bg2";
    book["1. Nf3 c5 2. g3 g6 3. Bg2"] = "Bg7";
    book["1. Nf3 c5 2. g3 g6 3. Bg2 Bg7"] = "0-0 | c4 | d4";
    book["1. Nf3 c5 2. g3 g6 3. Bg2 Bg7 4. 0-0"] = "Nc6";
    book["1. Nf3 c5 2. g3 g6 3. Bg2 Bg7 4. 0-0 Nc6"] = "d3 | c4";
    book["1. Nf3 c5 2. g3 g6 3. Bg2 Bg7 4. c4"] = "Nc6";
    book["1. Nf3 c5 2. g3 g6 3. Bg2 Bg7 4. c4 Nc6"] = "Nc3 | 0-0";
    book["1. Nf3 c5 2. g3 g6 3. Bg2 Bg7 4. d4"] = "cxd4";
    book["1. Nf3 c5 2. g3 g6 3. Bg2 Bg7 4. d4 cxd4"] = "Nxd4";
    book["1. Nf3 c5 2. g3 g6 3. Bg2 Bg7 4. d4 cxd4 5. Nxd4"] = "Nc6";
    book["1. Nf3 c5 2. g3 g6 3. Bg2 Bg7 4. d4 cxd4 5. Nxd4 Nc6"] = "Nb3 | Nxc6";
    book["1. Nf3 c5 2. g3 g6 3. Bg2 Bg7 4. d4 cxd4 5. Nxd4 Nc6 6. Nb3"] = "Nf6 | d6";
    book["1. Nf3 c5 2. g3 g6 3. Bg2 Bg7 4. d4 cxd4 5. Nxd4 Nc6 6. Nxc6"] = "bxc6";
    book["1. Nf3 c5 2. g3 g6 3. Bg2 Bg7 4. d4 cxd4 5. Nxd4 Nc6 6. Nxc6 bxc6"] = "0-0";
    book["1. Nf3 c5 2. g3 g6 3. Bg2 Bg7 4. d4 cxd4 5. Nxd4 Nc6 6. Nxc6 bxc6 7. 0-0"] = "Rb8 | Nf6";

    book["1. Nf3 c5 2. g3 g6 3. Bg2 Bg7 4. 0-0 Nc6 5. d3"] = "d6 | e6 | e5 | Nf6";
    book["1. Nf3 c5 2. g3 g6 3. Bg2 Bg7 4. 0-0 Nc6 5. c4"] = "e6 | e5 | d6 | Nf6";



    // A04 Zukertort Opening: Sicilian Invitation -- WHITE
    book["1. Nf3 c5 2. g3 g6 3. Bg2 Bg7 4. d4 Nc6"] = "d5";
    book["1. Nf3 c5 2. g3 g6 3. Bg2 Bg7 4. d4 Nc6 5. d5 Na5"] = "Nc3 | e4";
    book["1. Nf3 c5 2. g3 g6 3. Bg2 Bg7 4. d4 Nc6 5. d5 Nd4"] = "Nfd2";
    book["1. Nf3 c5 2. g3 g6 3. Bg2 Bg7 4. d4 Nc6 5. d5 Nd4 6. Nfd2 Nb5"] = "a4";
    book["1. Nf3 c5 2. g3 g6 3. Bg2 Bg7 4. d4 Nc6 5. d5 Nd4 6. Nfd2 Nb5 7. a4 Nd6"] = "e4";
    book["1. Nf3 c5 2. g3 g6 3. Bg2 Bg7 4. d4 Nc6 5. d5 Nd4 6. Nfd2 b6"] = "0-0";




    // English, symmetrical variation (A37)
    book["1. Nf3 c5 2. g3 Nc6 3. c4 Nf6"] = "Bg2 | Nc3 | d4";
    book["1. Nf3 c5 2. g3 Nc6 3. c4 Nf6 4. Bg2"] = "d5 | g6";
    book["1. Nf3 c5 2. g3 Nc6 3. c4 Nf6 4. Nc3"] = "g6 | d5 | e6 | d6";
    book["1. Nf3 c5 2. g3 Nc6 3. c4 Nf6 4. d4"] = "cxd4";
    book["1. Nf3 c5 2. g3 Nc6 3. c4 Nf6 4. d4 cxd4"] = "Nxd4";
    book["1. Nf3 c5 2. g3 Nc6 3. c4 Nf6 4. d4 cxd4 5. Nxd4"] = "g6 | Qb6 | e6 | e5 | d6";

    book["1. Nf3 c5 2. g3 Nc6 3. c4 g6"] = "Bg2 | d4 | Nc3";
    book["1. Nf3 c5 2. g3 Nc6 3. c4 g6 4. Bg2"] = "Bg7";
    book["1. Nf3 c5 2. g3 Nc6 3. c4 g6 4. Bg2 Bg7"] = "Nc3 | 0-0";
    book["1. Nf3 c5 2. g3 Nc6 3. c4 g6 4. d4"] = "cxd4";
    book["1. Nf3 c5 2. g3 Nc6 3. c4 g6 4. d4 cxd4"] = "Nxd4";
    book["1. Nf3 c5 2. g3 Nc6 3. c4 g6 4. d4 cxd4 5. Nxd4"] = "Bg7";
    book["1. Nf3 c5 2. g3 Nc6 3. c4 g6 4. d4 cxd4 5. Nxd4 Bg7"] = "Nc2 | Nxc6 | Nb3";
    book["1. Nf3 c5 2. g3 Nc6 3. c4 g6 4. Nc3"] = "Bg7";
    book["1. Nf3 c5 2. g3 Nc6 3. c4 g6 4. Nc3 Bg7"] = "Bg2";
    book["1. Nf3 c5 2. g3 Nc6 3. c4 g6 4. Nc3 Bg7 5. Bg2"] = "e6 | d6 | e5 | Nf6";





    // Reti opening (A04) -- BLACK
    book["1. Nf3 g6 2. g3 Bg7 3. d4"] = "d5 | Nf6";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 d5 4. c4"] = "dxc4";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 d5 4. c4 dxc4 5. Bg2"] = "c5";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 d5 4. c4 dxc4 5. Qa4+"] = "Nc6";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 d5 4. Nc3"] = "Nf6";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 d5 4. Nc3 Nf6 5. Bg2"] = "a5";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 d5 4. Bg2"] = "Nf6 | c6";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 d5 4. Bg2 Nf6 5. c4"] = "c6";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 d5 4. Bg2 Nf6 5. c4 c6 6. 0-0"] = "0-0";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 d5 4. Bg2 Nf6 5. c4 c6 6. cxd5"] = "cxd5";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 d5 4. Bg2 Nf6 5. 0-0"] = "0-0";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 d5 4. Bg2 Nf6 5. 0-0 0-0 6. c4"] = "c6";


    book["1. Nf3 g6 2. g3 Bg7 3. d4 d5 4. Bg2 c6 5. 0-0"] = "Nf6";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 d5 4. Bg2 c6 5. 0-0 Nf6 6. e3"] = "0-0 | Bf5";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 d5 4. Bg2 c6 5. 0-0 Nf6 6. Nbd2"] = "0-0 | Bf5";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 d5 4. Bg2 c6 5. 0-0 Nf6 6. c4"] = "dxc4 | 0-0";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 d5 4. Bg2 c6 5. 0-0 Nf6 6. c4 0-0 7. Qb3"] = "Qb6 | a5";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 d5 4. Bg2 c6 5. 0-0 Nf6 6. c4 0-0 7. b3"] = "Bf5 | dxc4";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 d5 4. Bg2 c6 5. 0-0 Nf6 6. c4 0-0 7. cxd5"] = "cxd5";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 d5 4. Bg2 c6 5. 0-0 Nf6 6. c4 0-0 7. cxd5 cxd5 8. Ne5"] = "Nfd7";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 d5 4. Bg2 c6 5. 0-0 Nf6 6. c4 0-0 7. cxd5 cxd5 8. Nc3"] = "Ne4";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 d5 4. Bg2 c6 5. 0-0 Nf6 6. c4 0-0 7. cxd5 cxd5 8. Nc3 Ne4 9. Ne5"] = "Nxc3";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 d5 4. Bg2 c6 5. 0-0 Nf6 6. c4 0-0 7. cxd5 cxd5 8. Nc3 Ne4 9. Ne5 Nxc3 10. bxc3"] = "Nc6";



    // Reti opening (A04)
    book["1. Nf3 g6"] = "d4 | c4 | g3 | e4";
    book["1. Nf3 g6 2. d4"] = "Bg7 | Nf6";
    book["1. Nf3 g6 2. c4"] = "Bg7";
    book["1. Nf3 g6 2. c4 Bg7"] = "d4 | Nc3";
    book["1. Nf3 g6 2. g3"] = "Bg7";
    book["1. Nf3 g6 2. g3 Bg7"] = "Bg2 | d4";

    book["1. Nf3 g6 2. g3 Bg7 3. d4 Nf6"] = "Bg2";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 c5"] = "Bg2 | c3";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 d6"] = "Bg2";


    // A04 Zukertort Opening: Kingside Fianchetto -- BLACK
    book["1. Nf3 g6 2. g3 Bg7 3. d4 Nf6 4. Bg2"] = "0-0 | c6 | d5";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 Nf6 4. Bg2 d5 5. c4"] = "c6 | 0-0";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 Nf6 4. Bg2 d5 5. c3"] = "Nbd7 | 0-0 | Nc6";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 Nf6 4. Bg2 d5 5. Nbd2"] = "c5";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 Nf6 4. Bg2 d5 5. 0-0"] = "0-0 | c6";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 Nf6 4. Bg2 d5 5. 0-0 0-0 6. c4"] = "c5 | dxc4 | c6";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 Nf6 4. Bg2 d5 5. 0-0 0-0 6. c3"] = "a5 | c6 | Nbd7";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 Nf6 4. Bg2 d5 5. 0-0 0-0 6. Nbd2"] = "c5 | a5 | Na6";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 Nf6 4. Bg2 d5 5. 0-0 0-0 6. Bf4"] = "c5";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 Nf6 4. Bg2 d5 5. 0-0 0-0 6. Bf4 c5 7. c3"] = "cxd4";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 Nf6 4. Bg2 d5 5. 0-0 0-0 6. Bf4 c5 7. c3 cxd4 8. cxd4"] = "Qb6";
    book["1. Nf3 g6 2. g3 Bg7 3. d4 Nf6 4. Bg2 d5 5. 0-0 0-0 6. Bf4 c5 7. dxc5"] = "Nbd7";


    book["1. Nf3 g6 2. e4"] = "Bg7 | c5 | d6";

    book["1. Nf3 g6 2. d4 Nf6 3. c4"] = "Bg7";

    book["1. Nf3 g6 2. c4 Bg7 3. d4"] = "d6 | Nf6 c5";
    book["1. Nf3 g6 2. c4 Bg7 3. d4 Nf6"] = "Nc3 | g3";

    book["1. Nf3 g6 2. c4 Bg7 3. Nc3"] = "d6 | c5 | Nf6 | e5";


    book["1. Nf3 g6 2. c4 Bg7 3. Nc3 e5 4. d4"] = "exd4";
    book["1. Nf3 g6 2. c4 Bg7 3. Nc3 e5 4. d4 exd4 5. Nxd4"] = "Nf6";
    book["1. Nf3 g6 2. c4 Bg7 3. Nc3 e5 4. d4 exd4 5. Bg5"] = "Nf6";
    book["1. Nf3 g6 2. c4 Bg7 3. Nc3 e5 4. h4"] = "Nc6";
    book["1. Nf3 g6 2. c4 Bg7 3. Nc3 e5 4. e3"] = "Ne7";
    book["1. Nf3 g6 2. c4 Bg7 3. Nc3 e5 4. g3"] = "Nc6";
    book["1. Nf3 g6 2. c4 Bg7 3. Nc3 e5 4. g3 Nc6 5. d3"] = "Nge7";
    book["1. Nf3 g6 2. c4 Bg7 3. Nc3 e5 4. g3 Nc6 5. Bg2"] = "Nge7";
    book["1. Nf3 g6 2. c4 Bg7 3. Nc3 e5 4. g3 Nc6 5. Bg2 Nge7 6. d3"] = "d6";
    book["1. Nf3 g6 2. c4 Bg7 3. Nc3 e5 4. g3 Nc6 5. Bg2 Nge7 6. 0-0"] = "d6 | 0-0";
    book["1. Nf3 g6 2. c4 Bg7 3. Nc3 e5 4. g3 Nc6 5. Bg2 Nge7 6. 0-0 0-0 7. d3"] = "d6";
    book["1. Nf3 g6 2. c4 Bg7 3. Nc3 e5 4. g3 Nc6 5. Bg2 Nge7 6. 0-0 0-0 7. d3 d6 8. e3"] = "a5";
    book["1. Nf3 g6 2. c4 Bg7 3. Nc3 e5 4. g3 Nc6 5. Bg2 Nge7 6. 0-0 0-0 7. d3 d6 8. e3 a5 9. a3"] = "Bf5";



    book["1. Nf3 g6 2. c4 Bg7 3. Nc3 d6"] = "d4 | g3 | e4";
    book["1. Nf3 g6 2. c4 Bg7 3. Nc3 d6 4. d4"] = "Nf6 | Nd7 | Bg4 | e5";
    book["1. Nf3 g6 2. c4 Bg7 3. Nc3 d6 4. d4 Nd7"] = "e4 | g3";
    book["1. Nf3 g6 2. c4 Bg7 3. Nc3 d6 4. d4 Nd7 5. e4"] = "e5 | e6";
    book["1. Nf3 g6 2. c4 Bg7 3. Nc3 d6 4. d4 Nd7 5. e4 c5"] = "d5 | Be3";


    book["1. Nf3 g6 2. c4 Bg7 3. d4 d6 4. Nc3 Nf6"] = "e4 | g3";
    book["1. Nf3 g6 2. c4 Bg7 3. d4 d6 4. Nc3 Nf6 5. e4 Bg4"] = "Be2 | Be3";
    book["1. Nf3 g6 2. c4 Bg7 3. d4 d6 4. Nc3 Nf6 5. e4 c5"] = "Be2 | d5";
    book["1. Nf3 g6 2. c4 Bg7 3. d4 d6 4. Nc3 Nf6 5. e4 0-0"] = "Be2 | h3";
    book["1. Nf3 g6 2. c4 Bg7 3. d4 d6 4. Nc3 Nf6 5. e4 0-0 6. Be2 b6"] = "0-0 | d5 | Be3";
    book["1. Nf3 g6 2. c4 Bg7 3. d4 d6 4. Nc3 Nf6 5. e4 0-0 6. Be2 b6 7. 0-0 Bb7"] = "Qc2";

    book["1. Nf3 g6 2. c4 Bg7 3. d4 d6 4. Nc3 Bg4"] = "e3 | g3";
    book["1. Nf3 g6 2. c4 Bg7 3. d4 d6 4. Nc3 Nd7"] = "e4 | g3";
    book["1. Nf3 g6 2. c4 Bg7 3. d4 d6 4. Nc3 e5"] = "e4 | dxe5";
    book["1. Nf3 g6 2. c4 Bg7 3. d4 d6 4. Nc3 Nc6"] = "d5 | e3 | g3";
    book["1. Nf3 g6 2. c4 Bg7 3. d4 d6 4. Nc3 c5"] = "d5 | dxc5 | e4";
    book["1. Nf3 g6 2. c4 Bg7 3. d4 d6 4. Nc3 c6"] = "e4";
    book["1. Nf3 g6 2. c4 Bg7 3. d4 d6 4. g3 Nf6"] = "Bg2 | Nc3";
    book["1. Nf3 g6 2. c4 Bg7 3. d4 d6 4. g3 Nd7"] = "Bg2 | Nc3 | e4";
    book["1. Nf3 g6 2. c4 Bg7 3. d4 d6 4. g3 c6"] = "Nc3 | Bg2";
    book["1. Nf3 g6 2. c4 Bg7 3. d4 d6 4. g3 e5"] = "Nc3 | dxe5";
    book["1. Nf3 g6 2. c4 Bg7 3. d4 d6 4. g3 c5"] = "Bg2 | d5 | Nc3";
    book["1. Nf3 g6 2. c4 Bg7 3. d4 d6 4. g3 f5"] = "Bg2 | Nc3";
    book["1. Nf3 g6 2. c4 Bg7 3. d4 d6 4. g3 Nc6"] = "Bg2 | d5 | Nc3";
    book["1. Nf3 g6 2. c4 Bg7 3. d4 d6 4. g3 Bg4"] = "Bg2 | Nc3";



    // English opening (A30)
    book["1. c4 c5"] = "Nc3 | Nf3 | g3";



    book["1. c4 c5 2. Nf3 Nc6"] = "Nc3 | d4 | g3 | e3";

    book["1. c4 c5 2. Nf3 Nc6 3. d4 cxd4"] = "Nxd4";
    book["1. c4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 e6"] = "Nc3";
    book["1. c4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Nf6"] = "Nc3";
    book["1. c4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6"] = "e4";
    book["1. c4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6 5. e4 Nf6"] = "Nc3";
    book["1. c4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6 5. e4 Nf6 6. Nc3 Nxd4"] = "Qxd4";
    book["1. c4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 g6 5. e4 Nf6 6. Nc3 d6"] = "Be2";


    book["1. c4 c5 2. Nf3 Nf6"] = "Nc3 | g3 | d4";
    book["1. c4 c5 2. Nf3 g6"] = "d4 | g3 | Nc3";


    book["1. c4 c5 2. Nf3 Nf6 3. d4 g6"] = "d5 | Nc3";
    book["1. c4 c5 2. Nf3 Nf6 3. d4 e6"] = "d5 | Nc3 | e3";
    book["1. c4 c5 2. Nf3 Nf6 3. d4 d5"] = "cxd5 | dxc5";
    book["1. c4 c5 2. Nf3 Nf6 3. d4 b6"] = "d5 | Nc3";
    book["1. c4 c5 2. Nf3 Nf6 3. d4 cxd4"] = "Nxd4";
    book["1. c4 c5 2. Nf3 Nf6 3. d4 cxd4 4. Nxd4 e5"] = "Nb5";
    book["1. c4 c5 2. Nf3 Nf6 3. d4 cxd4 4. Nxd4 Nc6"] = "e3 | Nc3";
    book["1. c4 c5 2. Nf3 Nf6 3. d4 cxd4 4. Nxd4 b6"] = "Bf4 | Nc3 | f3";
    book["1. c4 c5 2. Nf3 Nf6 3. d4 cxd4 4. Nxd4 g6"] = "g3 | Nc3";
    book["1. c4 c5 2. Nf3 Nf6 3. d4 cxd4 4. Nxd4 a6"] = "Nc3";
    book["1. c4 c5 2. Nf3 Nf6 3. d4 cxd4 4. Nxd4 d5"] = "cxd5";
    book["1. c4 c5 2. Nf3 Nf6 3. d4 cxd4 4. Nxd4 d5 5. cxd5 Nxd5"] = "e4";
    book["1. c4 c5 2. Nf3 Nf6 3. d4 cxd4 4. Nxd4 d5 5. cxd5 Qxd5"] = "Nc3";
    book["1. c4 c5 2. Nf3 Nf6 3. d4 cxd4 4. Nxd4 Qc7"] = "Nc3 | Nb5 | e3";
    book["1. c4 c5 2. Nf3 Nf6 3. d4 cxd4 4. Nxd4 e6"] = "Nc3 | g3 | e3";
    book["1. c4 c5 2. Nf3 Nf6 3. d4 cxd4 4. Nxd4 e6 5. Nc3 Bb4"] = "g3 | e3";
    book["1. c4 c5 2. Nf3 Nf6 3. d4 cxd4 4. Nxd4 e6 5. Nc3 a6"] = "e4 | Bg5 | g3";
    book["1. c4 c5 2. Nf3 Nf6 3. d4 cxd4 4. Nxd4 e6 5. Nc3 Nc6"] = "Bf4 | Ndb5";



    book["1. c4 c5 2. Nf3 Nf6 3. g3 d5"] = "cxd5";
    book["1. c4 c5 2. Nf3 Nf6 3. g3 d5 4. cxd5 Nxd5"] = "Bg2 | d4";
    book["1. c4 c5 2. Nf3 Nf6 3. g3 b6"] = "Bg2";
    book["1. c4 c5 2. Nf3 Nf6 3. g3 b6 4. Bg2 Bb7"] = "0-0";
    book["1. c4 c5 2. Nf3 Nf6 3. g3 b6 4. Bg2 Bb7 5. 0-0 g6"] = "Nc3 | d4";
    book["1. c4 c5 2. Nf3 Nf6 3. g3 b6 4. Bg2 Bb7 5. 0-0 e6"] = "Nc3";
    book["1. c4 c5 2. Nf3 Nf6 3. g3 b6 4. Bg2 Bb7 5. 0-0 e6 6. Nc3 Be7"] = "d4";
    book["1. c4 c5 2. Nf3 Nf6 3. g3 b6 4. Bg2 Bb7 5. 0-0 e6 6. Nc3 Be7 7. d4 cxd4"] = "Qxd4";
    book["1. c4 c5 2. Nf3 Nf6 3. g3 b6 4. Bg2 Bb7 5. 0-0 e6 6. Nc3 Be7 7. d4 cxd4 8. Qxd4 d6"] = "e4 | Rd1";
    book["1. c4 c5 2. Nf3 Nf6 3. g3 b6 4. Bg2 Bb7 5. 0-0 e6 6. Nc3 Be7 7. d4 cxd4 8. Qxd4 0-0"] = "e4";


    // A30 English Opening: Symmetrical Variation -- BLACK
    book["1. c4 c5 2. Nf3"] = "Nc6 | Nf6 | g6";
    book["1. c4 c5 2. Nf3 g6 3. d4"] = "cxd4 | Bg7";
    book["1. c4 c5 2. Nf3 g6 3. e4"] = "d6 | Bg7 | Nf6";
    book["1. c4 c5 2. Nf3 g6 3. Nc3"] = "Bg7 | Nc6";
    book["1. c4 c5 2. Nf3 g6 3. g3"] = "Bg7 | Nc6";


    // A30 English, symmetrical variation -- WHITE
    book["1. c4 c5 2. Nf3 e6"] = "g3";
    book["1. c4 c5 2. Nf3 e6 3. g3 b6"] = "Bg2";
    book["1. c4 c5 2. Nf3 e6 3. g3 Nf6"] = "Bg2";
    book["1. c4 c5 2. Nf3 e6 3. g3 d5"] = "cxd5";
    book["1. c4 c5 2. Nf3 e6 3. g3 d5 4. cxd5 exd5"] = "d4";
    book["1. c4 c5 2. Nf3 e6 3. g3 Nc6"] = "Bg2";


    // English opening, symmetrical variation (A34)
    book["1. c4 c5 2. Nc3"] = "Nc6 | Nf6 | g6";
    book["1. c4 c5 2. g3"] = "g6 | Nc6";

    book["1. c4 c5 2. g3 Nf6"] = "Bg2";


    book["1. c4 c5 2. Nc3 Nc6"] = "g3 | Nf3";
    book["1. c4 c5 2. Nc3 Nf6"] = "g3 | Nf3 | e4";
    book["1. c4 c5 2. Nc3 g6"] = "g3 | Nf3 | e3";

    book["1. c4 c5 2. Nc3 g6 3. Nf3"] = "Bg7";

    book["1. c4 c5 2. Nc3 Nc6 3. g3"] = "g6 | Nf6 | d6";
    book["1. c4 c5 2. Nc3 Nc6 3. Nf3"] = "g6 | Nf6 | e5";

    book["1. c4 g6"] = "Nc3 | g3 | d4 | Nf3";
    book["1. c4 g6 2. Nc3" ] = "Bg7 | c5 | Nf6 | d6";
    book["1. c4 g6 2. g3"] = "Bg7 | c5";
    book["1. c4 g6 2. d4"] = "Bg7 | Nf6 | d6";
    book["1. c4 g6 2. Nf3"] = "Bg7";
    book["1. c4 g6 2. Nf3 Bg7"] = "d4 | Nc3";

    book["1. c4 g6 2. Nf3 Bg7 3. d4 d6"] = "Nc3";


    // A10 English Opening: Great Snake Variation -- BLACK
    book["1. c4 g6 2. e3" ] = "Bg7 | Nf6";
    book["1. c4 g6 2. e3 Bg7 3. Nc3"] = "Nf6 | d6 | c5 | e6";
    book["1. c4 g6 2. e3 Bg7 3. d4"] = "d6 | Nf6 | c5 | e6 | b6";
    book["1. c4 g6 2. e3 Bg7 3. Nf3"] = "Nf6 | d6 | c5 | e6 | c6 | e5";
    book["1. c4 g6 2. e3 Nf6 3. Nc3"] = "Bg7 | d6 | d5 | c5";
    book["1. c4 g6 2. e3 Nf6 3. Nf3"] = "Bg7 | d6 | d5 |c5";
    book["1. c4 g6 2. e3 Nf6 3. d4"] = "Bg7 | d5 | d6 | c5 | c6 | e6 | b6";
    book["1. c4 g6 2. e3 Nf6 3. d4 Bg7 4. Nc3"] = "0-0 | d6 | d5 | c5"; 
    book["1. c4 g6 2. e3 Nf6 3. d4 Bg7 4. Nf3"] = "0-0 | d6 | d5 | c5";
    book["1. c4 g6 2. e3 Nf6 3. d4 Bg7 4. Bd3"] = "0-0 | d6 | d5 | c5";
    book["1. c4 g6 2. e3 Nf6 3. d4 Bg7 4. Be2"] = "0-0 | d6 | d5 | c5 | e6";
    book["1. c4 g6 2. e3 Nf6 3. d4 Bg7 4. b3"] = "0-0 | d6 | d5 | c5 | c6 | e6";
    book["1. c4 g6 2. e3 Nf6 3. d4 Bg7 4. Bd2"] = "0-0 | d6 | d5 | c5";
    book["1. c4 g6 2. e3 Nf6 3. d4 Bg7 4. Bd2 c5 5. Bc3"] = "0-0";
    book["1. c4 g6 2. e3 Nf6 3. d4 Bg7 4. Bd2 c5 5. Nf3"] = "0-0 | cxd4";
    book["1. c4 g6 2. e3 Nf6 3. d4 Bg7 4. Bd2 c5 5. Nc3"] = "0-0";
    book["1. c4 g6 2. e3 Nf6 3. d4 Bg7 4. Bd2 c5 5. d5"] = "0-0 | d6";



    // A30 English, symmetrical variation -- BLACK
    book["1. c4 c5 2. g3 Nc6 3. Nc3"] = "g6 | e6 | Nf6";
    book["1. c4 c5 2. g3 Nc6 3. Nf3"] = "g6 | e5 | Nf6";
    book["1. c4 c5 2. g3 Nc6 3. b3"] = "e6 | d5";
    book["1. c4 c5 2. g3 Nc6 3. Bg2"] = "g6 | Nf6 | e5";


    // A34 English, symmetrical variation -- BLACK
    book["1. c4 c5 2. Nc3 Nf6 3. Nf3"] = "e6 | Nc6";
    book["1. c4 c5 2. Nc3 Nf6 3. Nf3 e6 4. g3"] = "b6";
    book["1. c4 c5 2. Nc3 Nf6 3. Nf3 e6 4. e3"] = "d5";
    book["1. c4 c5 2. Nc3 Nf6 3. Nf3 e6 4. e3 d5 5. d4"] = "Nc6";
    book["1. c4 c5 2. Nc3 Nf6 3. Nf3 e6 4. e3 d5 5. d4 Nc6 6. cxd5"] = "exd5";
    book["1. c4 c5 2. Nc3 Nf6 3. Nf3 e6 4. d4"] = "cxd4";
    book["1. c4 c5 2. Nc3 Nf6 3. Nf3 e6 4. d4 cxd4 5. Nxd4"] = "d5";
    book["1. c4 c5 2. Nc3 Nf6 3. Nf3 e6 4. e4"] = "Nc6";


    // English opening (A10)
    book["1. c4 g6 2. g3 Bg7"] = "Bg2";
    book["1. c4 g6 2. g3 Bg7 3. Bg2"] = "e5 | d6 | c5 | Nf6";
    book["1. c4 g6 2. g3 c5"] = "Bg2 | Nc3 | Nf3";




    book["1. c4 g6 2. g3 Bg7 3. Bg2 e5"] = "Nc3";
    book["1. c4 g6 2. g3 Bg7 3. Bg2 e5 4. Nc3"] = "d6 | Nc6";
    book["1. c4 g6 2. g3 Bg7 3. Bg2 d6"] = "Nc3 | Nf3 | d4";
    book["1. c4 g6 2. g3 Bg7 3. Bg2 c5"] = "Nc3 | Nf3";
    book["1. c4 g6 2. g3 Bg7 3. Bg2 Nf6"] = "Nc3 | Nf3 | d4";

    book["1. c4 g6 2. Nc3 d6"] = "g3 | d4";
    book["1. c4 g6 2. Nc3 d6 3. g3"] = "Bg7";
    book["1. c4 g6 2. Nc3 d6 3. g3 Bg7"] = "Bg2";
    book["1. c4 g6 2. Nc3 d6 3. g3 Bg7 4. Bg2"] = "e5 | Nf6 | Nc6 | c5";



    // A10 English Opening: Great Snake Variation -- BLACK
    book["1. c4 g6 2. g3 c5 3. Bg2"] = "Bg7 | Nc6";



    // Modern defense (A41)
    book["1. c4 g6 2. Nc3 d6 3. d4"] = "Bg7";
    book["1. c4 g6 2. Nc3 d6 3. d4 Bg7"] = "e4 | Nf3";
    book["1. c4 g6 2. Nc3 d6 3. d4 Bg7 4. e4"] = "Nf6 | Nc6 | e5";
    book["1. c4 g6 2. Nc3 d6 3. d4 Bg7 4. Nf3"] = "Nf6 | Nd7 | Bg4";



    // A15 English Opening: Anglo-Indian Defense -- WHITE
    book["1. c4 Nf6 2. g3 c5"] = "Nc3 | Bg2";
    book["1. c4 Nf6 2. g3 c5 3. Nc3 e6"] = "Nf3";
    book["1. c4 Nf6 2. g3 c5 3. Nc3 Nc6"] = "Nf3 | Bg2";
    book["1. c4 Nf6 2. g3 c5 3. Nc3 g6"] = "Nf3 | Bg2 | Rb1";
    book["1. c4 Nf6 2. g3 c5 3. Bg2 g6"] = "Nf3 | Nc3";
    book["1. c4 Nf6 2. g3 c5 3. Bg2 Nc6"] = "Nc3 | Nf3";
    book["1. c4 Nf6 2. g3 c5 3. Bg2 d5"] = "cxd5";
    book["1. c4 Nf6 2. g3 c5 3. Bg2 d5 4. cxd5 Nxd5"] = "d4 | Nf3";



    // Anglo-Indian Defense (A15)
    book["1. c4 Nf6"] = "Nc3 | g3 | Nf3 | d4";
    book["1. c4 Nf6 2. Nc3"] = "g6 | e6 | c5 | e5";
    book["1. c4 Nf6 2. g3"] = "g6 | e6 | c6 | e5";
    book["1. c4 Nf6 2. Nf3"] = "g6 | e6";
    book["1. c4 Nf6 2. d4"] = "e6 | g6 | c5 | d6";


    book["1. c4 Nf6 2. Nc3 g6 3. e4"] = "Bg7 | e5";
    book["1. c4 Nf6 2. Nc3 g6 3. d4"] = "d5 | d6 | Bg7";
    book["1. c4 Nf6 2. Nc3 g6 3. Nf3"] = "d5 | Bg7";
    book["1. c4 Nf6 2. Nc3 g6 3. g3"] = "c5 | Bg7";
    book["1. c4 Nf6 2. Nc3 g6 3. g3 Bg7 4. e4"] = "c5";
    book["1. c4 Nf6 2. Nc3 g6 3. g3 Bg7 4. Nf3"] = "d5 | 0-0";
    book["1. c4 Nf6 2. Nc3 g6 3. g3 Bg7 4. d4"] = "d5 | 0-0";
    book["1. c4 Nf6 2. Nc3 g6 3. g3 Bg7 4. Bg2"] = "0-0 | d6";
    book["1. c4 Nf6 2. Nc3 g6 3. g3 Bg7 4. Bg2 0-0 5. d3"] = "c5 | d6";
    book["1. c4 Nf6 2. Nc3 g6 3. g3 Bg7 4. Bg2 0-0 5. Nf3"] = "c5 | d5";
    book["1. c4 Nf6 2. Nc3 g6 3. g3 Bg7 4. Bg2 0-0 5. d4"] = "c5 | d6";
    book["1. c4 Nf6 2. Nc3 g6 3. g3 Bg7 4. Bg2 0-0 5. e4"] = "c5 | d6";



    book["1. c4 Nf6 2. Nf3 d5"] = "cxd5";
    book["1. c4 Nf6 2. Nf3 d5 3. cxd5 c6"] = "dxc6";
    book["1. c4 Nf6 2. Nf3 d5 3. cxd5 c6 4. dxc6 Nxc6"] = "g3";
    book["1. c4 Nf6 2. Nf3 d5 3. cxd5 Nxd5"] = "d4";
    book["1. c4 Nf6 2. Nf3 d5 3. cxd5 g6"] = "e4";


    book["1. c4 Nf6 2. Nc3 d5"] = "cxd5 | d4";
    book["1. c4 Nf6 2. Nc3 d5 3. cxd5 Nxd5"] = "g3 | Nf3";

    book["1. c4 Nf6 2. Nf3 c5"] = "Nc3 | d4";
    book["1. c4 Nf6 2. Nf3 c5 3. Nc3 e6"] = "g3";
    book["1. c4 Nf6 2. Nf3 c5 3. Nc3 e6 4. g3 Nc6"] = "Bg2";


    book["1. c4 Nf6 2. d4 e6"] = "Nc3 | Nf3";
    book["1. c4 Nf6 2. d4 e6 3. Nf3 b6"] = "g3 | a3 | Nc3 | e3";
    book["1. c4 Nf6 2. d4 e6 3. Nf3 Bb4+"] = "Bd2 | Nbd2";
    book["1. c4 Nf6 2. d4 e6 3. Nf3 c5"] = "d5";
    book["1. c4 Nf6 2. d4 e6 3. Nf3 Nc6"] = "Nc3 | e3 | a3 | g3";
    book["1. c4 Nf6 2. d4 e6 3. Nf3 a6"] = "Nc3 | g3 | Bg5 | e3";
    book["1. c4 Nf6 2. d4 e6 3. Nf3 Be7"] = "Nc3 | g3";
    book["1. c4 Nf6 2. d4 e6 3. Nf3 c6"] = "Nc3 | g3 | Bf4";
    book["1. c4 Nf6 2. d4 e6 3. Nf3 d5"] = "Nc3";
    book["1. c4 Nf6 2. d4 e6 3. Nf3 d5 4. Nc3 dxc4"] = "e4 | e3";
    book["1. c4 Nf6 2. d4 e6 3. Nf3 d5 4. Nc3 Be7"] = "Bg5 | Bf4";
    book["1. c4 Nf6 2. d4 e6 3. Nf3 d5 4. Nc3 c6"] = "Bg5 | e3 | cxd5";
    book["1. c4 Nf6 2. d4 e6 3. Nf3 d5 4. Nc3 Bb4"] = "cxd5 | Bg5";
    book["1. c4 Nf6 2. d4 e6 3. Nf3 d5 4. Nc3 Nbd7"] = "Bg5 | Bf4 | cxd5";
    book["1. c4 Nf6 2. d4 e6 3. Nf3 d5 4. Nc3 c5"] = "cxd5 | e3";
    book["1. c4 Nf6 2. d4 e6 3. Nf3 d5 4. Nc3 a6"] = "cxd5";
    book["1. c4 Nf6 2. d4 e6 3. Nf3 d5 4. Nc3 a6 5. cxd5 exd5"] = "Bg5";
    book["1. c4 Nf6 2. d4 e6 3. Nf3 d5 4. Nc3 a6 5. cxd5 Nxd5"] = "e4 | g3";



    book["1. c4 Nf6 2. d4 g6"] = "Nc3 | Nf3";
    book["1. c4 Nf6 2. d4 c5"] = "d5";
    book["1. c4 Nf6 2. d4 c5 3. d5"] = "b5 | e6";
    book["1. c4 Nf6 2. d4 d6"] = "Nf3 | Nc3";



    // A60 Benoni Defense: Modern Variation -- WHITE
    book["1. c4 Nf6 2. d4 c5 3. d5 e6"] = "Nc3 | Nf3";
    book["1. c4 Nf6 2. d4 c5 3. d5 e6 4. Nc3 g6"] = "Bf4 | e4";
    book["1. c4 Nf6 2. d4 c5 3. d5 e6 4. Nc3 Bd6"] = "Nf3";
    book["1. c4 Nf6 2. d4 c5 3. d5 e6 4. Nc3 exd5"] = "cxd5";
    book["1. c4 Nf6 2. d4 c5 3. d5 e6 4. Nc3 exd5 5. cxd5 d6"] = "e4 | a4";
    book["1. c4 Nf6 2. d4 c5 3. d5 e6 4. Nc3 exd5 5. cxd5 g6"] = "d6";
    book["1. c4 Nf6 2. d4 c5 3. d5 e6 4. Nc3 exd5 5. cxd5 Bd6"] = "e3 | Nf3 | e4";
    book["1. c4 Nf6 2. d4 c5 3. d5 e6 4. Nc3 exd5 5. cxd5 Qe7"] = "Qa4 | Bf4";




    // A15 English Opening: Anglo-Indian Defense, King's Knight Variation -- WHITE
    book["1. c4 Nf6 2. Nf3 e6"] = "b3 | e3 | d4";
    book["1. c4 Nf6 2. Nf3 g6"] = "Nc3 | d4 | g3";
    book["1. c4 Nf6 2. Nf3 c6"] = "Nc3 | e3 | g3";
    book["1. c4 Nf6 2. Nf3 c6 3. Nc3 d6"] = "e4 | d4";
    book["1. c4 Nf6 2. Nf3 c6 3. Nc3 g6"] = "e4 | Qb3";
    book["1. c4 Nf6 2. Nf3 c6 3. Nc3 d5"] = "e3 | cxd5";
    book["1. c4 Nf6 2. Nf3 c6 3. Nc3 d5 4. e3 e6"] = "d4 | Qc2";
    book["1. c4 Nf6 2. Nf3 c6 3. Nc3 d5 4. e3 b6"] = "d4 | b3";
    book["1. c4 Nf6 2. Nf3 c6 3. Nc3 d5 4. e3 Nbd7"] = "d4 | Qc2";
    book["1. c4 Nf6 2. Nf3 c6 3. Nc3 d5 4. e3 a6"] = "d4";
    book["1. c4 Nf6 2. Nf3 c6 3. Nc3 d5 4. e3 a6 5. d4 e6"] = "b3";
    book["1. c4 Nf6 2. Nf3 c6 3. Nc3 d5 4. e3 a6 5. d4 e6 6. b3 Nbd7"] = "Bd3";
    book["1. c4 Nf6 2. Nf3 c6 3. Nc3 d5 4. e3 a6 5. d4 e6 6. b3 Bb4"] = "Bd2";



    // E00 Queen's pawn game -- WHITE
    book["1. c4 Nf6 2. d4 e6 3. Nc3 d5"] = "cxd5 | Nf3 | Bg5";
    book["1. c4 Nf6 2. d4 e6 3. Nc3 d5 4. cxd5 exd5"] = "Bg5";
    book["1. c4 Nf6 2. d4 e6 3. Nc3 d5 4. cxd5 Nxd5"] = "e4";
    book["1. c4 Nf6 2. d4 e6 3. Nc3 c5"] = "d5";
    book["1. c4 Nf6 2. d4 e6 3. Nc3 b6"] = "e4 | Nf3";
    book["1. c4 Nf6 2. d4 e6 3. Nc3 Be7"] = "e4 | Nf3";
    book["1. c4 Nf6 2. d4 e6 3. Nc3 Nc6"] = "e4 | Nf3 | a3";
    book["1. c4 Nf6 2. d4 e6 3. Nc3 Bb4"] = "e3 | Qc2 | Nf3";
    book["1. c4 Nf6 2. d4 e6 3. Nc3 Bb4 4. e3 0-0"] = "Bd3";
    book["1. c4 Nf6 2. d4 e6 3. Nc3 Bb4 4. e3 c5"] = "Ne2";


    // A15 English, 1...Nf6 (Anglo-Indian defense) -- WHITE
    book["1. c4 Nf6 2. g3 d5"] = "cxd5";
    book["1. c4 Nf6 2. g3 d5 3. cxd5 Qxd5"] = "Nf3";
    book["1. c4 Nf6 2. g3 d5 3. cxd5 Nxd5"] = "d4";



    // King's Indian (E60)
    book["1. c4 Nf6 2. d4 g6 Nf3"] = "Nc3";



    book["1. c4 Nf6 2. g3 e5"] = "Bg2 | Nc3";
    book["1. c4 Nf6 2. g3 e5 3. Bg2"] = "d5 | c6 | Nc6";
    book["1. c4 Nf6 2. g3 e5 3. Nc3"] = "d5 | Bb4 | c6";

    book["1. c4 Nf6 2. g3 e6"] = "Bg2 | Nf3";
    book["1. c4 Nf6 2. g3 e6 3. Bg2"] = "d5 | c5";
    book["1. c4 Nf6 2. g3 e6 3. Nf3"] = "d5 | b6";


    // A15 English, 1...Nf6 (Anglo-Indian defense) -- WHITE
    book["1. c4 Nf6 2. g3 g6"] = "Bg2";
    book["1. c4 Nf6 2. g3 g6 3. Bg2 Bg7"] = "Nc3";
    book["1. c4 Nf6 2. g3 g6 3. Bg2 d5"] = "cxd5";
    book["1. c4 Nf6 2. g3 g6 3. Bg2 d5 4. cxd5 Nxd5"] = "Nc3";
    book["1. c4 Nf6 2. g3 g6 3. Bg2 c6"] = "b3";


    // English opening (A17)
    book["1. c4 Nf6 2. Nc3 e6"] = "e4 | Nf3 | d4";
    book["1. c4 Nf6 2. Nc3 e6 3. e4"] = "d5 | c5";
    book["1. c4 Nf6 2. Nc3 e6 3. Nf3"] = "d5 | Bb4 | c5";
    book["1. c4 Nf6 2. Nc3 e6 3. d4"] = "Bb4 | d5 | c5";

    book["1. c4 Nf6 2. Nc3 e6 3. Nf3 Bb4"] = "Qc2 | g3";
    book["1. c4 Nf6 2. Nc3 e6 3. Nf3 Bb4 4. Qc2"] = "0-0 | c5";
    book["1. c4 Nf6 2. Nc3 e6 3. Nf3 Bb4 4. g3"] = "0-0";
    book["1. c4 Nf6 2. Nc3 e6 3. Nf3 Bb4 4. g3 0-0"] = "Bg2";
    book["1. c4 Nf6 2. Nc3 e6 3. Nf3 Bb4 4. g3 0-0 5. Bg2"] = "d5";
    book["1. c4 Nf6 2. Nc3 e6 3. Nf3 Bb4 4. g3 0-0 5. Bg2 d5"] = "a3 | Qb3";

    book["1. c4 Nf6 2. Nc3 e5"] = "Nf3 | g3 | d3";
    book["1. c4 Nf6 2. Nc3 e5 3. Nf3"] = "Nc6 | d6";
    book["1. c4 Nf6 2. Nc3 e5 3. g3"] = "d5 | Bb4 | c6 | Nc6";
    book["1. c4 Nf6 2. Nc3 e5 3. d3"] = "d5 | Bb4 | Nc6";

    book["1. c4 Nf6 2. Nc3 c5"] = "g3 | Nf3";

    book["1. c4 Nf6 2. Nc3 c5 3. Nf3"] = "Nc6 | e6 | d6 | g6 | b6";
    book["1. c4 Nf6 2. Nc3 c5 3. Nf3 b6"] = "g3 | e4 | d4 | e3";


    // A16 English Opening: Anglo-Indian Defense, Queen's Knight Variation -- BLACK
    book["1. c4 Nf6 2. Nc3 c5 3. Nf3 g6 4. e4"] = "Nc6 | d6";
    book["1. c4 Nf6 2. Nc3 c5 3. Nf3 g6 4. d4"] = "cxd4";
    book["1. c4 Nf6 2. Nc3 c5 3. Nf3 g6 4. d4 cxd4 5. Qxd4"] = "Nc6";
    book["1. c4 Nf6 2. Nc3 c5 3. Nf3 g6 4. d4 cxd4 5. Nxd4"] = "d5 | Nc6";
    book["1. c4 Nf6 2. Nc3 c5 3. Nf3 g6 4. g3"] = "d5";
    book["1. c4 Nf6 2. Nc3 c5 3. Nf3 g6 4. g3 d5 5. cxd5"] = "Nxd5";
    book["1. c4 Nf6 2. Nc3 c5 3. Nf3 g6 4. g3 d5 5. Nxd5"] = "Nxd5";
    book["1. c4 Nf6 2. Nc3 c5 3. Nf3 g6 4. g3 d5 5. Nxd5 Nxd5 6. cxd5"] = "Qxd5";
    book["1. c4 Nf6 2. Nc3 c5 3. Nf3 g6 4. g3 d5 5. Bg2"] = "d4 | Bg7";


    // English opening (A20)
    book["1. c4 e5"] = "Nc3 | g3";
    book["1. c4 e5 2. g3"] = "Nf6 | Nc6";
    book["1. c4 e5 2. g3 Nf6"] = "Bg2 | Nc3";
    book["1. c4 e5 2. g3 Nc6"] = "Bg2 | Nc3";


    // A20 English opening -- WHITE
    book["1. c4 e5 2. a3"] = "Nf6 | g6";
    book["1. c4 e5 2. a3 Nf6 3. Nc3"] = "c6";
    book["1. c4 e5 2. a3 Nf6 3. d3"] = "d5";
    book["1. c4 e5 2. a3 Nf6 3. d3 d5 4. cxd5"] = "Qxd5";
    book["1. c4 e5 2. a3 Nf6 3. d3 d5 4. cxd5 Qxd5 5. Nf3"] = "c5";
    book["1. c4 e5 2. a3 Nf6 3. d3 d5 4. cxd5 Qxd5 5. Nf3 c5 6. Nc3"] = "Qe6";
    book["1. c4 e5 2. a3 Nf6 3. d3 d5 4. cxd5 Qxd5 5. Nc3"] = "Qe6";
    book["1. c4 e5 2. a3 Nf6 3. d3 d5 4. Nf3"] = "dxc5";


    book["1. c4 e5 2. g3 Nf6 3. Bg2"] = "d5 | c6 | Nc6";

    book["1. c4 e5 2. g3 Nf6 3. Bg2 Nc6"] = "Nc3";

    book["1. c4 e5 2. g3 Nf6 3. Nc3"] = "d5 | Bb4";
    book["1. c4 e5 2. g3 Nf6 3. Nc3 d5"] = "cxd5";
    book["1. c4 e5 2. g3 Nf6 3. Nc3 d5 4. cxd5"] = "Nxd5";
    book["1. c4 e5 2. g3 Nf6 3. Nc3 d5 4. cxd5 Nxd5"] = "Bg2";
    book["1. c4 e5 2. g3 Nf6 3. Nc3 d5 4. cxd5 Nxd5 5. Bg2"] = "Nb6 | Be6";
    book["1. c4 e5 2. g3 Nf6 3. Nc3 Bb4"] = "Bg2";
    book["1. c4 e5 2. g3 Nf6 3. Nc3 Bb4 4. Bg2"] = "0-0";
    book["1. c4 e5 2. g3 Nf6 3. Nc3 Bb4 4. Bg2 0-0"] = "Nf3";
    book["1. c4 e5 2. g3 Nf6 3. Nc3 Bb4 4. Bg2 0-0 5. Nf3"] = "Re8 | e4";

    book["1. c4 e5 2. g3 c6"] = "d4 | Nf3 | Bg2";
    book["1. c4 e5 2. g3 c6 3. d4 d5"] = "dxe5";

    book["1. c4 e5 2. g3 Nc6 3. Bg2"] = "g6";
    book["1. c4 e5 2. g3 Nc6 3. Bg2 g6"] = "Nc3";
    book["1. c4 e5 2. g3 Nc6 3. Bg2 g6 4. Nc3"] = "Bg7 | d6";
    book["1. c4 e5 2. g3 Nc6 3. Bg2 g6 4. Nc3 Bg7"] = "e3 | d3";
    book["1. c4 e5 2. g3 Nc6 3. Bg2 g6 4. Nc3 d6"] = "e3 | d3";

    book["1. c4 e5 2. g3 Nc6 3. Bg2 Nf6"] = "Nc3 | Nf3";
    book["1. c4 e5 2. g3 Nc6 3. Bg2 Nf6 4. Nc3"] = "d3";
    book["1. c4 e5 2. g3 Nc6 3. Bg2 Nf6 4. Nf3"] = "Bc5 | d5 | g6";
    book["1. c4 e5 2. g3 Nc6 3. Bg2 Nf6 4. Nf3 d6"] = "Nc3 | 0-0";
    book["1. c4 e5 2. g3 Nc6 3. Bg2 Nf6 4. Nf3 d6 5. 0-0 Bg4"] = "Nc3";
    book["1. c4 e5 2. g3 Nc6 3. Bg2 Nf6 4. Nf3 d6 5. 0-0 Bg4 6. Nc3 Be7"] = "d4";


    // A22 English, Bremen, reverse dragon -- WHITE
    book["1. c4 e5 2. g3 Nf6 3. Nc3 d5 4. cxd5 Nxd5 5. Bg2 c6"] = "Nf3";
    book["1. c4 e5 2. g3 Nf6 3. Nc3 d5 4. cxd5 Nxd5 5. Bg2 c6 6. Nf3 Nxc3"] = "bxc3";
    book["1. c4 e5 2. g3 Nf6 3. Nc3 d5 4. cxd5 Nxd5 5. Bg2 c6 6. Nf3 Nd7"] = "0-0";
    book["1. c4 e5 2. g3 Nf6 3. Nc3 d5 4. cxd5 Nxd5 5. Bg2 c6 6. Nf3 Bd6"] = "d4";
    book["1. c4 e5 2. g3 Nf6 3. Nc3 d5 4. cxd5 Nxd5 5. Bg2 c6 6. Nf3 Bd6 7. d4 exd4"] = "Nxd5";
    book["1. c4 e5 2. g3 Nf6 3. Nc3 d5 4. cxd5 Nxd5 5. Bg2 c6 6. Nf3 Bd6 7. d4 exd4 8. Nxd5 Qa5+"] = "Kf1";
    book["1. c4 e5 2. g3 Nf6 3. Nc3 d5 4. cxd5 Nxd5 5. Bg2 c6 6. Nf3 Bd6 7. d4 exd4 8. Nxd5 Qa5+ 9. Kf1 Qxd5"] = "Nxd4";
    book["1. c4 e5 2. g3 Nf6 3. Nc3 d5 4. cxd5 Nxd5 5. Bg2 c6 6. Nf3 Bd6 7. d4 Nxc3"] = "bxc3";


    // A20 English opening -- WHITE
    book["1. c4 e5 2. g3 Nc6 3. Bg2 Bc5"] = "Nc3 | e3";
    book["1. c4 e5 2. g3 Nc6 3. Bg2 Bc5 4. Nc3 d6"] = "e3";
    book["1. c4 e5 2. g3 Nc6 3. Bg2 Bc5 4. Nc3 a6"] = "e3";
    book["1. c4 e5 2. g3 Nc6 3. Bg2 Bc5 4. Nc3 Nf6"] = "e3";
    book["1. c4 e5 2. g3 Nc6 3. Bg2 Bc5 4. Nc3 Nge7"] = "e3";


    book["1. c4 e5 2. g3 Nc6 3. Nc3"] = "g6 | f5 | Nf6";
    book["1. c4 e5 2. g3 Nc6 3. Nc3 g6"] = "Bg2";
    book["1. c4 e5 2. g3 Nc6 3. Nc3 g6 4. Bg2"] = "Bg7";
    book["1. c4 e5 2. g3 Nc6 3. Nc3 g6 4. Bg2 Bg7"] = "e3 | d3";
    book["1. c4 e5 2. g3 Nc6 3. Nc3 f5"] = "Bg2";
    book["1. c4 e5 2. g3 Nc6 3. Nc3 f5 4. Bg2"] = "Nf6";
    book["1. c4 e5 2. g3 Nc6 3. Nc3 f5 4. Bg2 Nf6"] = "d3 | e3";
    book["1. c4 e5 2. g3 Nc6 3. Nc3 Nf6"] = "Bg2";
    book["1. c4 e5 2. g3 Nc6 3. Nc3 Nf6 4. Bg2"] = "Bc5 | Bb4";

    book["1. c4 e5 2. g3 d5"] = "cxd5";
    book["1. c4 e5 2. g3 d5 3. cxd5 Nf6"] = "Bg2";

    book["1. c4 e5 2. g3 d6"] = "Bg2";
    book["1. c4 e5 2. g3 d6 3. Bg2 f5"] = "Nc3";
    book["1. c4 e5 2. g3 d6 3. Bg2 g6"] = "Nc3";
    book["1. c4 e5 2. g3 d6 3. Bg2 Nc6"] = "Nc3";


    // English opening (A21)
    book["1. c4 e5 2. Nc3"] = "Nf6 | Nc6 | d6";
    book["1. c4 e5 2. Nc3 Nf6"] = "Nf3 | g3 | d3";



    // A22 English Opening: King's English Variation, Two Knights Variation
    book["1. c4 e5 2. Nc3 Nf6 3. g3"] = "Bb4 | d5 | c6";
    book["1. c4 e5 2. Nc3 Nf6 3. g3 Bb4 4. Nf3"] = "e4";
    book["1. c4 e5 2. Nc3 Nf6 3. g3 Bb4 4. Nf3 e4 5. Nd4"] = "Nc6";
    book["1. c4 e5 2. Nc3 Nf6 3. g3 Bb4 4. Qc2"] = "0-0";
    book["1. c4 e5 2. Nc3 Nf6 3. g3 Bb4 4. e4"] = "d6";
    book["1. c4 e5 2. Nc3 Nf6 3. g3 Bb4 4. Bg2"] = "0-0";
    book["1. c4 e5 2. Nc3 Nf6 3. g3 Bb4 4. Bg2 0-0 5. Nf3"] = "e4";
    book["1. c4 e5 2. Nc3 Nf6 3. g3 Bb4 4. Bg2 0-0 5. Nf3 e4 6. Nd4"] = "Nc6 | Re8";
    book["1. c4 e5 2. Nc3 Nf6 3. g3 Bb4 4. Bg2 0-0 5. d3"] = "Re8";
    book["1. c4 e5 2. Nc3 Nf6 3. g3 Bb4 4. Bg2 0-0 5. Qb3"] = "Nc6";
    book["1. c4 e5 2. Nc3 Nf6 3. g3 Bb4 4. Bg2 0-0 5. e3"] = "Bxc3";
    book["1. c4 e5 2. Nc3 Nf6 3. g3 Bb4 4. Bg2 0-0 5. e3 Bxc3 6. dxc3"] = "e4";
    book["1. c4 e5 2. Nc3 Nf6 3. g3 Bb4 4. Bg2 0-0 5. e3 Bxc3 6. bxc3"] = "c6 | Re8";
    book["1. c4 e5 2. Nc3 Nf6 3. g3 Bb4 4. Bg2 0-0 5. e4"] = "Bxc3";
    book["1. c4 e5 2. Nc3 Nf6 3. g3 Bb4 4. Bg2 0-0 5. e4 Bxc3 6. bxc3"] = "c6";
    book["1. c4 e5 2. Nc3 Nf6 3. g3 Bb4 4. Bg2 0-0 5. e4 Bxc3 6. dxc3"] = "d6";
    book["1. c4 e5 2. Nc3 Nf6 3. g3 Bb4 4. Bg2 0-0 5. e4 Bxc3 6. dxc3 d6 7. Be3"] = "a5";
    book["1. c4 e5 2. Nc3 Nf6 3. g3 Bb4 4. Bg2 0-0 5. e4 Bxc3 6. dxc3 d6 7. Nh3"] = "a5";
    book["1. c4 e5 2. Nc3 Nf6 3. g3 Bb4 4. Bg2 0-0 5. e4 Bxc3 6. dxc3 d6 7. Qe2"] = "a5";



    book["1. c4 e5 2. Nc3 Nc6"] = "g3 | Nf3";
    book["1. c4 e5 2. Nc3 d6"] = "g3 | Nf3";

    book["1. c4 e5 2. Nc3 Nc6 3. g3"] = "g6 | f5";
    book["1. c4 e5 2. Nc3 Nc6 3. Nf3"] = "Nf6 | f5";
    book["1. c4 e5 2. Nc3 Nc6 3. Nf3 Nf6"] = "g3 | e3";

    book["1. c4 e5 2. Nc3 Nc6 3. g3 g6"] = "Bg2";
    book["1. c4 e5 2. Nc3 Nc6 3. g3 g6 4. Bg2"] = "Bg7";
    book["1. c4 e5 2. Nc3 Nc6 3. g3 g6 4. Bg2 Bg7"] = "e3 | d3";


    book["1. c4 e5 2. Nc3 Nc6 3. g3 g6 4. Bg2 Bg7 5. d3"] = "d6";
    book["1. c4 e5 2. Nc3 Nc6 3. g3 g6 4. Bg2 Bg7 5. d3 d6 6. e3"] = "Nf6 | Be6";



    book["1. c4 e5 2. Nc3 Nc6 3. g3 f5"] = "Bg2";
    book["1. c4 e5 2. Nc3 Nc6 3. g3 f5 4. Bg2"] = "Nf6";
    book["1. c4 e5 2. Nc3 Nc6 3. g3 f5 4. Bg2 Nf6"] = "d3 | e3";

    book["1. c4 e5 2. Nc3 Nc6 3. g3 f5 4. Bg2 Nf6 5. a3"] = "g6";
    book["1. c4 e5 2. Nc3 Nc6 3. g3 f5 4. Bg2 Nf6 5. d3"] = "Bb4";
    book["1. c4 e5 2. Nc3 Nc6 3. g3 f5 4. Bg2 Nf6 5. e3"] = "e4";
    book["1. c4 e5 2. Nc3 Nc6 3. g3 f5 4. Bg2 Nf6 5. e3 e4 6. d3"] = "Bb4";
    book["1. c4 e5 2. Nc3 Nc6 3. g3 f5 4. Bg2 Nf6 5. e3 e4 6. d4"] = "Nb4";

    book["1. c4 e5 2. Nc3 Bc5"] = "Nf3 | g3";
    book["1. c4 e5 2. Nc3 Bc5 3. Nf3 Nc6"] = "e3";
    book["1. c4 e5 2. Nc3 Bc5 3. Nf3 Nc6 4. e3 d6"] = "d4";
    book["1. c4 e5 2. Nc3 Bc5 3. Nf3 Nc6 4. e3 Nf6"] = "d4";

    book["1. c4 e5 2. Nc3 Bc5 3. Nf3 d6"] = "e3";
    book["1. c4 e5 2. Nc3 Bc5 3. Nf3 d6 4. e3 Nd7"] = "a3";
    book["1. c4 e5 2. Nc3 Bc5 3. Nf3 d6 4. e3 a6"] = "d4";
    book["1. c4 e5 2. Nc3 Bc5 3. Nf3 d6 4. e3 a6 5. d4 exd4"] = "exd4";
    book["1. c4 e5 2. Nc3 Bc5 3. Nf3 d6 4. e3 a6 5. d4 exd4 6. exd4 Ba7"] = "Bd3";
    book["1. c4 e5 2. Nc3 Bc5 3. Nf3 d6 4. e3 a6 5. d4 exd4 6. exd4 Bb4"] = "Qa4+";


    // English opening (A13)
    book["1. c4 e6"] = "Nc3 | Nf3 | g3 | d4";
    book["1. c4 e6 2. Nc3"] = "d5 | Nf6";
    book["1. c4 e6 2. Nf3"] = "d5 | Nf6";
    book["1. c4 e6 2. g3"] = "d5 | Nf6";
    book["1. c4 e6 2. d4"] = "Nf6";
    book["1. c4 e6 2. d4 Nf6"] = "Nc3 | Nf3 | g3";

    book["1. c4 e6 2. Nf3 d5"] = "g3 | d4";


    book["1. c4 e6 2. Nf3 d5 3. d4 c6"] = "e3";
    book["1. c4 e6 2. Nf3 d5 3. d4 c5"] = "cxd5";
    book["1. c4 e6 2. Nf3 d5 3. d4 c5 4. cxd5 exd5"] = "Nc3";
    book["1. c4 e6 2. Nf3 d5 3. d4 Nf6"] = "Nc3";
    book["1. c4 e6 2. Nf3 d5 3. d4 Nf6 4. Nc3 Be7"] = "Bf4";
    book["1. c4 e6 2. Nf3 d5 3. d4 Nf6 4. Nc3 Bb4"] = "Bg5";
    book["1. c4 e6 2. Nf3 d5 3. d4 Nf6 4. Nc3 c6"] = "e3";


    book["1. c4 e6 2. Nf3 Nf6"] = "g3 | Nc3 | d4";

    book["1. c4 e6 2. d4 Nf6 3. g3"] = "d5 | Bb4+ | c5";
    book["1. c4 e6 2. d4 Nf6 3. g3 d5"] = "Bg2 | Nf3";
    book["1. c4 e6 2. d4 Nf6 3. g3 d5 4. Nf3"] = "Be7 | dxc4 | Bb4+";

    book["1. c4 e6 2. g3 d5"] = "Bg2 | Nf3";
    book["1. c4 e6 2. g3 d5 3. Bg2"] = "Nf6";
    book["1. c4 e6 2. g3 d5 3. Nf3"] = "Nf6";

    book["1. c4 e6 2. g3 Nf6"] = "Bg2 | Nf3";


    // A13 English opening, Agincourt variation -- WHITE
    book["1. c4 e6 2. Nf3 d5 3. g3 Nf6"] = "Bg2";

    book["1. c4 e6 2. Nf3 d5 3. g3 dxc4"] = "Bg2";
    book["1. c4 e6 2. Nf3 d5 3. g3 dxc4 4. Bg2 a6"] = "0-0";
    book["1. c4 e6 2. Nf3 d5 3. g3 dxc4 4. Bg2 a6 5. 0-0 Nf6"] = "Qc2";
    book["1. c4 e6 2. Nf3 d5 3. g3 dxc4 4. Bg2 a6 5. 0-0 Nf6 6. Qc2 c5"] = "Ne5";
    book["1. c4 e6 2. Nf3 d5 3. g3 dxc4 4. Bg2 a6 5. 0-0 Nf6 6. Qc2 Bd6"] = "Qxc4";
    book["1. c4 e6 2. Nf3 d5 3. g3 dxc4 4. Bg2 a6 5. 0-0 Nf6 6. Qc2 Be7"] = "Qxc4";


    book["1. c4 e6 2. Nf3 d5 3. g3 c6"] = "d4";
    book["1. c4 e6 2. Nf3 d5 3. g3 g6"] = "Bg2";
    book["1. c4 e6 2. Nf3 d5 3. g3 c5"] = "cxd5";
    book["1. c4 e6 2. Nf3 d5 3. g3 c5 4. cxd5 exd5"] = "d4";

    book["1. c4 e6 2. g3 d5 3. Nf3 Nf6"] = "d4";
    book["1. c4 e6 2. g3 d5 3. Nf3 Nf6 4. d4 Be7"] = "Bg2";
    book["1. c4 e6 2. g3 d5 3. Nf3 Nf6 4. d4 Bb4+"] = "Bd2";
    book["1. c4 e6 2. g3 d5 3. Nf3 Nf6 4. d4 Bb4+ 5. Bd2 Be7"] = "Bg2";


    // English opening (A17)
    book["1. c4 e6 2. Nc3 Nf6"] = "e4 | Nf3 | d4 | g3";


    // A01 Nimzovich-Larsen attack -- BLACK
    book["1. b3"] = "e5 | d5 | Nf6";
    book["1. b3 e5 2. c4"] = "Nf6 | Nc6";
    book["1. b3 e5 2. Bb2"] = "Nc6 | d6";
    book["1. b3 e5 2. Bb2"] = "Nc6 | d6";
    book["1. b3 d5 2. Nf3"] = "Nf6 | c5 | Bf5";
    book["1. b3 d5 2. Bb2"] = "c5 | Nf6 | Bf5";
    book["1. b3 Nf6 2. Bb2"] = "g6 | e6 |d5"; 
    book["1. b3 Nf6 2. Nf3"] = "g6 | d5 | e6 | d6 | b6";



    // Reti opening (A04)
    book["1. Nf3 f6"] = "d4";
    book["1. Nf3 f6 2. d4 d5"] = "e3 | c4";
    book["1. Nf3 f6 2. d4 g6"] = "e4";
    book["1. Nf3 f6 2. d4 d6"] = "e4";


    // Bird's opening (A02)
    book["1. f4"] = "d5 | Nf6";
    book["1. f4 d5 2. e3"] = "Nf6";
    book["1. f4 d5 2. Nf3"] = "Nf6";
    book["1. f4 d5 2. b3"] = "Nf6";
    book["1. f4 d5 2. g3"] = "Nf6";

    book["1. f4 d5 2. Nf3 Nf6 3. e3"] = "g6";
    book["1. f4 d5 2. Nf3 Nf6 3. e3 g6 4. b3"] = "Bg7";
    book["1. f4 d5 2. Nf3 Nf6 3. e3 g6 4. b3 Bg7 5. Bb2"] = "0-0";
    book["1. f4 d5 2. Nf3 Nf6 3. e3 g6 4. d4"] = "Bg7";
    book["1. f4 d5 2. Nf3 Nf6 3. e3 g6 4. d4 Bg7 5. Bd3"] = "0-0";

    book["1. f4 d5 2. Nf3 Nf6 3. g3"] = "g6 | c5 | e6";

    book["1. f4 Nf6 2. Nf3"] = "g6";
    book["1. f4 Nf6 2. b3"] = "g6";
    book["1. f4 Nf6 2. e3"] = "g6";

    book["1. f4 Nf6 2. Nf3 g6 3. e3"] = "Bg7";

    book["1. f4 Nf6 2. b3 g6 3. Nf3"] = "Bg7";
    book["1. f4 Nf6 2. b3 g6 3. Nf3 Bg7 4. Bb2"] = "0-0 | d5";



    // B06 Robatsch (modern) defence -- WHITE
    book["1. d4 g6 2. e4 Bg7"] = "Nc3 | Nf3 | c4";
    book["1. d4 g6 2. e4 Bg7 3. Nc3 d6"] = "Be3";
    book["1. d4 g6 2. e4 Bg7 3. Nc3 c6"] = "Nf3";
    book["1. d4 g6 2. e4 Bg7 3. Nc3 a6"] = "f4";
    book["1. d4 g6 2. e4 Bg7 3. Nc3 c5"] = "dxc5";
    book["1. d4 g6 2. e4 Bg7 3. Nc3 d5"] = "exd5";
    book["1. d4 g6 2. e4 Bg7 3. Nc3 Nc6"] = "Nf3";
    book["1. d4 g6 2. e4 Bg7 3. Nc3 b6"] = "Nf3";
    book["1. d4 g6 2. e4 Bg7 3. Nc3 b6 4. Nf3 Bb7"] = "h4";
    book["1. d4 g6 2. e4 Bg7 3. Nc3 e6"] = "h4";
    book["1. d4 g6 2. e4 Bg7 3. Nc3 e6 4. h4 Ne7"] = "h5";
    book["1. d4 g6 2. e4 Bg7 3. Nc3 e6 4. h4 h5"] = "Bg5";
    book["1. d4 g6 2. e4 Bg7 3. Nc3 e6 4. h4 h5 5. Bg5 Ne7"] = "Nf3";
    book["1. d4 g6 2. e4 Bg7 3. Nc3 e6 4. h4 h5 5. Bg5 f6"] = "Be3";
    book["1. d4 g6 2. e4 Bg7 3. Nc3 e6 4. h4 Nf6"] = "e5";
    book["1. d4 g6 2. e4 Bg7 3. Nc3 e6 4. h4 Nf6 5. e5 Ng8"] = "Bg5";
    book["1. d4 g6 2. e4 Bg7 3. Nc3 e6 4. h4 Nf6 5. e5 Ng8 6. Bg5 f6"] = "exf6";
    book["1. d4 g6 2. e4 Bg7 3. Nc3 e6 4. h4 Nf6 5. e5 Ng8 6. Bg5 Ne7"] = "h5";
    book["1. d4 g6 2. e4 Bg7 3. Nc3 e6 4. h4 Nf6 5. e5 Nd5"] = "Bg5";
    book["1. d4 g6 2. e4 Bg7 3. Nc3 e6 4. h4 Nf6 5. e5 Nd5 6. Bg5 Ne7"] = "h5";
    book["1. d4 g6 2. e4 Bg7 3. Nc3 e6 4. h4 Nf6 5. e5 Nd5 6. Bg5 f6"] = "exf6";


    // B01 Scandinavian (centre counter) defence -- WHITE
    book["1. e4 d5"] = "exd5";
    book["1. e4 d5 2. exd5 Qxd5"] = "Nc3";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qa5"] = "d4";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd6"] = "d4";


    // B01 Scandinavian Defense: Mieses-Kotroc Variation -- WHITE
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 e6"] = "Nf3 | Bc4 | Bf4 | Be3 | Bd3";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 c6"] = "Nf3 | Bc4 | Be3";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 Bf5"] = "Nf3 | Bc4 | g4";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 g6"] = "Nf3 | Bc4 | Be3 | Bf4";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 Nc6"] = "Nf3 | d5 | Be3";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 Nf6"] = "Nf3 | Bc4 | Be3 | Bg5";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 Nf6 5. Nf3 e6"] = "Bd3 | Bc4 | Bg5 | Be3 | Be2";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 Nf6 5. Nf3 c6"] = "Bc4 | Bd3 | Be2 | Bg5";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 Nf6 5. Nf3 Bg4"] = "Be2 | h3 | Bc4 | Be3";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 Nf6 5. Nf3 Bf5"] = "Bc4 | Bd3 | Ne5";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 Nf6 5. Nf3 Nc6"] = "Bb5 | Be3 | Bc4 | Bg5 | d5";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 Nf6 5. Nf3 g6"] = "Bc4 | Bg5 | Be3 | Be2";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 Nf6 5. Nf3 g6 6. Bc4 Bg7"] = "0-0 | Ne5 | Bg5";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 Nf6 5. Nf3 g6 6. Bg5 Bg7"] = "Qd2 | Bc4";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 Nf6 5. Nf3 g6 6. Be3 Bg7"] = "Bc4 | Qd2 | Bd3";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qd8 4. d4 Nf6 5. Nf3 g6 6. Be2 Bg7"] = "0-0 | Be3";




    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qe5+"] = "Be2";
    book["1. e4 d5 2. exd5 Qxd5 3. Nc3 Qe6+"] = "Be2";
    book["1. e4 d5 2. exd5 Nf6"] = "d4";
    book["1. e4 d5 2. exd5 Nf6 3. d4 Nxd5"] = "Nf3";
    book["1. e4 d5 2. exd5 Nf6 3. d4 c6"] = "dxc6";
    book["1. e4 d5 2. exd5 Nf6 3. d4 c6 4. dxc6 Nxc6"] = "Nf3";
    book["1. e4 d5 2. exd5 Nf6 3. d4 Qxd5"] = "Nf3";
    book["1. e4 d5 2. exd5 Nf6 3. d4 Bg4"] = "Bb5+";
    book["1. e4 d5 2. exd5 Nf6 3. d4 Bg4 4. Bb5+ Nbd7"] = "Be2";
    book["1. e4 d5 2. exd5 Nf6 3. d4 Bf5"] = "Bb5+";
    book["1. e4 d5 2. exd5 Nf6 3. d4 Bf5 4. Bb5+ Nbd7"] = "Nc3";


    // A11 English, Caro-Kann defensive system -- WHITE
    book["1. c4 c6 2. Nf3 e6"] = "e3 | d4 | e4";
    book["1. c4 c6 2. Nf3 e6 3. e3 Nf6"] = "d4";
    book["1. c4 c6 2. Nf3 e6 3. e3 d5"] = "d4";



    // A82 Dutch Defense: Staunton Gambit -- BLACK
    book["1. d4 f6 2. e4"] = "fxe4";
    book["1. d4 f6 2. e4 fxe4 3. Nc3"] = "Nf6";
    book["1. d4 f6 2. e4 fxe4 3. Bg5"] = "d5 | g6 | Nc6";
    book["1. d4 f6 2. e4 fxe4 3. f3 Nf6 4. Nc3"] = "d5 | exf3";
    book["1. d4 f6 2. e4 fxe4 3. f3 Nf6 4. Bg5"] = "d5 | Nc6";
    book["1. d4 f6 2. e4 fxe4 3. f3 Nf6 4. fxe4"] = "Nxe4";
    book["1. d4 f6 2. e4 fxe4 3. f3 Nf6 4. fxe4 Nxe4 5. Nc3"] = "Nf6";
    book["1. d4 f6 2. e4 fxe4 3. f3 Nf6 4. fxe4 Nxe4 5. Nf3"] = "d5";
    book["1. d4 f6 2. e4 fxe4 3. f3 Nf6 4. fxe4 Nxe4 5. Bd3"] = "d5";



    // Rare openings
    book["1. Nc3"] = "Nf6 | d5";
    book["1. Nc3 Nf6 2. e4"] = "e5";
    book["1. Nc3 Nf6 2. Nf3"] = "d5";
    book["1. Nc3 Nf6 2. d3"] = "d5";
    book["1. Nc3 Nf6 2. d4"] = "d5";
    book["1. Nc3 Nf6 2. d4 d5 3. Bf4"] = "e6";
    book["1. Nc3 Nf6 2. d4 d5 3. Nf3"] = "e6";
    book["1. Nc3 Nf6 2. d4 d5 3. e4"] = "dxe4";
    book["1. Nc3 Nf6 2. d4 d5 3. Bg5"] = "Nbd7";
    book["1. Nc3 Nf6 2. d4 d5 3. Bg5 Nbd7 4. Nf3"] = "h6";
    book["1. Nc3 Nf6 2. d4 d5 3. Bg5 Nbd7 4. Nf3 h6 5. Bh4"] = "e6";
    book["1. Nc3 Nf6 2. d4 d5 3. Bg5 Nbd7 4. Nf3 h6 5. Bf4"] = "e6";
    book["1. Nc3 Nf6 2. d4 d5 3. Bg5 Nbd7 4. Nf3 h6 5. Bxf6"] = "Nxf6";
    book["1. Nc3 Nf6 2. d4 d5 3. Bg5 Nbd7 4. Bf4"] = "e6";
    book["1. Nc3 Nf6 2. d4 d5 3. Bg5 Nbd7 4. Qd3"] = "c5";
    book["1. Nc3 Nf6 2. d4 d5 3. Bg5 Nbd7 4. f3"] = "h6";
    book["1. Nc3 Nf6 2. d4 d5 3. Bg5 Nbd7 4. f3 h6 5. Bh4"] = "c5";
    book["1. Nc3 Nf6 2. d4 d5 3. Bg5 Nbd7 4. f3 h6 5. Bf4"] = "c5";
    book["1. Nc3 Nf6 2. d4 d5 3. Bg5 Nbd7 4. f3 h6 5. Bxf6"] = "Nxf6";
    book["1. Nc3 Nf6 2. d4 d5 3. Bg5 Nbd7 4. e3"] = "e6";

    book["1. e4 d6"] = "d4 | Nc3 | f4";
    book["1. e4 d6 2. d4 g6"] = "Nc3";
    book["1. e4 d6 2. d4 e5"] = "dxe5";
    book["1. e4 d6 2. d4 e5 3. dxe5 dxe5"] = "Qxd8+";
    book["1. e4 d6 2. d4 e5 3. dxe5 dxe5 4. Qxd8+ Kxd8"] = "Bc4";
    book["1. e4 d6 2. d4 c6"] = "c3 | Nf3 | c4 | Nc3";
    book["1. e4 d6 2. d4 Nf6"] = "Nc3 | Bd3";
    book["1. e4 d6 2. d4 Nf6 3. Nc3 e5"] = "dxe5";
    book["1. e4 d6 2. d4 Nf6 3. Nc3 e5 4. dxe5 dxe5"] = "Qxd8+";


    book["1. e4 d6 2. d4 Nf6 3. Nc3 e5 4. dxe5 dxe5 5. Qxd8+ Kxd8"] = "Bc4";
    book["1. e4 d6 2. d4 Nf6 3. Nc3 e5 4. dxe5 dxe5 5. Qxd8+ Kxd8 6. Bc4 Be6"] = "Bxe6";
    book["1. e4 d6 2. d4 Nf6 3. Nc3 e5 4. dxe5 dxe5 5. Qxd8+ Kxd8 6. Bc4 Be6 7. Bxe6 fxe6"] = "f3";
    book["1. e4 d6 2. d4 Nf6 3. Nc3 e5 4. dxe5 dxe5 5. Qxd8+ Kxd8 6. Bc4 Be6 7. Bxe6 fxe6 8. f3 Bb4"] = "Ne2";
    book["1. e4 d6 2. d4 Nf6 3. Nc3 e5 4. dxe5 dxe5 5. Qxd8+ Kxd8 6. Bc4 Ke8"] = "Bd2";
    book["1. e4 d6 2. d4 Nf6 3. Nc3 e5 4. dxe5 dxe5 5. Qxd8+ Kxd8 6. Bc4 Bb4"] = "Bd2";
    book["1. e4 d6 2. d4 Nf6 3. Nc3 e5 4. dxe5 dxe5 5. Qxd8+ Kxd8 6. Bc4 Bb4 7. Bd2 Ke7"] = "a3";




    book["1. e4 d6 2. d4 Nf6 3. Nc3 c6"] = "Nf3";
    book["1. e4 d6 2. d4 Nf6 3. Nc3 g6"] = "f4";
    book["1. e4 d6 2. d4 Nf6 3. Nc3 g6 4. f4 c5"] = "dxc5";
    book["1. e4 d6 2. d4 Nf6 3. Nc3 g6 4. f4 Bg7"] = "Nf3";
    book["1. e4 d6 2. d4 Nf6 3. Nc3 g6 4. f4 Bg7 5. Nf3 0-0"] = "e5";
    book["1. e4 d6 2. d4 Nf6 3. Nc3 g6 4. f4 Bg7 5. Nf3 0-0 6. e5 Nfd7"] = "Bc4";
    book["1. e4 d6 2. d4 Nf6 3. Nc3 g6 4. f4 Bg7 5. Nf3 0-0 6. e5 dxe5"] = "dxe5";
    book["1. e4 d6 2. d4 Nf6 3. Nc3 g6 4. f4 Bg7 5. Nf3 0-0 6. e5 dxe5 7.  dxe5 Qxd1+"] = "Nxd1";


    book["1. e4 d6 2. d4 b6"] = "Nc3 | c4 | Nf3 | Bd3 | f4";
    book["1. e4 d6 2. d4 b6 3. Nc3 Bb7"] = "Nf3 | Bd3 | f4";
    book["1. e4 d6 2. d4 b6 3. Nc3 e6"] = "Nf3 | Be3 | f4";
    book["1. e4 d6 2. d4 b6 3. c4 Bb7"] = "Nc3 | d5";
    book["1. e4 d6 2. d4 b6 3. c4 g6"] = "Nc3 | Nf3";
    book["1. e4 d6 2. d4 b6 3. Nf3 Bb7"] = "Nc3 | Bd3 | d5 | Bc4";
    book["1. e4 d6 2. d4 b6 3. Nf3 c5"] = "dxc5 | d5 | Nc3";
    book["1. e4 d6 2. d4 b6 3. Nf3 g6"] = "Nc3 | Bc4";
    book["1. e4 d6 2. d4 b6 3. Nf3 Nf6"] = "Nc3 | Bd3";
    book["1. e4 d6 2. d4 b6 3. Bd3 Bb7"] = "Nf3 | c4 | f4";
    book["1. e4 d6 2. d4 b6 3. Bd3 g6"] = "Ne2 | Nf3 | Be3";
    book["1. e4 d6 2. d4 b6 3. f4 Bb7"] = "Bd3 | Nc3";
    book["1. e4 d6 2. d4 b6 3. f4 e6"] = "Nf3 | Bd3 | c4";


    book["1. e4 d6 2. d4 Nf6 3. Bd3"] = "e5 | g6 | Nbd7";


    // B00 Pirc Defense -- BLACK
    book["1. e4 d6 2. d4"] = "Nf6";


    book["1. e4 e5 2. Qh5"] = "Nc6";
    book["1. e4 e5 2. Qh5 Nc6 3. Bc4"] = "g6";
    book["1. e4 e5 2. Qh5 Nc6 3. Bc4 g6 4. Qd1"] = "Bg7";
    book["1. e4 e5 2. Qh5 Nc6 3. Bc4 g6 4. Qf3"] = "Nf6";
    book["1. e4 e5 2. Qh5 Nc6 3. Bc4 g6 4. Qf3 Nf6 5. Ne2"] = "Bg7";
    book["1. e4 e5 2. Qh5 Nc6 3. Bc4 g6 4. Qf3 Nf6 5. d3"] = "Nd4";
    book["1. e4 e5 2. Qh5 Nc6 3. Bc4 g6 4. Qf3 Nf6 5. Nc3"] = "Nd4";


    // B00 King's pawn opening -- WHITE 
    book["1. e4 d6 2. d4 c6 3. Nc3 Nf6"] = "Nf3";
    book["1. e4 d6 2. d4 c6 3. Nc3 g6"] = "Be3";
    book["1. e4 d6 2. d4 c6 3. Nc3 e5"] = "Bc4";
    book["1. e4 d6 2. d4 c6 3. Nc3 Qc7"] = "f4";
    book["1. e4 d6 2. d4 c6 3. Nc3 b5"] = "Nf3";
    book["1. e4 d6 2. d4 c6 3. Nc3 Nd7"] = "Bc4";


    book["1. c4 c6"] = "Nf3";
    book["1. c4 c6 2. Nf3 Nf6"] = "d4";
    book["1. c4 c6 2. Nf3 d5"] = "e3";
    book["1. c4 c6 2. Nf3 d5 3. e3 Nf6"] = "Nc3";

    book["1. c4 c6 2. Nf3 d5 3. e3 Nf6 4. Nc3 e6"] = "d4";
    book["1. c4 c6 2. Nf3 d5 3. e3 Nf6 4. Nc3 e6 5. d4 Nbd7"] = "Qc2";
    book["1. c4 c6 2. Nf3 d5 3. e3 Nf6 4. Nc3 e6 5. d4 Nbd7 6. Qc2 h6"] = "b3";
    book["1. c4 c6 2. Nf3 d5 3. e3 Nf6 4. Nc3 e6 5. d4 Nbd7 6. Qc2 Bd6"] = "Bd3";
    book["1. c4 c6 2. Nf3 d5 3. e3 Nf6 4. Nc3 e6 5. d4 Nbd7 6. Qc2 Bd6 7. Bd3 dxc4"] = "Bxc4";
    book["1. c4 c6 2. Nf3 d5 3. e3 Nf6 4. Nc3 e6 5. d4 Nbd7 6. Qc2 Bd6 7. Bd3 0-0"] = "0-0";


    book["1. c4 c6 2. Nf3 d5 3. e3 Nf6 4. Nc3 g6"] = "d4";
    book["1. c4 c6 2. Nf3 d5 3. e3 Nf6 4. Nc3 g6 5. d4 Bg7"] = "Be2";
    book["1. c4 c6 2. Nf3 d5 3. e3 Nf6 4. Nc3 g6 5. d4 Bg7 6. Be2 0-0"] = "0-0";


    book["1. c4 c6 2. Nf3 d5 3. e3 Nf6 4. Nc3 a6"] = "d4";
    book["1. c4 c6 2. Nf3 d5 3. e3 Nf6 4. Nc3 a6 5. d4 e6"] = "b3";
    book["1. c4 c6 2. Nf3 d5 3. e3 Nf6 4. Nc3 a6 5. d4 e6 6. b3 Bb4"] = "Bd2";
    book["1. c4 c6 2. Nf3 d5 3. e3 Nf6 4. Nc3 a6 5. d4 e6 6. b3 Bb4 7. Bd2 Nbd7"] = "Bd3";


    book["1. c4 c6 2. Nf3 d5 3. e3 Nf6 4. Nc3 Nd7"] = "d4";
    book["1. c4 c6 2. Nf3 d5 3. e3 Nf6 4. Nc3 Bg4"] = "Qb3";
    book["1. c4 c6 2. Nf3 d5 3. e3 Nf6 4. Nc3 Bg4 5. Qb3 Qb6"] = "Ne5";
    book["1. c4 c6 2. Nf3 d5 3. e3 Nf6 4. Nc3 Bg4 5. Qb3 Qb6 6. Ne5 Be6"] = "d4";
    book["1. c4 c6 2. Nf3 d5 3. e3 Nf6 4. Nc3 Bg4 5. Qb3 Qb6 6. Ne5 Qxb3"] = "axb3";
    book["1. c4 c6 2. Nf3 d5 3. e3 Nf6 4. Nc3 Bg4 5. Qb3 Qb6 6. Ne5 Qxb3 7. axb3 e6"] = "Nxg4";
    book["1. c4 c6 2. Nf3 d5 3. e3 Nf6 4. Nc3 Bg4 5. Qb3 Qb6 6. Ne5 Qxb3 7. axb3 e6 8. Nxg4 Nxg4"] = "d4";

    book["1. c4 c6 2. Nf3 d5 3. e3 e6"] = "b3";



    book["1. d4 g6"] = "c4 | e4";

    book["1. d4 g6 2. c4 Bg7"] = "e4";
    book["1. d4 g6 2. c4 Bg7 3. e4 d6"] = "Nc3";
    book["1. d4 g6 2. c4 Bg7 3. e4 c5"] = "d5";

    book["1. e4 c6 2. Qf3"] = "d5";
    
    book["1. Nf3 Nc6"] = "d4";
    book["1. Nf3 Nc6 2. d4 e5"] = "dxe5";
    book["1. Nf3 Nc6 2. d4 e5 3. dxe5 Bc5"] = "Nc3";
    book["1. Nf3 Nc6 2. d4 e5 3. dxe5 Bc5 4. Nc3 d6"] = "Bf4";
    book["1. Nf3 Nc6 2. d4 e5 3. dxe5 Bc5 4. Nc3 d6 5. Bf4 Bg4"] = "exd6";
    book["1. Nf3 Nc6 2. d4 e5 3. dxe5 Bc5 4. Nc3 d6 5. Bf4 Bg4 6. exd6 cxd6"] = "Ne4";

    book["1. Nf3 d6"] = "d4 | c4 | e4 ";
    book["1. Nf3 d6 2. d4 Nf6"] = "c4 | g3";
    book["1. Nf3 d6 2. d4 Nc6"] = "e4 | c4 | d5";
    book["1. Nf3 d6 2. d4 Nc6 3. d5 Nb8"] = "c4";

    book["1. Nf3 Nc6 2. d4 d5"] = "Bf4 | c4";
    book["1. Nf3 Nc6 2. d4 d5 3. Bf4 a6"] = "c4";

    book["1. e3"] = "e5 | d5 | Nf6 | g6";
    book["1. e3 e5 2. Nc3"] = "Nf6 | d5";


    // A80 Dutch Defense -- WHITE
    book["1. d4 f5"] = "Nf3 | g3 | Bg5 | c4";






    book["1. d4 d6"] = "Nf3 | e4";
    book["1. d4 d6 2. Nf3 Bg4"] = "c4 | e4";
    book["1. d4 d6 2. Nf3 g6"] = "c4 | g3";
    book["1. d4 d6 2. Nf3 Nf6"] = "c4 | g3 | Nc3";
    book["1. d4 d6 2. e4 Nf6"] = "Nc3";
    book["1. d4 d6 2. e4 e5"] = "Nf3 | dxe5";



    // A80 Dutch Defense -- BLACK
    book["1. d4 f5 2. Nf3"] = "Nf6";
    book["1. d4 f5 2. Bg5"] = "h6 | g6";
    book["1. d4 f5 2. c4"] = "Nf6";


    book["1. d4 f5 2. g3 Nf6 3. Nf3"] = "d6 | g6";
    book["1. d4 f5 2. g3 Nf6 3. c4"] = "g6 | c6";
    book["1. d4 f5 2. g3 Nf6 3. Bg2"] = "d5 | g6";



    // A80 Dutch Defense -- WHITE
    book["1. d4 f5 2. g3 g6"] = "h4";
    book["1. d4 f5 2. g3 g6 3. h4 Bg7"] = "h5";
    book["1. d4 f5 2. g3 g6 3. h4 Bg7 4. h5 d5"] = "Nf3";
    book["1. d4 f5 2. g3 e6"] = "Nf3 | c4";
    book["1. d4 f5 2. g3 Nf6"] = "Bg2 | c4";
    book["1. d4 f5 2. g3 Nf6 3. Bg2 g6"] = "Nh3 | b3";
    book["1. d4 f5 2. g3 Nf6 3. Bg2 e6"] = "Nh3 | Nf3";
    book["1. d4 f5 2. g3 Nf6 3. Bg2 d6"] = "Nf3";
    book["1. d4 f5 2. g3 Nf6 3. Bg2 d5"] = "Nh3 | c4";



    // B06 Robatsch (modern) defence -- WHITE
    book["1. d4 d6 2. e4 g6 3. Nc3 c6"] = "Be3";
    book["1. d4 d6 2. e4 g6 3. Nc3 Nf6"] = "f4";
    book["1. d4 d6 2. e4 g6 3. Nc3 Bg7"] = "Nf3";
    book["1. d4 d6 2. e4 g6 3. Nc3 Bg7 4. Nf3 Nf6"] = "Be2";
    book["1. d4 d6 2. e4 g6 3. Nc3 Bg7 4. Nf3 a6"] = "Bc4";
    book["1. d4 d6 2. e4 g6 3. Nc3 Bg7 4. Nf3 Bg4"] = "Be3";
    book["1. d4 d6 2. e4 g6 3. Nc3 Bg7 4. Nf3 Nd7"] = "Be2";
    book["1. d4 d6 2. e4 g6 3. Nc3 Bg7 4. Nf3 Nc6"] = "Be3";
    book["1. d4 d6 2. e4 g6 3. Nc3 Bg7 4. Nf3 e6"] = "Bf4";
    book["1. d4 d6 2. e4 g6 3. Nc3 Bg7 4. Nf3 c6"] = "0-0";
    book["1. d4 d6 2. e4 g6 3. Nc3 Bg7 4. Nf3 c6 5. Be2 Nf6"] = "0-0";
    book["1. d4 d6 2. e4 g6 3. Nc3 Bg7 4. Nf3 c6 5. Be2 Nd7"] = "0-0";


    book["1. e4 e5 2. h4"] = "Nf6";

    book["1. g4"] = "d5 | e5";
    book["1. g4 d5 2. Bg2"] = "c6";

    book["1. d4 e5"] = "dxe5";
    book["1. d4 e5 2. dxe5 Nc6"] = "Nf3";
    book["1. d4 e5 2. dxe5 Nc6 3. Nf3 Qe7"] = "Nc3";

    book["1. e4 c5 2. Qf3"] = "Nc6 | e6";

    book["1. d3"] = "d5";
    book["1. d3 d5 2. e3"] = "e5";
    book["1. d3 d5 2. e3 e5 3. Nf3"] = "Nc6";
    book["1. d3 d5 2. e3 e5 3. Nc3"] = "Nc6";

    book["1. d3 d5 2. Qd2"] = "e5";

    book["1. b4"] = "d5 | e5";
    book["1. b4 e5 2. Bb2"] = "Bxb4"; 
    book["1. b4 e5 2. Bb2 Bxb4 3. Bxe5"] = "Nf6";
    book["1. b4 e5 2. Bb2 Bxb4 3. Bxe5 Nf6 4. Nf3"] = "d5";
    book["1. b4 e5 2. Bb2 Bxb4 3. Bxe5 Nf6 4. c4"] = "Nc6";
    book["1. b4 e5 2. Bb2 Bxb4 3. Bxe5 Nf6 4. e3"] = "d5";
    book["1. b4 e5 2. Bb2 Bxb4 3. Bxe5 Nf6 4. Nc3"] = "d5";
    book["1. b4 e5 2. Bb2 Bxb4 3. Bxe5 Nf6 4. c3"] = "Ba5";
    book["1. b4 e5 2. Bb2 Bxb4 3. Bxe5 Nf6 4. c3 Ba5 5. e3"] = "0-0";

    book["1. e4 e5 2. Ne2"] = "Nf6";
    book["1. e4 e5 2. Ne2 Nf6 3. Ng3"] = "Nc6";


    // Old Benoni Defense (A43)
    book["1. d4 c5"] = "d5";
    book["1. d4 c5 2. d5 e5"] = "e4";
    book["1. d4 c5 2. d5 Nf6"] = "c4 | Nc3";
    book["1. d4 c5 2. d5 d6"] = "c4";
    book["1. d4 c5 2. d5 e6"] = "c4";
    book["1. d4 c5 2. d5 g6"] = "e4";


    // A00 Hungarian opening -- BLACK
    book["1. g3"] = "d5 | c5 | Nf6 | e5 | g6";



    // A04 Zukertort Opening: Queen's Gambit Invitation -- WHITE
    book["1. Nf3 e6"] = "e4 | d4 | c4";


    // A04 Zukertort Opening: Queen's Gambit Invitation -- BLACK
    book["1. Nf3 e6 2. g3"] = "Nf6 | d5 | Be7";
    book["1. Nf3 e6 2. g3 Nf6 3. c4"] = "d5 | Be7 | Nc6";
    book["1. Nf3 e6 2. g3 Nf6 3. Bg2"] = "d5 | c6 | b6";

    book["1. Nf3 e6 2. d4"] = "d5 | Nf6 | c5";
    book["1. Nf3 e6 2. d4 Nf6 3. e3"] = "Be7 | b6 | d5";
    book["1. Nf3 e6 2. d4 Nf6 3. Bf4"] = "d5 | c5";
    book["1. Nf3 e6 2. d4 Nf6 3. c4"] = "d5 | Be7";
    book["1. Nf3 e6 2. d4 Nf6 3. c4 d5 4. g3"] = "Bb4+ | dxc4 | Nbd7";
    book["1. Nf3 e6 2. d4 Nf6 3. c4 d5 4. cxd5"] = "exd5";
    book["1. Nf3 e6 2. d4 Nf6 3. c4 d5 4. Bg5"] = "dxc4 | h6 | c6";
    book["1. Nf3 e6 2. d4 Nf6 3. c4 d5 4. Nc3"] = "c5 | Bb4 | c6";
    book["1. Nf3 e6 2. d4 Nf6 3. c4 d5 4. Nc3 Bb4 5. Qa4+"] = "Nc6";
    book["1. Nf3 e6 2. d4 Nf6 3. c4 d5 4. Nc3 Bb4 5. Bg5"] = "h6 | dxc4";
    book["1. Nf3 e6 2. d4 Nf6 3. c4 d5 4. Nc3 Bb4 5. e3"] = "0-0";
    book["1. Nf3 e6 2. d4 Nf6 3. c4 d5 4. Nc3 Bb4 5. Qb3"] = "a5 | c5";
    book["1. Nf3 e6 2. d4 Nf6 3. c4 d5 4. Nc3 Bb4 5. cxd5"] = "exd5";
    book["1. Nf3 e6 2. d4 Nf6 3. c4 d5 4. Nc3 Bb4 5. cxd5 exd5 6. Bf4"] = "Ne4 | Bf5 | Nc6";
    book["1. Nf3 e6 2. d4 Nf6 3. c4 d5 4. Nc3 Bb4 5. cxd5 exd5 6. Bg5"] = "0-0 | h6 | Nbd7";
    book["1. Nf3 e6 2. d4 Nf6 3. c4 d5 4. Nc3 Bb4 5. cxd5 exd5 6. Qa4+"] = "Nc6";


    // Rare openings
    book["1. h3"] = "e5";
    book["1. h3 e5 2. a3"] = "d5";
    book["1. a3"] = "c5";
    book["1 f3"] = "e5";
}



/*!
 * Find a reply move to a given sequence.
 *
 * This function searches the book file for a given sequence and returns a
 * random move out of the list of replies. If the sequence wasn't found, it
 * returns NULL.
 *
 * @return a string containing the randomly selected move from the replies.
 */
string getReplyTo(string sequence)
{
    string replies_buf;
    char delimiter = '|';
    vector<string> replies;
    string tok;

    // get the list of replies for a given sequence
    replies_buf = book[sequence];

    // if no replies, return
    if (replies_buf == "")
        return "";

    // if there are replies, parse them and return them
    stringstream ss(replies_buf);

    // tokenize the line and get a vector of strings with the
    // possible replies 
    while (getline(ss, tok, delimiter))
    {
        tok.erase(std::remove(tok.begin(), tok.end(),' '), tok.end());
        replies.push_back(tok);
    }

    // select a random reply and return it
    srand(time(NULL));
    int randomIndex = rand() % replies.size();
    return replies[randomIndex];
}
