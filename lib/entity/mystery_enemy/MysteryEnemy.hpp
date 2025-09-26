#pragma once
#include <raylib.h>

class MysteryEnemy
{
public:
    MysteryEnemy();
    ~MysteryEnemy();
    void Update();
    void Draw() const;
    void Spawn();

    constexpr bool isAlive() const noexcept { return alive_; }
    constexpr float getLastSpawned() const noexcept { return lastSpawned; }
    constexpr void updateLastSpawed() { lastSpawned = GetTime(); }
    constexpr float getSpawnInterval() const noexcept { return spawnInterval; }
    constexpr void newSpawnInterval() { spawnInterval = GetRandomValue(10, 20); }
private:
    Vector2 position_;
    Texture2D image_;
    float lastSpawned{};
    float spawnInterval{};
    static constexpr float startY{ 91.0f };
    float speed{ 3.0f };
    bool alive_{ false };
};