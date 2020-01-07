#include <Arduino.h>
#include "SetToggleBuiltin.h"
#include "../jobqueue/SimpleJobQueue.h"
SetToggleBuiltin::SetToggleBuiltin(SimpleJobQueue* queue){
    this->queue = queue;
}
void SetToggleBuiltin::setup(){
    pinMode(2, INPUT_PULLUP);
}
void SetToggleBuiltin::loop(){
    if(digitalRead(2)) return;
    digitalWrite(LED_BUILTIN, LOW);
    this->queue->pauseIt(0);
}