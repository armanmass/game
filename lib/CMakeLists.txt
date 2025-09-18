add_subdirectory(settings)

add_library(GameLib INTERFACE)

target_link_libraries(
    GameLib 
    INTERFACE 
        Settings
)
