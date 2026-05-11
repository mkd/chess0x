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



// @file main.cpp
//
// This file contains the code for creating and starting the actual
// application. The application interacts with the user to accept input
// (commands and moves), and performs an action based on the given input.
//
// The CLI mode makes the program run on the system command line and interact
// with the user by accepting text-based commands and moves.
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <map>
#include <set>
#include <iterator>
#include <algorithm>
#include <string>
#include <cstring>
#include <cctype>

#include "app.h"
#include "board.h"
#include "move.h"
#include "book.h"
#include "functions.h"
#include "globals.h"
#include "cmd.h"



using namespace std;



// Initialization
//
// Here, there is a number of variables that need to be defined and initialized
// when the app starts for the first time. These variables include game status,
// user messages, and editable options such as the use of openings book, search
// cache, etc.


// numberOfMove holds the move number in the current game, which is what is
// shown to the user on the CLI prompt (e.g., Black (12) means 'Move number 12,
// black to move'.
unsigned numberOfMove = 1;


// cursor holds the number of ply in the current game. This number is usually
// double than numberOfMove. For example, cursor = 6 means 'move 3 black to
// move'.
unsigned cursor = 0;


// playMode, wPlayer and bPlayer define the mode in which the application is
// working and which color is set to move. The three different game modes are:
//  - HUMAN_HUMAN  -->  both sides are controlled by human input
//  - HUMAN_CPU    -->  one side is controlled by human input, the other one is
//                      run by the computer
//  - CPU_CPU      -->  both sides are controlled by the computer (note: the
//                      game is played automatically on both sides by the
//                      computer, so the game cannot be stopped until its end)
int playMode = HUMAN_CPU;
int wPlayer = PLAYER_TYPE_HUMAN;
int bPlayer = PLAYER_TYPE_COMPUTER;


// listOfCommands holds a list of valid commands that can be fed to the computer
// through the command line. The complete list of commands is defined in the
// file cmd.cpp. Entering a command that is not listed in listOfCommands will
// raise an error.
vector<string> listOfCommands;


// useBook is a user-editable option to select whether opening books can be used
// by the computer or not. If the opening book is not in use, the computer will
// always search for a move.
bool useBook = true;


// sanMove holds a 'SAN' notation of the move selected. Internally, moves use a
// more efficient representation, i.e., origin-destination. However, SAN will
// have a more user-friendly version of the move, which can be shown on the user
// interface. For example Nf3, Bb5+, Qxd4.
char sanMove[12];


// validMoves holds a list of all the valid moves at the current time in the
// game. This is used to see whether there are no valid moves and finding end
// situations.
map<string, string> validMoves;


// i, j and number are temporary variables used to iterate over different moves
// and parts of the game.
int i, j, number;


// userinput holds the string entered by the user. This string is analyzed by
// the application to figure out whether it is a valid move or command, and act
// upon it.
char userinput[80];


// userMove holds a translation of a valid move entered by the user.
string userMove = "";


// useCache is a user-editable option to select whether the engine will save
// transpopsition tables for all searched positions. Cache significantly speeds
// up the search algorithm on positions that have previously appeared.
//
// cache is an object that holds all transposition tables and manages their
// storage, access and all the information related.
//
// Note: due to being very unstable at this point, Cache is disabled by default.
bool useCache = false;
Cache cache;


// LMR
bool LMR = true;


// beQuiet tells whether the engine should show its analysis or not,
// while thinking.
bool beQuiet = false;


// gameEnd holds the type of ending, when the game comes to an end. If the game
// end is END_TYPE_NOEND, the application continues asking the user for input
// and going through the main loop.
EndType gameEnd = END_TYPE_NOEND;



// MLhit calculates the hit-ratio of learned positions used in a game.
unsigned int MLhit = 0;


// UCI settings
bool UCI = false;




