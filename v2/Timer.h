#include <sys/time.h>
#include <cstddef>
#include <iostream>

#pragma once

class TimeInterval {
private:
    timeval start_time{};
    timeval end_time{};

public:
    TimeInterval() {
        start();
    }

    ~TimeInterval() {
        stop();
        std::cout << "Elapsed time: " << GetInterval() << " microseconds." << std::endl;
    }

    void start() {
        gettimeofday(&this->start_time, NULL);
    }

    void stop() {
        gettimeofday(&this->end_time, NULL);
    }

    float GetInterval() {
        float t = (float)(end_time.tv_sec - start_time.tv_sec) * 1000000.0
                  + (float)(end_time.tv_usec - start_time.tv_usec); // in micro-sec

        // t = t / 1000000.0 // in sec

        return t;
    }
};
