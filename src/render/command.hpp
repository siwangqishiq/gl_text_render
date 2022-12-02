#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <iostream>
#include "glm/vec4.hpp"

class RenderEngine;
struct CharInfo;

class RenderCommand{
public:
    RenderEngine *engine_;
    RenderCommand(RenderEngine *engine) : engine_(engine){}

    virtual void runCommands(){}

    bool used = false;

protected:
    unsigned int vbo_;
    unsigned int vao_;

    int vboOffset_;

    int vertexCount_;
};

const float FONT_DEFAULT_SIZE = 64.0f;

struct TextPaint{
    float textSizeScale = 1.0f;
    float gapSize = 4.0f;
    glm::vec4 textColor = glm::vec4(1.0f , 1.0f , 1.0f , 1.0f);
};

// 文本渲染命令
class TextRenderCommand : public RenderCommand{
public:
    static TextPaint defaultTextPaint;

    TextRenderCommand(RenderEngine *engine) : RenderCommand(engine) {
    }

    void putParams(std::wstring text , float left , float bottom 
                    ,TextPaint &paint = defaultTextPaint);

    virtual void runCommands();
private:
    std::wstring content;
    glm::vec4 textColor_;

    unsigned int fontTextureId_ = -1;

    void fillTextVertData(std::wstring &text , float left , float bottom , 
            TextPaint &paint = defaultTextPaint);
    
    float findCharMaxHeight(std::wstring &text , TextPaint &paint = defaultTextPaint);
    
    float calOffsetY(std::shared_ptr<CharInfo> charInfo , float scale = 1.0f);

    bool isSymbol(std::wstring ch);

    std::unordered_map<wchar_t , wchar_t> loadSymbolMap(){
        std::unordered_map<wchar_t , wchar_t> symbolMap;
        for(wchar_t ch : symbolStr){
            symbolMap[ch] = ch;
        }
        return symbolMap;
    }
    
    std::unordered_map<wchar_t , wchar_t> symbolMap_;
    std::wstring symbolStr = 
    L"1234567890!@#$%^&*()_[]{};,.<>/?abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
};



