//
// json解析库
//
#ifndef __JSON_H__
#define __JSON_H__

#include <string>
#include <map>
#include <memory>
#include <vector>

class JsonObject;
class JsonArray;

class IJson{
public:
    virtual std::string toJsonString() = 0;
    virtual std::shared_ptr<JsonObject> toJsonObject() = 0;
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

    JsonValue(int val) : intValue_(val){
        valueType = JsonValueType::Int;
    }

    JsonValue(float val) : floatValue_(val){
        valueType = JsonValueType::Float;
    }

    JsonValue(std::string val) : strValue_(val){
        valueType = JsonValueType::String;
    }

    JsonValue(std::shared_ptr<JsonObject> val) {
        jsonObjValue_ = val;
        valueType = JsonValueType::JSONOBJ;
    }

    int getIntValue(){
        return intValue_;
    }

    float getFloatValue() {
        return floatValue_;
    }

    std::string getStringValue() {
        return strValue_;
    }

    std::shared_ptr<JsonObject> getJsonObjectValue(){
        return jsonObjValue_;
    }

    std::shared_ptr<JsonArray> getJsonArrayValue(){
        return jsonArrayValue_;
    }

    std::string displayJsonString();
private:
    int intValue_ = 0;
    float floatValue_;
    std::string strValue_;
    std::shared_ptr<JsonObject> jsonObjValue_;
    std::shared_ptr<JsonArray> jsonArrayValue_;
};

///
//json数组
//
class JsonArray : public IJson{
public:
    virtual std::string toJsonString() override;

    virtual std::shared_ptr<JsonObject> toJsonObject() override;

private:
    std::vector<IJson> arrayData_;
};

// json对象
class JsonObject :public IJson{
public:
    JsonObject();

    virtual std::string toJsonString() override;

    virtual std::shared_ptr<JsonObject> toJsonObject() override;

    void putInt(std::string key , int value);
    void putFloat(std::string key , float value);
    void putString(std::string key , std::string value);
    void putJsonObject(std::string key , std::shared_ptr<JsonObject> value);

    void put(std::string key , int value);
    void put(std::string key , float value);
    void put(std::string key , std::string value);
    void put(std::string key , std::shared_ptr<JsonObject> value);

    int getInt(std::string key);
    float getFloat(std::string key);
    std::string getString(std::string key);
    std::shared_ptr<JsonObject> getJsonObject(std::string &key);
private:
    std::map<std::string , std::shared_ptr<JsonValue>> mapData_;

    void parseJsonString(std::string &jsonStr);

    std::string displayJsonStringValue(std::string originValue);
};

#endif


