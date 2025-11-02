//
// Created by Dean Wilson on 2025/01/20
//

#include <umbra/log.h>

namespace Umbra {
namespace Logging {

std::shared_ptr<Logger> Log::CoreLogger;
std::shared_ptr<Logger> Log::ClientLogger;

void Log::init(bool enableClientDebugLogging)
{
  CoreLogger = std::make_shared<Logger>("Umbra", true);
  ClientLogger = std::make_shared<Logger>("Client", enableClientDebugLogging);
}

void Log::init(std::string fileName, bool enableClientDebugLogging)
{
  CoreLogger = std::make_shared<Logger>("Umbra", fileName, true);
  ClientLogger = std::make_shared<Logger>("Client", fileName, enableClientDebugLogging);
}

}  // namespace Logging
}  // namespace Umbra
