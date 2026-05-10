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



// @file search.cpp
//
// This file contains the main search methods for finding the best next move.
//
// It is based on a simple alpha-beta pruning mechanism runnning on top of a
// mini-max, with plenty of optimizations.
#if defined(_WIN32) || defined(_WIN64)
#include <conio.h>
#else
#include <unistd.h>
#endif



#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <iomanip>
#include <cinttypes>
#include "definitions.h" 
#include "extglobals.h" 
#include "functions.h" 
#include "board.h" 
#include "timer.h" 
#include "app.h"
#include "cache.h"



using namespace std;



// initialize basic variables for the iterative-deepening search
unsigned short nextDepth = 0;
ttEntry tt;
float cacheHit;
int score = 0;



// Board::think
//
// This is the iterative deepening framework to use alphabeta search. It starts
// with depth=1 and searches the best move. After that, moves are sorted and
// the best move is then searched at depth=2, then depth=3, etc.
Move Board::think()
{
    int legalmoves, currentdepth;
    Move singlemove;
    cacheHit = 0;


    // if at the end of the game, terminate the search
    if (isEndOfgame(legalmoves, singlemove))
        return NOMOVE;


    // if one legal move, return the move and terminate the search
    if (legalmoves == 1) 
        return singlemove;


    // initialize search with PV
    lastPVLength = 0;
    memset(lastPV, 0 , sizeof(lastPV));
    memset(whiteHeuristics, 0, sizeof(whiteHeuristics));
    memset(blackHeuristics, 0, sizeof(blackHeuristics));
    nodes = 0;
    countdown = UPDATEINTERVAL;
    timedout = false;


    // display console header
    if (!beQuiet)
        displaySearchStats(1, 0, 0);  


    // initialize timer
    timer.init();
    msStart = timer.getms();


    //  iterative deepening:
    for (currentdepth = 1; currentdepth <= board.searchDepth; currentdepth++)
    {
        // clear the buffers
        memset(moveBufLen, 0, sizeof(moveBufLen));
        memset(moveBuffer, 0, sizeof(moveBuffer));
        memset(triangularLength, 0, sizeof(triangularLength));
        memset(triangularArray, 0, sizeof(triangularArray));
        followPV = true;
        allownull = true;


        // enter actual search
        score = alphabetapvs(0, currentdepth, -LARGE_NUMBER, LARGE_NUMBER);


        // check if time is up or if UCI asked to stop the search
        if (timedout)
        {
            rememberPV();
            return (lastPV[0]);
        }
        else
        {
            msStop = timer.getms();
            rememberPV();

            if ((msStop - msStart) > maxTime)
            {
                if (!beQuiet)
                    cout << "    ok" << endl;

                return (lastPV[0]);
            }
        }


        // display search analysis
        if (UCI)
        {
            cout << "info score cp " << score << " depth " << currentdepth << " nodes " << nodes << " time " << timer.getms();
            cout << " pv ";
            displayUCIPV();
        }
        else if (!beQuiet)
        {
            displaySearchStats(2, currentdepth, score);
        }


        // stop searching if the current depth leads to a forced mate
        if ((score > (CHECKMATESCORE-currentdepth)) || (score < -(CHECKMATESCORE-currentdepth))) 
        {
            rememberPV();
            currentdepth = board.searchDepth;
        }
    }

    return lastPV[0];
}



