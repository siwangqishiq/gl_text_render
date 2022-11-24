
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


#ifdef __ANDROID__

std::wstring AndroidAssetManager::readTextFile(std::string path){
    std::string filePath = path;
    AAsset *file = AAssetManager_open(AndroidAssetManagerInstance , filePath.c_str(), AASSET_MODE_BUFFER);
    if(file == nullptr){
        Logi("asset","open asset file : %s failed" , filePath.c_str());
        return L"";
    }

    Logi("asset" , "get asset file");
    size_t fileSize = AAsset_getLength(file);

    // std::unique_ptr<char []> fileContentBuf = std::unique_ptr<char []>(new char[fileSize + 1]);
    char *fileContentBuf = new char[fileSize + 1];
    AAsset_read(file , fileContentBuf , fileSize);
    fileContentBuf[fileSize] = '\0';
    AAsset_close(file);

    LOGI("file content = %s" , fileContentBuf);
    std::wstring contentStr = toWideString(std::string(fileContentBuf));
    delete[] fileContentBuf;

    return contentStr;
}

#endif

