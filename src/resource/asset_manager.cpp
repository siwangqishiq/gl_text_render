
#include "asset_manager.hpp"
#include "log.hpp"

std::shared_ptr<AssetManager> AssetManager::getInstance(){
    static std::shared_ptr<AssetManager> instance_;
    if(instance_ == nullptr){
        instance_ = std::make_shared<AssetManager>();
    }

    return instance_;
}

std::wstring AssetManager::readTextFile(std::string path){
    std::string filePath = assetRootDir() + path;
    // filePath = "D:\\code\\gl_text_render\\assets\\test.txt";
    Logi("asset" , "read file path %s" , filePath.c_str());
    return readFileAsWstring(filePath.c_str());
}

std::wstring AndroidAssetManager::readFileToText(std::string path){
    return L"android_xxx";
}

