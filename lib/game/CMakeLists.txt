add_library(
    GameModule 
    STATIC 
        Game.cpp
)

target_include_directories(
    GameModule 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    GameModule 
    PUBLIC 
        EntityLib
)
