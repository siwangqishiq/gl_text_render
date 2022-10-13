//
// json解析库
//
#ifndef __JSON_H__
#define __JSON_H__

#include <iostream>
#include <fstream>
#include <codecvt>
#include <streambuf>
#include <locale>
#include <string>
#include <map>
#include <memory>
#include <vector>

inline std::wstring ToWideString(const std::string& input){
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(input);
}

inline std::string ToByteString(const std::wstring& input){
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(input);
}

inline void WriteStringToFile(const char *path , std::wstring content){
    std::ofstream file(path);
    file << ToByteString(content);
    file.close();
}

inline std::wstring ReadTextFileAsWstring(const char *path){
    std::ifstream file(path);
    std::string str((std::istreambuf_iterator<char>(file)),
                 std::istreambuf_iterator<char>());
    return ToWideString(str);
}

class JsonObject;
class JsonArray;

class IJson{
public:
    virtual std::wstring toJsonString() = 0;
};

enum JsonValueType{
    Int,
    Float,
    String,
    JSONOBJ,
    JSONARRAY,
    None
};

class JsonValue{

public:
    JsonValueType valueType = None;

    ~JsonValue(){
    }

    JsonValue(int val) : intValue_(val){
        valueType = JsonValueType::Int;
    }

    JsonValue(float val) : floatValue_(val){
        valueType = JsonValueType::Float;
    }

    JsonValue(std::wstring val) : strValue_(val){
        valueType = JsonValueType::String;
    }

    JsonValue(std::shared_ptr<JsonObject> val) {
        jsonObjValue_ = val;
        valueType = JsonValueType::JSONOBJ;
    }

    JsonValue(std::shared_ptr<JsonArray> val) {
        jsonArrayValue_ = val;
        valueType = JsonValueType::JSONARRAY;
    }

    int getIntValue(){
        return intValue_;
    }

    float getFloatValue() {
        return floatValue_;
    }

    std::wstring getStringValue() {
        return strValue_;
    }

    std::shared_ptr<JsonObject> getJsonObjectValue(){
        return jsonObjValue_;
    }

    std::shared_ptr<JsonArray> getJsonArrayValue(){
        return jsonArrayValue_;
    }

    std::wstring displayJsonString();
private:
    int intValue_ = 0;
    float floatValue_;
    std::wstring strValue_;
    std::shared_ptr<JsonObject> jsonObjValue_;
    std::shared_ptr<JsonArray> jsonArrayValue_;
};

///
/// json对象
///
class JsonObject :public IJson{
public:
    JsonObject();

    ~JsonObject(){
        // std::cout << "destory json object" << std::endl;
    }

    static std::shared_ptr<JsonObject> create(){
        return std::make_shared<JsonObject>();
    }

    virtual std::wstring toJsonString() override;

    void putInt(std::string key , int value);
    void putFloat(std::string key , float value);
    void putString(std::string key , std::wstring value);
    void putJsonObject(std::string key , std::shared_ptr<JsonObject> value);
    void putJsonArray(std::string key , std::shared_ptr<JsonArray> value);

    void put(std::string key , int value){
        putInt(key , value);
    }
    
    void put(std::string key , float value){
        putFloat(key , value);
    }

    void put(std::string key , std::wstring value){
        putString(key , value);
    }

    void put(std::string key , std::shared_ptr<JsonObject> value){
        putJsonObject(key , value);
    }

    void put(std::string key , std::shared_ptr<JsonArray> value){
        putJsonArray(key , value);
    }

    int getInt(std::string key);
    float getFloat(std::string key);
    std::wstring getString(std::string key);
    std::shared_ptr<JsonObject> getJsonObject(std::string &key);
private:
    std::map<std::string , std::shared_ptr<JsonValue>> mapData_;

    void parseJsonString(std::wstring &jsonStr);

    std::wstring displayJsonStringValue(std::wstring originValue);
};

///
//json数组
//
class JsonArray : public IJson{
public:
    JsonArray(){
    }

    ~JsonArray(){
    }

    static std::shared_ptr<JsonArray> create(){
        return std::make_shared<JsonArray>();
    }

    void push(int value){
        pushInt(value);
    }

    void push(float value){
        pushFloat(value);
    }

    void push(std::wstring value){
        pushString(value);
    }

    void push(std::shared_ptr<JsonObject> value){
        pushJsonObject(value);
    }

    int size(){
        return arrayData_.size();
    }

    std::shared_ptr<JsonValue> get(int pos){
        return arrayData_[pos];
    }

    void pushInt(int value);
    void pushFloat(float value);
    void pushString(std::wstring value);
    void pushJsonObject(std::shared_ptr<JsonObject> value);

    virtual std::wstring toJsonString() override;
private:
    std::vector<std::shared_ptr<JsonValue>> arrayData_;
};

#endif


