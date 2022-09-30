

#include "json.h"

std::string JsonValue::displayJsonString(){
    std::string result;
    switch (valueType){
        case Int:
            result = std::to_string(intValue_);
            break;
        case Float:
            result = std::to_string(floatValue_);
            break;
        case String:
            result += "\"";
            result += strValue_;
            result += "\"";
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

void JsonObject::put(std::string key , int value){
    putInt(key , value);
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

void JsonObject::put(std::string key , float value){
    putFloat(key , value);
}

float JsonObject::getFloat(std::string key){
    std::shared_ptr<JsonValue> value = mapData_[key];
    if(value != nullptr || value->valueType == JsonValueType::Float){
        return value->getFloatValue();
    }else{
        return 0.0f;
    }
}

void JsonObject::putString(std::string key , std::string value){
    mapData_[key] = std::make_shared<JsonValue>(value);
}

void JsonObject::put(std::string key ,std::string value){
    putString(key , value);
}

std::string JsonObject::getString(std::string key){
    std::shared_ptr<JsonValue> value = mapData_[key];
    if(value != nullptr || value->valueType == JsonValueType::String){
        return value->getStringValue();
    }else{
        return "";
    }
}

void JsonObject::putJsonObject(std::string key , std::shared_ptr<JsonObject> value){
    mapData_[key] = std::make_shared<JsonValue>(value);
}

void JsonObject::put(std::string key , std::shared_ptr<JsonObject> value){
    putJsonObject(key , value);
}

std::shared_ptr<JsonObject> JsonObject::getJsonObject(std::string &key){
    std::shared_ptr<JsonValue> value = mapData_[key];
    if(value != nullptr || value->valueType == JsonValueType::String){
        return value->getJsonObjectValue();
    }else{
        return nullptr;
    }
}


std::string JsonObject::toJsonString(){
    std::string jsonString;
    jsonString += "{";
    int index = 0;
    for(auto &entry : mapData_){
        jsonString += displayJsonStringValue(entry.first);
        jsonString += ":";
        jsonString += entry.second->displayJsonString();

        if(index < mapData_.size() - 1){
            jsonString += ",";
        }
        index++;
    }//end for each
    jsonString += "}";
    return jsonString;
}

std::shared_ptr<JsonObject> JsonObject::toJsonObject(){
    return nullptr;
}

void JsonObject::parseJsonString(std::string &jsonStr){
    
}

std::string JsonObject::displayJsonStringValue(std::string originValue){
    std::string result ="";
    result += "\"";
    result += originValue;
    result += "\"";
    return result;
}

std::string JsonArray::toJsonString(){
    return "";
}

std::shared_ptr<JsonObject> JsonArray::toJsonObject(){
    return nullptr;
}
