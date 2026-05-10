# This file is part of Chess0x, a computer chess program based on Winglet Chess
# by Stef Luijten.
#    
# Copyright (C) 2022 Claudio M. Camacho
#
# Chess0x is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Chess0x is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.


### Figure the operating system name and architecture
UNAME_S = $(shell uname -s)
UNAME_M = $(shell uname -m)

### Executable name
APP = chess0x

### Object files
OBJS = bit.o board.o book.o cache.o cmd.o data.o displaymove.o eval.o fen.o hash.o io.o main.o make.o move.o movgen.o perft.o search.o see.o timer.o uci.o

### Base Compilation flags (Aggressive Optimizations)
# -O3 + -ffast-math replaces the deprecated -Ofast
# -march=native tells the compiler to optimize specifically for the CPU it's compiling on
CXXFLAGS += -O3 -ffast-math -march=native -Wall -Wcast-qual -std=c++17 -fno-exceptions -fno-rtti -flto
DEPENDFLAGS += -std=c++17

### Architecture-specific flags
# Only apply Intel/AMD specific flags if we are on an x86_64 architecture
ifeq ($(UNAME_M),x86_64)
    CXXFLAGS += -m64 -mpopcnt
endif
ifeq ($(UNAME_M),amd64)
    CXXFLAGS += -m64 -mpopcnt
endif


### Build targets
#all: $(APP) .depend
all: $(APP)

clean:
	$(RM) $(APP) $(APP).exe *.o

$(APP): $(OBJS)
	$(CXX) -o $@ $(OBJS)
