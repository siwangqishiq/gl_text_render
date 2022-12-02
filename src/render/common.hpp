#pragma once

#include "glm/vec4.hpp"

//文本绘制 配置
struct TextPaint{
    float textSizeScale = 1.0f;
    float gapSize = 4.0f;
    glm::vec4 textColor = glm::vec4(1.0f , 1.0f , 1.0f , 1.0f);
};

//矩形
struct Rect{
    float left;
    float top;
    float width;
    float height;
};



