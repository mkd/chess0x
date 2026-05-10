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



// @file timer.h
//
// TODO: replace this by C++11 timers (using clock_t).
#ifndef _TIMER_H
#define _TIMER_H



#include <sys/timeb.h>
#include "definitions.h"



struct Timer
{
    uint64_t   startTime;   
    uint64_t   stopTime;    
    uint64_t   currentTime;
    uint64_t   stopTimeDelta;
    timeb startBuffer;   
    timeb stopBuffer;   
    timeb currentBuffer;
    bool running;  

    void init();               // start the timer
    void stop();               // stop the timer
    void reset();              // reset the timer
    void display();                   // display time in seconds with 2 decimals
    void displayhms();         // display time in hh:mm:ss.dd
    uint64_t getms();               // return time in milliseconds
    uint64_t getsysms();         // return system time
    Timer();
};



#endif // _TIMER_H_
