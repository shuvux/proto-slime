#include "PlatformManager.h"
#include "raylib.h"
#include <cstdlib>

// Constructor: initializes base platform Y and loads resources
PlatformManager::PlatformManager(float baseY) : basePlatformY(baseY) {
    LoadResources();
}

// Loads the texture for platforms
void PlatformManager::LoadResources() {
    platformTexture = LoadTexture("assets/platform-1.png");
}

// Seeds initial platforms at the start of the game
void PlatformManager::SeedInitial(float startX, int count) {
    float x = startX;
    for (int i = 0; i < count; ++i) {
        float w = RandRange(minPlatWidth, maxPlatWidth);
        Platform p;
        p.rect.x = x;
        p.rect.y = basePlatformY - (std::rand() % 120); // Randomize vertical position
        p.rect.width = w;
        p.rect.height = 19;
        p.color = BLACK;
        platforms.push_back(p);
        x += w + RandRange(minGap, maxGap); // Move to next platform position
    }
}

// Removes platforms that are no longer needed to save memory
void PlatformManager::Cleanup(float cleanupX) {
    while (!platforms.empty() && platforms.front().rect.x + platforms.front().rect.width < cleanupX) {
        platforms.erase(platforms.begin());
    }
}

// Generates new platforms as the player progresses
void PlatformManager::Generate(float untilX, float dt) {
    elapsedTime += dt;

    if (platforms.empty()) {
        // Create initial platform if none exist
        Platform p;
        p.rect.x = untilX - 200;
        p.rect.width = 200;
        p.rect.y = basePlatformY;
        p.rect.height = 19;
        p.color = BLACK;
        platforms.push_back(p);
    }

    // Continue generating platforms until the required X position is reached
    while (platforms.back().rect.x + platforms.back().rect.width < untilX) {
        Platform last = platforms.back();

        // Dynamically increase gap between platforms over time
        float gapIncreaseSpeed = 1.0f;  // pixels per second increase
        float dynamicMinGap = minGap + elapsedTime * gapIncreaseSpeed;
        float dynamicMaxGap = maxGap + elapsedTime * gapIncreaseSpeed;

        float gap = RandRange(dynamicMinGap, dynamicMaxGap);
        float w = RandRange(minPlatWidth, maxPlatWidth);

        Platform p;
        p.rect.x = last.rect.x + last.rect.width + gap;

        // Randomize vertical offset for platform
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

// Draws all platforms on the screen
void PlatformManager::Draw() const {
    for (const auto &p : platforms) {
        Rectangle src = { 0, 0, (float)platformTexture.width, (float)platformTexture.height };
        Rectangle dest = { p.rect.x, p.rect.y, p.rect.width, p.rect.height };
        Vector2 origin = { 0, 0 }; // top-left as origin
        DrawTexturePro(platformTexture, src, dest, origin, 0.0f, WHITE);

        DrawRectangleLinesEx(p.rect, 2.0f, DARKBROWN); // Draw outline for platform
    }
}

// Returns a random float between minVal and maxVal
float PlatformManager::RandRange(float minVal, float maxVal) {
    return minVal + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX/(maxVal - minVal)));
}

// Destructor: unloads resources
PlatformManager::~PlatformManager() {
    UnloadResources();
}

// Unloads the platform texture
void PlatformManager::UnloadResources() {
    UnloadTexture(platformTexture);
}