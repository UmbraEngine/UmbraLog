#pragma once

#include <cstdlib>
#include <sstream>
#include <iomanip>

struct ClockSync {
 public:
  std::chrono::steady_clock::time_point steadyTime;
  std::chrono::system_clock::time_point systemTime;

  ClockSync()
  {
    this->steadyTime = std::chrono::steady_clock::now();
    this->systemTime = std::chrono::system_clock::now();
  }

  ClockSync(
      std::chrono::steady_clock::time_point steadyTime,
      std::chrono::system_clock::time_point systemTime
  )
  {
    this->steadyTime = steadyTime;
    this->systemTime = systemTime;
  }

  static std::string systemTimeToString(std::chrono::system_clock::time_point& systemTimePoint)
  {
    std::time_t t = std::chrono::system_clock::to_time_t(systemTimePoint);
    std::tm tm_struct;

#ifdef _WIN32
    localtime_s(&tm_struct, &t);
#else
    localtime_r(&t, &tm_struct);
#endif

    std::ostringstream oss;
    oss << std::put_time(&tm_struct, "%Y-%m-%d %H:%M:%S");
    auto ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(systemTimePoint.time_since_epoch()) %
        1000;

    oss << "." << std::setfill('0') << std::setw(3) << ms.count();
    return oss.str();
  }
};
