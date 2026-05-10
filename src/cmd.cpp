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



// @file cmd.cpp
//
// This file contains the functionality to execute all commands from the CLI
// interface of Chess0x.
#include <iostream>
#include <fstream>
#include <iomanip>
#include <unordered_map>
#include <stdio.h>
#include <sstream>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
#include "definitions.h"
#include "app.h"
#include "uci.h"
#include "functions.h"
#include "board.h"
#include "timer.h"
#include "move.h"
#include "search.h"
#include "cmd.h"
#include "extglobals.h"



using namespace std;



// Global variables used in this part of the program
int curPlayerType;
uint64_t msStart,msStop, moves;
Timer timer;



// initListOfCommands
//
// Initialize the list of commands supported by the application.
void initListOfCommands()
{
    listOfCommands.push_back("analyze");
    listOfCommands.push_back("auto");
    listOfCommands.push_back("back");
    listOfCommands.push_back("bench");
    listOfCommands.push_back("book");
    listOfCommands.push_back("cache");
    listOfCommands.push_back("depth");
    listOfCommands.push_back("display");
    listOfCommands.push_back("eval");
    listOfCommands.push_back("exit");
    listOfCommands.push_back("fen");
    listOfCommands.push_back("flip");
    listOfCommands.push_back("game");
    listOfCommands.push_back("go");
    listOfCommands.push_back("help");
    listOfCommands.push_back("history");
    listOfCommands.push_back("lmr");
    listOfCommands.push_back("load");
    listOfCommands.push_back("manual");
    listOfCommands.push_back("moves");
    listOfCommands.push_back("new");
    listOfCommands.push_back("q");
    listOfCommands.push_back("quiet");
    listOfCommands.push_back("quit");
    listOfCommands.push_back("remove");
    listOfCommands.push_back("recall");
    listOfCommands.push_back("resign");
    listOfCommands.push_back("restart");
    listOfCommands.push_back("save");
    listOfCommands.push_back("sd");
    listOfCommands.push_back("set");
    listOfCommands.push_back("setboard");
    listOfCommands.push_back("show");
    listOfCommands.push_back("solve");
    listOfCommands.push_back("st");
    listOfCommands.push_back("test");
    listOfCommands.push_back("think");
    listOfCommands.push_back("uci");
    listOfCommands.push_back("undo");
    listOfCommands.push_back("v");
    listOfCommands.push_back("ver");
    listOfCommands.push_back("version");
}



