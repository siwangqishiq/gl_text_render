#include <iostream>
#include "json.h"

void testJsonObjectPut();
void testJsonArrayPut();

int main(){
    // std::string data = "{\"name\":\"毛利兰\" , \"age\":17}";
    // testJsonObjectPut();
    testJsonArrayPut();
    return 0;
}

void testJsonArrayPut(){
    auto jsonArray = JsonArray::create();
    for(int i = 0;i<10;i++){
        std::wstring str = L"id=";
        str += std::to_wstring(i);

        jsonArray->pushString(str);
    }

    auto childList = JsonArray::create();
    for(int i = 0;i<10;i++){
        std::wstring str = L"毛利兰_";
        str += std::to_wstring(i);

        auto jObj = JsonObject::create();
        childList->push(jObj);
        
        jObj->put("name" , str);
        jObj->put("age" , 17);
    }

    auto jObj = JsonObject::create();
    jObj->put("name" , L"你好世界 Muhaha");
    jObj->put("age",17);
    jObj->put("weight" , 56.33f);
    jObj->put("desc" , L"汝等踏入此地者，接受所有命运吧~!");
    jObj->put("data" , jsonArray);
    jObj->put("childList" , childList);

    WriteStringToFile("test.txt" , jObj->toJsonString());
}

void testJsonObjectPut(){
    auto jObj = JsonObject::create();
    
    jObj->put("name" , L"你好世界 Muhaha");
    jObj->put("age",17);
    jObj->put("weight" , 56.33f);
    jObj->put("desc" , L"汝等踏入此地者，接受所有命运吧~!");

    std::shared_ptr<JsonObject> childObj = JsonObject::create();
    childObj->put("name" , L"毛利兰");
    childObj->put("age",15);
    jObj->put("child" , childObj);
    jObj->put("child2" , childObj);
    
    WriteStringToFile("test.txt" , jObj->toJsonString());
}
