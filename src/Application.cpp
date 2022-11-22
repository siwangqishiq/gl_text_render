#include "Application.hpp"
#include "log.hpp"

//window surface header
#include "glheader.hpp"
#include "render/render.hpp"
#include "resource/asset_manager.hpp"

void Application::onFree(){
    Logi(TAG , "app onFree");
    // triangleDemo_->free();
    if(renderEngine_ != nullptr){
        renderEngine_->free();
    }
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
        renderEngine_->onScreenResize();
    }
}

void Application::onInit(){
    Logi(TAG , "app onInit");

    // renderEngine_ = std::shared_ptr<RenderEngine>(new RenderEngine(std::shared_ptr<Application>(this)));

    renderEngine_ = std::make_shared<RenderEngine>(this);
    renderEngine_->init();
    
    renderEngine_->onScreenResize();

    triangleDemo_ = std::make_shared<Triangle>();
    triangleDemo_->init();

    auto fileContent = AssetManager::getInstance()->readTextFile("test.txt");
    std::wcout <<"file len" << fileContent.length() <<  fileContent << std::endl;
}

void Application::onTrick(){
    // Log(TAG , "app trick");
    
    if(renderEngine_ == nullptr){
        return;
    }

    //user logic and draw
    onSceneUpdate();

    //gl commands run
    renderEngine_->render();

    // triangleDemo_->trick(renderEngine_->normalMatrix_);
    // Logi(TAG , "time %lld" , currentTimeMillis());
}

void Application::onSceneUpdate(){
    float x = 0;
    float y = 0;

    for(;y < screenHeight_ ;y += 40.0f){
        x = 0.0f;
        for(; x < screenWidth_ ; x += 50.0f){
            renderEngine_->renderText(L"梅西" , x , y);
        }
    }
}






