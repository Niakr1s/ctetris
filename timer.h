#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <functional>
#include <thread>

using namespace std::chrono_literals;

class Timer {
 public:
  enum class Status { RUNNING, PAUSED, END, NOTHING };

  Timer(const std::chrono::nanoseconds &duration);

  template <class Func>
  void start(Func &&f) {
    status_ = Status::RUNNING;
    std::thread([f, this] {
      while (status_ != Status::END) {
        switch (status_) {
          case (Status::RUNNING):
            std::this_thread::sleep_for(duration_);
            f();
            break;
          case (Status::PAUSED):
            std::this_thread::sleep_for(1s);
            break;
          default:
            break;
        }
      }
    }).detach();
  }

  void pause();
  void stop();

  void setDuration(const std::chrono::nanoseconds &duration);
  std::chrono::nanoseconds duration() const;

 private:
  std::chrono::nanoseconds duration_;
  Status status_ = Status::NOTHING;
};

#endif  // TIMER_H
