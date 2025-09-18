find_library(RAYLIB_LIBRARY raylib REQUIRED)

add_executable(
    Game 
    main.cpp
)

target_link_libraries(
    Game 
    PRIVATE 
        GameLib
        ${RAYLIB_LIBRARY}
)
