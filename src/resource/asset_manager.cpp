
#include "asset_manager.hpp"
#include "log.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.hpp"

std::shared_ptr<AssetManager> AssetManager::getInstance(){
    static std::shared_ptr<AssetManager> instance_;
    if(instance_ == nullptr){
        #ifdef __ANDROID__
        instance_ = std::make_shared<AndroidAssetManager>();
        #else
        instance_ = std::make_shared<AssetManager>();
        #endif
    }
    return instance_;
}

std::wstring AssetManager::readTextFile(std::string path){
    std::string filePath = assetRootDir() + path;
    Logi("asset" , "read file path %s" , filePath.c_str());
    return readFileAsWstring(filePath.c_str());
}

uint8_t* AssetManager::readTextureFile(std::string path ,TextureFileConfig &fileConfig){
    std::string filePath = assetRootDir() + path;
    Logi("asset" , "read file path %s" , filePath.c_str());

    uint8_t *data = stbi_load(filePath.c_str() ,
                        &fileConfig.width , 
                        &fileConfig.height , &fileConfig.channel , 0);
    return data;
}

std::wstring AndroidAssetManager::readFileToText(std::string path){
    return L"android_xxx";
}

