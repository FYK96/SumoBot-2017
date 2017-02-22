#ifndef SumoBotFuctions.h
#define SumoBotFunctions.h
#include "Arduino.h"

const unsigned int  cui_FORWARD     = 1;
const unsigned int  cui_BACKWARD    = 2;
const unsigned int  cui_SHARP_LEFT  = 3;
const unsigned int  cui_SHARP_RIGHT = 4;
const unsigned int  cui_F_LEFT      = 5;
const unsigned int  cui_F_RIGHT     = 6;
const unsigned int  cui_B_LEFT      = 7;
const unsigned int  cui_B_RIGHT     = 8;
const unsigned int  cui_NEITHER     = 0;

const unsigned int  cui_pwmSTOP     = 127;
const unsigned int  cui_pwmFRONT    = 255;
const unsigned int  cui_pwmBACK     = 0;

#define DISTANCE_BOUNDARIES 102
unsigned int uiSensorReadPin = 0;

unsigned int g_uiPaintValue        =   1000;
unsigned int g_uiWhiteBorder       =   HIGH;
#define LINE_SENSOR_WAIT 10

bool motorDrive(
          unsigned int ui_direction,
          unsigned int ui_FRMotor,
          unsigned int ui_FLMotor,
          unsigned int ui_BRMotor,
          unsigned int ui_BLMotor);

bool LineDetection (
          unsigned int uiLineSensorIO);
bool IsWithinDistance(
          unsigned int uiAnalogPin);

#endif
