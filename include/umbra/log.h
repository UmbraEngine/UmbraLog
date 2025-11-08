#pragma once

#include <umbra/logger.h>
#include <string>

namespace Umbra {
namespace Logging {

#ifdef UMBRA_PLATFORM_MACOS
#define UMBRA_API __attribute__((visibility("default")))
#elif UMBRA_PLATFORM_WINDOWS
#define UMBRA_API __declspec(dllexport)
#else
#define UMBRA_API
#endif

#define BIT(x) (1 << x)

class Log {
 public:
  UMBRA_API static void init(bool enableClientDebugLogging = true);
  UMBRA_API static void init(std::string fileName, bool enableClientDebugLogging = true);
  UMBRA_API inline static std::shared_ptr<Logger>& getCoreLogger() { return CoreLogger; };
  UMBRA_API inline static std::shared_ptr<Logger>& getClientLogger() { return ClientLogger; }

 private:
  static std::shared_ptr<Logger> CoreLogger;
  static std::shared_ptr<Logger> ClientLogger;
};
}  // namespace Logging
}  // namespace Umbra

// Client Log Macros
#define LOG_TRACE(...) Umbra::Logging::Log::getClientLogger()->trace(__VA_ARGS__)
#define LOG_DEBUG(...) Umbra::Logging::Log::getClientLogger()->debug(__VA_ARGS__)
#define LOG_INFO(...) Umbra::Logging::Log::getClientLogger()->info(__VA_ARGS__)
#define LOG_WARNING(...) Umbra::Logging::Log::getClientLogger()->warning(__VA_ARGS__)
#define LOG_ERROR(...) Umbra::Logging::Log::getClientLogger()->error(__VA_ARGS__)
#define LOG_FATAL(...) Umbra::Logging::Log::getClientLogger()->fatal(__VA_ARGS__)

// Core Log Macros
#define LOG_CORE_TRACE(...) Umbra::Logging::Log::getCoreLogger()->trace(__VA_ARGS__)
#define LOG_CORE_DEBUG(...) Umbra::Logging::Log::getCoreLogger()->debug(__VA_ARGS__)
#define LOG_CORE_INFO(...) Umbra::Logging::Log::getCoreLogger()->info(__VA_ARGS__)
#define LOG_CORE_WARNING(...) Umbra::Logging::Log::getCoreLogger()->warning(__VA_ARGS__)
#define LOG_CORE_ERROR(...) Umbra::Logging::Log::getCoreLogger()->error(__VA_ARGS__)
#define LOG_CORE_FATAL(...) Umbra::Logging::Log::getCoreLogger()->fatal(__VA_ARGS__)