// main
//
// Start the whole application. This includes setting up all variables and
// entering the main CLI loop.
int main(void)
{
    // Prompt the user for input from the command line
    cout << "Welcome to " << PROGRAM_NAME << "!" << endl;


    // Clear all the variables necessary for starting a new game
    string input = "";
    curPlayerType = wPlayer;
    Move myMove;
    string moveIsFromBook = "";
    clock_t start, end;
    InputType itype;
    string bookSequence = "";
    string prevFEN = "";


    // Initialize the board, the list of commands and the openings book
    dataInit();
    board.init();
    initListOfCommands();
    initBook();
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


    // Application's main loop:
    // - Prompt the user for an input (move or command)
    // - Read the input and check if it is a move or a command
    // - If invalid command or move, show error and return to previous prompt
    // - If valid command, execute and return to previous prompt
    // - If valid move, perform the move
    //
    // This loop is exited by entering Ctrl+D or the commands "quit" or "exit",
    // which call terminateApp().
    while (1)
    {
        // Check for game end (e.g., resign)
        if (gameEnd)
            dealEnd();


        // Clear both the input and output buffer, to make sure the new input
        // isn't altered from something entered during the program's output
        cout.flush();
        input = "";


        // Show the prompt and ask the user for an input (move or command)
        prompt(numberOfMove);


        // Current player is human, ask for input
        if (curPlayerType == PLAYER_TYPE_HUMAN)
        {
            input = getInput();
        }

        // Current player is the computer, find a move
        else if (curPlayerType == PLAYER_TYPE_COMPUTER)
        {
            // first, we try to get a reply from the openings book
            moveIsFromBook = "";
            if (useBook)
            {
                bookSequence = getGameSequence();
                if (bookSequence == "")
                    bookSequence = "%";
                input = getReplyTo(bookSequence);
            }


            // second, we try to get a reply using machine learning (ML)
            if (input.empty())
            {
                input = getMLreply();

                if (!input.empty())
                {
                    MLhit++;
                    moveIsFromBook = " [learned] ";
                }
            }


            // no move found from the book nor from learned positions, enter search
            if (input.empty())
            {
                start = clock();
                cout << endl << "Thinking..." << endl << endl;

                // search the move
                myMove = board.think();

                // set the input from computer to the SAN move
                toSan(myMove, sanMove);
                input = string(sanMove);

                end   = clock();
            }

            // if the move was form the book, show it with a (%) symbol
            else if (useBook)
            {
                if (moveIsFromBook != " [learned] ")
                    moveIsFromBook = " [book] ";
            }
        }


        // handle checks and mates notation for the moves
        string addSymbol = "";
        size_t pos = input.rfind("#");
        if (pos != std::string::npos)
            addSymbol = "#";
        pos = input.rfind("+");
        if (pos != std::string::npos)
            addSymbol = "+";
        input.erase(std::remove(input.begin(), input.end(), '+'), input.end());
        input.erase(std::remove(input.begin(), input.end(), '#'), input.end());


        // check what type of input was entered: move, null move, command, etc.
        itype = getInputType(input);


        // If the input was a move (and the game is still running), make the
        // move -- thus updating the board and other variables --, display the
        // updated board, change side to move and go to the beginning of the
        // loop again.
        if (itype == INPUT_TYPE_MOVE)
        {
            // make a list of current valid moves
            validMoves = getValidMoves();


            // if 'move' is a null move ('pass' or 'null'), simply change the
            // sides and advance the cursor
            if ((input == "pass") || (input == "null"))
            {
                cout << "Null move baby!" << endl;

                myMove.moveInt = 0;
                makeMove(myMove);
                board.endOfGame++;
                board.endOfSearch = board.endOfGame;
                board.display();
                changeSide();
                continue;
            }


            // if valid move, make the move
            auto t = validMoves.find(input);
            if (t != validMoves.end())
            {
                userMove = t->second;
                sscanf(userMove.c_str(), "%s", userinput);

                // generate the pseudo-legal move list
                board.moveBufLen[0] = 0;
                board.moveBufLen[1] = movegen(board.moveBufLen[0]);

                // check to see if the user move is also found in the pseudo-legal move list
                prevFEN = "";
                string userinput_str(userinput);
                if (isValidTextMove(userinput_str, myMove))
                {
                    prevFEN = board.toFEN();

                    makeMove(myMove);

                    // post-move check to see if we are leaving our king in check
                    if (isOtherKingAttacked())
                    {
                        unmakeMove(myMove);
                        cout << "    invalid move, leaving king in check: " << userinput << endl;
                        prevFEN = "";
                    }
                    else
                    {
                        board.endOfGame++;
                        board.endOfSearch = board.endOfGame;
                    }
                }
                else
                {
                    cout << "    move is invalid or not recognized: " << userinput << endl;
                }
            }

            // not a valid move
            else
            {
                cout << "Invalid move '" << input << "'" << endl;
                continue;
            }


            if (curPlayerType == PLAYER_TYPE_COMPUTER)
            {
                // measure how long it takes to think the move
                float timeUsed = (end - start) / (CLOCKS_PER_SEC / 1000);
                if (timeUsed > THINK_MAX_TIME)
                    timeUsed = 0;


                // display the move chosen by the computer and other info
                cout << endl << endl << "\a\033[1mMy move: ";
                if (board.nextMove)
                    cout << to_string(numberOfMove) << ". ";
                else
                    cout << to_string(numberOfMove) << "... ";
                cout << "\033[96m";
                input += addSymbol;
                cout << input;


                // show if the move is from the book
                cout << moveIsFromBook;


                // show how much time was used to think
                cout.fill('0');
                cout << "\033[0m (time: ";
                cout << setprecision(2) << timeUsed / 1000.00f << "s)";

                cout.fill(' ');

                // add move to ML, if it doesn't exist, so it can be learned
                // after the game is completed
                learned.push_back(make_tuple(prevFEN, input, 0));
            }


            // show the board and change side to move
            board.display();
            changeSide();


            // check for the end of the game
            Move tmpMove;
            if (board.isEndOfgame(number, tmpMove))
                dealEnd();
        }


        // if the input was a command, execute it and prompt again.
        else if (itype == INPUT_TYPE_CMD)
        {
            exec(input);
        }


        // if the input is not a command nor a move, display an error and prompt
        // again.
        else
        {
            cerr << "Unknown command or move '" << input << "'." << endl << endl;
        }
    }

    return 0;
}



