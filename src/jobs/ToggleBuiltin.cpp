#include <Arduino.h>
#include "ToggleBuiltin.h"

void ToggleBuiltin::setup(){
  pinMode(LED_BUILTIN, OUTPUT);
}
void ToggleBuiltin::loop(){
  int status = digitalRead(LED_BUILTIN);
  if(status)
    digitalWrite(LED_BUILTIN, LOW);
  else
    digitalWrite(LED_BUILTIN, HIGH);
}