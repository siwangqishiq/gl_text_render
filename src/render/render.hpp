/**
 * @file render.hpp
 * @author panyi
 * @brief 
 * @version 0.1
 * @date 2022-11-17
 * 
 * renderer
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include <memory>
#include "glheader.hpp"

class Application;

class RenderEngine{
public:
    RenderEngine(Application *appContext) : appContext_(appContext){}

    Application *appContext_;

    void render();

    void onScreenResize();
};