// prompt
//
// Show the prompt to the user, waiting for an input.
//
// nmove holds the current move number in the game.
void prompt(unsigned nmove)
{
    ostringstream line(ostringstream::out);

    if (board.nextMove)
        line << "Black (" << nmove << "): ";
    else
        line << "White (" << nmove << "): ";

    cout << endl << line.str();
}



// getInput
//
// Retrieve an input line from the user.
string getInput()
{
    // clean the input, if necessary
    if (cin.peek() == '\n')
        cin.ignore(1, '\n');

    char input[MAX_INPUT_SIZE];


    // get a line from the input until we reach the maximum input size.
    cin.getline(input, MAX_INPUT_SIZE);
    string input_str(input);


    // Ctrl+D terminates the program
    if (cin.eof())
        terminateApp();

    return input_str;
}



// terminateApp
//
// Terminate the app in a safe way.
void terminateApp()
{
    cout << endl << "Goodbye!" << endl;
    exit(0);
}



// getInputType
//
// Analyze a given input and find out whether it is a move, a command or an
// invalid input.
InputType getInputType(string input)
{
    // handle null moves
    if ((input == "pass") || (input == "null"))
        return INPUT_TYPE_MOVE;


    // first check if the input matches any of the supported commands
    int pos = input.find_first_of(' ', 0);
    string cmd = input.substr(0, pos);
    if (find(listOfCommands.begin(), listOfCommands.end(), cmd) != listOfCommands.end())
        return INPUT_TYPE_CMD;


    // if it is not a command, it must be a move (length 2-6 chars)
    if ((input.length() < 2) || (input.length() > 7))
        return INPUT_TYPE_INVALID;


    // look for pawn moves => column + row (e.g. e4, d4, f3, b7..)
    else if ((input.length() == 2) && (isFile(input[0])) && (isRank(input[1])))
        return INPUT_TYPE_MOVE;


    // look for simple piece moves => piece + column|row + column|row (e.g. Nd4)
    // and short castling moves (0-0)
    else if (input.length() == 3)
    {
        if ((input == "0-0") || (input == "O-O"))
            return INPUT_TYPE_MOVE;

        else if (isPiece(input[0]) && isFile(input[1]) && isRank(input[2]))
            return INPUT_TYPE_MOVE;

        else if (isFile(input[0]) && (input[1] == 'x') && isFile(input[2]))
            return INPUT_TYPE_MOVE;

        else if (isPiece(input[0]) && (input[1] == 'x') && isFile(input[2]))
            return INPUT_TYPE_MOVE;

        else
            return INPUT_TYPE_INVALID;
    }


    // look for 4-character moves, including:
    // - move_orig_dest   => column + row + column + row (e.g. d2d4)
    // - capture_simple   => piece|column + 'x' + column + row (e.g. exd4, Nxd4)
    // - promotion_simple => column + row + '=' + piece
    else if (input.length() == 4)
    {
        // look for promotions
        if (isFile(input[0]) && isRank(input[1]) && (input[2] == '=') &&
                isPiece(input[3])  && (input[3] != 'K') && (input[3] != 'k'))
            return INPUT_TYPE_MOVE;


        // look for algebraic move (xyXY)
        else if ((isFile(input[0])) && (isRank(input[1]))
                && (isFile(input[2]))
                && (isRank(input[3])))
            return INPUT_TYPE_MOVE;


        // look for captures
        else if (isFile(input[0]) && (input[1] == 'x'))
            return INPUT_TYPE_MOVE;

        else if (isPiece(input[0]) && (input[1] == 'x'))
            return INPUT_TYPE_MOVE;


        // look for long moves
        else if (isPiece(input[0]) && (isFile(input[1]) || isRank(input[1]))
                && isFile(input[2]) && isRank(input[3]))
            return INPUT_TYPE_MOVE;

        else
            return INPUT_TYPE_INVALID;

    }


    // look for 5-character moves, including:
    // - algebraic promotion     => e7e8Q
    // - move_piece_ambiguous    => piece + column|row + column + row
    // - castle_long             => 0-0-0
    // - promotion_capture_short => column + 'x' + column + '=' + piece
    else if (input.length() == 5)
    {
        // look for algebraic promotions
        if (isFile(input[0]) && isRank(input[1]) &&
                isFile(input[2]) && isRank(input[3]) &&
                isPiece(input[4]))
            return INPUT_TYPE_MOVE;


        // look for promotions
        else if (isFile(input[0]) && (input[1] == 'x') && isFile(input[2]) &&
                (input[3] == '=')  && (input[4] != 'K') && (input[4] != 'k'))
            return INPUT_TYPE_MOVE;


        // look for long castling
        else if ((input == "0-0-0") || (input == "O-O-O"))
            return INPUT_TYPE_MOVE;


        // look for long moves
        else if (isPiece(input[0]) && (isFile(input[1]) || isRank(input[1]))
                && (input[2] == 'x')
                && isFile(input[3]) && isRank(input[4]))
            return INPUT_TYPE_MOVE;


        else
            return INPUT_TYPE_INVALID;
    }


    // look for 6-character moves => promotion after capture in SAN notation =>
    // column + 'x' + column + '8' + '=' + piece.
    else if (input.length() == 6)
    {
        if (isFile(input[0]) && (input[1] == 'x') && isFile(input[2]) &&
                ((input[3] == '8') || (input[3] == '1')) && (input[4] == '=') &&
                (input[5] != 'K') && (input[5] != 'k'))
            return INPUT_TYPE_MOVE;

        else
            return INPUT_TYPE_INVALID;
    }


    // by default, an input is invalid unless proven otherwise.
    return INPUT_TYPE_INVALID;
}



