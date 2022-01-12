/************************************************************************
 * condi_on_off 
 * 
 * Example for VentiCondi Project:
 *    switches ON / OFF the Conditioner
 * 
 * 29.07.2021 ZT
 * 31.07.2021 
 * 08.08.2021 v. 2.x
 * 10.08.2021 Last update
 ************************************************************************/
#include <zt_venti_condi.h>

unsigned int outputPwmPin = 3;
unsigned int pwmUnits     = 255;

int count          = 0;
long delayAfterOn  = 60;    // sec
long delayAfterOff = 180;  // sec

void setup() {
  Serial.begin(9600);
  setOutputMode(outputPwmPin);    // MUST BE!!! Otherwise some voltage is at Multimeter...
  sleep(2);
  Printf("===== Starting ON / OFF test for VentiCondi Project. Pin: %d\n", outputPwmPin);
}

void loop() {
  Printf("Loop %d:\n", ++count);
  condiOff(outputPwmPin, delayAfterOff);
  condiOn(outputPwmPin, pwmUnits, delayAfterOn);
}
