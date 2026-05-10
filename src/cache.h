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



// @file cache.h
//
// This file describes the data structures to store transposition tables (a.k.a.
// chess board posititions cache memory).
#ifndef _CACHE_H_
#define _CACHE_H_


#include <string>
#include <unordered_map>
#include "move.h"


using namespace std;



struct ttEntry
{
    uint64_t key   =  0;
    int      depth =  TT_EMPTY_VALUE;
    int      score =  0;
};



class Cache
{
    private:
        std::unordered_map<uint64_t, ttEntry> cacheData;

    public:
        ttEntry  find(uint64_t, int);
        void     add(uint64_t, ttEntry *);
        void     remove(uint64_t);
        void     clear();
        uint64_t size();
        uint64_t positions();
        void     dump();
};



#endif // _CACHE_H_
