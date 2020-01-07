#ifndef JOBFUNCTION
#define JOBFUNCTION

class JobFunction
{
    public:
        virtual void setup()=0;
        virtual void loop()=0;
};
#endif