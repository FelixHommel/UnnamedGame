#ifndef SRC_INFRASTRUCTURE_LOGGING_SPDLOG_ADPATER_HPP
#define SRC_INFRASTRUCTURE_LOGGING_SPDLOG_ADPATER_HPP

#include "common/ILogger.hpp"

#include <string_view>

namespace ugame::infrastructure::logging
{
using namespace ugame::core::common;

/// \brief Spdlog adapter for the Logger Interface
///
/// \author Felix Hommel
/// \date 10/5/2025
class SpdlogAdapter : public ILogger
{
public:
    void info(std::string_view msg) override;
    void warn(std::string_view msg) override;
    void error(std::string_view msg) override;
};

} // !ugame::infrastructure::logging

#endif // !SRC_INFRASTRUCTURE_LOGGING_SPDLOG_ADPATER_HPP
