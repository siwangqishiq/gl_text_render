#include <iostream>
#include "libjson/json.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Application.hpp"

class LinuxApplication : public Application{
public:
    void init(){
        onInit();
    }

    void update(){
        onTrick();
    }

    void free(){
        onFree();
    }
};


int main(int argc , char *argv[]){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //todo create instance
    std::unique_ptr<LinuxApplication> app = std::make_unique<LinuxApplication>();


    GLFWwindow* window = glfwCreateWindow(
                            app->screenWidth_, 
                            app->screenHeight_, 
                            "run", nullptr, nullptr);
    
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    app->init();
    while (!glfwWindowShouldClose(window)) {
        // std::cout << "tick" << std::endl;
        app->update();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }//end while
    
    app->onFree();
	glfwTerminate();
    return 0;
}