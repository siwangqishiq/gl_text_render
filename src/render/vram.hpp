#pragma once

#include "glheader.hpp"
#include <memory>
#include <vector>
#include "log.hpp"

struct MemoryAllocatorInfo{
    unsigned int bufferId = -1;
    int size = 0;
    int offset = 0;
};

//显存分配器
class VRamAllcator{
private:
    std::vector<std::shared_ptr<MemoryAllocatorInfo>> allocatedList_; //已分配的显存记录表

    unsigned int currentBufferIdIndex_ = -1;
    
    unsigned int genBuffer();

    void createNewBuffer();
public:
    const int ALLOCATOR_SIZE = 8 * 1024;//8K 一次分配8K字节 

    int fetchVideoMemory(int requestSize ,unsigned int &bufferId , int &offset , int &size);

    void recycleAllMemory();

    void freeMemory();
};

//显存管理
class VRamManager{
public:
    const char *TAG = "VRamManager";

    static VRamManager& getInstance();

    VRamManager();

    ~VRamManager(){
        Logi(TAG , "~VRamManager deconstruct");
    }

    void onPostRender();

    void clear();

    //获取一块显存 用于写入内容
    int fetchVideoMemory(int requestSize , unsigned int &bufferId , int &offset , int &size);
private:
    std::shared_ptr<VRamAllcator> allocator_;
};


