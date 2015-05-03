#ifndef TIMER_H
#define TIMER_H

#include <time.h>
#include <iostream>

using namespace std;

class Timer
{
public:
    Timer();
    Timer(string theName);
    ~Timer();
private:
    string name;

    clock_t start, end;

};

#endif // TIMER_H
