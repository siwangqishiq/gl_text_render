#include "Application.hpp"
#include "Log.hpp"

//window surface header
#ifdef _WIN32
#include <glad/glad.h>
#elif _WIN64
#include <glad/glad.h>
#elif __ANDROID__
#include <glad/glad.h>
#elif __APPLE__
#include <glad/glad.h>
#endif

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

void Application::onResize(int w , int h){
    std::string msg = "app onResize ";
    msg += std::to_string(w);
    msg += " , ";
    msg += std::to_string(h);
    Log(TAG , msg);
}




