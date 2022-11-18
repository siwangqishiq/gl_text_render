#include "triangle.hpp"

void Triangle::init(){
    std::string vertSrc = 
    #ifdef __ANDROID__
    "#version 300 es\n"
    #else
    "#version 330 core\n"
    #endif
    "layout(location = 0) in vec2 aPos;"
    "void main() {\n"
    "   gl_Position = vec4(aPos ,1.0 , 1.0);\n"
    "}\n";

    std::string fragSrc = 
    #ifdef __ANDROID__
    "#version 300 es\n"
    #else
    "#version 330 core\n"
    #endif
    "out vec4 FragColor;"
    "void main(){\n"
    "   FragColor = vec4(1.0f , 1.0f , 0.0f , 1.0f);\n"
    "}\n";
    
    shader = ShaderManager::getInstance().fetchShader("triangle_render" , vertSrc, fragSrc);

    glGenVertexArrays(1 , &vao);
    glGenBuffers(1 , &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER , vbo);
    glBufferData(GL_ARRAY_BUFFER , sizeof(vertices) , vertices , GL_STATIC_DRAW);

    glVertexAttribPointer(0 , 2 , GL_FLOAT , GL_FALSE , 2 * sizeof(float) , (void *)0);
    glEnableVertexAttribArray(0);
}

void Triangle::trick(){
    shader.useShader();
    
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_FAN , 0 , 3);
}

void Triangle::free(){
    ShaderManager::getInstance().clear();
}