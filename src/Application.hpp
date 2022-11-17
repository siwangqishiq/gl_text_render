#pragma once

#include <string>
#include <memory>
#include "render/triangle.hpp"
#include <ctime>
#include <chrono>
#include <sstream>


class RenderEngine;
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

    virtual void onSceneUpdate();
    
    virtual void onResize(int width , int height);
    
    //平台相关
    virtual void init();

    virtual void update();

    virtual void free();

    ~Application();

    std::shared_ptr<RenderEngine> getRender() {
        return renderEngine_;
    }
private:
    std::shared_ptr<RenderEngine> renderEngine_ = nullptr;

    //for test
    std::shared_ptr<Triangle> triangleDemo_ = nullptr;
};