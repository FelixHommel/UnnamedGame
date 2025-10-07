set(NAME "Test")

include (${PROJECT_SOURCE_DIR}/cmake/StaticAnalyzers.cmake)

add_executable(${NAME}
    main.cpp
    core/item/ItemRepositoryContractTest.cpp
)

# use when header files are added
# target_sources(${NAME}
#     PRIVATE
#         FILE_SET HEADERS
#         FILES
# )

target_compile_features(${NAME} PRIVATE cxx_std_23)
target_link_libraries(${NAME}
    PRIVATE
        project_warnings
        GTest::gtest
        UnnamedGameCore
        UnnamedGameInfrastructure
)

add_test(NAME ${NAME} COMMAND ${NAME})
