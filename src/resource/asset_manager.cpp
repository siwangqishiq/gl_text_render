
#include "asset_manager.hpp"
#include "log.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

int AssetManager::readTextureFile(std::string path ,long &filesize, uint8_t *data){
    std::string filePath = assetRootDir() + path;
    Logi("asset" , "read file path %s" , filePath.c_str());
    
    return 0;
}

std::wstring AndroidAssetManager::readFileToText(std::string path){
    return L"android_xxx";
}

