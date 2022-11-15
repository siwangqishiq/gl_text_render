#pragma once

#include <string>

/**
 * @brief  应用入口
 * 
 */
class Application {
public:
    const std::string TAG = "Application"; 

    int screenWidth_ = 800;
    int screenHeight_ = 600;

    void onInit();

    void onTrick();

    void onFree();
    
    void onResize(int width , int height);
    
    //平台相关
    virtual void init() = 0;

    virtual void update() = 0;

    virtual void free() = 0;
};