#include "timer.hpp"
#include "log.hpp"

Timer::Timer(){
    time_ = currentTimeMillis();
}

Timer::~Timer(){
    if(!taskList_.empty()){
        clear();
    }
}

    //delay 毫秒后 执行
long Timer::schedule(std::function<void(void)> runnable,long long delay){
    auto resultTask = buildTimerTask(runnable , delay);
    taskList_.push_back(resultTask);
    return resultTask->taskId;
}

std::shared_ptr<TimerTask> Timer::buildTimerTask(std::function<void(void)> runnable,long delay){
    auto timeTask = std::make_shared<TimerTask>();

    timeTask->taskId = genTaskId();
    timeTask->shuldRunTime = currentTimeMillis() + delay;
    timeTask->runnable = runnable;

    return timeTask;
}

// 以固定时间 period 毫秒 执行
// long Timer::scheduleAtFixedRate(std::function<int(void *)> runnable , long period);

//step a timestamp
void Timer::trick(){
    time_ = currentTimeMillis();
    
    auto iter = taskList_.begin();
    while(iter != taskList_.end()){
        std::shared_ptr<TimerTask> task = *iter;
        // Logi("timer" , "task id %d time tasktime %lld cur %lld" ,
        //     task->taskId , task->shuldRunTime , time_);
        if(time_ >= task->shuldRunTime){
            task->runnable();
            taskList_.erase(iter);
        }
        iter++;
    }//end while
}
    
void Timer::clear(){
    idIndex_ = 0;
    taskList_.clear();
}



