#include "application.hpp"
#include "log.hpp"

//window surface header
#include "glheader.hpp"
#include "render/render.hpp"
#include "resource/asset_manager.hpp"
#include "render/texture.hpp"

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
    
    // auto fileContent = AssetManager::getInstance()->readTextFile("test.txt");
    // Logi("asset" , "test.txt szie: %d \n content: %s" , 
    //         fileContent.size() , fileContent.c_str());

    // TextureFileConfig config;
    // AssetManager::getInstance()->readTextureFile("lan.jpg", config);
    // Logi("asset" , "image info width : %d , height %d , channel : %d , datasize : %d",
    //      config.width , config.height , config.channel , config.dataSize);
    
    // auto info1 = TextureManager::getInstance()->acquireTexture("text/font_texture_0.png");
    // auto info2 = TextureManager::getInstance()->acquireTexture("text/font_texture_1.png");
}

void Application::onTrick(){
    // Log(TAG , "app trick");

    long timeStart = currentTimeMillis();
    
    if(renderEngine_ == nullptr){
        return;
    }

    //user logic and draw
    onSceneUpdate();

    //gl commands run
    renderEngine_->render();
    
    // for test
    // triangleDemo_->trick(renderEngine_->normalMatrix_);

    long timeEnd = currentTimeMillis();
    auto deltaTime = timeEnd - timeStart;
    // Logi(TAG , "frame cost time : %ld" , deltaTime);
}

void Application::onSceneUpdate(){
    // float x = x_;

    float x = 0.0f;
    float y = 0.0f;

    renderEngine_->renderText(L"你好,世界,Hello World" , x_ , y_);
    // for(;y < viewHeight_ ;y += 40.0f){
    //     x = 0.0f;
    //     for(; x < viewWidth_ ; x += 50.0f){
    //         renderEngine_->renderText(L"梅西" , x , y);
    //     }
    // }

    x_ += 0.02f;
    if(x_ > viewWidth_){
        x_ = 0.0f;
        y_ += 20.0f;
    }

    renderEngine_->renderText(L"一二三四五六七" , 100, 300 + 80);
    renderEngine_->renderText(L"嬛嬛一袅楚宫腰" , 100, 300);
    renderEngine_->renderText(L"从此君王不早朝" , 100, 300 - 80);
}






