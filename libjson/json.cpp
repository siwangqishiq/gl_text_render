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

std::shared_ptr<JsonObject> JsonObject::getJsonObject(std::string key){
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

int JsonObjectParser::doParseObject(std::wstring &jsonStr ,int beginPostion){
    // std::cout << "setBegin Pos " << beginPostion << std::endl;
    int readIndex = beginPostion;
    while(readIndex < jsonStr.size()){
        auto ch = jsonStr[readIndex];
        
        // std::wcout << "read :" << ch << " state " << state << std::endl;
        if(state == ParserState::INIT){//初始状态
            switch (ch){
                case L'{':
                    state = WAIT_KEY;
                    createNewJsonObject();
                    break;
                case L' ':
                case L'\r':
                case L'\t':
                case L'\n':
                    break;
                default:
                    std::cout << "parse json error in position " << readIndex << std::endl;
                    return -1;
            }//end switch
        }else if(state == ParserState::WAIT_KEY){//等待读取key
            switch (ch){
                case L' ':
                case L'\r':
                case L'\t':
                case L'\n':
                    break;
                case L'\"':
                    state = READ_KEY;
                    keyBuf = L"";
                    break;
                default:
                    std::cout << "parse json error in position " << readIndex << std::endl;
                    return -1;
            }//end switch
        }else if(state == ParserState::READ_KEY){//解析key
            switch (ch){
                case L'\"':
                    state = END_READ_KEY;
                    currentKey = keyBuf;
                    // std::wcout << "read key -> " << currentKey << std::endl;
                    break;
                default:
                    keyBuf += ch;
                    break;
            }//end switch
        }else if(state == ParserState::END_READ_KEY){//等待读到冒号
            switch (ch){
                case L' ':
                case L'\t':
                case L'\n':
                    break;
                case L':':
                    state = WAIT_VALUE;
                    break;
                default:
                    std::cout << "parse json error in position " << readIndex << std::endl;
                    return -1;
            }//end switch
        }else if(state == ParserState::WAIT_VALUE){//等待读取value
            switch(ch){
                case L' ':
                case L'\r':
                case L'\t':
                case L'\n':
                    break;
                case L'\"'://value是字符串
                    state = READ_STRING_VALUE;
                    valueBuf = L"";
                    break;
                case L'{'://子JsonObject
                    //解析子Object
                    // readIndex--;//将读取坐标左移一位
                    {
                        JsonObjectParser childParser;
                        if(childParser.doParseObject(jsonStr , readIndex) >= 0){
                            state = END_READ_VALUE;
                            if(onReadJsonObjectItem(currentKey ,childParser.currentJsonObject, readIndex, childParser.readEndPosition) < 0){
                                return -1;
                            }
                        }else{
                            std::cout << "parse child object error" <<std::endl;
                            return -1;
                        }
                    }
                    break;
                default:
                    // std::cout << "enter read value state" << std::endl;
                    state = READ_VALUE;
                    valueBuf = ch;
                    break;
            }//end switch
        }else if(state == ParserState::READ_STRING_VALUE){//等待读取value
            if(ch == L'\"'){
                state = END_READ_VALUE;
                if(onReadStringItem(currentKey , valueBuf , readIndex) < 0){
                    std::cout << "parse json error in position " << readIndex << std::endl;
                    return -1;
                }
            }else{
                valueBuf += ch;
            }
        } else if(state == ParserState::READ_VALUE){ // 读取int or float
            switch (ch){
                case L' ':
                case L'\r':
                case L'\t':
                case L'\n':
                    break;
                case L','://
                    state = END_READ_VALUE;
                    if(onReadNumItem(currentKey , valueBuf , readIndex) < 0){
                        return -1;
                    }
                    state = WAIT_KEY;
                    break;
                case L'}':
                    state = END_READ_VALUE;
                    // readIndex--;
                    break;
                default:
                    valueBuf += ch;
                    // std::wcout << "valuebuf " << valueBuf << std::endl;
                    break;
            }//end switch
        } else if(state == ParserState::END_READ_VALUE){
            switch (ch){
                case L' ':
                case L'\r':
                case L'\t':
                case L'\n':
                    break;
                case L','://
                    state = WAIT_KEY;
                    break;
                case L'}':
                    state = END;
                    readEndPosition = readIndex;
                    // if(onReadNumItem(currentKey , valueBuf , readIndex) < 0){
                    //     return -1;
                    // }
                    break;
                default:
                    break;
            }//end switch
        } else if(state == ParserState::END){
            // std::cout << "quit " << readEndPosition << std::endl;
            return 0;
        }
        //end if

        readIndex++;
    }//end while

    return 0;
}

int JsonObjectParser::createNewJsonObject(){
    currentJsonObject = JsonObject::create();
    return 0;
}

int JsonObjectParser::onReadStringItem(std::wstring &key , std::wstring &value , int &position){
    if(currentJsonObject == nullptr){
        std::cout << "onReadStringItem parse json error in position " << position << std::endl;
        return -1;
    }

    if(key == L""){
        return 0;
    }

    // std::wcout << key << " = " << value << std::endl;
    currentJsonObject->putString(ToByteString(key) , value);
    
    key = L"";
    return 0;
}

int JsonObjectParser::onReadNumItem(std::wstring &key , std::wstring &value , int &position){
    if(currentJsonObject == nullptr){
        std::cout << "onReadNumItem parse json error in position " << position << std::endl;
        return -1;
    }

    if(key == L""){
        return 0;
    }
    
    // std::wcout <<"onReadNumItem " << key << " = " << value << std::endl;
    if(isFloatValue(value)){ //按浮点数据处理
        currentJsonObject->putFloat(ToByteString(key) , strToFloat(value));
    }else{ //按整型数据处理
        currentJsonObject->putInt(ToByteString(key) , strToInt(value));
    }

    key = L"";
    std::wcout <<"onReadNumItem currentKey " << currentKey << this << std::endl;
    return 0;
}

int JsonObjectParser::onReadJsonObjectItem(std::wstring &key , 
        std::shared_ptr<JsonObject> jsonObject , int &position , int offsetPosition){
    if(currentJsonObject == nullptr){
        std::cout << "onReadJsonObjectItem parse json error in position " << position << std::endl;
        return -1;
    }

    if(jsonObject == nullptr){
        std::cout << "onReadJsonObjectItem parse json error in position " << position << std::endl;
        return -1;
    }

    if(key == L""){
        return 0;
    }

    std::wcout <<"onReadJsonObjectItem " << key << " = " << jsonObject->toJsonString() << std::endl;
    currentJsonObject->putJsonObject(ToByteString(key) , jsonObject);

    position = offsetPosition;
    key == L"";

    std::wcout <<"onReadJsonObjectItem currentKey " << currentKey << this << std::endl;

    return 0;
}

std::shared_ptr<JsonObject> JsonObjectParser::parseJsonObject(std::wstring &jsonStr){
    if(doParseObject(jsonStr , 0) >= 0){
        std::cout << "map size : " << currentJsonObject->size() <<std::endl;
        return currentJsonObject;
    }

    std::cout << "parse json error" << std::endl;
    return JsonObject::create();
}

std::shared_ptr<JsonArray> JsonObjectParser::parseJsonArray(std::wstring &jsonArrayStr){
    return nullptr;
}
