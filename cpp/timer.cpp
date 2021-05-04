#include "timer.h"

Timer::Timer(int targetMS, bool debounce) {
    _targetMS = targetMS;
    _debounce = debounce;
}

void Timer::Tick() {
    run = chrono::duration_cast<chrono::milliseconds> (
        chrono::system_clock::now().time_since_epoch()
    );

    if (_debounce) {
        adj = 8*runCounter;
        if (adj > _targetMS+20) {
            adj = _targetMS+20;
        }
    }
    else {
        adj = 0;
    }

    if (oldrun+chrono::milliseconds(_targetMS-adj) < run) {
        _atTarget = true;
    } else {
        _atTarget = false;
    }

}

bool Timer::AtTarget() {
    return _atTarget;
}

void Timer::RunComplete() {
    oldrun = run;
    runCounter++;
}

void Timer::Reset() {
    oldrun = chrono::milliseconds(0);
    run = chrono::milliseconds(0);
    runCounter = 0;
}