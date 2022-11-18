#include "vram.hpp"
#include "log.hpp"

VRamManager& VRamManager::getInstance() {
    static VRamManager instance;
    return instance;
}


VRamManager::VRamManager(){
    Logi("VRamManager" , "vram manager construct");
}

