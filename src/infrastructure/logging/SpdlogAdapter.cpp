#include "SpdlogAdapter.hpp"

#include "spdlog/spdlog.h"

#include <string_view>

namespace ugame::infrastructure
{

void SpdlogAdapter::info(std::string_view msg)
{
    spdlog::info(msg);
}

void SpdlogAdapter::warn(std::string_view msg)
{
    spdlog::warn(msg);
}

void SpdlogAdapter::error(std::string_view msg)
{
    spdlog::error(msg);
}

} // !ugame::infrastructure
