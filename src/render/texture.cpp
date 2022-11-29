#include "texture.hpp"
#include "glheader.hpp"
#include "resource/asset_manager.hpp"

std::shared_ptr<TextureManager> TextureManager::getInstance(){
    static std::shared_ptr<TextureManager> instance_;
    if(instance_ == nullptr){
        instance_ = std::make_shared<TextureManager>();
    }
    return instance_;
}

//将纹理传送至GPU
std::shared_ptr<TextureInfo> TextureManager::loadTexture(std::string textureFilePath){
    Logi(TAG , "load texture %s" , textureFilePath.c_str());
    
    TextureFileConfig fileConfig;
    std::unique_ptr<uint8_t> data = AssetManager::getInstance()->readTextureFile(textureFilePath ,fileConfig);

    int format = TEXTURE_FILE_CHANNEL_UNKNOW;
    if(fileConfig.channel == TEXTURE_FILE_CHANNEL_RGB){
        format = GL_RGB;
    }else if(fileConfig.channel == TEXTURE_FILE_CHANNEL_ARGB){
        format = GL_RGBA;
    }else if(fileConfig.channel = TEXTURE_FILE_CHANNEL_RGBA){
        format = GL_RGBA;
    }
    
    if(format == TEXTURE_FILE_CHANNEL_UNKNOW){
        return nullptr;
    }

    unsigned int tId = -1;
    glGenTextures(1 , &tId);
    if(tId <= 0 ){
        return nullptr;
    }

    glBindTexture(GL_TEXTURE_2D , tId);
    glTexParameterf(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D , GL_TEXTURE_WRAP_S , GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D , GL_TEXTURE_WRAP_T , GL_CLAMP_TO_EDGE);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, format, 
        fileConfig.width, 
        fileConfig.height, 0, 
        format, GL_UNSIGNED_BYTE, data.get());
    glBindTexture(GL_TEXTURE_2D , 0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    auto textureInfo = std::make_shared<TextureInfo>();
    textureInfo->name = textureFilePath;
    textureInfo->textureId = tId;
    textureInfo->width = fileConfig.width;
    textureInfo->height = fileConfig.height;

    //add pool
    textureBank_[textureInfo->name] = textureInfo;
    
    Logi(TAG , "load texture id : %d , width : %d , height : %d" , 
        textureInfo->textureId,
        textureInfo->width,
        textureInfo->height);
    
    return textureInfo;
}

std::shared_ptr<TextureInfo> TextureManager::acquireTexture(std::string textureFilePath){
    if(textureBank_.find(textureFilePath) != textureBank_.end()){
        return textureBank_[textureFilePath];
    }
    return loadTexture(textureFilePath);
}

