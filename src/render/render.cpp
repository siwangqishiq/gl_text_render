#include "render.hpp"
#include "application.hpp"

void RenderEngine::render(){
    glClearColor(0.0f , 0.0f , 0.0f , 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderEngine::onScreenResize(){
    glViewport(0 , 0 , appContext_->screenWidth_ , appContext_->screenHeight_);
}