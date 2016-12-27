/*========================================INCLUDES AND USINGS===============================================*/

/*========================================CONSTANTS AND GLOBAL VARIABLES====================================*/

unsigned int IRSensors[]       = {3,5};        // Array containing all the current IRSensor pins. 

unsigned int ROBOTARRSIZE      = 4;            // Unrelated to IRSensors[] array. It is the amount of values to 
                                               // read from the sensor. Larger values = more accuracy, but longer. 
                                               
unsigned long DISTANCE_BOUNDARY = 102.3;        // Any input greater than this will be considered a detected robot.
                                               // 102.3 is equivalent to 0.5V which is the range of 5cm-130cm.
                                               
unsigned long CHARGE_DISTANCE   = 409.2;        // Any robot detected within this boundary will be charged at.
                                               // 409.2 is equivalent to 2V, which is the range of 10-30cm

/*========================================MAIN FUNCTION=====================================================*/  

void setup() {
  Serial.begin(9600);
}

void loop() {

  for (int i=0; i<numOfIRSensors; i++)         //Checks each sensor for a robot in sight.
  {
    if (isWithinDistance(i))
    {
      Serial.println("Some loser is detected at sensor i, get in position");
      if (isWithinChargeDistance(i))
          Serial.println("CHARGE!");
    }
    else
    {
      Serial.println("Nothing around, you can chill");
    }
  } 
}
/*========================================FUNCTION DEFINITIONS==============================================*/ 


/*************************************************************************************************************
Function Name: readIR


Parameters: An integer representing the IRSensor's value.


Return value: The average raw value read from the specified IR Sensor

Comments: 
*************************************************************************************************************/

long readIR(int IRSensor)
{
  unsigned long tempArray [ROBOTARRSIZE];                        
  unsigned long ul_AvgDistance;
  unsigned int iMin = 0;
  
  for (int i=0; i<ROBOTARRSIZE; i++)                              // Loop: loads sensor values into a temporary array 
  {
    tempArray[i] = analogRead(IRSensors[IRSensor]);
  }  
    
  for (int i = 1; i<ROBOTARRSIZE; i++)                           //Loop: sorts array in increasing order
  {
    for (int j = 1; j<ROBOTARRSIZE-i; j++)
    {
      if (tempArray[i] > tempArray[iMin])
          iMin = i;
    }
    unsigned long temp = tempArray[i];
    tempArray[i] = tempArray[iMin];
    tempArray[iMin] = temp;
  }

  if(ROBOTARRSIZE % 2 == 0)
     ul_AvgDistance = tempArray[ROBOTARRSIZE/2] + tempArray[(ROBOTARRSIZE/2)+1];
  else
     ul_AvgDistance = tempArray[ROBOTARRSIZE/2];
     
  return ul_AvgDistance;
}

/*************************************************************************************************************
Function Name: isWithinDistance


Parameters: An integer representing the IRSensor's value.


Return value: True if there is a robot within the distance boundary. False otherwise.

Comments: This will interpret the raw values read from the readIR to detect a robot within 130cm.
*************************************************************************************************************/

bool isWithinDistance(int IRSensor)
{
  if (readIR(IRSensor) > DISTANCE_BOUNDARY)
    return true;
  else
    return false;
}

/*************************************************************************************************************
Function Name: isWithinChargeDistance


Parameters: An integer representing the IRSensor's value.


Return value: True if there is a robot within charge distance. False otherwise.

Comments: The CHARGE_DISTANCE constant is used in this function to set a proximity at which the robot should 
          charge at the opponent. 
*************************************************************************************************************/

bool isWithinChargeDistance(int IRSensor)
{
  if(readIR(IRSensor) > CHARGE_DISTANCE)
    return true;
  else
    return false;
}



