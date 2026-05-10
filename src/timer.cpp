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



// @file timer.cpp
#include <sys/timeb.h>
#include <stdio.h>
#include "timer.h"



// Timer::Timer
//
// Initialize a Timer class with start and stop time = 0.
Timer::Timer()
{
    running       = false;
    startTime     = 0;
    stopTime      = 0;
    stopTimeDelta = 0;
}



// Timer::init
//
// Start a timer.
void Timer::init()
{
    if (!running)
    {
        running = true;
        ftime(&startBuffer);
        startTime = startBuffer.time * 1000 + startBuffer.millitm + stopTimeDelta;
    }
}



// Timer::stop
//
// Stop a timer.
void Timer::stop()
{
    if (running)
    {
        running = false;
        ftime(&stopBuffer);
        stopTime = stopBuffer.time * 1000 + stopBuffer.millitm;
        stopTimeDelta = startTime - stopTime;
    }
    return;
}



// Timer::reset
//
// Reset a timer. Don't stop it if it was running.
void Timer::reset()
{
    if (running)
    {
        ftime(&startBuffer);
        startTime = startBuffer.time * 1000 + startBuffer.millitm;
    }
    else
    {
        startTime = stopTime;
        stopTimeDelta = 0;
    }
    return;
}



// Timer::display
//
// Show current timer count in milliseconds.
void Timer::display()
{
    if (running)
    {
        ftime(&currentBuffer);
        currentTime = currentBuffer.time * 1000 + currentBuffer.millitm;
        printf("%6.2f", (currentTime - startTime)/1000.0);
    }
    else
        printf("%6.2f", (stopTime - startTime)/1000.0);
    return;
}



// Timer::displayhms
//
// Show current timer count in hours, minutes and seconds.
void Timer::displayhms()
{
    int hh, mm, ss;
    if (running)
    {
        ftime(&currentBuffer);
        currentTime = currentBuffer.time * 1000 + currentBuffer.millitm;
        hh = (currentTime - startTime)/1000/3600;
        mm = ((currentTime - startTime)-hh*3600000)/1000/60;
        ss = ((currentTime - startTime)-hh*3600000-mm*60000)/1000;
        printf("%02d:%02d:%02d", hh, mm, ss);
    }
    else
    {
        hh = (stopTime - startTime)/1000/3600;
        mm = ((stopTime - startTime)-hh*3600000)/1000/60;
        ss = ((stopTime - startTime)-hh*3600000-mm*60000)/1000;
        printf("%02d:%02d:%02d", hh, mm, ss);
    }
    return;
}



// Timer::getms
//
// Get the number of milliseconds elapsed.
uint64_t Timer::getms()
{
    if (running)
    {
        ftime(&currentBuffer);
        currentTime = currentBuffer.time * 1000 + currentBuffer.millitm;
        return (currentTime - startTime) ;
    }
    else
        return (stopTime - startTime);
}



// Timer::getsysms
//
// Get the number of milliseconds counted by the system, not the elapsed time.
uint64_t Timer::getsysms()
{
    ftime(&currentBuffer);
    return (currentBuffer.time * 1000 + currentBuffer.millitm);
}
