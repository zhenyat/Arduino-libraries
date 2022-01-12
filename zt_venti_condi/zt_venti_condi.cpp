/***********************************************************************
 * zt_venti_condi.cpp
 * 
 * Library Functions for Ventilation-Conditioner Projects
 * 	  check_trend()		  - verifies whether array elements are in up/down trend
 *    condiOff()        - switches OFF the device
 *    CondiOn()         - switches ON  the device
 *    getCondiLevel()   - identifies Condi Level according to Venti PWM signal
 *    getTrend()        - defines Grow/Fall/Standby trend of an array elements
 *    isVentiOnBottom() - verifies whether Venti requests Minimum Power ( 0 V)
 *    isVentiOnTop()    - verifies whether Venti requests maximum Power (10 V)
 *    resetCondi()      - resets the Conditioner (Off and On with corresponding "after" delays)
 * 	  shiftArrayLeft()  - shifts array left and adds new value to right
 * 
 * 29.07.2021 ZT
 * 31.07.2021 Update: unsigned long for delay() argument
 * 02.08.2021 Update: serious changes and new functions
 * 04.08.2021 Update: isVentiOnBottom(), resetCondi() added
 * 07.08.2021 Update
 * 09.08.2021 2.x
 * 10.08.2021 sleep() instead of delay()
 * 12.08.2021 3.x
 * 11.01.2022 Last update
 **********************************************************************/
#include <zt_venti_condi.h>

void condiOff(unsigned int outputPwmPin, unsigned int delayTime)
{
  unsigned long delayTimeMin = 180;  // After Condi switched OFF it is unavailable 3 minutes
  
  analogWrite(outputPwmPin, 0);
  delayTime = (delayTime < delayTimeMin) ? delayTimeMin : delayTime;
  Printf("\n***** The Conditioner is OFF (pin: %i) and sleeping %i seconds...\n", outputPwmPin, delayTime);
  sleep(delayTime);	  // Delay before to switch ON again
}

void condiOn(unsigned int outputPwmPin,  unsigned int pwmUnits, unsigned int delayTime)
{
  analogWrite(outputPwmPin, pwmUnits);
  Printf("\n***** The Conditioner is ON (pin: %i) and sleeping %i sec...\n", outputPwmPin, delayTime);
  sleep(delayTime);
}

/*********************************************************
 *  Identifies Condi Level according to Venti PWM signal
 *********************************************************/
int getCondiLevel(unsigned int ventiPwm, unsigned int *ventiPwms, unsigned int ventiLevels)
{
  for (int ventiLevel = 0; ventiLevel <  ventiLevels - 1; ventiLevel++) {
    if (ventiPwms[ventiLevel] <= ventiPwm && ventiPwm < ventiPwms[ventiLevel + 1]) {
      return ventiLevel;
    }
  }
}

/****************************************************
 * Defines a trend of an array elements:
 *    Up:       Growing     a[0] < a[1] < ... < a[n]
 *    Down:     Falling     a[0] > a[1] > ... > a[n]
 *    Standby:  other cases
 ****************************************************/
char* getTrend(unsigned int *arrayBuffer, unsigned int arraySize)
{
  int up   = 0;
  int down = 0;

  for (int i = 1; i < arraySize; i++) {
    if (arrayBuffer[i] > arrayBuffer[i-1]) {
      up++;
    } else if (arrayBuffer[i] < arrayBuffer[i-1]) {
      down++;
    } else {
      // Standby...
    }
  }
  if      (up   == arraySize-1) return "Up";
  else if (down == arraySize-1) return "Down";
  else                          return "Standby";
}

bool isVentiOnBottom(unsigned int analogPin, unsigned int bottomLevel, unsigned int checkAttempts, unsigned int delayTime)
{
  unsigned int count = 0;
  for (int i = 0; i < checkAttempts; i++) {
    unsigned int value = analogRead(analogPin);
    if (value < bottomLevel) {
      count++;
    }
    sleep(delayTime);
  }
  
  if (count == checkAttempts) {
    return true;
  } else {
    return false;
  }
}

bool isVentiOnTop(unsigned int analogPin, unsigned int topLevel, unsigned int checkAttempts, unsigned int delayTime)
{
  unsigned int count = 0;
  for (int i = 0; i < checkAttempts; i++) {
    unsigned int value = analogRead(analogPin);
    if (value >= topLevel) {
      count++;
    }
    sleep(delayTime);
  }
  
  if (count == checkAttempts) {
    return true;
  } else {
    return false;
  }
}

void resetCondi(unsigned int outputPwmPin,  unsigned int topPwmUnits, unsigned int delayAfterOff, unsigned int delayAfterOn)
{
  condiOff(outputPwmPin, delayAfterOff);
  condiOn(outputPwmPin, topPwmUnits, delayAfterOn);
}

void shiftArrayLeft(unsigned int *arrayBuffer, unsigned int arraySize, unsigned int pushedInValue)
{
  for(int i = 0; i < arraySize-1; ++i) {
    arrayBuffer[i] = arrayBuffer[i+1];
  }
  arrayBuffer[arraySize-1] = pushedInValue;
}


