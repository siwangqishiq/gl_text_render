#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <iostream>
#include "common.hpp"
#include <vector>

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

// 文本渲染命令
class TextRenderCommand : public RenderCommand{
public:
    static TextPaint defaultTextPaint;

    TextRenderCommand(RenderEngine *engine) : RenderCommand(engine) {
    }

    void putParams(std::wstring text , float left , float bottom 
                    ,TextPaint &paint = defaultTextPaint);

    virtual void runCommands();
    
    void setPaint(TextPaint &paint){
        paint_ = paint;
    }
private:
    TextPaint paint_;
    glm::vec4 textColor_;

    const int vertCountPerChar = 6;//一个字符由几个顶点确定

    unsigned int fontTextureId_ = -1;

    void buildGlCommands(std::vector<float> &buf);

    void fillTextVertData(std::wstring &text , float left , float bottom , 
            TextPaint &paint = defaultTextPaint);
    
    float findCharMaxHeight(std::wstring &text , TextPaint &paint = defaultTextPaint);
    
    float calOffsetY(std::shared_ptr<CharInfo> charInfo , float scale = 1.0f);

    float calTextStyleItalicOffset(std::shared_ptr<CharInfo> charInfo , TextPaint &paint);

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