// alphabetapvs
//
// Main alphabeta algorithm (Negamax) which relies on a Principal Variation
// search. This algorithm uses the following steps:
//
//  1. null move pruning
//  2. sort moves (score based on historic appearance, capture gain, etc)
//  3. look up move hash (from previous searches)
//  4. late move reductions (LMR)
//  8. start full search
//
// The score returned by the algorithm is always from calling qsearch().
int Board::alphabetapvs(int ply, int depth, int alpha, int beta)
{
	int i, j, movesfound, pvmovesfound, val;
    bool cached = false;


    // prepare structure to store the principal variation (PV)
	triangularLength[ply] = ply;


    // if at leaf node, return qiescent value
    if (depth <= 0) 
	{
		followPV = false;
		return qsearch(ply, alpha, beta);
	}


	// repetition check
	if (repetitionCount() >= 3)
        return DRAWSCORE;


    // in case ply gets too deep, avoid overflow and return
    if (ply > SOLVE_MAX_DEPTH)
        return qsearch(ply, alpha, beta);


    // increment nodes count
    nodes++;



	
    // 1. Null move pruning
    // 
    // Not allowed if:
    //  - side on move is in check (illegal position)
    //  - coming from another null move (burn 2 plies uselessly)
    //  - side on move has only pawns left (avoid zugzwang regressions)
	if (!followPV && allownull)
	{
		if ((nextMove && (board.totalBlackPieces > NULLMOVE_LIMIT)) || (!nextMove && (board.totalWhitePieces > NULLMOVE_LIMIT)))
		{
			if (!isOwnKingAttacked())
			{
                // don't allow two consecutive null moves
				allownull = false;

                // check the clock and the input status
				if (--countdown <=0)
                    readClockAndInput();

				nextMove = !nextMove;
				hashkey ^= KEY.side; 
				val = -alphabetapvs(ply, depth - NULLMOVE_REDUCTION, -beta, -beta+1);
				nextMove = !nextMove;
				hashkey ^= KEY.side;

                // if time's up, stop searching
				if (timedout)
                    return 0;

                // end of null move pruning
				allownull = true;

                // if fail high, return beta bound
				if (val >= beta)
                    return beta;
			}
		}
	}


    // prepare to start a full-depth search
	allownull       = true;
	movesfound      = 0;
	pvmovesfound    = 0;
    unsigned moveNo = 0;


    // generate a list of moves, sorted by three main criteria:
    //  1. first  -> static exchange evaluatoin (SEE)
    //  2. second -> high-gain captures first (MVV/LVA)
    //  3. third  -> historically "good" moves (those which produce cut-off) 
    //  4. rest of the moves
	moveBufLen[ply+1] = movegen(moveBufLen[ply]);



    // go through every move and search the tree below
	for (i = moveBufLen[ply]; i < moveBufLen[ply+1]; i++)
	{
        // pick the next best move from a sorted list
		selectmove(ply, i, depth, followPV); 


        // make th emove and evaluate the board
		makeMove(moveBuffer[i]);
		{
            // try to find the current position in the cache
            cached = false;
            if (useCache)
            {
                tt = cache.find(board.hashkey, depth);
                if ((tt.key != 0) && (tt.depth != TT_EMPTY_VALUE))
                {
                    cacheHit++;
                    val = tt.score;
                    cached = true;

                    // XXX TT XXX
					triangularArray[ply][ply] = moveBuffer[i];
                    //lastPV[i] = board.triangularArray[0][i];
                    //lastPVLength = board.triangularLength[0];
                    rememberPV();
                }
            }

            // only search this move if legal --> remember that movegen() returns
            // pseudo-legal moves
			if (!isOtherKingAttacked()) 
			{
                moveNo++;

                // check the clock and the input status
				if (--countdown <=0)
                    readClockAndInput();

				movesfound++;


				if (!ply && (depth > 1))
                    if (!beQuiet)
                        displaySearchStats(3, ply, i); 


                // Alphabeta with Principal Variation Search (PVS)
                if (!cached)
                {
                    // LMR
                    //
                    // Configure late-move reductions (LMR): assuming that the moves in the
                    // list are ordered from potential best to potential worst, analyzing 
                    // the first moves is more critical than the last ones. Therefore, 
                    // using LMR we analyze the first 2 moves in full-depth, but cut down
                    // the analysis depth for the rest of moves.
                    nextDepth = depth - 1;
                    if (LMR && (ply > LMR_PLY_START) && (depth > LMR_SEARCH_DEPTH)
                                              && !((moveBuffer[i]).isCapture())
                                              && !((moveBuffer[i]).isPromo())
                                              && !(isOwnKingAttacked())
                                              && !(isOtherKingAttacked())
                                              && (moveNo > LMR_MOVE_START) && !pvmovesfound)
                    {
                        nextDepth = depth - 2;
                    }

                    if (pvmovesfound)
                    {
                        val = -alphabetapvs(ply+1, depth-1, -alpha-1, -alpha); 

                        // in case of failure, proceed with normal alphabeta
                        if ((val > alpha) && (val < beta))
                        {
                            val = -alphabetapvs(ply+1, depth-1, -beta, -alpha);  		        
                        }
                    } 
                    // normal alphabeta
                    else
                    {
                        val = -alphabetapvs(ply+1, nextDepth, -beta, -alpha);
                    }
                }
				unmakeMove(moveBuffer[i]);


                // if time is up, then return
				if (timedout)
                    return 0;


                // fail high (beta cutoff): return beta and update history heuristics
				if (val >= beta)
				{
					if (nextMove) 
						blackHeuristics[moveBuffer[i].getFrom()][moveBuffer[i].getTosq()] += depth*depth;
					else 
						whiteHeuristics[moveBuffer[i].getFrom()][moveBuffer[i].getTosq()] += depth*depth;

					return beta;
				}


                // found a better move (PV candidate)
				if (val > alpha)
				{
                    // update bounds
					alpha = val;
					pvmovesfound++;


                    // save this move in Principal Variation
					triangularArray[ply][ply] = moveBuffer[i];


                    // append the latest best PV from deeper plies
					for (j = ply + 1; j < triangularLength[ply+1]; j++) 
						triangularArray[ply][j] = triangularArray[ply+1][j];
					triangularLength[ply] = triangularLength[ply+1];


                    // show intermediate search results
					if (!ply && !beQuiet && (depth > 1))
                        displaySearchStats(2, depth, val);
				}
			}
			else unmakeMove(moveBuffer[i]);
		}

        
        // Store in cache (replacement scheme --> always replace)
        if (useCache && !cached)
        {
            if ((val > -CHECKMATESCORE) && (val < CHECKMATESCORE))
            {
                tt.key   = board.hashkey;
                tt.score = val;
                tt.depth = depth;
                cache.add(board.hashkey, &tt);
            }
        }
	}


	// update the history heuristic
	if (pvmovesfound)
	{
		if (nextMove) 
			blackHeuristics[triangularArray[ply][ply].getFrom()][triangularArray[ply][ply].getTosq()] += depth*depth;
		else
			whiteHeuristics[triangularArray[ply][ply].getFrom()][triangularArray[ply][ply].getTosq()] += depth*depth;
	}


	//	50-move rule:
	if (fiftyMove > 99)
        return DRAWSCORE;


	//	Checkmate/stalemate detection
	if (!movesfound)
	{
		if (isOwnKingAttacked())
            return (-CHECKMATESCORE+ply-1);
		else
            return (STALEMATESCORE);
	}


    // return the best possible score that fails low
	return alpha;
}



