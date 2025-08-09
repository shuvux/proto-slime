#ifndef PLATFORM_MANAGER_H
#define PLATFORM_MANAGER_H

#include <vector>
#include "Platform.h"

class PlatformManager {
public:
    std::vector<Platform> platforms;

    //basic config of platform 
    float minPlatWidth{64.0f};
    float maxPlatWidth{160.0f};
    float minGap{32.0f};
    float maxGap{128.0f};
    float basePlatformY;


    Texture2D platformTexture;

    PlatformManager(float baseY);
    ~PlatformManager();

    //load the platform
    void LoadResources();
    void UnloadResources();

    void SeedInitial(float startX, int count);
    void Cleanup(float cleanupX);
    void Generate(float untilX,float dt);
    void Draw() const; 

    

private:
    float RandRange(float minVal, float maxVal);
    float elapsedTime = 0.0f;
};

#endif // PLATFORM_MANAGER_H
