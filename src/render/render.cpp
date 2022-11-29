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
    resetNormalMat(appContext_->viewWidth_ , appContext_->viewHeight_);
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
    textRenderShader_ = ShaderManager::getInstance()->loadAssetShader("text_render" 
                                , "shader/render_text_vert.glsl"
                                , "shader/render_text_frag.glsl");
}