 

unsigned int g_uiPaintValue        =   500;
unsigned int g_uiWhiteBorder       =   HIGH;
#define LINE_SENSOR_WAIT 50
unsigned int uiLineSensorIO1       =   7;


 
void setup()
{
  Serial.begin(9600);
}

void loop()
{
 // Serial.println(LineDetection(uiLineSensorIO1));
 
  if (LineDetection(uiLineSensorIO1))
  {
    Serial.println("White");
  }
  else
  {
    Serial.println("Black");
  }

}


/*************************************************************************************************************
Function Name:LineDetection


Parameters:   in uiLineSensorIO        Sensor to read from


Return value: true if white border is detected, false otherwise


Comments:     The global variable g_uiPaintValue can be modified to change the sensitivity.
*************************************************************************************************************/
bool LineDetection (unsigned int uiLineSensorIO)
{
  /*Initiate */
  unsigned int uiSensorValue         =   LOW;
  
  /*Send pulse to the sensor*/
  pinMode(uiLineSensorIO,OUTPUT);
  digitalWrite(uiLineSensorIO,HIGH);

  /*Wait and read value from sensor*/
  delayMicroseconds(LINE_SENSOR_WAIT);
  pinMode(uiLineSensorIO,INPUT);

  /*Start "timer"*/
  long liTimeStart = micros();

  /*Detect the amount of time it takes for the capacitor to charge
  //If the sensor is exposed to a lot of light, it will discharge at a high rate
  //and output HIGH causing the time difference to be max value.*/
  while (digitalRead(uiLineSensorIO) == g_uiWhiteBorder && (micros() - liTimeStart < 3000) );

  /*Detect amount of time since start */ 
  unsigned int uiTimeDiff = micros() - liTimeStart;
  uiSensorValue = uiTimeDiff;

  /* If the sensor is exposed to a lot of light, return true, otherwise false */
  if(uiTimeDiff > g_uiPaintValue)
  {
      return false;
  }
  else if(uiTimeDiff <= g_uiPaintValue)
  {
    return true;
  }
}  



