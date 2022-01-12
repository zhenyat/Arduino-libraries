/**********************************************************************
 * zt_venti_condi.h
 * 
 * Library for Ventilation-Conditioner Project
 * 
 * 29.07.2021	ZT
 * 04.08.2021 Update: resetCondi()
 * 08.08.2021 2.x
 * 10.08.2021 Last update
 * 11.08.2021 v 3.x
 * 11.01.2022 Last update
 **********************************************************************/
#ifndef ZT_VENTI_CONDI_H
  #define ZT_VENTI_CONDI_H

  #include <Arduino.h>
  #include <zt_io.h>

  void  condiOff(unsigned int outputPwmPin, unsigned int delayTime);
  void  condiOn(unsigned int outputPwmPin,  unsigned int pwmUnits, unsigned int delayTime);
  int   getCondiLevel(unsigned int ventiPwm, unsigned int *ventiPwms, unsigned int ventiLevels);
  char* getTrend(unsigned int *arrayBuffer, unsigned int arraySize);
  bool  isVentiOnBottom(unsigned int analogPin, unsigned int bottomLevel, unsigned int checkAttempts, unsigned int delayTime);
  bool  isVentiOnTop(unsigned int analogPin, unsigned int topLevel, unsigned int checkAttempts, unsigned int delayTime);
  void  resetCondi(unsigned int outputPwmPin,  unsigned int topPwmUnits, unsigned int delayAfterOff, unsigned int delayAfterOn);
  void  shiftArrayLeft(unsigned int *arrayBuffer, unsigned int arraySize, unsigned int pushedInValue);
#endif
