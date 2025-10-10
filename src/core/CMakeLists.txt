set(NAME "UnnamedGameCore")

include(${PROJECT_SOURCE_DIR}/cmake/StaticAnalyzers.cmake)

add_library(${NAME}
    ./gameLoop/GameLoop.cpp
    ./item/Item.cpp
)

target_sources(${NAME}
    PRIVATE
        FILE_SET HEADERS
        FILES
            ./common/Definitions.hpp
            ./common/ILogger.hpp
            ./common/exceptions/RepositoryException.hpp
            ./gameLoop/GameLoop.hpp
            ./item/Item.hpp
            ./item/IItemRepository.hpp
            ./stats/StatModifier.hpp
)

target_compile_features(${NAME} PRIVATE cxx_std_23)
target_link_libraries(${NAME}
    PRIVATE
        project_warnings
    PUBLIC
        fmt::fmt
        spdlog::spdlog
        nlohmann_json::nlohmann_json
)
target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
