#pragma once

#include <functional>
#include <list>
#include <memory>

enum TimerTaskType{
    Once, //仅运行一次
    FixedRate //以固定频率执行
};

struct TimerTask{
    int taskId;
    long long shuldRunTime = 0;
    long long delayTime = 0;
    std::function<void(void)> runnable;
    TimerTaskType type = Once;
};

//定时器 只在主线程中执行
class Timer{
public:
    Timer();

    ~Timer();

    //delay 毫秒后 执行
    int schedule(std::function<void(void)> runnable, long long delay);

    // 以固定时间 period 毫秒 执行
    int scheduleAtFixedRate(std::function<void(void)> runnable ,long long period);

    //step a timestamp
    void trick();
    
    void clear();
private:
    long long time_;

    std::list<std::shared_ptr<TimerTask>> taskList_;

    int idIndex_;
    int genTaskId(){
        return ++idIndex_;
    }
    
    std::shared_ptr<TimerTask> buildTimerTask(std::function<void(void)> runnable ,long long delay ,TimerTaskType taskType);
};