// displaySearchStats
//
// Display analysis statistics about the calculation of a move.
void Board::displaySearchStats(int mode, int depth, int score)
{
    char sanMove[12], timestring[8];
    float dt = (timer.getms() - msStart) / 1000.0;
    int netScore = score;
    int z = 1;


    // '+' is advantage for White, '-' is advantage for Black
    if (board.nextMove)
    {
        netScore *= -1;
        z = -1;
    }


    // display various search statistics
    //
    // mode = 1 : display header
    // mode = 2 : display full stats, including score and latest PV
    // mode = 3 : display current root move that is being searched
    //            depth = ply, score = loop counter in the search move list 
    switch (mode)
    {
        case 1: 
        {
            cout << "  Ply  Score    Nodes     Time\t Speed kN/s  PV" << endl;
            break;
        }

        case 2:
        {
            // depth
            cout << setw(5) << depth;

            // score
            cout << showpos << setw(7) << setprecision(2) << float(netScore/100.0);
            cout << noshowpos;

            // display the amount of nodes searched
            float cacheHitRatio = cacheHit / nodes;
            cout.fill(' ');
            if (cacheHitRatio > CACHE_HIT_LEVEL)
            {
                cout << "   Cached";
            }
            else
            {
                cout << " ";
                if (nodes > 1000000)
                    cout << setw(7) << setprecision(1) << float(nodes/1000000.0) << "M";
                else if (nodes > 1000)
                    cout << setw(7) << setprecision(1) << float(nodes/1000.0) << "K";
                else
                    cout << setw(8) << setprecision(0) << nodes;
            }
            cout.fill(' ');


            // search time
            cout << setw(8) << fixed << setprecision(2) << dt << "s ";


            // search speed
            float knps = (nodes / (dt * 1000)) / 1.0;
            if (dt > 0)
                cout << fixed << setprecision(1) << setw(7) << knps << " kN/s  ";
            else
                cout << "           -  ";

            // store this PV
            rememberPV();

            // display the PV
            displayPV();

            break;
        }

        case 3: 
        {
            if (!TO_CONSOLE)
                break;

            mstostring(dt, timestring);
            printf("             (%2d/%2d) %8s       ", score+1, moveBufLen[depth+1]-moveBufLen[depth], timestring);
            unmakeMove(moveBuffer[score]);
            toSan(moveBuffer[score], sanMove);
            cout << sanMove;
            makeMove(moveBuffer[score]);
            printf("...    \r");
            cout.flush();
            break;
        }

        default: break;
    }
}



