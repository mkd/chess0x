# Overview
Chess0x [pronounced ***chess-ou***] is a computer chess program developed in C++
and loosely based on [Winglet](https://www.chessprogramming.org/Winglet), by
Stef Luijten. Chess0x is an evolution from [Chess0](https://github.com/mkd/chess0),
a C++ chess engine developed as a final year project for my Computer
Science degree for learning purposes (with very few optimizations) and, therefore,
it is not the most competitive chess engine you can find.

If you need a modern engine with proper chess skills, you should check out
[Stockfish](https://github.com/official-stockfish/Stockfish).

Chess0x' current approximate ELO rating is around ~2200, based on the Elometer
test (http://www.elometer.net), various tournaments against other rated chess
engines, and a series of games played on the
[Free Internet Chess Server (FICS)](https://www.freechess.org/).



# Files
This distribution of Chess0x consists of the following files:
- [README.md](https://github.com/mkd/chess0x/blob/master/README.md), the file
  you are currently reading.
- [copying.txt](https://github.com/mkd/chess0x/blob/master/copying.txt), a text
  file containing the GNU General Public License version 3.
- [TODO](https://github.com/mkd/chess0/blob/master/TODO), a list of improvements
  and future features (i.e., a backlog).
- [Changelog](https://github.com/mkd/chess0x/blob/master/Changelog), a readable
  list of changes introduced in every version.
- [book_count.sh](https://github.com/mkd/chess0/blob/master/book_count.sh), a
  script to count the number of opening entries in the book.
- [lines.sh](https://github.com/mkd/chess0x/blob/master/lines.sh), a script to
  count the number of lines in the source code.
- [src](https://github.com/mkd/chess0x/blob/master/src), a subdirectory
  containing the full source code, including a Makefile that can be used
  to compile Chess0x on Unix-like systems.
- [src/benchmark.py](https://github.com/mkd/chess0x/blob/master/src/benchmark.py),
  a simple script written in Python3 that tests many different chess positions
  using the python-chess UCI library, telling the speed of search, nodes and
  time to complete the tests. The script is engine-agnostic, and it can be 
  used to benchmark any UCI chess engine.



# Building Chess0x
The default [Makefile](https://github.com/mkd/chess0x/blob/master/src/Makefile)
in [src](https://github.com/mkd/chess0x/blob/master/src) contains the instructions
to build Chess0x in Unix systems, and it has been tested both on Linux and MacOS.

Cross-compilation to Windows 64-bit should be possible using e.g., mingw32;
however, I haven't taken the time to add that in the Makefile yet.



# Using Chess0x
## Using the command line interface (CLI)
Chess0x was built with research and learn purposes in mind. That is, by design,
I didn't develop Chess0x to be a super-portable, highly competitive chess
engine. Instead, I focused on code clarity and ease of use in the command line
interface (CLI).

When you run Chess0x, it prompts you with a ready-to-move interface like this:
```
Welcome to Chess0x!

White (1):
```

This means that the engine automatically starts a new game, where White can
enter the first (1) move. You can enter here moves in short algebraic notation
(SAN) to start playing against the computer. SAN moves are the ones used in 
modern chess literature; e.g., Nf3 Bxd5+ 0-0 d8=Q. As you enter your move,
the computer will start thinking (and, by default, you can see how it's 
thinking) and return the best move after the thinking time is up. By default,
the thinking time for the computer is 5s. See the following example:
```
White (1): e4


    +----+----+----+----+----+----+----+----+
  8 | R* | N* | B* | Q* | K* | B* | N* | R* |
    +----+----+----+----+----+----+----+----+
  7 | P* | P* | P* | P* | P* | P* | P* | P* |
    +----+----+----+----+----+----+----+----+
  6 |    |    |    |    |    |    |    |    |
    +----+----+----+----+----+----+----+----+
  5 |    |    |    |    |    |    |    |    |
    +----+----+----+----+----+----+----+----+
  4 |    |    |    |    | P  |    |    |    |
    +----+----+----+----+----+----+----+----+
  3 |    |    |    |    |    |    |    |    |
    +----+----+----+----+----+----+----+----+
  2 | P  | P  | P  | P  |    | P  | P  | P  |
    +----+----+----+----+----+----+----+----+
  1 | R  | N  | B  | Q  | K  | B  | N  | R  |
    +----+----+----+----+----+----+----+----+
      a    b    c    d    e    f    g    h


Black (1): 
Thinking...

  Ply  Score    Nodes     Time	 Speed kN/s  PV
    2  +0.02       51    0.00s            -  Nc6 Nc3      
    3  -0.40      206    0.00s            -  Nc6 Nc3 Nf6      
    4  +0.02      523    0.00s            -  Nc6 Nc3 Nf6 Nf3      
    4  +0.02     1.2K    0.00s            -  Nc6 Nc3 Nf6 Nf3      
    5  +0.05     2.1K    0.00s  2110.0 kN/s  Nc6 Nc3 Nf6 Nf3 d5      
    5  -0.02     4.0K    0.00s  4015.0 kN/s  Nf6 Nc3 d5 e5 Bg4      
    5  -0.02     4.8K    0.00s  2401.5 kN/s  Nf6 Nc3 d5 e5 Bg4      
    6  +0.07     7.9K    0.00s  2642.0 kN/s  Nf6 Nc3 Nc6 Nf3 d5 Bd3      
    6  +0.07    14.3K    0.00s  2858.2 kN/s  Nf6 Nc3 Nc6 Nf3 d5 Bd3      
    7  +0.05    28.5K    0.01s  3567.1 kN/s  Nf6 Nc3 Nc6 Nf3 d5 Bd3 Be6      
    7  +0.05    65.5K    0.02s  3855.6 kN/s  Nf6 Nc3 Nc6 Nf3 d5 Bd3 Be6      
    8  +0.08   100.5K    0.03s  3351.0 kN/s  Nf6 Nc3 Nc6 Nf3 d5 e5 d4 Bc4      
    8  +0.05   117.3K    0.04s  3170.1 kN/s  Nc6 Nf3 Nf6 Nc3 e5 Bc4 Bc5      
    8  +0.05   195.3K    0.06s  3255.1 kN/s  Nc6 Nf3 Nf6 Nc3 e5 Bc4 Bc5      
    9  +0.06   455.8K    0.15s  3122.0 kN/s  Nc6 Nf3 d5 exd5 Qxd5 Nc3 Qe6+ Be2 Nf6      
    9  +0.06   896.6K    0.28s  3179.5 kN/s  Nc6 Nf3 d5 exd5 Qxd5 Nc3 Qe6+ Be2 Nf6      
   10  +0.05     1.7M    0.58s  2961.4 kN/s  Nc6 Nc3 Nf6 Nf3 e5 Bc4 Bc5 0-0 0-0      
   10  +0.05     3.4M    1.09s  3099.7 kN/s  Nc6 Nc3 Nf6 Nf3 e5 Bc4 Bc5 0-0 0-0      
   11  +0.11     7.5M    2.32s  3224.9 kN/s  Nc6 Bd3 Nf6 Ne2 d5 exd5 Ne5 Bb5+ Bd7 Bxd7+ Qxd7      
             ( 8/20)      4ms       e5...     


My move: 1... Nc6 (time: 4.96s)

    +----+----+----+----+----+----+----+----+
  8 | R* |    | B* | Q* | K* | B* | N* | R* |
    +----+----+----+----+----+----+----+----+
  7 | P* | P* | P* | P* | P* | P* | P* | P* |
    +----+----+----+----+----+----+----+----+
  6 |    |    | N* |    |    |    |    |    |
    +----+----+----+----+----+----+----+----+
  5 |    |    |    |    |    |    |    |    |
    +----+----+----+----+----+----+----+----+
  4 |    |    |    |    | P  |    |    |    |
    +----+----+----+----+----+----+----+----+
  3 |    |    |    |    |    |    |    |    |
    +----+----+----+----+----+----+----+----+
  2 | P  | P  | P  | P  |    | P  | P  | P  |
    +----+----+----+----+----+----+----+----+
  1 | R  | N  | B  | Q  | K  | B  | N  | R  |
    +----+----+----+----+----+----+----+----+
      a    b    c    d    e    f    g    h


White (2): 
```

Besides entering moves, this prompt also is used to enter different commands to
change the type of the game as well as configuring some settings. Just type
'help' to see the following list:
```
Welcome to Chess0x!

White (1): help
analyze  auto  book  cache  depth  eval  fen  flip
game  go  help  history  lmr  load  manual  new  null
pass  quiet  quit  recall  remove  resign  restart
save  sd  set  setboard  show  silent  solve  st  test
think  uci  verbose  undo  version
```

For any of those settings, you can simply type 'help COMMAND' for every
setting and Chess0x will show you further instructions on how to use
a specific settings. For example:

```
White (1): help cache

cache [on | off]
 Let the computer use the transposition tables to find
 previously searched positions faster. This typically
 makes the engine more powerful in middle and end-game.
 Please note that using transposition tables can take
 a few hundreds of Megabytes for a ~1h game.
```

## Using a graphical user interface (GUI)
Thanks to the UCI protocol, you can use Chess0x with your favorite chess GUI. 
Chess GUI applications use the UCI protocol to communicate with the engine, so
you can analyze your games, play against it or even run a computer chess
tournament from your own computer.

I personally use [ScidvsMac](http://scidvspc.sourceforge.net/) (a version
of ScidvsPC for MacOS) to test Chess0x. There's a ton of free chess graphical
interfaces for UCI chess engines, just pick your favorite one.



# Implementation
Chess0x is implemented mainly in C++, with numerous functions written in pure C
for performance reasons. When I wrote the first version of Chess0x, I tried to
use only C++ with strict object orientation. This made the code much more
readable and maintainable. However, C++ objects starated to become a real
bottleneck as the search tree grew. So finally, I decided to optimize core
objects and functionalities using C-like structures whenever the execution
speed would increase exponentially.



# Contributing to Chess0x
This is not one of my most active projects at the moment. There're way too many
great things out there to stay inside coding another chess engine for ages
(it's a work that never ends!). So, if you have tried Chess0x and would like to
improve the current source code in any way, please go ahead!



# Features
- **Bitboards:** 
  https://en.wikipedia.org/wiki/Bitboard

- **Principal Variation Search:** 
  https://en.wikipedia.org/wiki/Principal_variation_search

- **Iterative Deepening:**:
  https://en.wikipedia.org/wiki/Iterative_deepening_depth-first_search

- **Alpha-beta pruning:**
  https://en.wikipedia.org/wiki/Alpha–beta_pruning
 
- **Quiescence search:**
  https://en.wikipedia.org/wiki/Quiescence_search

- **Null Move Reductions:** 
  https://en.wikipedia.org/wiki/Null-move_heuristic

- **Trasnposition tables:** 
  https://en.wikipedia.org/wiki/Transposition_table

- **Late Move Reductions (LMR):** 
  https://www.chessprogramming.org/Late_Move_Reductions

- **Universal Chess Interface (UCI) protocol:**
  http://wbec-ridderkerk.nl/html/UCIProtocol.html

- **Opening book:** Chess0x comes with a built-in openings book (3500+
  positions). The book is always in use by default, however you can disable
  it with the command 'book off'.
