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



### Figure the operating system name
UNAME = $(shell uname)


### Executable name
APP = chess0x


### Object files
OBJS = bit.o board.o book.o cache.o cmd.o data.o displaymove.o eval.o fen.o hash.o io.o main.o make.o move.o movgen.o perft.o search.o see.o timer.o uci.o 


### Compilation flags
CXXFLAGS += -O3 -Ofast -Wall -Wcast-qual -std=c++17 -fno-exceptions -fno-rtti -m64 -mpopcnt -flto
DEPENDFLAGS += -std=c++17


### Build targets
#all: $(APP) .depend
all: $(APP)

clean:
	$(RM) $(APP) $(APP).exe *.o

$(APP): $(OBJS)
	$(CXX) -o $@ $(OBJS)
