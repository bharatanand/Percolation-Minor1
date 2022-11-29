#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#pragma once

#include <iostream>
#include <chrono>

class Timer
{
public:
    Timer()
    {
        startTimePoint = std::chrono::high_resolution_clock::now();
    }

    ~Timer()
    {
        stop();
    }

    void stop()
    {
        auto endTimePoint = std::chrono::high_resolution_clock::now();

        auto start = std::chrono::time_point_cast<std::chrono::milliseconds>(startTimePoint).time_since_epoch().count();
        auto stop = std::chrono::time_point_cast<std::chrono::milliseconds>(endTimePoint).time_since_epoch().count();

        auto duration = stop - start;

        std::cout << setw(30)<<"Total time taken : " << duration << " ms" << std::endl;
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTimePoint;
};

#endif // TIMER_H_INCLUDED
