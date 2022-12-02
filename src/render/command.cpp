#include "command.hpp"
#include "render.hpp"
#include "log.hpp"
#include "vram.hpp"
#include "../../libjson/json.hpp"


TextPaint TextRenderCommand::defaultTextPaint;

float TextRenderCommand::findCharMaxHeight(std::wstring &text , TextPaint &paint){
    auto textRenderHelper = engine_->textRenderHelper_;
    float maxHeight = 0.0f;
    for(int i = 0 ; i < text.length() ;i++){
        wchar_t ch = text[i];
        auto charInfoPtr = textRenderHelper->findCharInfo(ch);
        if(charInfoPtr == nullptr){
            continue;
        }

        float realHeight = charInfoPtr->height * defaultTextPaint.textSizeScale;
        if(maxHeight < realHeight) {
            maxHeight = realHeight;
        }
    }//end for i
    return maxHeight;
}

float TextRenderCommand::calOffsetY(std::shared_ptr<CharInfo> charInfo , float scale){
    if(charInfo == nullptr || isSymbol(charInfo->value)){
        return 0.0f;
    }else{
        float charRealHeight = charInfo->height * scale;
        float fontMaxHeight = FONT_DEFAULT_SIZE * scale;
        return fontMaxHeight / 2.0f - charRealHeight / 2.0f;
    }
}

bool TextRenderCommand::isSymbol(std::wstring ch){
    // if(ch.empty()){
    //     return false;
    // }
    
    auto charMap = loadSymbolMap();
    //Logi("issymbol" , "%d symbolMap %s" ,ch.empty(), ToByteString(ch).c_str());
    //std::cout << "xx : " << (symbolMap_.find(ch[0]) != symbolMap_.end()) << std::endl;
    return charMap.find(ch[0]) != charMap.end();
}

void TextRenderCommand::putParams(std::wstring text 
        ,float left , float bottom
        ,TextPaint &paint){
    textColor_ = paint.textColor;
    
    vertexCount_ = 6 * text.length();
    const int attrCount = 3 + 2;
    int requestSize = vertexCount_ * attrCount * sizeof(float);
    int allocateSize = 0;
    // Logi("command" , "allocator size = %d" , requestSize);
    VRamManager::getInstance().fetchVideoMemory(requestSize , 
        vbo_ ,vao_, vboOffset_ , allocateSize);

    if(vbo_ <= 0){
        return;
    }
    // Logi("command" , "allocator vbo = %d" , vbo_);

    float x = left;
    float y = bottom;

    std::vector<float> buf(vertexCount_ * attrCount);
    const int attrPerChar = 30;

    auto textRenderHelper = engine_->textRenderHelper_;
    for(int i = 0 ; i < text.length() ;i++){
        wchar_t ch = text[i];
        auto charInfoPtr = textRenderHelper->findCharInfo(ch);
        if(charInfoPtr == nullptr){
            continue;
        }

        fontTextureId_ = charInfoPtr->textureId;

        float charRealWidth = charInfoPtr->width * paint.textSizeScale;
        float charRealHeight = charInfoPtr->height * paint.textSizeScale;
        // Logi("text_render" , "x y %f %f charRealWidth %f , charRealHeight %f" ,
        //     x, y ,charRealWidth,charRealHeight);

        float texLeft = charInfoPtr->textureCoords[0];
        float texTop = charInfoPtr->textureCoords[1];
        float texRight = charInfoPtr->textureCoords[2];
        float texBottom = charInfoPtr->textureCoords[3];

        //eg: 一 need a offset in y ax
       
        float offsetY = calOffsetY(charInfoPtr , paint.textSizeScale);

        //v1
        buf[i * attrPerChar + 0] = x;
        buf[i * attrPerChar + 1] = y + offsetY;
        buf[i * attrPerChar + 2] = 1.0f;
        buf[i * attrPerChar + 3] = texLeft;
        buf[i * attrPerChar + 4] = texBottom;
        
        //v2
        buf[i * attrPerChar + 5] = x + charRealWidth;
        buf[i * attrPerChar + 6] = y + offsetY;
        buf[i * attrPerChar + 7] = 1.0f;
        buf[i * attrPerChar + 8] = texRight;
        buf[i * attrPerChar + 9] = texBottom;

        //v3
        buf[i * attrPerChar + 10] = x + charRealWidth;
        buf[i * attrPerChar + 11] = y + offsetY + charRealHeight;
        buf[i * attrPerChar + 12] = 1.0f;
        buf[i * attrPerChar + 13] = texRight;
        buf[i * attrPerChar + 14] = texTop;

        //v4
        buf[i * attrPerChar + 15] = x;
        buf[i * attrPerChar + 16] = y + offsetY;
        buf[i * attrPerChar + 17] = 1.0f;
        buf[i * attrPerChar + 18] = texLeft;
        buf[i * attrPerChar + 19] = texBottom;

        //v5
        buf[i * attrPerChar + 20] = x + charRealWidth;
        buf[i * attrPerChar + 21] = y + offsetY + charRealHeight;
        buf[i * attrPerChar + 22] = 1.0f;
        buf[i * attrPerChar + 23] = texRight;
        buf[i * attrPerChar + 24] = texTop;

        //v6
        buf[i * attrPerChar + 25] = x;
        buf[i * attrPerChar + 26] = y + offsetY + charRealHeight;
        buf[i * attrPerChar + 27] = 1.0f;
        buf[i * attrPerChar + 28] = texLeft;
        buf[i * attrPerChar + 29] = texTop;

        x += charRealWidth + paint.gapSize;
    }//end for i

    glBindVertexArray(vao_);
    // Logi("cmd" , "vboOffset_ = %d",vboOffset_);
    glBindBuffer(GL_ARRAY_BUFFER , vbo_);
    glBufferSubData(GL_ARRAY_BUFFER , vboOffset_ , 
        buf.size() * sizeof(float) , buf.data());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , 5 * sizeof(float) , 
        reinterpret_cast<void *>(vboOffset_));
    glVertexAttribPointer(1 , 2 , GL_FLOAT , GL_FALSE , 5 * sizeof(float) , 
        reinterpret_cast<void *>(vboOffset_ + 3 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER , 0);
    glBindVertexArray(0);
}


