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
            ./common/exceptions/RepositoryException.hpp
            ./common/IEvent.hpp
            ./common/IEventChannel.hpp
            ./common/IItemRepository.hpp
            ./common/ILogger.hpp
            ./common/IPlayerInput.hpp
            ./gameLoop/EventBus.hpp
            ./gameLoop/GameLoop.hpp
            ./gameLoop/events/PlayerInputReceivedEvent.hpp
            ./item/Item.hpp
            ./stats/StatModifier.hpp
)

target_compile_features(${NAME} PRIVATE cxx_std_23)
target_link_libraries(${NAME}
    PRIVATE
        project_warnings
)
target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
