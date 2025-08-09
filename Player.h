#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"


enum PlayerState {
    IDLE,
    MOVING
};

enum PlayerDirection {
    LEFT,
    RIGHT
};


class Player {
public:
    Vector2 pos{};
    Vector2 vel{};
    float radius{32.0f};
    bool onGround{false};

    float moveSpeed{180.0f};
    float dashMultiplier{2.5f};
    float jumpImpulse{420.0f};
    float gravity{1000.0f};
    float maxFallSpeed{800.0f};

    void Init(const Vector2 &startPos);
    void LoadTextures();   // New function to load textures from assets folder
    void UnloadTextures(); // Free textures when done
    void Update(float dt);
    Rectangle GetBounds() const;
    void LandOn(float platformY);
    void StopHorizontalAt(float newX);
    void Draw() const;

    Texture2D texIdleLeft{};
    Texture2D texIdleRight{};
    Texture2D texMoveLeft{};
    Texture2D texMoveRight{};

    PlayerState state{IDLE};
    PlayerDirection direction{RIGHT};

    ~Player();


};

#endif // PLAYER_H