void TextRenderCommand::runCommands(){
    if(fontTextureId_ <= 0){
        return;
    }

    //打开混合模式 文字有透明度
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA);

    auto shader = engine_->textRenderHelper_->textRenderShader_;
    shader.useShader();
    shader.setUniformMat3("transMat" , engine_->normalMatrix_);
    shader.setUniformVec4("textColor" , textColor_);
    
    glBindVertexArray(vao_);
    // Logi("cmmmand" , "vbo id %d vao id %d" , vbo_ , vao_);
    glBindBuffer(GL_ARRAY_BUFFER , vbo_);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fontTextureId_);
    shader.setUniformInt("fontTexture" , 0);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , 5 * sizeof(float) , 
        reinterpret_cast<void *>(vboOffset_));
    glVertexAttribPointer(1 , 2 , GL_FLOAT , GL_FALSE , 5 * sizeof(float) , 
        reinterpret_cast<void *>(vboOffset_ + 3 * sizeof(float)));
    glDrawArrays(GL_TRIANGLES , 0 , vertexCount_);

    glBindBuffer(GL_ARRAY_BUFFER , 0);
    glBindVertexArray(0);
}

//计算文本顶点数据
void TextRenderCommand::fillTextVertData(std::wstring &text , float left , float bottom,
        TextPaint &paint){
    auto textRenderHelper = engine_->textRenderHelper_;

    float x = left;
    float y = bottom;

    vertexCount_ = 6 * text.length();

    for(int i = 0; i < text.size() ;i++) {
        wchar_t ch = text[i];
        auto charInfoPtr = textRenderHelper->findCharInfo(ch);
        if(charInfoPtr == nullptr){
            continue;
        }

        float realWidth = charInfoPtr->width * paint.textSizeScale;
        float realHeight = charInfoPtr->height * paint.textSizeScale;

        x += realWidth + paint.gapSize;
    }//end for i;
}