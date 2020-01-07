#include <Arduino.h>
#include "jobqueue/SimpleJobQueue.h"
#include "jobs/ToggleBuiltin.h"
#include "jobs/SetToggleBuiltin.h"
SimpleJobQueue* jobs;

int TOGGLE_BUILTIN = 0;
int SET_TOGGLE_BUILTIN = 1;
void setup() {
  jobs = new SimpleJobQueue();
  jobs->pushJob(new ToggleBuiltin(), 400, TOGGLE_BUILTIN);
  jobs->pushJob(new SetToggleBuiltin(jobs), 10, SET_TOGGLE_BUILTIN);
}

void loop() {
  jobs->doIt();
}
