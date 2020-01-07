#ifndef SIMPLEJOBQUEUE
#define SIMPLEJOBQUEUE

#include "JobFunction.h"

class SimpleJobQueue{
    public:
        SimpleJobQueue();
        void pushJob(JobFunction* , unsigned int, int);//Job 생성(새로)
        void doIt();//Job 반복 관리
        void pauseIt(int);//Job 삭제(jobnum 이용)
        void resumeIt(int);//Job 삭제(jobnum 이용)
    private:
        class Job{
            public:
                //constructor
                Job(JobFunction*, unsigned int, unsigned long, int);
                //variables
                JobFunction* func;
                unsigned int delay;//0일 경우 
                unsigned int default_delay;//0일 경우 
                unsigned long recent;
                Job *nextJob;
                int jobnum;//0 이상. 음수 사용 x
                
        };
        Job* head;
        Job* tail;
        void push(Job *);//Job 추가(doIt only)(Delay 전용으로 사용)
        Job* pop();
};
#endif