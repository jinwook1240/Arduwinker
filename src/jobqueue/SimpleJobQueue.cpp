#include <Arduino.h>
#include "SimpleJobQueue.h"
#include "JobFunction.h"
//constructors
SimpleJobQueue::Job::Job(JobFunction* func, unsigned int delay, unsigned long recent, int jobnum){
    this->func = func;
    this->delay = delay;
    this->default_delay = delay;
    this->recent = recent;
    this->nextJob = 0;
    this->jobnum = jobnum;
}
SimpleJobQueue::SimpleJobQueue(){
    this->head = nullptr;
    this->tail = nullptr;
}
//private
void SimpleJobQueue::push(Job *job){
    if(this->head==nullptr){
        this->head = job;
    }
    if(this->tail!=nullptr){
        this->tail->nextJob = job;
    }
    this->tail = job;
    job->func->setup();
}
SimpleJobQueue::Job* SimpleJobQueue::pop(){
    if(this->head==nullptr){
        return nullptr;
    }
    else if(this->head==this->tail){
        Job* tmp = head;
        this->head=nullptr;
        this->tail=nullptr;
        return tmp;
    }
    else{
        Job* ret = this->head;
        this->head = ret->nextJob;
        return ret;
    }
}
Job* SimpleJobQueue:: findJob(int jobnum){
    /*
    caution : 4294967295 milliseconds 후(약 3달)에 일시중지된 작업이 실행됩니다.
    */
    unsigned int MAX_UNSIGNED_INT = 4294967294;
    Job* nowJob = pop();
    int startJobNum = nowJob->jobnum;
    push(nowJob);
    nowJob = pop();
    if(nowJob->jobnum == jobnum){
        return nowJob;
    }
    while(startJobNum != nowJob->jobnum){
        push(nowJob);
        if(nowJob->jobnum == jobnum){
            return nowJob;
        }
        nowJob = pop();
    }
    push(nowJob);
    return -1;
}
//public
void SimpleJobQueue::pushJob(JobFunction* func, unsigned int delay, int jobnum){
    Job* tmpJob = new Job(func, delay, millis()-delay, jobnum);
    this->push(tmpJob);
}
void SimpleJobQueue::doIt(){
    Job* nowJob = pop();
    if(nowJob->delay){//add queue(delay not 0)
        if(nowJob->delay<millis()-nowJob->recent){
            nowJob->func->loop();
            nowJob->recent = millis();
        }
        this->push(nowJob);
    }
    else{
        nowJob->func->loop();
    }
}
void SimpleJobQueue::pauseIt(int jobnum){
    /*
    caution : 4294967295 milliseconds 후(약 3달)에 일시중지된 작업이 실행됩니다.
    */
    unsigned int MAX_UNSIGNED_INT = 4294967294;
    Job* nowJob = pop();
    int startJobNum = nowJob->jobnum;
    if(nowJob->jobnum == jobnum){
        nowJob->delay = MAX_UNSIGNED_INT;
    }
    push(nowJob);
    nowJob = pop();
    while(startJobNum != nowJob->jobnum){
        if(nowJob->jobnum == jobnum){
            nowJob->delay = MAX_UNSIGNED_INT;
        }
        push(nowJob);
        nowJob = pop();
    }
    push(nowJob);
}
void SimpleJobQueue::resumeIt(int jobnum){
    /*
    caution : 4294967295 milliseconds 후(약 3달)에 일시중지된 작업이 실행됩니다.
    */
    unsigned int MAX_UNSIGNED_INT = 4294967294;
    Job* nowJob = pop();
    int startJobNum = nowJob->jobnum;
    if(nowJob->jobnum == jobnum){
        nowJob->delay = MAX_UNSIGNED_INT;
    }
    push(nowJob);
    nowJob = pop();
    while(startJobNum != nowJob->jobnum){
        if(nowJob->jobnum == jobnum){
            nowJob->delay = MAX_UNSIGNED_INT;
        }
        push(nowJob);
        nowJob = pop();
    }
    push(nowJob);
}

