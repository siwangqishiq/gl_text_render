/**
 * @file render.hpp
 * @author panyi
 * @brief 
 * @version 0.1
 * @date 2022-11-17
 * 
 * renderer
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include <memory>
#include "glheader.hpp"
#include <string>
#include <vector>
#include "glm/matrix.hpp"
#include "render/shader.hpp"


class Application;
class RenderCommand;
class TextRenderHelper;

struct TextConfig{
    float size = 1.0f;
};

class TextRenderCommand;

class RenderEngine{
public:
    const std::string TAG = "RenderEngine";

    RenderEngine(Application *appContext) : appContext_(appContext){}

    Application *appContext_;

    void init();

    void clearRenderCommands();

    void submitRenderCommand(std::shared_ptr<RenderCommand> cmd);

    void render();

    void free();

    void onScreenResize();

    //render api
    void renderText(std::wstring text , float left , float bottom); //文本

    std::shared_ptr<TextRenderHelper> textRenderHelper_;

    //归一化变换矩阵
    glm::mat3 normalMatrix_;

private:
    std::vector<std::shared_ptr<RenderCommand>> renderCommandList_;

    void loadTextRenderResource();

    void resetNormalMat(float w , float h);

    int textCommandIndex;
    std::vector<std::shared_ptr<TextRenderCommand>> textCommandPool;
    std::shared_ptr<TextRenderCommand> fetchTextRenderCommand(RenderEngine *engine);
};

class TextRenderHelper{
public:
    void loadRes(RenderEngine &engine);

    Shader textRenderShader_;
};

