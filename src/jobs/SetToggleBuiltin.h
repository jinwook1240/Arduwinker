#include "../jobqueue/JobFunction.h"
#include "../jobqueue/SimpleJobQueue.h"

class SetToggleBuiltin : public JobFunction {
    public:
        SetToggleBuiltin(SimpleJobQueue*);
        SimpleJobQueue* queue;
        void setup();
        void loop();
};