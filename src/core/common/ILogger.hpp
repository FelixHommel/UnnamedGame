#ifndef SRC_CORE_COMMON_I_LOGGER_HPP
#define SRC_CORE_COMMON_I_LOGGER_HPP

#include <string_view>

namespace ugame::core
{

/// \brief Logger Interface for the use in the core library
///
/// \author Felix Hommel
/// \date 10/5/2025
class ILogger
{
public:
    explicit ILogger() = default;
    virtual ~ILogger() = default;

    ILogger(const ILogger&) = default;
    ILogger(ILogger&&) = delete;
    ILogger& operator=(const ILogger&) = default;
    ILogger& operator=(ILogger&&) = delete;

    /// \brief log messages of the info level (informal)
    virtual void info(std::string_view msg) = 0;
    /// \brief log messages of the warning level (medium)
    virtual void warn(std::string_view msg) = 0;
    /// \brief log messages of the error level (high)
    virtual void error(std::string_view msg) = 0;
};

} // !ugame::core

#endif // !SRC_CORE_COMMON_I_LOGGER_HPP
