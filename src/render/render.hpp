/**
 * @file render.hpp
 * @author panyi
 * @brief 
 * @date 2022-11-17
 * 
 * renderer
 * 
 * 
 */
#pragma once
#include <memory>
#include "glheader.hpp"
#include <string>
#include <vector>
#include "glm/matrix.hpp"
#include "render/shader.hpp"
#include <unordered_map>
#include "common.hpp"


class Application;
class RenderCommand;
class TextRenderHelper;
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

    std::shared_ptr<TextRenderHelper> textRenderHelper_;

    //归一化变换矩阵
    glm::mat3 normalMatrix_;

        //render api
    void renderText(std::wstring text , 
            float left , 
            float bottom , 
            TextPaint &paint); //文本

    void renderText(std::wstring text , Rect &showRect , TextPaint &paint);
private:
    std::vector<std::shared_ptr<RenderCommand>> renderCommandList_;

    void loadTextRenderResource();

    void resetNormalMat(float w , float h);

    int textCommandIndex;
    std::vector<std::shared_ptr<TextRenderCommand>> textCommandPool;
    std::shared_ptr<TextRenderCommand> fetchTextRenderCommand(RenderEngine *engine);
};

//字符信息
struct CharInfo{
    std::wstring value; 
    float width;
    float height;
    float textureCoords[4];
    unsigned int textureId;
};

const float SPACE_WIDTH = 16.0f;

class TextRenderHelper{
public:
    void loadRes(RenderEngine &engine);

    Shader textRenderShader_;

    std::shared_ptr<CharInfo> findCharInfo(wchar_t &ch);
private:
    void buildTextCharConfig();

    void addSpecialTextCharInfo();

    std::unordered_map<wchar_t , std::shared_ptr<CharInfo>> charInfoMaps_;
};

