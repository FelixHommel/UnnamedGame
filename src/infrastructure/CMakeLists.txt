set(NAME "UnnamedGameInfrastructure")

include(${PROJECT_SOURCE_DIR}/cmake/StaticAnalyzers.cmake)

add_library(${NAME}
    logging/SpdlogAdapter.cpp
    persistence/JsonItemRepository.cpp
)

target_sources(${NAME}
    PRIVATE
        FILE_SET HEADERS
        FILES
        logging/SpdlogAdapter.hpp
        persistence/JsonItemRepository.hpp
)

target_compile_features(${NAME} PRIVATE cxx_std_23)
target_link_libraries(${NAME}
    PRIVATE
        project_warnings
    PUBLIC
        fmt::fmt
        spdlog::spdlog
        nlohmann_json::nlohmann_json
        UnnamedGameCore
)
target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
