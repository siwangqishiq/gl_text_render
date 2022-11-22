
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

class AndroidAssetManager;

class AssetManager{
public:
    static std::shared_ptr<AssetManager> getInstance();

    static std::shared_ptr<AssetManager> instance_;

    virtual std::wstring readTextFile(std::string path);

    AssetManager(){
        Logi("asset_manager" , "asset manager construct");
    }

    ~AssetManager(){
        Logi("asset_manager" , "asset manager deconstruct");
    }

    inline std::wstring toWideString(const std::string& input){
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.from_bytes(input);
    }

    inline std::string toByteString(const std::wstring& input){
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.to_bytes(input);
    }

    std::wstring readFileAsWstring(const char *path){
        std::ifstream file(path);
        std::string str((std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());
        return toWideString(str);
    }

protected:
    std::string assetRootDir() {
        return "../assets/";
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
