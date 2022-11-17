#pragma once

#include <iostream>
#include <string>
#include <stdexcept>
#include <memory>

#ifdef __ANDROID__

#include <android/log.h>

#define  LOG_TAG    "textrender"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

#endif

#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <iostream>


#ifdef __ANDROID__

#include <android/log.h>
// #define  LOG_TAG    "textrender"
// #define  Logi(...)  __android_log_print(ANDROID_LOG_INFO, __VA_ARGS__)

inline void Logi(std::string tag , std::string format , ...){
    __android_log_print(ANDROID_LOG_INFO, tag.c_str() , format.c_str() , nullptr);
}

#else
//日志过滤tag
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
    Log(tag , StringFormat(format , args ...));
}
#endif


inline std::string date_time(std::time_t posix)
{
    char buf[20]; // big enough for 2015-07-08 10:06:51\0
    std::tm tp = *std::localtime(&posix);
    return {buf, std::strftime(buf, sizeof(buf), "%F %T", &tp)};
}

inline long long currentTimeMillis(){
    using namespace std;
    using namespace std::chrono;

    // get absolute wall time
    auto now = system_clock::now();

    // find the number of milliseconds
    auto ms = duration_cast<milliseconds>(now.time_since_epoch());
    return ms.count();
}

inline long long currentTimeMicro(){
    using namespace std;
    using namespace std::chrono;

    auto now = system_clock::now();

    auto us = duration_cast<microseconds>(now.time_since_epoch());

    return us.count();
}



