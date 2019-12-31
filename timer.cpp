#include "timer.h"

Timer::Timer(const std::chrono::nanoseconds &duration) : duration_(duration) {}

void Timer::setDuration(const std::chrono::nanoseconds &duration) {
  duration_ = duration;
}

std::chrono::nanoseconds Timer::duration() const { return duration_; }