// changeSide
//
// Change the side playing, including color, type of input (human vs computer),
// clocks, etc.
void changeSide()
{
    if (playMode == HUMAN_CPU)
        (curPlayerType == PLAYER_TYPE_HUMAN) ? curPlayerType = PLAYER_TYPE_COMPUTER : curPlayerType = PLAYER_TYPE_HUMAN;
    else if (playMode == CPU_CPU)
        curPlayerType = PLAYER_TYPE_COMPUTER;

    cursor++;

    numberOfMove = (cursor / 2) + 1;
}



// dealEnd
//
// Deal with the end of the current match.
void dealEnd()
{
    cout << endl;


    // show result for draw due to insufficient material.
    if (bitCnt(board.whitePieces | board.blackPieces) < 3)
        cout << "1/2-1/2 {Insufficient material}" << endl;


    // deal with 50-fold repetition which ends the game.
    else if (board.fiftyMove > 99)
        cout << "1/2-1/2 {Draw by 50-move repetition}" << endl;


    // resignation
    if (gameEnd == END_TYPE_RESIGN)
    {
        if (board.nextMove)
        {
            cout << "1-0 {Black resigns}" << endl;
            winingDelta = 1;
        }
        else
        {
            cout << "0-1 {White resigns}" << endl;
            winingDelta = -1;
        }
    }


    // display how much ML was used during the game
    float MLpercent = ((MLhit * 1.0f) / (cursor * 1.0f)) * 100.0f;
    cout << setprecision(2) << "ML hit ratio = " << MLpercent << " %      (" << MLhit << "/" << cursor << ")" << endl << endl;


    // don't let the computer control the program after a game
    wPlayer = PLAYER_TYPE_HUMAN;
    bPlayer = PLAYER_TYPE_COMPUTER;
    curPlayerType = wPlayer;
    playMode = HUMAN_CPU;


    // update ML database
    bool learnedFound;
    int noLearned = 0;
    for (tuple<string, string, float> &tup : learned)
    {
        learnedFound = false; 

        for (tuple<string, string, float> &tupML : ML)
        {
            if ((get<0>(tup) == get<0>(tupML)) && (get<1>(tup) == get<1>(tupML)))
            {
                get<2>(tupML) += winingDelta;
                learnedFound = true;
                noLearned++;
            }
        }

        // if we updated a record, we can move to the next one
        // if we didn't update a record, we need to insert as new
        if (!learnedFound)
        {
            ML.push_back(make_tuple(get<0>(tup), get<1>(tup), winingDelta));
            noLearned++;
        }
    }

    if (noLearned > 0)
        cout << endl << "Learning " << noLearned << " new positions.. ";


    // save ML database to file
    ofstream outputFile("learn.db");
    if (outputFile.is_open())
    {
        for (tuple<string, string, float> &tup : ML)
        {
            outputFile << get<0>(tup) << endl << get<1>(tup) << endl << get<2>(tup) << endl;
        }
    }
    else
        cerr<<"Unable to save to learn.db!";
    outputFile.close();
    if (noLearned > 0)
        cout << "done." << endl << endl;

    
    // prompt the user again
    cout << "Type 'restart' to start a new game." << endl;
}



