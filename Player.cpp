#include "Player.h"
#include "raylib.h"

void Player::Init(const Vector2 &startPos) {
    pos = startPos;
    vel = {0, 0};
    onGround = false;

    state = IDLE;
    direction = RIGHT;


    moveSpeed = 200.0f;       // Starting speed
    elapsedTime = 0.0f;       // Reset timer
    speedIncreaseRate = 1.0f; // Increase speed by 50 units per second (adjust as needed)
    maxMoveSpeed = 999.0f;    // Maximum speed cap


    LoadTextures();
}

void Player::Update(float dt) {

    elapsedTime += dt;

    moveSpeed += speedIncreaseRate * dt;
    if (moveSpeed > maxMoveSpeed) moveSpeed = maxMoveSpeed;

    
    float inputX = 0.0f;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) inputX -= 1.0f;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) inputX += 1.0f;

    bool dashHeld = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);

    float hVel = inputX * moveSpeed;
    if (dashHeld && inputX != 0) hVel *= dashMultiplier;

    vel.x = hVel;

    // Update player direction for sprite flip
    if (inputX < 0) direction = LEFT;
    else if (inputX > 0) direction = RIGHT;

    // Update player state for sprite selection
    if (inputX == 0) state = IDLE;
    else state = MOVING;

    // Start jump if pressed and on ground
    // Start jump when jump key pressed AND player is on ground
    if ((IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && onGround) {
        isJumping = true;       // start jump hold state
        jumpHoldTime = 0.0f;    // reset hold timer
        vel.y = -jumpImpulse;   // initial jump impulse
        onGround = false;
    }

    // Check if jump key is currently held down
    bool jumpHeld = IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_W) || IsKeyDown(KEY_UP);

    // If jump is in progress and button is held and max hold time not reached
    if (isJumping && jumpHeld && jumpHoldTime < maxJumpHoldTime) {
        // Sustain upward velocity to allow higher jump while holding
        vel.y = -jumpImpulse;
        jumpHoldTime += dt;
    } else {
        // Jump hold ended or button released or max hold reached
        isJumping = false;
    }

    // Apply gravity normally
    vel.y += gravity * dt;
    if (vel.y > maxFallSpeed) vel.y = maxFallSpeed;

    // Update position normally
    pos.x += vel.x * dt;
    pos.y += vel.y * dt;
}

Rectangle Player::GetBounds() const {
    return { pos.x - radius + 1, pos.y - radius, radius * 2 - 2, radius * 2 };
}

void Player::LandOn(float platformY) {
    int texHeight = texIdleRight.height;
    pos.y = platformY - (texHeight / 2.0f);
    vel.y = 0;
    onGround = true;
}

void Player::StopHorizontalAt(float newX) {
    pos.x = newX;
    vel.x = 0;
}

void Player::Draw() const {
    Texture2D currentTex;

    if (direction == LEFT) {
        if (state == IDLE)
            currentTex = texIdleLeft;
        else
            currentTex = texMoveLeft;
    } else { // RIGHT
        if (state == IDLE)
            currentTex = texIdleRight;
        else
            currentTex = texMoveRight;
    }

    float scale = 0.55f;

    // Draw texture centered on player position
    Vector2 origin = { (currentTex.width) / 2.0f, (currentTex.height*scale) / 2.0f };
    DrawTexturePro(currentTex, 
                   Rectangle{0, 0, (float)currentTex.width, (float)currentTex.height}, 
                   Rectangle{pos.x, pos.y, (float)currentTex.width, (float)currentTex.height}, 
                   origin, 0.0f, WHITE);
}


void Player::LoadTextures() {
    texIdleLeft = LoadTexture("src/assets/idle-left.png");
    texIdleRight = LoadTexture("src/assets/idle-right.png");
    texMoveLeft = LoadTexture("src/assets/idle-left.png");
    texMoveRight = LoadTexture("src/assets/idle-right.png");
}

void Player::UnloadTextures() {
    UnloadTexture(texIdleLeft);
    UnloadTexture(texIdleRight);
    UnloadTexture(texMoveLeft);
    UnloadTexture(texMoveRight);
}

Player::~Player() {
    UnloadTextures();
}
