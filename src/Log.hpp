#pragma once

#include <iostream>
#include <string>
#include <stdexcept>
#include <memory>


//日志过滤tag
#ifndef _LOG_H_
#define _LOG_H_

const std::string logFilter = "";

/**
 * @brief  log output iostream
 * 
 * @param tag 
 * @param msg 
 */
inline void Log(std::string tag , std::string msg){
    if(logFilter != "" && logFilter != tag){
        return;
    }

    std::cout << tag << " :" << msg << std::endl;
}

template<typename ... Args>
inline std::string StringFormat(const std::string& format, Args ... args){
    #ifdef __ANDROID__
    return std::string();
    #else
    int size_s = std::snprintf(nullptr, 0, format.c_str(), args ... ) + 1;
    if( size_s <= 0 ){
        throw std::runtime_error( "Error during formatting." );
    }

    auto size = static_cast<size_t>(size_s);
    std::unique_ptr<char[]> buf(new char[size]);
    auto format_ = format;
    std::snprintf(buf.get(), size, format_.c_str(), args ...);
    return std::string( buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
    #endif
}

template<typename ... Args>
inline void Logi(std::string tag , std::string format , Args ... args){
    // auto out = StringFormat(format , args ...);
    // std::cout << "out " << out << std::endl;
    Log(tag , StringFormat(format , args ...));
}

#endif