// displayGame
//
// Display the list of moves of this game.
void displayGame()
{
    if (board.endOfGame > 0)
    {
        // make a temporary copy of board.gameLine[]
        number = board.endOfGame;
        size_t numRecords = static_cast<size_t>(number);

        GameLineRecord *tmp = new GameLineRecord[numRecords];
        memcpy(tmp, board.gameLine, numRecords * sizeof(GameLineRecord));


        // unmake all moves
        for (i = number-1 ; i >= 0 ; i--) 
        { 
            unmakeMove(tmp[i].move);
            board.endOfSearch = --board.endOfGame;
        }


        // redo all moves
        j = board.nextMove;
        for (i = 0 ; i < number; i++)
        {
            // move numbering
            if (!((i+j+2)%2)) cout << (i+2*j+2)/2 << ". ";
            else if (!i) cout << "1. ... ";

            // construct the move string
            toSan(tmp[i].move, sanMove);
            cout << sanMove; 

            // output new line or space
            if (!((i+j+1)%2)) cout << endl;
            else cout << ", ";

            // make the move
            makeMove(tmp[i].move);
            board.endOfSearch = ++board.endOfGame;
        }
        cout << endl;


        // delete the temporary copy:
        delete[] tmp;
    } 

    // if there are no moves in the game, tell the user
    else
        cout << "there are no game moves" << endl;        
}



