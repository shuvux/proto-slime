#ifndef PLATFORM_MANAGER_H // Prevent multiple inclusions of this header file
#define PLATFORM_MANAGER_H

#include <vector>      // For using std::vector
#include "Platform.h"  // Include Platform struct definition

// Class responsible for managing all platforms in the game
class PlatformManager {
public:
    std::vector<Platform> platforms; // List of platforms currently in the game

    // Basic configuration for platform generation
    float minPlatWidth{64.0f};   // Minimum width of a platform
    float maxPlatWidth{160.0f};  // Maximum width of a platform
    float minGap{32.0f};         // Minimum gap between platforms
    float maxGap{128.0f};        // Maximum gap between platforms
    float basePlatformY;         // Y position for the base platform

    Texture2D platformTexture;   // Texture used for rendering platforms

    PlatformManager(float baseY); // Constructor
    ~PlatformManager();           // Destructor

    // Resource management for platform textures
    void LoadResources();
    void UnloadResources();

    // Platform generation and cleanup
    void SeedInitial(float startX, int count);      // Seed initial platforms
    void Cleanup(float cleanupX);                   // Remove platforms past a certain X
    void Generate(float untilX,float dt);           // Generate platforms up to a certain X
    void Draw() const;                              // Draw all platforms

private:
    float RandRange(float minVal, float maxVal);    // Utility for random float in range
    float elapsedTime = 0.0f;                       // Time accumulator for generation logic
};

#endif // PLATFORM_MANAGER_H
