#include "Application.hpp"
#include "Log.hpp"

//window surface header
#include "common.hpp"

void Application::onResize(int w , int h){
    Logi(TAG , "app onresize %d , %d" , w , h);

    glViewport(0 , 0 , w , h);
}

void Application::onInit(){
    Log(TAG , "app onInit");

    triangleDemo_ = std::make_shared<Triangle>();
    triangleDemo_->init();
}

void Application::onTrick(){
    // Log(TAG , "app trick");
    glClearColor(0.0f , 0.0f , 0.0f , 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    triangleDemo_->trick();
}

void Application::onFree(){
    Log(TAG , "app onFree");

    triangleDemo_->free();
}





