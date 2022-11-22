#include "render.hpp"
#include "application.hpp"
#include "log.hpp"
#include "command.hpp"
#include "vram.hpp"

void RenderEngine::render(){
    glClearColor(0.0f , 0.0f , 0.0f , 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glEnable(GL_DEPTH_TEST);
    
    //gl render
    for(auto &cmd : renderCommandList_){
        cmd->runCommands();
        cmd->used = false;
    }
    
    //clear cmd list
    clearRenderCommands();
    VRamManager::getInstance().onPostRender();
}

void RenderEngine::free(){
    VRamManager::getInstance().clear();
}

void RenderEngine::clearRenderCommands(){
    renderCommandList_.clear();
}

void RenderEngine::onScreenResize(){
    resetNormalMat(appContext_->screenWidth_ , appContext_->screenHeight_);
    glViewport(0 , 0 , appContext_->screenWidth_ , appContext_->screenHeight_);
}

void RenderEngine::init(){
    Logi(TAG , "render engine init start");
    loadTextRenderResource();//text render init
    // Logi(TAG , "render engine init end");
}

void RenderEngine::loadTextRenderResource(){
    Logi(TAG , "render init loadTextRenderResource");
    textRenderHelper_ = std::make_shared<TextRenderHelper>();
    textRenderHelper_->loadRes(*this);
}

void RenderEngine::resetNormalMat(float w , float h){
    Logi(TAG , "reset normal matrix %f , %f" , w , h);
    normalMatrix_[0][0] = 2.0f / w;
    normalMatrix_[0][1] = 0.0f;
    normalMatrix_[0][2] = 0.0f;

    normalMatrix_[1][0] = 0.0f;
    normalMatrix_[1][1] = 2.0f / h;
    normalMatrix_[1][2] = 0.0f;

    normalMatrix_[2][0] = -1.0f;
    normalMatrix_[2][1] = -1.0f;
    normalMatrix_[2][2] =  1.0f;
}

void RenderEngine::submitRenderCommand(std::shared_ptr<RenderCommand> cmd){
    renderCommandList_.push_back(cmd);
}

void RenderEngine::renderText(std::wstring text , float left , float bottom){
    auto cmd = fetchTextRenderCommand(this);
    cmd->putParams(text , left , bottom);
    submitRenderCommand(cmd);
}

std::shared_ptr<TextRenderCommand> RenderEngine::fetchTextRenderCommand(RenderEngine *engine){
    //new a new instace later use pool to reuse
    auto newCmd = 
        std::make_shared<TextRenderCommand>(this);
    newCmd->used = true;
    return newCmd;
}

void TextRenderHelper::loadRes(RenderEngine &engine){
    //init shader
    std::string vertSrc = 
    #ifdef __ANDROID__
    "#version 300 es\n"
    #else
    "#version 330 core\n"
    #endif
    "layout(location = 0) in vec3 a_position;\n"
    "layout(location = 1) in vec2 a_texture;\n"
    "uniform mat3 transMat;\n"
    "out vec2 vUv;\n"
    "void main() {\n"
    "   gl_Position = vec4(transMat * a_position ,1.0f);\n"
    "   vUv = a_texture;\n"
    "}\n";

    std::string fragSrc = 
    #ifdef __ANDROID__
    "#version 300 es\n"
    #else
    "#version 330 core\n"
    #endif
    "precision mediump float;"
    "in vec2 vUv;"
    "out vec4 outColor;"
    "void main(){\n"
    "   outColor = vec4(1.0f , 1.0f , 0.0f , 1.0f);\n"
    "}\n";

    textRenderShader_ = ShaderManager::getInstance()
                            .fetchShader("text_render" , vertSrc, fragSrc);
}