#include <iostream>

#include "json.h"

int main(){
    // std::string data = "{\"name\":\"毛利兰\" , \"age\":17}";

    JsonObject jObj;

    jObj.put("name" , "luanma");
    jObj.put("age",17);
    jObj.put("weight" , 56.33f);

    std::cout << jObj.toJsonString() << std::endl;
    
    return 0;
}