// isEndOfgame()
//
// Checks if the current position is end-of-game due to:
// checkmate, stalemate, 75-move rule, or insufficient material.
bool Board::isEndOfgame(int &legalmoves, Move &singlemove)
{
    int whiteknights, whitebishops, whiterooks, whitequeens, whitetotalmat;
    int blackknights, blackbishops, blackrooks, blackqueens, blacktotalmat;

    // are we checkmating the other side?
    if (isOtherKingAttacked()) 
    {
        if (nextMove)
        {
            cout << "0-1 {Black mates}" << endl;
            winingDelta = -1;
        }
        else
        {
            cout << "1-0 {White mates}" << endl;
            winingDelta = +1;
        }

        return true;
    }

    // how many legal moves do we have?
    legalmoves = 0;
    moveBufLen[0] = 0;
    moveBufLen[1] = movegen(moveBufLen[0]);
    for (auto i = moveBufLen[0]; i < moveBufLen[1]; i++)
    {
        makeMove(moveBuffer[i]);
        if (!isOtherKingAttacked())
        { 
            legalmoves++;
            singlemove = moveBuffer[i];
        }
        unmakeMove(moveBuffer[i]);
    }

    // checkmate or stalemate?
    if (!legalmoves) 
    {
        if (isOwnKingAttacked()) 
        {
            if (nextMove)
            {
                cout << "1-0 {White mates}" << endl;
                winingDelta = 1;
            }
            else
            {
                cout << "0-1 {Black mates}" << endl;
                winingDelta = -1;
            }
        }
        else cout << "1/2-1/2 {stalemate}" << endl;
        return true;
    }

    // draw due to insufficient material:
    if (!whitePawns && !blackPawns)
    {
        whiteknights = bitCnt(whiteKnights);
        whitebishops = bitCnt(whiteBishops);
        whiterooks = bitCnt(whiteRooks);
        whitequeens = bitCnt(whiteQueens);
        whitetotalmat = 3 * whiteknights + 3 * whitebishops + 5 * whiterooks + 10 * whitequeens;
        blackknights = bitCnt(blackKnights);
        blackbishops = bitCnt(blackBishops);
        blackrooks = bitCnt(blackRooks);
        blackqueens = bitCnt(blackQueens);
        blacktotalmat = 3 * blackknights + 3 * blackbishops + 5 * blackrooks + 10 * blackqueens;

        // king versus king:
        if ((whitetotalmat == 0) && (blacktotalmat == 0)) 
        {
            cout << "1/2-1/2 {material}" << endl;
            return true;
        }

        // king and knight versus king:
        if (((whitetotalmat == 3) && (whiteknights == 1) && (blacktotalmat == 0)) ||
                ((blacktotalmat == 3) && (blackknights == 1) && (whitetotalmat == 0))) 
        {
            cout << "1/2-1/2 {material}" << endl;
            return true;
        }

        // 2 kings with one or more bishops, all bishops on the same colour:
        if ((whitebishops + blackbishops) > 0)
        {
            if ((whiteknights == 0) && (whiterooks == 0) && (whitequeens == 0) &&
                    (blackknights == 0) && (blackrooks == 0) && (blackqueens == 0))
            {
                if (!((whiteBishops | blackBishops) & WHITE_SQUARES) ||
                        !((whiteBishops | blackBishops) & BLACK_SQUARES))
                {
                    cout << "1/2-1/2 {material}" << endl;
                    return true;
                }
            }
        }

        // 4.5 K(B||N)-K(B||N)
        if ((whitetotalmat == 3) && (blacktotalmat == 3))
        {
            cout << "1/2-1/2 {material}" << endl;
            return true;
        }
    }

    // draw due to repetition:
    if (repetitionCount() >= 3) 
    {
        cout << "1/2-1/2 {repetition}" << endl;
        return true;

    }

    // draw due to 50-move rule:
    if (fiftyMove > 99) 
    {
        cout << "1/2-1/2 {75-move rule}" << endl;
        return true;
    }

    return false;
}



