#include "timer.hpp"
#include "log.hpp"
#include <list>
#include <vector>

Timer::Timer(){
    time_ = currentTimeMillis();
}

Timer::~Timer(){
    if(!taskList_.empty()){
        clear();
    }
}

//delay 毫秒后 执行
int Timer::schedule(std::function<void(void)> runnable,long long delay){
    auto resultTask = buildTimerTask(runnable , delay , TimerTaskType::Once);
    taskList_.push_back(resultTask);
    return resultTask->taskId;
}

int Timer::scheduleAtFixedRate(std::function<void(void)> runnable ,long long period){
    auto resultTask = buildTimerTask(runnable , period , FixedRate);
    taskList_.push_back(resultTask);
    return resultTask->taskId;
}


std::shared_ptr<TimerTask> Timer::buildTimerTask(std::function<void(void)> runnable,long long delay ,TimerTaskType taskType){
    auto timeTask = std::make_shared<TimerTask>();

    timeTask->taskId = genTaskId();
    timeTask->shuldRunTime = currentTimeMillis() + delay;
    timeTask->delayTime = delay;
    timeTask->runnable = runnable;
    timeTask->type = taskType;
    return timeTask;
}

// 以固定时间 period 毫秒 执行

// long Timer::scheduleAtFixedRate(std::function<int(void *)> runnable , long period);

//step a timestamp
void Timer::trick(){
    time_ = currentTimeMillis();
    
    std::vector<std::list<std::shared_ptr<TimerTask>>::iterator> removeList;
    auto iter = taskList_.begin();
    while(iter != taskList_.end()){
        std::shared_ptr<TimerTask> task = *iter;
        if(time_ >= task->shuldRunTime){
            // Logi("timer" , "task id %d time tasktime %lld cur %lld" ,
            // task->taskId , task->shuldRunTime , time_);
            task->runnable();
            if(task->type == Once){
                removeList.push_back(iter);
            }else if(task->type == FixedRate){
                task->shuldRunTime = currentTimeMillis() + task->delayTime;
            }
            // taskList_.erase(iter);
        }
        iter++;
    }//end while

    if(!removeList.empty()){
        for(auto iter : removeList){
            taskList_.erase(iter);
        }//end for each
    }
}
    
void Timer::clear(){
    idIndex_ = 0;
    taskList_.clear();
}



