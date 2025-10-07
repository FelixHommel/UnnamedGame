cmake_minimum_required(VERSION 3.30)
project(
    UnnamedGame
    DESCRIPTION "Rougelike game"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/DefaultProjectSettings.cmake)
include(cmake/CodeCoverage.cmake)

add_library(project_warnings INTERFACE)
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

enable_testing()
add_subdirectory(deps)
add_subdirectory(src)