// exec()
//
// Execute a given command.
//
// exec() takes an input string (it can be anything) and tries to find a command
// and its arguments, and execute the command. This is how this function works:
//
// 1) convert everyting to lower case, since all commands and arguments are
//    case insensitive
// 2) take only the first and second 'words' from the input string, being the
//    first one the command (cmd) and the second one the argument (arg)
// 3) try to match the command (cmd) in a if-else fashion and execute the given
//    command; apply the argument (arg)  if any
void exec(string input)
{
    string cmd;
    string arg, arg2, arg3, arg4, arg5 = "0", arg6 = "1";


    // divide the command into arguments
    istringstream ss(input);
    ss >> cmd >> arg >> arg2 >> arg3 >> arg4 >> arg5 >> arg6;


    // 'cmd' is case insensitive
    for (unsigned int i = 0; i < cmd.length(); i++)
        cmd[i] = tolower(cmd[i]);


    // Run the command (cmd) through a list of supported commands in an if-else
    // fashion. If the command is found in the list, execute the code associated
    // and use the argument as a parameter, otherwise return without doing
    // anything.
    //
    // See the list of supported commmands below:


    // auto: make the machine play both sides
    if (cmd == "auto")
    {
        wPlayer = PLAYER_TYPE_COMPUTER;
        bPlayer = PLAYER_TYPE_COMPUTER;
        curPlayerType = PLAYER_TYPE_COMPUTER;
        playMode = CPU_CPU;
    }


    // book: turn on or off openings book
    else if (cmd == "book")
    {
        // turn default book on
        if (arg == "on")
        {
            useBook = true;
        }

        // turn book off
        else if (arg == "off")
        {
            useBook = false;
        }

        // show current use of book
        else if (useBook)
            cout << "Opening book is enabled." << endl;
        else
            cout << "Opening book is disabled." << endl;
    }



    // cache: Enable/disable/show cache usage.
    else if (cmd == "cache")
    {
        // turn cache on
        if ((arg == "on") || (arg == "true"))
            useCache = true;

        // turn cache off
        else if ((arg == "off") || (arg == "false"))
        {
            cache.clear();
            useCache = false;
        }

        // show current cache status
        if (useCache)
        {
            char measure = '\0';
            float size = 0;

            cout << "Cache is enabled." << endl;

            // check the current cache size (usage)
            size = cache.size();
            if (size > 1024)
            {
                measure = 'K';
                size /= 1024;
            }
            if (size > 1024)
            {
                measure = 'M';
                size /= 1024;
            }
            if (size > 1024)
            {
                measure = 'G';
                size /= 1024;
            }
            cout << "Current cache size: " << fixed << setprecision(2);
            cout << size << " ";
            cout << measure << "bytes (";
            cout << cache.positions() << " positions)" << endl;
        }
        else
        {
            cout << "Cache is disabled." << endl;
        }
    }



    // depth: change hsearch depth
    else if ((cmd == "depth") || (cmd == "sd"))
    {
        int d;
        d = atoi(arg.c_str());
        if ((d > 3) &&  (d < SOLVE_MAX_DEPTH))
            board.searchDepth = d;

        cout << "Search depth: " << board.searchDepth << endl;
    }



    // eval: display current board's evaluation
    else if (cmd == "eval")
    {
        displayEval();
    }


    // lmr
    //
    // Enable/disable late-move reductions (LMR) optimization
    else if (cmd == "lmr")
    {
        if ((arg == "on") || (arg == "true"))
            LMR = true;
        else if ((arg == "off") || (arg == "false"))
            LMR = false;

        if (LMR)
            cout << "LMR optimizations are enabled." << endl;
        else
            cout << "LMR optimizations are disabled." << endl;
    }



    // load: load position from a file
    else if (cmd == "load")
    {
        // force the user to provide a file
        if (arg.empty())
        {
            cerr << "Cannot load file!" << endl;
            return;
        }

        // loading a position from a file disables book usage, and sets the game
        // to manual mode
        wPlayer = PLAYER_TYPE_HUMAN;
        bPlayer = PLAYER_TYPE_HUMAN;
        playMode = HUMAN_HUMAN;
        useBook = false;

        // read the FEN string and update the board
        vector<char> char_array(arg.begin(), arg.end());
        char_array.push_back(0);
        readFen(&char_array[0]);
    }



    // fen: prints the current board's FEN string
    else if (cmd == "fen")
    {
        board.display();
        cout << board.toFEN() << endl;
    }



    // flip: flip the board when displaying
    else if (cmd == "flip")
    {
        board.flipBoard = !board.flipBoard;
        board.display();
    }



    // go: force the computer to move now
    else if (cmd == "go")
    {
        if (board.nextMove)
        {
            wPlayer = PLAYER_TYPE_HUMAN;
            bPlayer = PLAYER_TYPE_COMPUTER;
            curPlayerType = bPlayer;
            playMode = HUMAN_CPU;
        }
        else
        {
            wPlayer = PLAYER_TYPE_COMPUTER;
            bPlayer = PLAYER_TYPE_HUMAN;
            curPlayerType = wPlayer;
            playMode = HUMAN_CPU;
        }
    }


    // help: print help about commands
    else if (cmd == "help")
    {
        displayHelp(arg);
    }



    // history: display game history
    else if ((cmd == "history") || (cmd == "game"))
    {
        displayGame();
    }



    // manual: human vs human
    else if (cmd == "manual")
    {
        wPlayer = PLAYER_TYPE_HUMAN;
        bPlayer = PLAYER_TYPE_HUMAN;
        playMode = HUMAN_HUMAN;
        cout << "Both sides are now played by the user." << endl;
    }



    // moves: show the list of valid moves
    else if (cmd == "moves")
    {
        unsigned int i = 0, number = 0;
        char sanMove[12];

        board.moveBufLen[0] = 0;
        board.moveBufLen[1] = movegen(board.moveBufLen[0]);
        cout << endl << "moves from this position:" << endl;

        for (i = board.moveBufLen[0]; i < board.moveBufLen[1]; i++)
        {
            makeMove(board.moveBuffer[i]);
            if (isOtherKingAttacked())
            {
                unmakeMove(board.moveBuffer[i]);
            }
            else
            {
                unmakeMove(board.moveBuffer[i]);
                toSan(board.moveBuffer[i], sanMove);
                cout << ++number << ". " << sanMove << endl;
            }
        }
    }



    // new | restart: new game / restart
    else if ((cmd == "new") || (cmd == "restart"))
    {
        cout << "Starting a new game..." << endl;

        // restart the game
        wPlayer = PLAYER_TYPE_HUMAN;
        bPlayer = PLAYER_TYPE_COMPUTER;
        curPlayerType = wPlayer;
        playMode = HUMAN_CPU;
        cursor = 0;
        numberOfMove = 1;
        gameEnd = END_TYPE_NOEND;

        dataInit();
        board.init();
        cache.clear();
        learned.clear();
        ML.clear();


        // Load learned positions from the past
        string fenStr, moveStr, scoreStr;
        ifstream learnFile("learn.db");
        float MLentries = 0;
        while (true)
        {
            getline(learnFile, fenStr);
            getline(learnFile, moveStr);
            getline(learnFile, scoreStr);

            if (fenStr == "")
                break;

            tuple<string, string, float> winingMove(fenStr, moveStr, atof(scoreStr.c_str()));
            ML.push_back(winingMove);

            MLentries++;
        }
        learnFile.close();
        if (MLentries > 0)
            cout << endl << "Learning from " << MLentries << " saved positions..  done." << endl << endl;


        // enable book by default
        useBook = true;
    }



    // test | bench: perform test or benchmark
    else if ((cmd == "test") || (cmd == "bench"))
    {
        // disable book, cache and verbosity
        bool wasUsingCache   = useCache;
        bool wasUsingBook    = useBook;
        bool wasQuiet        = beQuiet;
        useCache = false;
        useBook  = false;
        beQuiet  = true;


        // test raw moves (make / unmake)
        if (arg == "moves")
        {
            cout << "Testing move performance: " << flush;

            board.moveBufLen[0] = 0;
            board.moveBufLen[1] = movegen(board.moveBufLen[0]);

            // prepare the clock to measure the time of the test
            clock_t start, end;
            float delta;
            long iterations = MOVES_TEST_ITER;
            start = clock();
            for (long i = 0; i < iterations; i++)
            {
                makeMove(board.moveBuffer[0]);
                unmakeMove(board.moveBuffer[0]);
            }
            end = clock();
            delta = (end - start) / (CLOCKS_PER_SEC / 1000);

            cout << iterations/1000000 << " million moves in ";
            cout << fixed << setprecision(2) << delta/1000 << " seconds; speed = ";
            cout << fixed << setprecision(2) << (iterations/1000000)/(delta/1000);
            cout << " Mmps." << endl;
        }

        else if (arg == "perft")
        {
            clock_t start, end;
            uint64_t perftMoves;

            cout << "Testing Perft() function:" << endl;
            cout << "Ply\t  Moves\t     Time\t Moves/s" << endl;
            cout << flush;

            for (int z = 0; z <= PERFT_DEPTH_LIMIT; z++)
            {
                board.moveBufLen[0] = 0;

                start = clock();
                perftMoves = perft(z, z);
                end = clock();

                float sec = (end - start) / (CLOCKS_PER_SEC / 1000);
                float speed = perftMoves / sec;

                // display test depth, moves, time and moves per second
                cout.fill(' ');
                cout << setw(3) << z << "   " << setw(9) << perftMoves << "\t   " << setw(5) << fixed << setprecision(2) << sec / 1000 << "s\t";
                if (isinf(speed))
                    cout << "  -" << endl;
                else
                    cout << fixed << setw(4) << setprecision(0) << speed << "K/s" << endl;
                cout << flush;
            }

            cout << endl;
        }

        else
        {
            cout << "Testing node search speed: " << endl << endl << flush;

            // store current settings to restore them after the test
            int cur_depth = board.searchDepth;
            uint64_t prevTPM = board.maxTime;


            // change the depth to make sure the test runs in a controlled environment
            board.searchDepth = NODES_TEST_DEPTH;
            board.maxTime = NODES_TEST_TIME * 1000;


            // perform the test and measure the time
            clock_t start;
            clock_t end;
            start = clock();
            board.think();
            end = clock();


            // estimate nodes per second
            double ms = (end - start) / (CLOCKS_PER_SEC / 1000);
            cout << endl << board.nodes << " nodes evaluated in " << fixed << setprecision(2) <<  (ms / 1000) << "s ";
            cout << "(" << fixed << setprecision(2) << (board.nodes / ms);
            cout << " kN/s)." << endl << flush;

            // restore settings after the test
            board.maxTime = prevTPM;
            board.searchDepth = cur_depth;
        }


        // re-enable book, cache and verbosity
        useCache = wasUsingCache;
        useBook  = wasUsingBook;
        beQuiet  = wasQuiet;
    }



    // think: change AI thinking time limit
    else if ((cmd == "think") || (cmd == "st"))
    {
        int t;

        if (arg != "")
        {
            t = atoi(arg.c_str());

            if (t < 0)
                t = 0;

            board.maxTime = t * 1000;
        }

        cout << "Max. time per move: " << (board.maxTime / 1000) << "s" << endl;
    }



    // recall: list all learned moves for the current position
    else if (cmd == "recall")
    {
        vector<tuple<string, string, float>> v;

        board.display();

        for (tuple<string, string, float> &tup : ML)
        {
            if (get<0>(tup) == board.toFEN())
            {
                v.push_back(make_tuple(board.toFEN(), get<1>(tup), get<2>(tup)));
            }
        }
        sort(v.begin(), v.end(), sortByScore);

        // try to recall the current position, for memorized moves
        cout << "List of memorized moves:" << endl;
        if (v.size() <= 0)
        {
            cout << "No moves found!" << endl;
        }
        else
        {
            for (auto it = v.begin(); it != v.end(); ++it)
            {
                int index = distance(v.begin(), it);
                cout << get<1>(v[index]) << "  " << get<2>(v[index]) << endl;
            }
        }
    }



    // resign: resign for current player
    else if (cmd == "resign")
    {
        gameEnd = END_TYPE_RESIGN;
    }



    // save: save a position to a disk file
    else if (cmd == "save")
    {
        // open the disk file for loading or return on fail
        string filename = arg.c_str();
        filename += ".c0";
        ofstream fout(filename);
        if (!fout.is_open())
        {
            cout << "Error saving position to '" << filename << "'." << endl;
        }
        else
        { 
            // if the file was successfully opened, save the position
            fout << "[FEN ";
            fout << board.toFEN();
            fout << "]";
            fout.close();

            // tell the user that the saving was correct
            cout << "Current board position saved to file '" << filename;
            cout << "'." << endl;
        }
    }


    // setboard: load position from a FEN string
    //else if ((cmd == "set") || (cmd == "setboard"))
    else if ((cmd == "set") || (cmd == "setboard"))
    {
        // loading a position from a file disables book usage, and sets the game
        // to manual mode
        wPlayer = PLAYER_TYPE_HUMAN;
        bPlayer = PLAYER_TYPE_HUMAN;
        playMode = HUMAN_HUMAN;
        useBook = false;


        // check that the FEN string has all 6 components
        if (arg.empty() || arg2.empty() || arg3.empty() ||
            arg4.empty() || arg5.empty() || arg6.empty())
        {
            cerr << "Cannot load position: invalid FEN string!" << endl;
            return;
        }


        // read the FEN string and update the board
        vector<char> args1(arg.c_str(), arg.c_str() + arg.size() + 1);
        vector<char> args2(arg2.c_str(), arg2.c_str() + arg2.size() + 1);
        vector<char> args3(arg3.c_str(), arg3.c_str() + arg3.size() + 1);
        vector<char> args4(arg4.c_str(), arg4.c_str() + arg4.size() + 1);
        setupFen(args1.data(), args2.data(), args3.data(), args4.data(), atoi(arg5.c_str()), atoi(arg6.c_str()));
        board.display();
    }


    // show | display: show current board
    else if ((cmd == "show") || (cmd == "display"))
    {
        board.display();
    }



    // solve: try to find a checkmate for the given position
    else if ((cmd == "analyze") || (cmd == "solve"))
    {
        // disable book moves for infinite analysis
        useBook = false;

        board.searchDepth = SOLVE_MAX_DEPTH;
        board.maxTime = SOLVE_MAX_TIME * 1000;

        // force computer to start thinking
        if (board.nextMove)
        {
            wPlayer = PLAYER_TYPE_HUMAN;
            bPlayer = PLAYER_TYPE_COMPUTER;
            curPlayerType = bPlayer;
            playMode = HUMAN_CPU;
        }
        else
        {
            wPlayer = PLAYER_TYPE_COMPUTER;
            bPlayer = PLAYER_TYPE_HUMAN;
            curPlayerType = wPlayer;
            playMode = HUMAN_CPU;
        }
    }



    // back | undo: go back one move
    else if ((cmd == "back") || (cmd == "undo"))
    {
        if (board.endOfGame)
        {
            unmakeMove(board.gameLine[--board.endOfGame].move);
            board.endOfSearch = board.endOfGame;

            wPlayer = PLAYER_TYPE_HUMAN;
            bPlayer = PLAYER_TYPE_HUMAN;
            playMode = HUMAN_HUMAN;

            cursor--;
            numberOfMove = (cursor / 2) + 1;
        }
        else
        {
            cout << "Can't undo move. Already at the start of the game!" << endl;
        }

        board.display();
    }



    // uci: enter UCI mode
    else if (cmd == "uci")
    {
        beQuiet = true;
        uciLoop();
    }



    // remove: go back two moves 
    else if (cmd == "remove")
    {
        if (board.endOfGame)
        {
            unmakeMove(board.gameLine[--board.endOfGame].move);
            board.endOfSearch = board.endOfGame;
            cursor--;
            numberOfMove = (cursor / 2) + 1;
        }
        else
            cout << "Can't remove last moves. Already at the start of the game!" << endl;

        if (board.endOfGame)
        {
            unmakeMove(board.gameLine[--board.endOfGame].move);
            board.endOfSearch = board.endOfGame;
            cursor--;
            numberOfMove = (cursor / 2) + 1;
        }
        else
            cout << "Can't remove last moves. Already at the start of the game!" << endl;

        board.display();
    }



    // version: show application version number
    else if ((cmd == "version") || (cmd == "ver") || (cmd == "v"))
    {
        cout << PROGRAM_NAME << " (version " << PROGRAM_VERSION << ")" << endl;
        cout << PROGRAM_AUTHOR << endl;
        cout << PROGRAM_WEB << endl;
    }



    // silent | quiet: turn dispalying analysis on or off
    else if ((cmd == "quiet") || (cmd == "silent"))
    {
        if ((arg == "on") || (arg == "true"))
            beQuiet = true;

        else if ((arg == "off") || (arg == "false"))
            beQuiet = false;

        else if (beQuiet)
            cout << "Quiet mode is enabled." << endl;
        else
            cout << "Quiet mode is disabled." << endl;
    }



    // verbose: turn dispalying analysis on or off
    else if (cmd == "verbose")
    {
        if ((arg == "on") || (arg == "true"))
            beQuiet = false;

        else if ((arg == "off") || (arg == "false"))
            beQuiet = true;

        else if (beQuiet)
            cout << "Quiet mode is enabled." << endl;
        else
            cout << "Quiet mode is disabled." << endl;
    }



    // exit | quit: terminate the app
    else if ((cmd == "quit") || (cmd == "exit") || (cmd == "q"))
    {
        terminateApp();
    }
}



