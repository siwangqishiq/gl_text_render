#include "utest.hpp"
#include <iostream>
#include "asset_manager.hpp"

int main(){
    Test("test asset mgr read text" , [](){
        std::wstring content = AssetManager::getInstance()->readTextFile("test.txt");
        EqualWString(L"Hello World!你好世界" , content);
    });

    Test("test asset mgr read image" , [](){
        
    });

    return utest.testAll();
}