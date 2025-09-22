find_library(RAYLIB_LIBRARY raylib REQUIRED)

add_executable(
    Game 
    main.cpp
)

target_link_libraries(
    Game 
    PRIVATE 
        GameModule
        ${RAYLIB_LIBRARY}
)