// displayHelp()
//
// Display help information, either general or about a concrete command.
void displayHelp(string which)
{
    // no specific command
    if (which == "")
    {
        cout << "List of commands: (help COMMAND to get more help)" << endl;
        cout << "analyze  auto  book  cache  depth  eval  fen  flip" << endl;
        cout << "game  go  help  history  lmr  load  manual  new  null" << endl;
        cout << "pass  quiet  quit  recall  remove  resign  restart" << endl;
        cout << "save  sd  set  setboard  show  silent  solve  st  test" << endl;
        cout << "think  uci  verbose  undo  version" << endl;
        return;
    }


    // help auto
    else if (which == "auto")
    {
        cout << "auto" << endl;
        cout << " Let the computer play both sides (black and white). This can";
        cout << endl;
        cout << " be the equivalent to 'solve' in other computer chess";
        cout << endl;
        cout << " programs, because the computer plays both sides and finishes";
        cout << endl;
        cout << " the match by itself." << endl;
    }


    // help book
    else if (which == "book")
    {
        cout << "book [on | off]" << endl;
        cout << " Enable or disable the moves from the book for the computer.";
        cout << endl;
    }


    // help cache
    else if (which == "cache")
    {
        cout << "cache [on | off]" << endl;
        cout << " Let the computer use the transposition tables to find" << endl;
        cout << " previously searched positions faster. This typically" << endl;
        cout << " makes the engine more powerful in middle and end-game." << endl;
        cout << " Please note that using transposition tables can take" << endl;
        cout << " a few hundreds of Megabytes for a ~1h game." << endl;
    }



    // help depth | sd
    else if ((which == "depth") || (which == "sd"))
    {
        cout << "depth | sd [N]" << endl;
        cout << " Set the search depth of the computer to N-plies" << endl;
        cout << " (half-moves). The depth must be a minimum of 1," << endl;
        cout << " and there is no maximum limit. However, consider" << endl;
        cout << " that a depth higher than 7 will result in a very" << endl;
        cout << " long time for obtaining a move from the computer." << endl;
        cout << " If no depth is given, then the application tells" << endl;
        cout << " what is the current search depth." << endl;
    }


    // help fen
    else if (which == "fen")
    {
        cout << "fen" << endl;
        cout << " Print out the current board's FEN string representing" << endl;
        cout << " the game position." << endl;

    }


    // help flip
    else if (which == "flip")
    {
        cout << "flip" << endl;
        cout << " Flip the board so that when it is displayed, white" << endl;
        cout << " and black sides are flipped." << endl;

    }


    // help show
    else if (which == "show")
    {
        cout << "show" << endl;
        cout << " Display an ASCII representation of the current game's";
        cout << endl;
        cout << " board. The white pieces are represented with capital";
        cout << endl;
        cout << " letters, whereas the black pieces are represented";
        cout << endl;
        cout << " with small letters next to an asterisk." << endl;
    }


    // help eval
    else if (which == "eval")
    {
        cout << "eval" << endl;
        cout << " Give an absolut heuristic evaluation of the current board.";
        cout << endl;
        cout << " Please note that this command will make use of the current";
        cout << endl;
        cout << " AI engine in use. Thus, depending on the engine, the";
        cout << endl;
        cout << " heuristic evaluation may differ quite much." << endl;
    }


    // help go
    else if (which == "go")
    {
        cout << "go" << endl;
        cout << " Tell the machine to take the control on the current" << endl;
        cout << " turn and play for the player whose turn is the" << endl;
        cout << " the current one. After this command, the machine will";
        cout << endl;
        cout << " always control the side whose control has been taken.";
        cout  << endl;
    }


    // help help
    else if (which == "help")
    {
        cout << "help" << endl;
        cout << " Show the general help." << endl;
    }


    // help history
    else if (which == "history")
    {
        cout << "history" << endl;
        cout << " Display the history (sequence of moves) of the current";
        cout << endl;
        cout << " game." << endl;
    }


    // help load
    else if (which == "load")
    {
        cout << "load FILENAME" << endl;
        cout << " Load a board position from a file. Please note that";
        cout << endl;
        cout << " this command loads a position, not a match (do not confuse";
        cout << endl;
        cout << " with the PGN format). If the file is not valid, or the";
        cout << endl;
        cout << " position in it is not valid, the program will not load it";
        cout << endl;
        cout << " and return to the previously working board position.";
        cout << endl;
        cout << endl;
        cout << " As a note, these board positions (files) are usually saved";
        cout << endl;
        cout << " with the command 'save', although you could manually create";
        cout << endl;
        cout << " and edit your own board position file." << endl;
    }


    // help manual
    else if (which == "manual")
    {
        cout << "manual" << endl;
        cout << " Set both players to be played by human input." << endl;
    }


    // help new/restart
    else if ((which == "new") || (which == "restart"))
    {
        cout << "new | restart" << endl;
        cout << " Start a new game." << endl;
    }



    // help null/pass
    else if ((which == "null") || (which == "pass"))
    {
        cout << "null | pass" << endl;
        cout << " Make a null move, which passes the turn to the other side";
        cout << " without performing any actual move." << endl;
    }


    // help recall
    else if (which == "recall")
    {
        cout << "recall" << endl;
        cout << " Try to recall the game's current position and all";
        cout << endl;
        cout << " memorized moves with scores." << endl;
    }


    // help resign
    else if (which == "resign")
    {
        cout << "resign" << endl;
        cout << " Resign and let your opponent win immediately. The game";
        cout << endl;
        cout << " is then finished at this point." << endl;
    }


    // help save
    else if (which == "save")
    {
        cout << "save FILENAME" << endl;
        cout << " Save a board position to a file. Please note that";
        cout << endl;
        cout << " this command saves a position using FEN notation, not an";
        cout << endl;
        cout << " entire match (do not confuse with the PGN format).";
        cout << endl;
        cout << endl;
        cout << " As a note, these board positions (files) are usually loaded";
        cout << endl;
        cout << " with the command 'load', although you could manually create";
        cout << endl;
        cout << " and edit your own board position using the 'edit' command.";
        cout << endl;
    }


    // help set | setboard
    else if ((which == "set") || (which == "setboard"))
    {
        cout << "set|setboard FEN" << endl;
        cout << " Load a board position from a given FEN string. If the";
        cout << endl;
        cout << " position is not valid, the program will not load it";
        cout << endl;
        cout << " and return to the previously working board position.";
        cout << endl;
    }


    // help solve | analyze
    else if ((which == "analyze") || (which == "solve"))
    {
        cout << "analyze | solve" << endl;
        cout << " Start thinking how to solve the current board. This mode";
        cout << endl;
        cout << " puts the computer to play both sides and makes it try to";
        cout << endl;
        cout << " solve the current situation on the board without a depth.";
        cout << " limit." << endl;
    }


    // help test
    else if (which == "test")
    {
        cout << "test [moves | nodes | perft]" << endl;
        cout << " Test either the number of moves that can be done and undone";
        cout << endl;
        cout << " per second (without calling evaluation), the number of nodes";
        cout << endl;
        cout << " that can be evaluated per second, and perform a Perft()";
        cout << endl;
        cout << " test which is a standard moves test for computer chess";
        cout << endl;
        cout << " programs to test that the move generator works correctly.";
        cout << endl;
        cout << " If no argument is given, all three tests are performed.";
        cout << endl;
        cout << " Please note that the efficiency of the tests will depend";
        cout << endl;
        cout << " on the situation on the board." << endl;
    }



    // help st | think (time per move)
    else if ((which == "think") || (which == "st"))
    {
        cout << "st | think [N]" << endl;
        cout << " Set the maximum amount of time the engine can think" << endl;
        cout << " before performing a move. The time must be a minimum of" << endl;
        cout << " 1 (seconds) and there is no maximum limit. Setting the" << endl;
        cout << " thinking time to 0 allows the engine to think indefinitely " << endl;
        cout << " (or until it hits the depth limit, if there is any)." << endl;
        cout << " Using this command disables the game clock (time)." << endl;
    }



    // help uci
    else if (which == "uci")
    {
        cout << "uci" << endl;
        cout << " Start UCI engine." << endl;
    }


    // help undo
    else if ((which == "undo") || (which == "back"))
    {
        cout << "undo | back" << endl;
        cout << " Take back a move from the game." << endl;
    }



    // help version
    else if (which == "version")
    {
        cout << "version" << endl;
        cout << " Show the application version number, author and website.";
        cout << endl;
    }



    // help quit
    else if (which == "quit")
    {
        cout << "quit | exit" << endl;
        cout << " Quit the application." << endl;
    }



    // help quiet | silent
    else if ((which == "quiet") || (which == "silent"))
    {
        cout << "quiet | silent [on | off]" << endl;
        cout << " Turn off displaying the analysis while the computer" << endl;
        cout << " is thinking." << endl;
    }


    // help verbose
    else if (which == "verbose")
    {
        cout << "verbose [on | off]" << endl;
        cout << " Turn on displaying the analysis while the computer" << endl;
        cout << " is thinking." << endl;
    }


    // help unknown
    else
    {
        cout << which << endl;
        cout << " No help available for '" << which << "'" << endl;
    }
}



// displayEval()
//
// Display the current heuristic evaluation according to the board.
void displayEval()
{
    float evaluationValue = 0;
    evaluationValue = board.eval() / 100.00f;

    cout << "Evaluation: " << showpos << setw(4) << fixed << setprecision(2) << evaluationValue << endl << "(m: " << (board.Material / 100.00f) << ")" << endl;
    cout << noshowpos;
}
