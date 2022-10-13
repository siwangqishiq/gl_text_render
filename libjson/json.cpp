#include "json.h"

std::wstring JsonValue::displayJsonString(){
    std::wstring result;
    switch (valueType){
        case Int:
            result = std::to_wstring(intValue_);
            break;
        case Float:
            result = std::to_wstring(floatValue_);
            break;
        case String:
            result += L"\"";
            result += strValue_;
            result += L"\"";
            break;
        case JSONOBJ:
            result = jsonObjValue_->toJsonString();
            break;
        case JSONARRAY:
            result = jsonArrayValue_->toJsonString();
            break;
        default:
            break;
    }//end switch
    
    return result;
}

JsonObject::JsonObject(){
}

void JsonObject::putInt(std::string key , int value){
    mapData_[key] = std::make_shared<JsonValue>(value);
}

int JsonObject::getInt(std::string key){
    std::shared_ptr<JsonValue> value = mapData_[key];
    if(value != nullptr || value->valueType == JsonValueType::Int){
        return value->getIntValue();
    }else{
        return 0;
    }
}

void JsonObject::putFloat(std::string key , float value){
    mapData_[key] = std::make_shared<JsonValue>(value);
}

float JsonObject::getFloat(std::string key){
    std::shared_ptr<JsonValue> value = mapData_[key];
    if(value != nullptr || value->valueType == JsonValueType::Float){
        return value->getFloatValue();
    }else{
        return 0.0f;
    }
}

void JsonObject::putString(std::string key , std::wstring value){
    mapData_[key] = std::make_shared<JsonValue>(value);
}

std::wstring JsonObject::getString(std::string key){
    std::shared_ptr<JsonValue> value = mapData_[key];
    if(value != nullptr || value->valueType == JsonValueType::String){
        return value->getStringValue();
    }else{
        return L"";
    }
}

void JsonObject::putJsonObject(std::string key , std::shared_ptr<JsonObject> value){
    mapData_[key] = std::make_shared<JsonValue>(value);
}

void JsonObject::putJsonArray(std::string key , std::shared_ptr<JsonArray> value){
    mapData_[key] = std::make_shared<JsonValue>(value);
}

std::shared_ptr<JsonObject> JsonObject::getJsonObject(std::string &key){
    std::shared_ptr<JsonValue> value = mapData_[key];
    if(value != nullptr || value->valueType == JsonValueType::String){
        return value->getJsonObjectValue();
    }else{
        return nullptr;
    }
}

std::wstring JsonObject::toJsonString(){
    std::wstring jsonString;
    jsonString += L"{";
    int index = 0;
    for(auto &entry : mapData_){
        jsonString += displayJsonStringValue(ToWideString(entry.first));
        jsonString += L":";

        // std::wcout << L"value type: " << entry.second->valueType << std::endl;

        jsonString += entry.second->displayJsonString();

        if(index < mapData_.size() - 1){
            jsonString += L",";
        }
        index++;
    }//end for each
    jsonString += L"}";
    return jsonString;
}

std::wstring JsonObject::displayJsonStringValue(std::wstring originValue){
    std::wstring result = L"";
    result += L"\"";
    result += originValue;
    result += L"\"";
    return result;
}

std::wstring JsonArray::toJsonString(){
    std::wstring jsonArrayString;
    jsonArrayString += L"[";
    int index = 0;
    for(int i = 0 ; i< arrayData_.size() ;i++){
        if(i != 0){
            jsonArrayString += L",";
        }
        std::shared_ptr<JsonValue> value = arrayData_[i];
        jsonArrayString += value->displayJsonString();
    }//end for i

    jsonArrayString += L"]";
    return jsonArrayString;
}

void JsonArray::pushInt(int value){
    arrayData_.push_back(std::make_shared<JsonValue>(value));
}

void JsonArray::pushFloat(float value){
    arrayData_.push_back(std::make_shared<JsonValue>(value));
}

void JsonArray::pushString(std::wstring value){
    arrayData_.push_back(std::make_shared<JsonValue>(value));
}

void JsonArray::pushJsonObject(std::shared_ptr<JsonObject> value){
    arrayData_.push_back(std::make_shared<JsonValue>(value));
}
