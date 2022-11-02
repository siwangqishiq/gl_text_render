#include <iostream>
#include <string>
#include "utest.h"
#include "json.h"

void testJsonObject(){
 Test("Test JsonObject construct" , [](){
        auto json = JsonObject::create();
        std::wcout << json->toJsonString() << std::endl;
        EqualWString(L"{}" , json->toJsonString());
    });

    Test("Test JsonObject set Int" , [](){
        auto json = JsonObject::create();
        json->put("key1" , 1);
        json->put("key2" , 2);
        json->put("key3" , 303);

        Equal(1 , json->getInt("key1"));
        Equal(2 , json->getInt("key2"));
        Equal(303 , json->getInt("key3"));
    });

    Test("Test JsonObject set Float" , [](){
        auto json = JsonObject::create();
        json->put("key1" , 1.0f);
        json->put("key2" , 2.0f);
        json->put("key3" , 3.0f);

        Equal(1.0f , json->getFloat("key1"));
        Equal(2.0f , json->getFloat("key2"));
        Equal(3.0f , json->getFloat("key3"));
    });

    Test("Test JsonObject set String" ,[](){
        auto json = JsonObject::create();

        json->put("key1" , L"key1_value");
        json->put("key2" , L"key2_value");
        json->put("key3" , L"key3_值");

        EqualWString(json->getString("key1") , L"key1_value");
        EqualWString(json->getString("key2") , L"key2_value");
        EqualWString(json->getString("key3") , L"key3_值");
    });
}

void testJsonArray(){
    Test("Test JsonArray" ,[](){
        auto jsonArray = JsonArray::create();
        EqualWString(jsonArray->toJsonString() , L"[]");
    });

    Test("Test JsonArray1" ,[](){
        auto jsonArray = JsonArray::create();
        
        jsonArray->pushInt(1);
        jsonArray->pushInt(2);
        jsonArray->pushInt(3);

        EqualWString(jsonArray->toJsonString() , L"[1,2,3]");
    });
}

std::shared_ptr<JsonObject> buildJsonObject(){
    auto subJson = JsonObject::create();
    subJson->put("name" , L"毛利兰");
    subJson->put("age" , 17);
    subJson->put("desc" , L"头上有犄角");
    
    auto json = JsonObject::create();
    json->put("name" , L"工藤新一");
    json->put("age" , 18);
    json->put("wife" , subJson);
    json->put("socre" , 27);

    return json;
}

int main(){
    testJsonObject();
    testJsonArray();

    Test("Test json parse1", [](){
        std::wstring jsonString = L"{  \"name\" : \"maolilan\" ,  \"age\":17  , \"count\": 123.333 ,\"desc\":\"xxxxyyyyyzzzzz\"}";
        JsonObjectParser parser;
        auto json = parser.parseJsonObject(jsonString);

        Equal(17 , json->getInt("age"));
        Equal(123.333f , json->getFloat("count"));
    });

    Test("Test json parse2", [](){
        auto subJson = JsonObject::create();
        subJson->put("name" , L"毛利兰");
        subJson->put("age" , 17);
        subJson->put("desc" , L"头上有犄角");

        EqualWString(L"头上有犄角" , subJson->getString("desc"));

        auto jsonStr = subJson->toJsonString();

        JsonObjectParser parser;
        auto result = parser.parseJsonObject(jsonStr);
        EqualWString(L"头上有犄角" , result->getString("desc"));
        EqualWString(L"毛利兰" , result->getString("name"));
        Equal(17 , result->getInt("age"));
    });

    Test("Test json parse circusive" , [](){
        auto originJson = buildJsonObject();
        std::wstring jsonStr = originJson->toJsonString();

        JsonObjectParser parser;
        auto json = parser.parseJsonObject(jsonStr);
        // WriteStringToFile("out.json" , json->toJsonString());

        auto wifeJson = json->getJsonObject("wife");
        Equal(originJson->getInt("score") , json->getInt("score"));

        
    });

    utest.testAll();
    return 0;
}




