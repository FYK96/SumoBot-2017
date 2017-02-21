/*========================================CYTRON MDD10A H BRIDGE============================================*/
/*__________________________________________________________________________________________________________*/

/*========================================CONSTANTS AND GLOBAL VARIABLES====================================*/
unsigned int        ui_FRMotor      = 3;
unsigned int        ui_FLMotor      = 5;
unsigned int        ui_BRMotor      = 6;
unsigned int        ui_BLMotor      = 10;
const unsigned int  cui_FORWARD     = 1, cui_BACKWARD = 2; 
const unsigned int  cui_LEFT        = 11, cui_RIGHT = 12, cui_NEITHER = 0;
const unsigned int  cui_pwmSTOP     = 127;
const unsigned int  cui_pwmFRONT    = 255;
const unsigned int  cui_pwmBACK     = 0;
/*========================================FUNCTION DEFINITIONS==============================================*/ 

/*************************************************************************************************************
Function Name: motorDrive
Parameters: ui_direction    desired movement of the robot
            ui_FRMotor      Front right motor's pwm pin in the motor's driver
            ui_FLMotor      Front left motor's pwm pin in the motor's driver
            ui_BRMotor      Back right motor's pwm pin in the motor's driver
            ui_BLMotor      Back left motor's pwm pin in the motor's driver
            
Return value: boolean, true if successful false otherwise
Comments: -
*************************************************************************************************************/
bool motorDrive(
          unsigned int ui_direction,
          unsigned int ui_FRMotor,
          unsigned int ui_FLMotor,
          unsigned int ui_BRMotor,
          unsigned int ui_BLMotor)
{

  switch(ui_direction)
  { 
    case cui_FORWARD:
      digitalWrite(ui_FRMotor, cui_pwmFRONT);
      digitalWrite(ui_FLMotor, cui_pwmFRONT);
      digitalWrite(ui_BRMotor, cui_pwmFRONT);
      digitalWrite(ui_BLMotor, cui_pwmFRONT);
      break;
      
    case cui_BACKWARD:
      digitalWrite(ui_FRMotor, cui_pwmBACK);
      digitalWrite(ui_FLMotor, cui_pwmBACK);
      digitalWrite(ui_BRMotor, cui_pwmBACK);
      digitalWrite(ui_BLMotor, cui_pwmBACK);
      break;
      
    case cui_RIGHT:
      digitalWrite(ui_FRMotor, cui_pwmBACK);
      digitalWrite(ui_FLMotor, cui_pwmFRONT);
      digitalWrite(ui_BRMotor, cui_pwmBACK);
      digitalWrite(ui_BLMotor, cui_pwmFRONT);
      break;
      
    case cui_LEFT:
      digitalWrite(ui_FRMotor, cui_pwmFRONT);
      digitalWrite(ui_FLMotor, cui_pwmBACK);
      digitalWrite(ui_BRMotor, cui_pwmFRONT);
      digitalWrite(ui_BLMotor, cui_pwmBACK);
      break;
      
    default:
      return false;
  }
  return true;
}

/*========================================IRSENSOR==========================================================*/
/*__________________________________________________________________________________________________________*/
/* The minimum distance the ir's have to detect will be at 0.5 Volts (ie: about 2cm. Thus, an analog value 
 *  over 102 is acceptable. 
 *  The maximum distance the ir's have to detect will be at 0.5 Volts as well (ie: about 140cm). This is due 
 *  to the physical properties of the sensor.
 It is reccommended to look at the GP2Y0A02 datasheet for further consultation on why this value was taken.*/
//========================================CONSTANTS AND GLOBAL VARIABLES====================================\\
#define DISTANCE_BOUNDARIES 102

unsigned int uiSensorReadPin = 0;
//========================================FUNCTION DEFINITIONS==============================================\\  


