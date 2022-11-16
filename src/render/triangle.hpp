
//draw a triangle for test
#pragma once

#include "common.hpp"
#include "shader.hpp"

class Triangle{
public:
    void init();
    void trick();
    void free();

private:
    // for test
    GLuint vao;
    GLuint vbo;

    Shader shader;

    float vertices[3 * 2] = {
        -0.5f , -0.5f,
         0.5f , -0.5f,
         0.0f ,  0.5f 
    };
};

