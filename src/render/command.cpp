#include "command.hpp"
#include "render.hpp"
#include "log.hpp"
#include "vram.hpp"

void TextRenderCommand::putParams(std::wstring text , float left , float bottom){
    float charWidth = 20.0f;
    float charHeight = 25.0f;

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
    for(int i = 0 ; i < text.length() ;i++){
        //v1
        buf[i * attrPerChar + 0] = x;
        buf[i * attrPerChar + 1] = y;
        buf[i * attrPerChar + 2] = 1.0f;
        buf[i * attrPerChar + 3] = 0.0f;
        buf[i * attrPerChar + 4] = 0.0f;
        
        //v2
        buf[i * attrPerChar + 5] = x + charWidth;
        buf[i * attrPerChar + 6] = y;
        buf[i * attrPerChar + 7] = 1.0f;
        buf[i * attrPerChar + 8] = 0.0f;
        buf[i * attrPerChar + 9] = 0.0f;

        //v3
        buf[i * attrPerChar + 10] = x + charWidth;
        buf[i * attrPerChar + 11] = y + charHeight;
        buf[i * attrPerChar + 12] = 1.0f;
        buf[i * attrPerChar + 13] = 0.0f;
        buf[i * attrPerChar + 14] = 0.0f;

        //v4
        buf[i * attrPerChar + 15] = x;
        buf[i * attrPerChar + 16] = y;
        buf[i * attrPerChar + 17] = 1.0f;
        buf[i * attrPerChar + 18] = 0.0f;
        buf[i * attrPerChar + 19] = 0.0f;

        //v5
        buf[i * attrPerChar + 20] = x + charWidth;
        buf[i * attrPerChar + 21] = y + charHeight;
        buf[i * attrPerChar + 22] = 1.0f;
        buf[i * attrPerChar + 23] = 0.0f;
        buf[i * attrPerChar + 24] = 0.0f;

        //v6
        buf[i * attrPerChar + 25] = x;
        buf[i * attrPerChar + 26] = y + charHeight;
        buf[i * attrPerChar + 27] = 1.0f;
        buf[i * attrPerChar + 28] = 0.0f;
        buf[i * attrPerChar + 29] = 0.0f;

        x += charWidth;
    }//end for i

    glBindVertexArray(vao_);
    // Logi("cmd" , "vboOffset_ = %d",vboOffset_);
    glBindBuffer(GL_ARRAY_BUFFER , vbo_);
    glBufferSubData(GL_ARRAY_BUFFER , vboOffset_ , 
        buf.size() * sizeof(float) , buf.data());
    // glEnableVertexAttribArray(0);
    // glEnableVertexAttribArray(1);
    // glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , 5 * sizeof(float) , 
    //     (void *)(vboOffset_));
    // glVertexAttribPointer(1 , 2 , GL_FLOAT , GL_FALSE , 5 * sizeof(float) , 
    //     (void *)(vboOffset_ + 3 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER , 0);
    glBindVertexArray(0);
}

void TextRenderCommand::runCommands(){
    auto shader = engine_->textRenderHelper_->textRenderShader_;
    shader.useShader();
    shader.setUniformMat3("transMat" , engine_->normalMatrix_);
    
    glBindVertexArray(vao_);
    // Logi("cmmmand" , "vbo id %d vao id %d" , vbo_ , vao_);
    glBindBuffer(GL_ARRAY_BUFFER , vbo_);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , 5 * sizeof(float) , 
        reinterpret_cast<void *>(vboOffset_));
    glVertexAttribPointer(1 , 2 , GL_FLOAT , GL_FALSE , 5 * sizeof(float) , 
        reinterpret_cast<void *>(vboOffset_ + 3 * sizeof(float)));

    // Logi("cmd" , "render vertex count %d" , vertexCount_);
    glDrawArrays(GL_TRIANGLE_FAN , 0 , vertexCount_);
}