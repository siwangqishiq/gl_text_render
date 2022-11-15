#include "application.hpp"
#include "log.hpp"

//window surface header
#include "common.hpp"

void Application::onResize(int w , int h){
    Logi(TAG , "app onresize %d , %d" , w , h);
}

void Application::onInit(){
    Log(TAG , "app onInit");
}

void Application::onTrick(){
    // Log(TAG , "app trick");
    glClearColor(0.0f , 0.0f , 0.0f , 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Application::onFree(){
    Log(TAG , "app onFree");
}





