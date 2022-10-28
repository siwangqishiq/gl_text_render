#include <iostream>
#include "utest.h"
#include "json.h"

#include <string>

int main(){

    Test("Test JsonObject construct" , [](){
        auto json = JsonObject::create();
        std::wcout << json->toJsonString() << std::endl;
        EqualWString(L"{}" , json->toJsonString());
    });

    

    utest.testAll();
    return 0;
}




