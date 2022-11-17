#pragma once

#include <string>

class RenderEngine;

class RenderCommand{
public:
    RenderEngine *engine_;
    RenderCommand(RenderEngine *engine) : engine_(engine){}

    virtual void runCommands(){}
};

//
class TextRenderCommand : public RenderCommand{
public:
    TextRenderCommand(RenderEngine *engine) : RenderCommand(engine) {
    }

    void putParams(std::wstring &text , float left , float bottom);

    virtual void runCommands();
private:
    std::wstring content;
};