// getGameSequence
//
// Get the whole game history into a linear sequence, encoded in a string.
string getGameSequence()
{
    int count = 1;
    string sequence = "";

    if (board.endOfGame > 0)
    {
        // make a temporary copy of board.gameLine[]
        number = board.endOfGame;
        size_t numRecords = static_cast<size_t>(number);

        GameLineRecord *tmp = new GameLineRecord[numRecords];
        memcpy(tmp, board.gameLine, numRecords * sizeof(GameLineRecord));


        // unmake all moves
        for (i = number-1 ; i >= 0 ; i--) 
        { 
            unmakeMove(tmp[i].move);
            board.endOfSearch = --board.endOfGame;
        }

        for (i = 0; i < number; i++)
        {
            toSan(tmp[i].move, sanMove);
            string ts(sanMove);

            if (i % 2)
            {
                sequence += " " + ts;
                count++;
            }
            else
            {
                // don't add a blank before the first move
                if (count == 1)
                    sequence += to_string(count) + ". " + ts;
                else
                    sequence += " " + to_string(count) + ". " + ts;
            }

            // make the move:
            makeMove(tmp[i].move);
            board.endOfSearch = ++board.endOfGame;
        }


        // delete the temporary copy
        delete[] tmp;
    }

    return sequence; 
}



// getMLreply
//
// Try to find a good move from past games.
string getMLreply()
{
    vector<tuple<string, string, float>> v;

    // go through learned moves and pick those with wining scores
    for (tuple<string, string, float> &tup : ML)
    {
        if (get<0>(tup) == board.toFEN())
        {
            // black choose a move that has negative score (e.g., -2.00)
            if (board.nextMove)
            {
                if (get<2>(tup) < 0)
                    v.push_back(make_tuple(board.toFEN(), get<1>(tup), get<2>(tup)));
            }

            // white choose a move that has positive socre (e.g., +3.00)
            else
            {
                if (get<2>(tup) > 0)
                    v.push_back(make_tuple(board.toFEN(), get<1>(tup), get<2>(tup)));
            }
        }
    }

    sort(v.begin(), v.end(), sortByScore);

    if (!v.empty())
        return get<1>(v[0]);
    else
        return "";
}



// sortByScore
bool sortByScore(const tuple<string, string, float>& a, const tuple<string, string, float>& b)
{
    if (board.nextMove)
        return (get<2>(a) < get<2>(b));
    else
        return (get<2>(a) > get<2>(b));
}




// getValidMoves
map<string, string> getValidMoves(void)
{
    map<string, string> listOfValidMoves;
    string tmpStr = "";
    string s1 = "", s2 = "";
    board.moveBufLen[0] = 0;
    board.moveBufLen[1] = movegen(board.moveBufLen[0]);

    for (auto i = board.moveBufLen[0]; i < board.moveBufLen[1]; i++)
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

            string moveStr(sanMove);
            s1 = SQUARENAME[(board.moveBuffer[i]).getFrom()];
            s2 = SQUARENAME[(board.moveBuffer[i]).getTosq()];
            tmpStr = s1 + s2;
            moveStr.erase(std::remove(moveStr.begin(), moveStr.end(), '+'), moveStr.end());
            moveStr.erase(std::remove(moveStr.begin(), moveStr.end(), '#'), moveStr.end());

            // if promo, append promo piece
            if ((board.moveBuffer[i]).isPromo())
            {
                string tc(PIECECHARS[(board.moveBuffer[i]).getPromo()]);
                tmpStr += tc;
                transform(tmpStr.begin(), tmpStr.end(), tmpStr.begin(), ::tolower);
            }

            listOfValidMoves[moveStr] = tmpStr;
        }
    }

    return listOfValidMoves;


}
