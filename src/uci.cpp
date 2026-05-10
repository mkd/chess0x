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



// @file uci.cpp
//
// This file contains implementation of the UCI protocol.
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>

#include "board.h"
#include "extglobals.h"
#include "definitions.h"
#include "functions.h"
#include "app.h"



using namespace std;



// UCI time controls
int movestogo = 40;
int movetime = -1;
int comptime = -1;
int otime = 1;
int inc = 0;
int starttime = 0;
bool infsearch = false;



// uciLoop()
//
// Main program loop accepting UCI commands and executing them. This part of
// the application does not have a user interface (not even a CLI prompt).
int uciLoop(void)
{
    string cmd  = "";


    // turn off verbosity and flag UCI mode
    UCI = true;
    beQuiet = true;


    // Prompt the user for input from the command line
    cout << PROGRAM_NAME << " v" << PROGRAM_VERSION << endl << endl;
    cout << "id name " << PROGRAM_NAME << endl;
    cout << "id author " << PROGRAM_AUTHOR << endl;
    cout << "uciok" << endl;



    // UCI engine main loop:
    // - Wait for an input
    // - Read the input and check if it is a move or a command
    // - If invalid command, ignore
    // - If valid command, execute and return to previous prompt
    while (1)
    {
        infsearch = false;


        // Clear both the input and output buffer, to make sure the new input
        // isn't altered from something entered during the program's output
        cmd.clear();
        cout << endl;


        // read from the input
        std::getline(cin, cmd);


        // Process the 'input' here and execute, if it is a valid command.
        //
        // isready
        if (cmd == "isready")
        {
            cout << "readyok" << endl;
        }


        else if ((cmd == "d") || (cmd == "display") || (cmd == "show"))
        {
            board.display();
        }


        // go + parameters
        else if (cmd.find("go") != string::npos)
        {
            // reset time control
            resetTimeControl();
            
            // init parameters
            int depth = -1;

            string arg;
            if (cmd.length() > 2)
                arg = cmd.substr(3);
            else
                arg = "";

            // infinite search
            if ((arg == "") || (arg == "infinite"))
            {
                infsearch = true;
                board.searchDepth = SOLVE_MAX_DEPTH;

                comptime = SOLVE_MAX_TIME * 1000;
                board.maxTime = starttime + comptime + inc;
            }


            // parse the entire "go" argument
            // sample command: go wtime 199870 btime 147734 winc 5 binc 5
            size_t pos;

            // match UCI "wtime" parameter
            pos = arg.find("wtime");
            if (pos != string::npos)
            {
                if (!board.nextMove)
                    comptime = stoi(arg.substr(pos + 6));
                else
                    otime = stoi(arg.substr(pos + 6));
            }

            // match UCI "btime" parameter
            pos = arg.find("btime");
            if (pos != string::npos)
            {
                if (board.nextMove)
                    comptime = stoi(arg.substr(pos + 6));
                else
                    otime = stoi(arg.substr(pos + 6));
            }

            // match UCI "winc" parameter
            pos = arg.find("winc");
            if ((pos != string::npos) && !board.nextMove)
            {
                inc = stoi(arg.substr(pos + 5));
            }

            // match UCI "binc" parameter
            pos = arg.find("binc");
            if ((pos != string::npos) && board.nextMove)
            {
                inc = stoi(arg.substr(pos + 5));
            }

            // match UCI "movestogo" parameter
            pos = arg.find("movestogo");
            if (pos != string::npos)
            {
                movestogo = stoi(arg.substr(pos + 10));
            }

            // match UCI "movetime" parameter
            pos = arg.find("movetime");
            if (pos != string::npos)
            {
                board.maxTime = movetime = stoi(arg.substr(pos + 9));
            }

            // match UCI "depth" parameter
            pos = arg.find("depth");
            if (pos != string::npos)
            {
                // make time "infinite" and let depth stop the search
                infsearch = false;
                board.maxTime = comptime = SOLVE_MAX_TIME * 1000;

                depth = board.searchDepth = stoi(arg.substr(pos + 6));
                if (stoi(arg.substr(pos + 6)) < 4)
                    depth = board.searchDepth = 4;
            }

            // if move time is not available
            if (movetime != -1)
            {
                // set time equal to move time
                board.maxTime = comptime = movetime;

                // set moves to go to 1
                movestogo = 1;
            }

            // init start time
            board.timer.reset();
            starttime = board.timer.getms();

            // if time control is available
            if((comptime != -1) && !infsearch)
            {
                // set up timing
                comptime /= movestogo;
                
                // disable time buffer when time is almost up
                if (comptime > 1500) comptime -= 50;
                
                // init max. stop time
                board.maxTime = starttime + comptime + inc;
                
                // treat increment as seconds per move when time is almost up
                if (comptime < 1500 && inc && depth == SOLVE_MAX_DEPTH)
                    board.maxTime = starttime + inc - 50;
            }

            // if depth is not available
            if (depth == -1)
                board.searchDepth = depth = SOLVE_MAX_DEPTH;

            // print debug info
            cout << "time: " << comptime << "  start: " << starttime << "  stop: " << board.maxTime;
            cout << "  depth: " << depth << endl;

            // search position
            Move m = board.think();

            // print best move
            cout << "bestmove " << moveToUCI(m) << endl;
        }


        // ucinewgame
        else if (cmd == "ucinewgame")
        {
            istringstream ss2(STARTPOS);
            string arg1, arg2, arg3, arg4, arg5 = "0", arg6 = "1";
            ss2 >> arg1 >> arg2 >> arg3 >> arg4 >> arg5 >> arg6;

            if (!arg1.empty() && !arg2.empty() && !arg3.empty() &&
                !arg4.empty() && !arg5.empty() && !arg6.empty())
            {
                vector<char> args1(arg1.c_str(), arg1.c_str() + arg1.size() + 1);
                vector<char> args2(arg2.c_str(), arg2.c_str() + arg2.size() + 1);
                vector<char> args3(arg3.c_str(), arg3.c_str() + arg3.size() + 1);
                vector<char> args4(arg4.c_str(), arg4.c_str() + arg4.size() + 1);
                setupFen(args1.data(), args2.data(), args3.data(), args4.data(), atoi(arg5.c_str()), atoi(arg6.c_str()));
            }
        }


        // position startpos moves ...
        //
        // Set the starting position and parse moves given after the "moves"
        // argument. Iterate over the moves and apply them, in order, if
        // they are valid.
        else if (cmd.find("position startpos") != string::npos)
        {
            istringstream ss2(STARTPOS);
            string arg1, arg2, arg3, arg4, arg5 = "0", arg6 = "1";
            ss2 >> arg1 >> arg2 >> arg3 >> arg4 >> arg5 >> arg6;

            if (!arg1.empty() && !arg2.empty() && !arg3.empty() &&
                !arg4.empty() && !arg5.empty() && !arg6.empty())
            {
                vector<char> args1(arg1.c_str(), arg1.c_str() + arg1.size() + 1);
                vector<char> args2(arg2.c_str(), arg2.c_str() + arg2.size() + 1);
                vector<char> args3(arg3.c_str(), arg3.c_str() + arg3.size() + 1);
                vector<char> args4(arg4.c_str(), arg4.c_str() + arg4.size() + 1);
                setupFen(args1.data(), args2.data(), args3.data(), args4.data(), atoi(arg5.c_str()), atoi(arg6.c_str()));
            }

            size_t movesIndex = cmd.find("moves ");
            string moveList;
            if (movesIndex != string::npos)
            {
                moveList = cmd.substr(movesIndex + 6);
                istringstream iss(moveList);
                vector<string> inputMoves{istream_iterator<string>{iss},
                                          istream_iterator<string>{}};
                vector<string> validMoveList;

                // apply each move, if legal
                for (string i: inputMoves)
                {
                    string inputMove = "";

                    // create a vector with all valid moves in UCI format (e.g., "e2e4")
                    map<string, string> validMoves = getValidMoves();
                    for (map<string, string>::iterator it = validMoves.begin(); it != validMoves.end(); ++it)
                    {
                        validMoveList.push_back (it->second);
                    }

                    // if valid move, make the move
                    if (find(validMoveList.begin(), validMoveList.end(), i) != validMoveList.end())
                    {
                        Move myMove;

                        // generate the pseudo-legal move list
                        board.moveBufLen[0] = 0;
                        board.moveBufLen[1] = movegen(board.moveBufLen[0]);

                        // check to see if the user move is also found in the pseudo-legal move list
                        if (isValidTextMove(i, myMove))
                        {
                            makeMove(myMove);

                            // post-move check to see if we are leaving our king in check
                            if (isOtherKingAttacked())
                            {
                                unmakeMove(myMove);
                            }
                        }
                    }
                }
            }
        }

        // position fen ... moves ...
        //
        // Set the board position according to the given FEN string and parse
        // moves given after the "moves" argument. Iterate over the moves and
        // apply them, in order, if they are valid.
        else if (cmd.find("position fen") != string::npos)
        {
            string fenInput = cmd.substr(13);
            istringstream ss2(fenInput);
            string arg1, arg2, arg3, arg4, arg5 = "0", arg6 = "1";
            ss2 >> arg1 >> arg2 >> arg3 >> arg4 >> arg5 >> arg6;

            if (!arg1.empty() && !arg2.empty() && !arg3.empty() &&
                !arg4.empty() && !arg5.empty() && !arg6.empty())
            {
                vector<char> args1(arg1.c_str(), arg1.c_str() + arg1.size() + 1);
                vector<char> args2(arg2.c_str(), arg2.c_str() + arg2.size() + 1);
                vector<char> args3(arg3.c_str(), arg3.c_str() + arg3.size() + 1);
                vector<char> args4(arg4.c_str(), arg4.c_str() + arg4.size() + 1);
                setupFen(args1.data(), args2.data(), args3.data(), args4.data(), atoi(arg5.c_str()), atoi(arg6.c_str()));
            }

            size_t movesIndex = cmd.find("moves ");
            string moveList;
            if (movesIndex != string::npos)
            {
                moveList = cmd.substr(movesIndex + 6);
                istringstream iss(moveList);
                vector<string> inputMoves{istream_iterator<string>{iss},
                                          istream_iterator<string>{}};
                vector<string> validMoveList;

                // apply each move, if legal
                for (string i: inputMoves)
                {
                    string inputMove = "";

                    // create a vector with all valid moves in UCI format (e.g., "e2e4")
                    map<string, string> validMoves = getValidMoves();
                    for (map<string, string>::iterator it = validMoves.begin(); it != validMoves.end(); ++it)
                    {
                        validMoveList.push_back (it->second);
                    }

                    // if valid move, make the move
                    if (find(validMoveList.begin(), validMoveList.end(), i) != validMoveList.end())
                    {
                        Move myMove;

                        // generate the pseudo-legal move list
                        board.moveBufLen[0] = 0;
                        board.moveBufLen[1] = movegen(board.moveBufLen[0]);

                        // check to see if the user move is also found in the pseudo-legal move list
                        if (isValidTextMove(i, myMove))
                        {
                            makeMove(myMove);

                            // post-move check to see if we are leaving our king in check
                            if (isOtherKingAttacked())
                            {
                                unmakeMove(myMove);
                            }
                        }
                    }
                }
            }
        }


        // stop
        else if (cmd == "stop")
        {
            // stop engine from thinking
            board.timedout = true;
        }

        
        // quit
        else if (cmd == "quit") 
        {
            exit(0);
        }


        // uci
        else if (cmd == "uci")
        {
            UCI = true;
            beQuiet = true;

            cout << "id name " << PROGRAM_NAME << endl;
            cout << "id author " << PROGRAM_AUTHOR << endl;
            cout << "uciok" << endl;
        }


        // unknown command
        else
        {
            cout << "Unknown command: " << cmd << endl;
        }
    }

    return 0;
}




// resetTimeControl
void resetTimeControl()
{
    movestogo = 40;
    movetime = -1;
    comptime = -1;
    inc = 0;
    starttime = 0;
    infsearch = false;
}
