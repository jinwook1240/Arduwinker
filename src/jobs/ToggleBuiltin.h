#include "../jobqueue/JobFunction.h"

class ToggleBuiltin : public JobFunction {
    public:
        void setup();
        void loop();
};