// repetitionCount()
//
// RepetitionCount is used to detect threefold repetitions of the current position.
int Board::repetitionCount()
{
    int i, ilast, rep;
    rep = 1;                                              // current position has occurred once, namely now!
    ilast = board.endOfSearch - board.fiftyMove;          // we don't need to go back all the way
    for (i = board.endOfSearch - 2; i >= ilast; i -= 2)   // we can skip every other position
    {
        if (gameLine[i].key == board.hashkey) rep++;
    }
    return rep;
}



// rememberPV()
//
// Remember the last PV, and also the 5 previous ones because
// they usually contain good moves to try.
void Board::rememberPV()
{
    lastPVLength = board.triangularLength[0];

    for (int i = 0; i < board.triangularLength[0]; i++)
    {
        lastPV[i] = board.triangularArray[0][i];
    }
}



// mstostring()
//
// convert milliseconds to a time string (hh:mm:ss, mm:ss, s, ms)
void mstostring(uint64_t dt, char *timestring)
{
    uint64_t hh, mm, ss;

    if (dt > 3600000) 
    {      
        hh = dt/3600000;
        mm = (dt - 3600000*hh)/60000;
        ss = (dt - 3600000*hh - 60000*mm)/1000;
        sprintf(timestring, "%02" PRIu64 ":%01" PRIu64 ":%02" PRIu64 "", hh, mm, ss);
    }
    else if (dt > 60000) 
    {      
        mm = dt/60000;
        ss = (dt - 60000*mm)/1000;
        sprintf(timestring, "%02" PRIu64 ":%02" PRIu64 "", mm, ss);
    }
    else if (dt > 10000)        sprintf(timestring, "%6.1f%s", float(dt/1000.0), "s");
    else if (dt > 1000)         sprintf(timestring, "%6.2f%s", float(dt/1000.0), "s");
    else if (dt > 0)            sprintf(timestring, "%5" PRIu64 "ms", dt);
    else                        sprintf(timestring, "0ms");
}



