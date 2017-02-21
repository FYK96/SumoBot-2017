/*========================================INCLUDES=========================================================*/

#include "SumoBotFuction.cpp"
/*========================================CONSTANTS AND GLOBAL VARIABLES====================================*/
//Analog pins for bridge
const unsigned int cui_pwmM1Driver  = 11;
const unsigned int cui_pwmM2Driver  = 10;
const unsigned int cui_pwmM3Driver  = 9;
const unsigned int cui_pwmM4Driver  = 6;

//Digital pins for bridge
const unsigned int cui_digM1Driver  = 13;
const unsigned int cui_digM2Driver  = 12;
const unsigned int cui_digM3Driver  = 8;
const unsigned int cui_digM4Driver  = 7;

//Line sensor Pins
const unsigned int cui_LSFR          = 5;
const unsigned int cui_LSFL          = 4;
const unsigned int cui_LSBR          = 3;
const unsigned int cui_LSBL          = 2;

//IR sensor pins
const unsigned int cui_IRF          = 0;
const unsigned int cui_IRR          = 1;
const unsigned int cui_IRL          = 2;

//Directions
const unsigned int  cui_FORWARD     = 1;
const unsigned int  cui_BACKWARD    = 2;
const unsigned int  cui_SHARP_LEFT  = 3;
const unsigned int  cui_SHARP_RIGHT = 4;
const unsigned int  cui_F_LEFT      = 5;
const unsigned int  cui_F_RIGHT     = 6;
const unsigned int  cui_B_LEFT      = 5;
const unsigned int  cui_B_RIGHT     = 6;
const unsigned int  cui_NEITHER     = 0;

//Location of the enemy relative to the robot

bool b_isClockwise                  = true;

/*========================================INITIALIZATION============================================*/

void setup() {
  
  /* Pin initialization*/
  pinMode(cui_pwmM1Driver, OUTPUT);
  pinMode(cui_pwmM2Driver, OUTPUT);
  pinMode(cui_pwmM3Driver, OUTPUT);
  pinMode(cui_pwmM4Driver, OUTPUT);
  pinMode(cui_digM1Driver, OUTPUT);
  pinMode(cui_digM2Driver, OUTPUT);
  pinMode(cui_digM3Driver, OUTPUT);
  pinMode(cui_digM4Driver, OUTPUT);
}
/*========================================MAIN FUNCTION============================================*/

void loop() 
{

  // -----------------------Check if robot is crossing the line---------------------------------

  //Front Left or Right Line Sensors
  if(LineDetection(cui_LSFR) || LineDetection(cui_LSFL) )
  {
      if(LineDetection(cui_LSFR) && LineDetection(cui_LSFL))
          {
            motorDrive(cui_BACKWARD,cui_pwmM1Driver, cui_pwmM2Driver, cui_pwmM3Driver, cui_pwmM4Driver);
          }
      else if(LineDetection(cui_LSFR))
          {
            motorDrive(cui_B_LEFT,cui_pwmM1Driver, cui_pwmM2Driver, cui_pwmM3Driver, cui_pwmM4Driver);
          }
      else if(LineDetection(cui_LSFL))
          {
            motorDrive(cui_B_RIGHT,cui_pwmM1Driver, cui_pwmM2Driver, cui_pwmM3Driver, cui_pwmM4Driver);
          }
  }
  
  //Back Left or Right Line Sensors
  else if   (LineDetection(cui_LSBR) || LineDetection(cui_LSBL) ) 
    {
        if (LineDetection(cui_LSBR) && LineDetection(cui_LSBL))
            {
              motorDrive(cui_FORWARD,cui_pwmM1Driver, cui_pwmM2Driver, cui_pwmM3Driver, cui_pwmM4Driver);
            }
            
        else if   (LineDetection(cui_LSBR))
            {
            motorDrive(cui_F_LEFT,cui_pwmM1Driver, cui_pwmM2Driver, cui_pwmM3Driver, cui_pwmM4Driver);   
            }
          
        else if   (LineDetection(cui_LSBL))
            {
            motorDrive(cui_F_RIGHT,cui_pwmM1Driver, cui_pwmM2Driver, cui_pwmM3Driver, cui_pwmM4Driver);   
            }
    }
  
  //Right Side Sensors
  else if   (LineDetection(cui_LSBR) || LineDetection(cui_LS))
    {
      motorDrive(cui_F_RIGHT,cui_pwmM1Driver, cui_pwmM2Driver, cui_pwmM3Driver, cui_pwmM4Driver);
    }
  
    //Left Side Sensors
  else if   (LineDetection(cui_LSBR) || LineDetection(cui_LSFR))
    {
      motorDrive(cui_F_LEFT,cui_pwmM1Driver, cui_pwmM2Driver, cui_pwmM3Driver, cui_pwmM4Driver);
    }
  
  //-----------------------------------------Check if enemy robot is detected---------------------------//
  
  else if   (IsWithinDistance(cui_IRF))
  {
    motorDrive(cui_FORWARD,cui_pwmM1Driver, cui_pwmM2Driver, cui_pwmM3Driver, cui_pwmM4Driver);
            
    if   (LineDetection(cui_LSFR) || LineDetection(cui_LSFL))
            {
            motorDrive(cui_SHARP_LEFT,cui_pwmM1Driver, cui_pwmM2Driver, cui_pwmM3Driver, cui_pwmM4Driver);   
            }
  }
  
  else if   (IsWithinDistance(cui_IRR))
  {
    b_isClockwise = true;
    motorDrive(cui_F_RIGHT,cui_pwmM1Driver, cui_pwmM2Driver, cui_pwmM3Driver, cui_pwmM4Driver);
  }
  else if   (IsWithinDistance(cui_IRL))
  {
    b_isClockwise = false; 
    motorDrive(cui_F_LEFT,cui_pwmM1Driver, cui_pwmM2Driver, cui_pwmM3Driver, cui_pwmM4Driver);
  }
  else 
  {
    if(b_Clockwise)
      motorDrive(cui_SHARP_RIGHT,cui_pwmM1Driver, cui_pwmM2Driver, cui_pwmM3Driver, cui_pwmM4Driver);
    else
      motorDrive(cui_SHARP_LEFT,cui_pwmM1Driver, cui_pwmM2Driver, cui_pwmM3Driver, cui_pwmM4Driver);
  }
  
}
