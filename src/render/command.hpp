#pragma once

#include <string>

class RenderEngine;

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

// 文本渲染命令
class TextRenderCommand : public RenderCommand{
public:
    TextRenderCommand(RenderEngine *engine) : RenderCommand(engine) {
    }

    void putParams(std::wstring text , float left , float bottom);

    virtual void runCommands();
private:
    std::wstring content;
};



