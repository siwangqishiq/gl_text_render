#include "Application.hpp"
#include "Log.hpp"

//window surface header
#include "glheader.hpp"
#include "render/render.hpp"

void Application::onFree(){
    Log(TAG , "app onFree");
    
    // triangleDemo_->free();
}

void Application::init(){
    onInit();
}

void Application::update(){
    onTrick();
}

void Application::free(){
    onFree();
}

Application::~Application(){
    Logi(TAG , "~app Application");
}

void Application::onResize(int w , int h){
    Logi(TAG , "app onresize %d , %d" , w , h);
    screenWidth_ = w;
    screenHeight_ = h;
    
    if(renderEngine_ != nullptr){

    }
}

void Application::onInit(){
    Log(TAG , "app onInit");

    // triangleDemo_ = std::make_shared<Triangle>();
    // triangleDemo_->init();

    // renderEngine_ = std::shared_ptr<RenderEngine>(new RenderEngine(std::shared_ptr<Application>(this)));

    renderEngine_ = std::make_shared<RenderEngine>(this);
}

void Application::onTrick(){
    // Log(TAG , "app trick");

    // triangleDemo_->trick();


    if(renderEngine_ != nullptr){
        renderEngine_->render();
    }
}






