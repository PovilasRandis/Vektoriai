#ifndef TIMER_H
#define TIMER_H

#include <chrono>

// Čia yra laiko matavimo klasė
///////////////////////////////

class Timer 
{
    private:
       std::chrono::time_point<std::chrono::high_resolution_clock> start;
    public:
        Timer();
        void reset();
        double current_time();
        double split_time(double &full_time);

};
#endif