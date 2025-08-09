#include "PlatformManager.h"
#include "raylib.h"
#include <cstdlib>

PlatformManager::PlatformManager(float baseY) : basePlatformY(baseY) {
    LoadResources();
}

void PlatformManager::LoadResources() {
    platformTexture = LoadTexture("assets/platform-1.png");
}



void PlatformManager::SeedInitial(float startX, int count) {
    float x = startX;
    for (int i = 0; i < count; ++i) {
        float w = RandRange(minPlatWidth, maxPlatWidth);
        Platform p;
        p.rect.x = x;
        p.rect.y = basePlatformY - (std::rand() % 120);
        p.rect.width = w;
        p.rect.height = 19;
        p.color = BLACK;
        platforms.push_back(p);
        x += w + RandRange(minGap, maxGap);
    }
}

void PlatformManager::Cleanup(float cleanupX) {
    while (!platforms.empty() && platforms.front().rect.x + platforms.front().rect.width < cleanupX) {
        platforms.erase(platforms.begin());
    }
}

void PlatformManager::Generate(float untilX, float dt) {
    elapsedTime += dt;

    if (platforms.empty()) {
        // initial platform, same as before
        Platform p;
        p.rect.x = untilX - 200;
        p.rect.width = 200;
        p.rect.y = basePlatformY;
        p.rect.height = 19;
        p.color = BLACK;
        platforms.push_back(p);
    }

    while (platforms.back().rect.x + platforms.back().rect.width < untilX) {
        Platform last = platforms.back();

        // Increase gap based on elapsedTime: e.g. start from minGap and increase linearly
        float gapIncreaseSpeed = 1.0f;  // pixels per second increase, tweak as needed
        float dynamicMinGap = minGap + elapsedTime * gapIncreaseSpeed;
        float dynamicMaxGap = maxGap + elapsedTime * gapIncreaseSpeed;

        float gap = RandRange(dynamicMinGap, dynamicMaxGap);
        float w = RandRange(minPlatWidth, maxPlatWidth);

        Platform p;
        p.rect.x = last.rect.x + last.rect.width + gap;

        const float maxVerticalGap = 50.0f;
        float verticalOffset = (std::rand() % ((int)(maxVerticalGap * 2 + 1))) - maxVerticalGap;
        float vy = last.rect.y + verticalOffset;

        p.rect.y = vy;
        p.rect.width = w;
        p.rect.height = 19;
        p.color = BLACK;
        platforms.push_back(p);
    }
}


// Before Draw()


void PlatformManager::Draw() const {
    for (const auto &p : platforms) {
        Rectangle src = { 0, 0, (float)platformTexture.width, (float)platformTexture.height };
        Rectangle dest = { p.rect.x, p.rect.y, p.rect.width, p.rect.height };
        Vector2 origin = { 0, 0 }; // top-left as origin
        DrawTexturePro(platformTexture, src, dest, origin, 0.0f, WHITE);

        DrawRectangleLinesEx(p.rect, 2.0f, DARKBROWN);
    }
}


float PlatformManager::RandRange(float minVal, float maxVal) {
    return minVal + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX/(maxVal - minVal)));
}


PlatformManager::~PlatformManager() {
    UnloadResources();
}

void PlatformManager::UnloadResources() {
    UnloadTexture(platformTexture);
}