/*************************************************************************************************************
Function Name:LineDetection


Parameters:   in uiAnalogPin        The analog pin connected to the IR sensor


Return value: true if an object is within the specifed boundaries, false otherwise


Comments:     The global variable DISTANCE_BOUNDARIES can be modified to change the sensitivity.
*************************************************************************************************************/
bool IsWithinDistance(
                    unsigned int uiAnalogPin)
{
    unsigned int uiAvgDistance     = 0;
    unsigned int uiRead1           = 0;
    unsigned int uiRead2           = 0;
    unsigned int uiRead3           = 0;
    int          iDiffCompare1     = 0;
    int          iDiffCompare2     = 0;
    int          iDiffCompare3     = 0;
    
    
    uiRead1 = analogRead (uiAnalogPin);
    uiRead2 = analogRead (uiAnalogPin);
    uiRead3 = analogRead (uiAnalogPin);
    
    //Get all possible combinations of differences between reads
    iDiffCompare1 = abs(uiRead1 - uiRead2);
    iDiffCompare2 = abs(uiRead1 - uiRead3);
    iDiffCompare3 = abs(uiRead2 - uiRead3);
    
    //Check which has the smallest difference
    if      (iDiffCompare1 <= iDiffCompare2    &&
            iDiffCompare1 <= iDiffCompare3)
    {
        uiAvgDistance = (uiRead1 + uiRead2)/2;
    }
    
    else if (iDiffCompare2 <= iDiffCompare1    &&
            iDiffCompare2 <= iDiffCompare3)
    {
        uiAvgDistance = (uiRead1 + uiRead3)/2;
    }
    
    else if (iDiffCompare3 <= iDiffCompare1    &&
            iDiffCompare3 <= iDiffCompare2)
    {
        uiAvgDistance = (uiRead2 + uiRead3)/2;
    }
    
    //Return true if within specified boundaries
    if ( uiAvgDistance > DISTANCE_BOUNDARIES )
    {
        return true;
    }
    
    //false otherwise
    else
    {
        return false;   
    }
}
    
   


/*========================================LINE SENSOR==========================================================*/
/*_____________________________________________________________________________________________________________*/
//========================================CONSTANTS AND GLOBAL VARIABLES====================================\\
unsigned int g_uiPaintValue        =   1000;//3mm
unsigned int g_uiWhiteBorder       =   HIGH;
#define LINE_SENSOR_WAIT 10 

//========================================FUNCTION DEFINITIONS==============================================\\  


/*************************************************************************************************************
Function Name:LineDetection


Parameters:   in uiLineSensorIO        Sensor to read from


Return value: true if white border is detected, false otherwise


Comments:     The global variable g_uiPaintValue can be modified to change the sensitivity.
*************************************************************************************************************/
bool LineDetection (unsigned int uiLineSensorIO)
{
  //Initiate 
  unsigned int uiSensorValue         =   LOW;
  
  //Send pulse to the sensor
  pinMode(uiLineSensorIO,OUTPUT);
  digitalWrite(uiLineSensorIO,HIGH);

  //Wait and read value from sensor
  delayMicroseconds(LINE_SENSOR_WAIT);
  pinMode(uiLineSensorIO,INPUT);

  //Start "timer"
  long liTimeStart = micros();

  //Detect the amount of time it takes for the capacitor to charge
  //If the sensor is exposed to a lot of light, it will discharge at a high rate
  //and output HIGH causing the time difference to be max value.
  while (digitalRead(uiLineSensorIO) == g_uiWhiteBorder && (micros() - liTimeStart < 3000) );

  //Detect amount of time since start  
  unsigned int uiTimeDiff = micros() - liTimeStart;
  uiSensorValue = uiTimeDiff;

  // If the sensor is exposed to a lot of light, return true, otherwise false 
  if(uiTimeDiff > g_uiPaintValue)
  {
      return true;
  }
  else if(uiTimeDiff <= g_uiPaintValue)
  {
    return false;
  }
}
