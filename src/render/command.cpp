#include "command.hpp"
#include "render.hpp"
#include "log.hpp"


void TextRenderCommand::putParams(std::wstring &text , float left , float bottom){
    content = text;
}

void TextRenderCommand::runCommands(){
    // Logi("cmd" , "render text size %d" , content.length());
}