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

//json array 
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

    Test("Test JsonArray String" , [](){
        auto jsonArray = JsonArray::create();
        jsonArray->push(L"你好");
        jsonArray->push(L"世界");
        jsonArray->push(L"Hello");
        jsonArray->push(L"World");

        EqualWString(L"[\"你好\",\"世界\",\"Hello\",\"World\"]" , jsonArray->toJsonString());
    });
}

void testJsonParse(){
    Test("Test json parse1", [](){
        std::wstring jsonString = L"{  \"name\" : \"maolilan\" ,  \"age\":17  , \"count\": 123.333 ,\"desc\":\"xxxxyyyyyzzzzz\"}";
        JsonParser parser;
        auto json = parser.parseJsonObject(jsonString);

        Equal(17 , json->getInt("age"));
        Equal(123.333f , json->getFloat("count"));
        EqualWString(L"maolilan" , json->getString("name"));
    });

    Test("Test json parse2", [](){
        auto subJson = JsonObject::create();
        subJson->put("name" , L"毛利兰");
        subJson->put("age" , 17);
        subJson->put("desc" , L"头上有犄角");

        EqualWString(L"头上有犄角" , subJson->getString("desc"));

        auto jsonStr = subJson->toJsonString();

        JsonParser parser;
        auto result = parser.parseJsonObject(jsonStr);
        EqualWString(L"头上有犄角" , result->getString("desc"));
        EqualWString(L"毛利兰" , result->getString("name"));
        Equal(17 , result->getInt("age"));
    });

    Test("Test json parse circular" , [](){
        auto _subJson = JsonObject::create();
        _subJson->put("name" , L"毛利兰");
        _subJson->put("age" , 17);
        _subJson->put("desc" , L"头上有犄角");
        
        auto _json = JsonObject::create();
        _json->put("friend" , _subJson);
        _json->put("score" , 27);
        _json->put("name" , L"工藤新一");
        _json->put("age" , 18);
        _json->put("score2" , 123456);
        _json->put("my" , L"HelloWorld");


        auto originJson = _json;
        std::wstring jsonStr = originJson->toJsonString();
        WriteStringToFile("out.json" , jsonStr);
        
        JsonParser parser;
        auto json = parser.parseJsonObject(jsonStr);

        auto originWifeJson = originJson->getJsonObject("friend");
        Equal(originWifeJson->getInt("age") , 17);

        auto wifeJson = json->getJsonObject("friend");
        Equal(originWifeJson->getInt("age") , wifeJson->getInt("age"));
        EqualWString(originWifeJson->getString("desc") , wifeJson->getString("desc"));
        EqualWString(originWifeJson->getString("name") , wifeJson->getString("name"));


        Equal(originJson->getInt("age") , json->getInt("age"));
        // Equal(originJson->getInt("score") , json->getInt("score"));
        EqualWString(originJson->getString("name") , json->getString("name"));
    });
    
    Test("Test parse json from string" , [](){
        std::wstring str = L"{\"age\":18,\"friend\":{   \"age\":17,\"desc\":\"头上有犄角\",\"name\":\"毛利兰\"},\"my\":\"HelloWorld\",\"name\":\"工藤新一\",\"score\":27, \"add\":\"test add!!\",\"score2\":123456}";

        // std::wstring str = L"{\"age\":18,\"my\":\"HelloWorld\",\"name\":\"工藤新一\",\"score\":27, \"add\":\"test add!!\",\"score2\":123456}";

        JsonParser parser;
        auto json = parser.parseJsonObject(str);
        Equal(18 , json->getInt("age"));
        Equal(27 , json->getInt("score"));
        Equal(123456 , json->getInt("score2"));
        EqualWString(L"test add!!" , json->getString("add"));
    });

    Test("Test json parse circular2" , [](){
        auto _subJson = JsonObject::create();
        _subJson->put("name" , L"毛利兰");
        _subJson->put("age" , 17);
        _subJson->put("desc" , L"头上有犄角");
        
        auto _json = JsonObject::create();
        _json->put("wife" , _subJson);
        _json->put("score" , 27);
        _json->put("name" , L"工藤新一");
        _json->put("age" , 18);
        _json->put("score2" , 123456);
        _json->put("my" , L"HelloWorld");


        auto originJson = _json;
        std::wstring jsonStr = originJson->toJsonString();
        WriteStringToFile("out.json" , jsonStr);
        
        JsonParser parser;
        auto json = parser.parseJsonObject(jsonStr);

        auto originWifeJson = originJson->getJsonObject("wife");
        Equal(originWifeJson->getInt("age") , 17);

        auto wifeJson = json->getJsonObject("wife");
        Equal(originWifeJson->getInt("age") , wifeJson->getInt("age"));
        EqualWString(originWifeJson->getString("desc") , wifeJson->getString("desc"));
        EqualWString(originWifeJson->getString("name") , wifeJson->getString("name"));

        Equal(originJson->getInt("age") , json->getInt("age"));
        EqualWString(originJson->getString("name") , json->getString("name"));
    });
}

int main(){
    testJsonObject();
    testJsonArray();
    testJsonParse();

    utest.testAll();
    return 0;
}




