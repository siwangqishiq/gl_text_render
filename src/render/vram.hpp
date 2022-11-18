#pragma once

#include "glheader.hpp"


//显存分配器
class VRamAllcator{
};

//显存管理
class VRamManager{
public:
    static VRamManager& getInstance();

    VRamManager();

    ~VRamManager(){
    }

private:
    VRamAllcator allocator_;
};



