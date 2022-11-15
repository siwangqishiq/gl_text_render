#pragma once

#include <iostream>
#include <string>

/**
 * @brief  log output iostream
 * 
 * @param tag 
 * @param msg 
 */
void Log(std::string tag , std::string msg){
    std::cout << tag << " :" << msg << std::endl;
}

