#include "Game.h"
#include <cstdlib>
#include <ctime>
#include "raylib.h"

Game::Game() : platformManager(screenH * 0.7f) {
    InitWindow(screenW, screenH, "Slymania");
    SetTargetFPS(60);
    std::srand((unsigned)time(nullptr));

    camera.offset = { screenW * 0.3f, screenH * 0.5f };
    camera.target = { 0, 0 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    platformManager.SeedInitial(-100.0f, 8);
    if (!platformManager.platforms.empty()) {
        auto &first = platformManager.platforms.front();
        player.Init({ first.rect.x + first.rect.width * 0.5f, first.rect.y - player.radius });
    }
}

void Game::Run() {
    while (!WindowShouldClose()) {
        Update();
        Draw();
    }
    CloseWindow();
}

void Game::Update() {
    if (!gameOver) {
        float dt = GetFrameTime();

        elapsedTime+=dt;

        cameraSpeed = 100.0f +elapsedTime*1.0f;
        if (cameraSpeed > 999.0f)cameraSpeed = 999.0f;

        camera.target.x += cameraSpeed * dt;
        distanceTraveled += cameraSpeed * dt;

        player.Update(dt);
        HandleCollisions(dt);

        float cleanupX = camera.target.x - screenW * 1.2f;
        platformManager.Cleanup(cleanupX);

        float generateUntilX = camera.target.x + screenW * 1.8f;
        platformManager.Generate(generateUntilX, dt);

        float camBottom = camera.target.y + (screenH - camera.offset.y);
        float camLeft = camera.target.x - camera.offset.x;
        if (player.pos.y - player.radius > camBottom + 40) Respawn(true);
        if (player.pos.x + player.radius < camLeft + 6) Respawn(true);

        camera.target.y = screenH * 0.5f;
    } else {
        if (IsKeyPressed(KEY_R)) Reset();
    }
}

void Game::HandleCollisions(float dt) {
    player.onGround = false;
    Rectangle playerBB = player.GetBounds();

    for (auto &p : platformManager.platforms) {
        if (CheckCollisionRecs(playerBB, p.rect)) {
            float playerBottom = player.pos.y + player.radius;
            float platTop = p.rect.y;
            if (player.vel.y >= 0 && playerBottom - player.vel.y * dt <= platTop + 3) {
                player.LandOn(platTop);
            } else {
                if (player.pos.x < p.rect.x) player.StopHorizontalAt(p.rect.x - player.radius - 1);
                else player.StopHorizontalAt(p.rect.x + p.rect.width + player.radius + 1);
            }
        }
    }
}

void Game::Respawn(bool loseLife) {
    if (loseLife) {
        lives--;
        if (lives <= 0) { gameOver = true; return; }
    }
    float camLeft = camera.target.x - camera.offset.x;
    Platform* respawnPlat = nullptr;
    for (auto &p : platformManager.platforms) {
        if (p.rect.x + p.rect.width >= camLeft - 50) { respawnPlat = &p; break; }
    }
    if (!respawnPlat && !platformManager.platforms.empty())
        respawnPlat = &platformManager.platforms.front();
    if (respawnPlat) {
        player.pos.x = respawnPlat->rect.x + respawnPlat->rect.width * 0.5f;
        player.pos.y = respawnPlat->rect.y - player.radius - 1;
        player.vel = { 0,0 };
        player.onGround = true;
        camera.target.x = player.pos.x + 100;
    }
}

void Game::Reset() {
    platformManager.platforms.clear();
    platformManager.SeedInitial(-100.0f, 8);
    if (!platformManager.platforms.empty()) {
        auto &first = platformManager.platforms.front();
        player.Init({ first.rect.x + first.rect.width * 0.5f, first.rect.y - player.radius });
    }
    lives = 5;
    gameOver = false;
    camera.target.x = 0;
    distanceTraveled = 0;
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(DARKGREEN);

    BeginMode2D(camera);
    for (int gx = -2000; gx < 50000; gx += 200)
        DrawLineEx(Vector2{ (float)gx, 0 }, Vector2{ (float)gx, 2000 }, 1.0f, Fade(GRAY, 0.08f));

    platformManager.Draw();
    player.Draw();
    EndMode2D();

    DrawRectangle(8, 8, 220, 76, Fade(BLACK, 0.35f));
    DrawRectangleLines(8, 8, 220, 76, BLUE);
    DrawText(TextFormat("Lives: %d", lives), 16, 16, 20, RED);
    DrawText(TextFormat("Distance: %d m", (int)(distanceTraveled / 10.0f)), 16, 40, 16, DARKGRAY);
    DrawText("Move: A/D or ←/→  Jump: Space/W/↑  Dash: Shift", 250, 16, 14, DARKGRAY);
    if (gameOver) DrawText("GAME OVER - Press R to Restart", screenW / 2 - 180, screenH / 2 - 10, 20, RED);

    EndDrawing();
}
