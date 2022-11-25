#include "triangle.hpp"
#include "log.hpp"

void Triangle::init(){
    std::string vertSrc = 
    #ifdef __ANDROID__
    "#version 300 es\n"
    #else
    "#version 330 core\n"
    #endif
    "layout(location = 0) in vec2 aPos;"
    "uniform mat3 transMat;\n"
    "void main() {\n"
    "   // gl_Position = vec4(aPos , 1.0f , 1.0f);\n"
    "   gl_Position = vec4(transMat * vec3(aPos , 1.0f) , 1.0);\n"
    "}\n";

    std::string fragSrc = 
    #ifdef __ANDROID__
    "#version 300 es\n"
    #else
    "#version 330 core\n"
    #endif
    "precision mediump float;"
    "out vec4 FragColor;"
    "void main(){\n"
    "   FragColor = vec4(1.0f , 1.0f , 0.0f , 1.0f);\n"
    "}\n";
    
    shader = ShaderManager::getInstance().fetchShader("triangle_render" , vertSrc, fragSrc);
    
    glGenVertexArrays(1 , &vao);
    glGenBuffers(1 , &vbo);
    Logi("test" , "vao = %d",vao);
    Logi("test" , "vbo = %d",vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER , vbo);
    glEnableVertexAttribArray(0);
    glBufferData(GL_ARRAY_BUFFER , 3 *2 * sizeof(float) , vertices , GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0 , 2 , GL_FLOAT , GL_FALSE , 2 * sizeof(float) , (void *)0);
}

void Triangle::trick(glm::mat3 &normalMat){
    shader.useShader();
    shader.setUniformMat3("transMat" , normalMat);

    // glBindVertexArray(vao);
    // // Logi("test" , "shade run %d" , shader.programId);
    // // std::cout << "error 0 " << glGetError() << std::endl;
    // glBindBuffer(GL_ARRAY_BUFFER , vbo);
    // // std::cout << "error 1 " << glGetError() << std::endl;
    // glEnableVertexAttribArray(0);
    // // std::cout << "error 2 " << glGetError() << std::endl;
    // glVertexAttribPointer(0 , 2 , GL_FLOAT , GL_FALSE , 2 * sizeof(float) , (void *)0);
    // std::cout << "error 3 " << glGetError() << std::endl;
    // std::cout << std::endl;
    
    // glDrawArrays(GL_TRIANGLE_FAN , 0 , 3);
    // glBindBuffer(GL_ARRAY_BUFFER , 0);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_FAN , 0 , 3);
    // std::cout << "error " << glGetError() << std::endl;
}

void Triangle::free(){
    ShaderManager::getInstance().clear();
}