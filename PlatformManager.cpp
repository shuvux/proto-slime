#include "PlatformManager.h"
#include "raylib.h"
#include <cstdlib>

PlatformManager::PlatformManager(float baseY) : basePlatformY(baseY) {
    LoadResources();
}

void PlatformManager::LoadResources() {
    platformTexture = LoadTexture("platform-1.png");
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

void PlatformManager::Generate(float untilX) {
    if (platforms.empty()) {
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
        float gap = RandRange(minGap, maxGap);
        float w = RandRange(minPlatWidth, maxPlatWidth);
        Platform p;
        p.rect.x = last.rect.x + last.rect.width + gap;
        
        const float maxVerticalGap = 256.0f; // or your preferred gap limit
        
        float verticalOffset = (std::rand() % ((int)(maxVerticalGap * 2 + 1))) - maxVerticalGap; // random between -maxVerticalGap and +maxVerticalGap
        float vy = last.rect.y + verticalOffset;

        if (vy < 120) vy = 120;
        if (vy > 540 - 100) vy = 540 - 100;
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