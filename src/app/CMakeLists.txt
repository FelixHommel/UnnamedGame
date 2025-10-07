set(NAME "UnnamedGame")

include(${PROJECT_SOURCE_DIR}/cmake/StaticAnalyzers.cmake)

add_executable(${NAME}
    main.cpp
)

target_compile_features(${NAME} PRIVATE cxx_std_23)
target_link_libraries(${NAME}
    PRIVATE
        project_warnings
        spdlog::spdlog
        fmt::fmt
        nlohmann_json::nlohmann_json
        UnnamedGameCore
        UnnamedGameInfrastructure
)
target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
