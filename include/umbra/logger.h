#pragma once

#include <chrono>
#include <ctime>
#include <format>
#include <fstream>
#include <iostream>
#include <utility>
#include <sstream>
#include <string>

const int LOG_LEVEL_TRACE = 0;
const int LOG_LEVEL_DEBUG = 1;
const int LOG_LEVEL_INFO = 2;
const int LOG_LEVEL_WARNING = 3;
const int LOG_LEVEL_ERROR = 4;
const int LOG_LEVEL_FATAL = 5;
const int LOG_LEVEL_OFF = 6;

enum LogLevel : int {
  Trace = LOG_LEVEL_TRACE,
  Debug = LOG_LEVEL_DEBUG,
  Info = LOG_LEVEL_INFO,
  Warning = LOG_LEVEL_WARNING,
  Error = LOG_LEVEL_ERROR,
  Fatal = LOG_LEVEL_FATAL,
  Off = LOG_LEVEL_OFF
};

namespace Umbra {
namespace Logging {
class Logger {
 public:
  Logger(std::string name, bool debugEnabled = false);
  Logger(std::string name, std::string fileName, bool debugEnabled = false);
  ~Logger();

  Logger& operator=(const Logger& other)
  {
    if (this == &other) {
      return *this;
    }

    if (this->logFile.is_open()) {
      this->logFile.close();
    }

    std::string newFileName = other.logFile.rdbuf()->getloc().name();
    this->logFile.open(newFileName, std::ios::out | std::ios::app);

    return *this;
  }

  template <typename... Args>
  void trace(const std::format_string<Args...> message, Args&&... args)
  {
    logFormattedString(LogLevel::Trace, message, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void debug(const std::format_string<Args...> message, Args&&... args)
  {
    logFormattedString(LogLevel::Debug, message, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void info(const std::format_string<Args...> message, Args&&... args)
  {
    logFormattedString(LogLevel::Info, message, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void warning(const std::format_string<Args...> message, Args&&... args)
  {
    logFormattedString(LogLevel::Warning, message, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void error(const std::format_string<Args...> message, Args&&... args)
  {
    logFormattedString(LogLevel::Error, message, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void fatal(const std::format_string<Args...> message, Args&&... args)
  {
    logFormattedString(LogLevel::Fatal, message, std::forward<Args>(args)...);
  }

  bool enableDebugging();
  bool disableDebugging();

 private:
  std::string name;
  bool debugEnabled;
  std::ofstream logFile;
  std::string fileName;

  [[nodiscard]] bool shouldLogMessage(LogLevel level) const;
  [[nodiscard]] bool getDebugEnabled() const;
  void setColor(LogLevel level);
  void resetColor();
  std::string getLevelString(LogLevel level);
  std::string getTimestamp();

  template <typename... Args>
  void logFormattedString(LogLevel level, const std::format_string<Args...> format, Args&&... args)
  {
    std::string formattedString = std::format(format, std::forward<Args>(args)...);
    this->log(level, formattedString);
  };

  void log(LogLevel level, std::string formattedMessage);
};
}  // namespace Logging
}  // namespace Umbra
