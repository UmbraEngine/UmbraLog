//
// Created by Dean Wilson on 2023/9/27
//

#include <umbra/logger.h>

namespace Umbra {
namespace Logging {

Logger::Logger(std::string name, bool debugEnabled)
{
  this->name = std::move(name);
  this->debugEnabled = debugEnabled;
}

Logger::Logger(std::string name, std::string fileName, bool debugEnabled)
{
  name = std::move(name);
  this->debugEnabled = debugEnabled;
  this->fileName = fileName;
  this->logFile.open(fileName, std::ios::out | std::ios::app);
  if (!this->logFile.is_open()) {
    std::cerr << "Error: Could not open log file." << std::endl;
  }
}

Logger::~Logger()
{
  if (this->logFile.is_open()) {
    this->logFile.close();
  }
}

void Logger::setColor(LogLevel level)
{
  switch (level) {
    case LogLevel::Trace:
      std::cout << "\033[0;32m";  // Green
      break;
    case LogLevel::Debug:
      std::cout << "\033[0;34m";  // Blue
      break;
    case LogLevel::Info:
      std::cout << "\033[0;36m";  // Grey [Normal]
      break;
    case LogLevel::Warning:
      std::cout << "\033[0;33m";  // Yellow
      break;
    case LogLevel::Error:
      std::cout << "\033[0;31m";  // Red
      break;
    case LogLevel::Fatal:
      std::cout << "\033[0;35m";  // Magenta
      break;
    case LogLevel::Off:
      std::cout << "\033[0m";  // Reset
      break;
    default:
      std::cout << "\033[0m";
      break;
  }
}

void Logger::resetColor()
{
  std::cout << "\033[0m";
}

std::string Logger::getLevelString(LogLevel level)
{
  switch (level) {
    // TODO: Add Tracing?
    case LogLevel::Trace:
      return "[TRACE]: ";
    case LogLevel::Debug:
      return "[DEBUG]: ";
    case LogLevel::Info:
      return "[INFO]: ";
    case LogLevel::Warning:
      return "[WARNING]: ";
    case LogLevel::Error:
      return "[ERROR]: ";
    case LogLevel::Fatal:
      return "[Fatal]: ";
    case LogLevel::Off:
      return "[OFF]: ";
    default:
      return "[UNKNOWN]: ";
  }
}

std::string Logger::getTimestamp()
{
  std::time_t now = std::time(0);
  std::tm* timeinfo = std::localtime(&now);
  char timestamp[80];
  std::strftime(timestamp, sizeof(timestamp), "[%Y-%m-%d %H:%M:%S] ", timeinfo);

  return std::string(timestamp);
}

void Logger::log(LogLevel level, std::string formattedMessage)
{
  if (Logger::shouldLogMessage(level)) {
    std::string levelString = this->getLevelString(level);
    std::string loggerName = "[" + this->name + "] ";
    std::string timestamp = this->getTimestamp();
    if (this->logFile.is_open()) {
      this->logFile << timestamp << loggerName << levelString << formattedMessage << std::endl;
    }
    this->setColor(level);
    std::cout << timestamp << loggerName << levelString << formattedMessage << std::endl;
    this->resetColor();
  }
}

bool Logger::shouldLogMessage(LogLevel level) const
{
  if (this->debugEnabled) {
    return true;
  }
  return level >= LogLevel::Info;
}

bool Logger::enableDebugging()
{
  return debugEnabled = true;
}

bool Logger::disableDebugging()
{
  return debugEnabled = false;
}

bool Logger::getDebugEnabled() const
{
  return debugEnabled;
}

}  // namespace Logging
}  // namespace Umbra
