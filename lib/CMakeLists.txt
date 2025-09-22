add_subdirectory(settings)
add_subdirectory(game)

file(GLOB_RECURSE ENTITY_SOURCES CONFIGURE_DEPENDS "entity/**/*.cpp")

add_library(
    EntityLib 
    STATIC 
        ${ENTITY_SOURCES}
)

target_include_directories(
    EntityLib 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    EntityLib 
    PUBLIC
        Settings
)
