#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "Player.h"
#include "PlatformManager.h"

class Game {
public:
    Game();
    void Run();

private:
    const int screenW = 1920;
    const int screenH = 1200;
    Camera2D camera{};
    Player player;
    PlatformManager platformManager;
    int lives{5};
    bool gameOver{false};
    float cameraSpeed{80.0f};
    float distanceTraveled{0.0f};
    float elapsedTime{0.0f};

    void Update();
    void HandleCollisions(float dt);
    void Respawn(bool loseLife);
    void Reset();
    void Draw();
};

#endif // GAME_H
