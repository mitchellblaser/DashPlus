#include <chrono>

using namespace std;

#ifndef DP_TIMER
#define DP_TIMER

class Timer {
    public:
        Timer(int targetMS, bool debounce=false);
        void Tick();
        bool AtTarget();
        void RunComplete();
        void Reset();
    private:
        chrono::milliseconds oldrun = chrono::milliseconds(0);
        chrono::milliseconds run = chrono::milliseconds(0);
        int runCounter = 0;
        int _targetMS;
        bool _debounce;
        bool _atTarget = false;
        int adj;
};

#endif