
/**
 * @brief  
 * resource access 
 * 
 */
#pragma once

#include <string>
#include <memory>
#include "log.hpp"
#include <fstream>
#include <streambuf>
#include <codecvt>

const int TEXTURE_FILE_CHANNEL_UNKNOW = -1;
const int TEXTURE_FILE_CHANNEL_RGB = 3;
const int TEXTURE_FILE_CHANNEL_ARGB = 4;

struct TextureFileConfig{
    int width = 0;
    int height = 0;
    int channel = TEXTURE_FILE_CHANNEL_UNKNOW;
};

class AndroidAssetManager;

class AssetManager{
public:
    static std::shared_ptr<AssetManager> getInstance();

    static std::shared_ptr<AssetManager> instance_;

    // read text file
    virtual std::wstring readTextFile(std::string path);

    // read png file 
    virtual uint8_t* readTextureFile(std::string path ,TextureFileConfig &fileConfig);

    AssetManager(){
        Logi("asset_manager" , "asset manager construct");
    }

    ~AssetManager(){
        Logi("asset_manager" , "asset manager deconstruct");
    }

protected:
    std::string assetRootDir() {
        return "../assets/";
    }

private:
     inline std::wstring toWideString(const std::string& input){
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.from_bytes(input);
    }

    inline std::string toByteString(const std::wstring& input){
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.to_bytes(input);
    }

    inline std::wstring readFileAsWstring(const char *path){
        std::ifstream file(path);
        std::string str((std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());
        return toWideString(str);
    }
};

/**
 * @brief 
 * for android asset resouce access
 * 
 */
class AndroidAssetManager : public AssetManager{
public:
    virtual std::wstring readFileToText(std::string path);
};
