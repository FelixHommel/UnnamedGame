#ifndef SRC_CORE_COMMON_EXCEPTIONS_REPOSITORY_EXCEPTION_HPP
#define SRC_CORE_COMMON_EXCEPTIONS_REPOSITORY_EXCEPTION_HPP

#include <stdexcept>

namespace ugame::core::common
{

// \brief exception class that is used by Repositories in the case that something didn't go as expected
//
// This exception can be used for a multitude of reasons (i.e. File opening failed, internal Repository actions failed, ...)
//
// \author Felix Hommel
// \date 10/10/2025
class RepositroyException : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;

    ~RepositroyException() override = default;

    RepositroyException(const RepositroyException&) = default;
    RepositroyException(RepositroyException&&) = default;
    RepositroyException& operator=(const RepositroyException&) = default;
    RepositroyException& operator=(RepositroyException&&) = default;

private:
};

} //!ugame::core::common

#endif //!SRC_CORE_COMMON_EXCEPTIONS_REPOSITORY_EXCEPTION_HPP
