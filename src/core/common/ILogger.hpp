#ifndef SRC_CORE_COMMON_I_LOGGER_HPP
#define SRC_CORE_COMMON_I_LOGGER_HPP

#include <format>
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

    /// \brief log message with format string on info level
    template<typename... Args>
    void info(std::format_string<Args...> format, Args&&... args)
    {
        info(std::format(format, std::forward<Args>(args)...));
    }

    /// \brief log message with format string on warning level
    template<typename... Args>
    void warn(std::format_string<Args...> format, Args&&... args)
    {
        warn(std::format(format, std::forward<Args>(args)...));
    }

    /// \brief log message with format string on error level
    template<typename... Args>
    void error(std::format_string<Args...> format, Args&&... args)
    {
        error(std::format(format, std::forward<Args>(args)...));
    }
};

} // !ugame::core

#endif // !SRC_CORE_COMMON_I_LOGGER_HPP