// qsearch
//
// Perform a search indefinitely until all the following conditions happen:
// a) no more possible captures
// b) no more checks possible
// c) no more pawn promotions
int Board::qsearch(int ply, int alpha, int beta)
{
    int i, j, val;


    // check the clock and the input status
    if (--countdown <=0)
        readClockAndInput();


    // if interrupted, return immediately
    if (timedout)
        return 0;


    // increment nodes count
    nodes++;


    // XXX
    triangularLength[ply] = ply;


    // in-check extension (search one more ply when in check)
    if (isOwnKingAttacked())
        return alphabetapvs(ply, 1, alpha, beta);

   
    // calculate standing pat as a baseline for the quiescent search
    val = board.eval();

    if (val >= beta)
        return beta;

    if (val > alpha)
        alpha = val;


    // generate captures & promotions: captgen returns a sorted move list
    moveBufLen[ply+1] = captgen(moveBufLen[ply]);
    for (i = moveBufLen[ply]; i < moveBufLen[ply+1]; i++)
    {
        makeMove(moveBuffer[i]);

        if (!isOtherKingAttacked()) 
        {
            val = -qsearch(ply+1, -beta, -alpha);
            unmakeMove(moveBuffer[i]);

            if (val >= beta)
                return beta;

            if (val > alpha)
            {
                alpha = val;
                triangularArray[ply][ply] = moveBuffer[i];
                for (j = ply + 1; j < triangularLength[ply+1]; j++) 
                    triangularArray[ply][j] = triangularArray[ply+1][j];
                triangularLength[ply] = triangularLength[ply+1];
            }
        }
        else unmakeMove(moveBuffer[i]);

    }

    return alpha;
}



// Board::selectmove()
//
// Re-order the move list so that the best move is selected as the next move to try.
void Board::selectmove(int &ply, int &i, int &depth, bool &isFollowPV)
{
    int j, k;
    unsigned int best;
    Move temp;

    if (isFollowPV && depth > 1)
    {
        for (j = i; j < moveBufLen[ply+1]; j++)
        {
            if (moveBuffer[j].moveInt == lastPV[ply].moveInt)
            {
                temp.moveInt = moveBuffer[j].moveInt;
                moveBuffer[j].moveInt = moveBuffer[i].moveInt;
                moveBuffer[i].moveInt = temp.moveInt;
                return;
            }
        }
    }


    if (nextMove) 
    {
        best = blackHeuristics[moveBuffer[i].getFrom()][moveBuffer[i].getTosq()];
        j = i;
        for (k = i + 1; k < moveBufLen[ply+1]; k++)
        {
            if (blackHeuristics[moveBuffer[k].getFrom()][moveBuffer[k].getTosq()] > best)
            {
                best = blackHeuristics[moveBuffer[k].getFrom()][moveBuffer[k].getTosq()];
                j = k;                  
            }
        }
        if (j > i)
        {
            temp.moveInt = moveBuffer[j].moveInt;
            moveBuffer[j].moveInt = moveBuffer[i].moveInt;
            moveBuffer[i].moveInt = temp.moveInt;
        }
    }
    else
    {
        best = whiteHeuristics[moveBuffer[i].getFrom()][moveBuffer[i].getTosq()];
        j = i;
        for (k = i + 1; k < moveBufLen[ply+1]; k++)
        {
            if (whiteHeuristics[moveBuffer[k].getFrom()][moveBuffer[k].getTosq()] > best)
            {
                best = whiteHeuristics[moveBuffer[k].getFrom()][moveBuffer[k].getTosq()];
                j = k;                  
            }
        }
        if (j > i)
        {
            temp.moveInt = moveBuffer[j].moveInt;
            moveBuffer[j].moveInt = moveBuffer[i].moveInt;
            moveBuffer[i].moveInt = temp.moveInt;
        }
    }
}
