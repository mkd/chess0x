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



// @file cache.cpp
//
// This file contains the functions to manipulate the cache data structure and
// transposition tables.
#include <iostream>
#include "definitions.h"
#include "cache.h"



using namespace std;



// find
//
// Look for a ttEntry in the cache.
ttEntry Cache::find(uint64_t key, int depth)
{
    ttEntry tt, ttfalse;

    auto search = cacheData.find(key);

    if (search != cacheData.end())
    {
        tt = search->second;

        if ((tt.key == key) && (tt.depth >= depth))
            return tt;
    }

    return ttfalse;
}



// add
//
// Insert a new ttEntry in the cache.
void Cache::add(uint64_t key, ttEntry *tt)
{
    cacheData[key] = *tt;
}



// remove
//
// Remove a ttEntry from the cache.
void Cache::remove(uint64_t key)
{
    cacheData.erase(key);
}



// clear
//
// Empty the entire cache structure.
void Cache::clear()
{
    cacheData.clear();
}



// positions
//
// Return the number of entries stored in the cache.
uint64_t Cache::positions()
{
    return cacheData.size();
}



// size
//
// Return the total memory size (in bytes) occupied by the cache data
// structures.
uint64_t Cache::size()
{
    return cacheData.size() * BOARD_SERIAL_SIZE;
}


// dump
// 
// Print out the entire cache memory structure.
void Cache::dump()
{
    for (auto i : cacheData)
    {
        cout << "Key = " << i.first << " => {score = " << (i.second).score << "; depth = " << (i.second).depth << "}" << endl;
    }
}
