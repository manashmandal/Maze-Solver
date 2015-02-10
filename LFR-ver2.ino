#define THRESHOLD 300
#include <SoftwareSerial.h>

SoftwareSerial bluetooth (10, 11); // RX , Tx



                                        

  
int sensor[] = {54, 55, 56, 57, 58, 59, 60, 61};
int leftMotor[] = {3,4};
int rightMotor[] = {5,6};
                  
// New Patterns

String hardTurn00000011 = "00000011";
String hardTurn00000001 = "00000001";
//String softTurn00111111 = "00000111";
//String softTurn000000111 = "000001111";
String slightTurn11111100 = "11111100";



//-------------------
String pattern = "00000000";
 
String forwardPattern = "00111100";
String leftPattern = "01111000";
String rightPattern = "00011110"; //old


String slightLeft01111000 ="01111000";
String slightRight00011110 ="00011110";

String hardLeft11100000 = "11100000";
String hardRight00011111 = "00011111"; 

String slightLeft11111000 = "11111000";

String forward00111110 ="00111110";
String forward01111100 ="01111100";

String hardLeft11110000 ="11110000";
String hardRight00001111 ="00001111";

void setMotors(int leftSpeed, int rightSpeed)
{
  if (leftSpeed >= 0 && rightSpeed >= 0)
  {
   analogWrite(leftMotor[0], leftSpeed);   /*   Forward  */
   analogWrite(leftMotor[1], 0);
   analogWrite(rightMotor[0], rightSpeed);
   analogWrite(rightMotor[1], 0);
  }
  
  else if (leftSpeed < 0 && rightSpeed < 0)
  {
    leftSpeed = -leftSpeed;
    rightSpeed = -rightSpeed;
    
    analogWrite(leftMotor[0], 0);
    analogWrite(leftMotor[1], leftSpeed);
    analogWrite(rightMotor[0], 0);
    analogWrite(rightMotor[1], rightSpeed);    /* Backward */
  }
  
  else if (leftSpeed == 0 && rightSpeed >= 0)
  {
    analogWrite(leftMotor[0], 0);                     /*Left */
    analogWrite(leftMotor[1], 0);
    analogWrite(rightMotor[0], rightSpeed);
    analogWrite(rightMotor[1], 0);
  }
  
  else if (leftSpeed >= 0 && rightSpeed == 0)
  
  {
    analogWrite(leftMotor[0], leftSpeed);
    analogWrite(leftMotor[1], 0);
    analogWrite(rightMotor[0], 0);  /*right */
    analogWrite(rightMotor[1], 0);
  }
  
  else if (leftSpeed >= 0 && rightSpeed <= 0)
  {
    rightSpeed = - rightSpeed;
    analogWrite(leftMotor[0], leftSpeed);  /* turn clockwise */
    analogWrite(leftMotor[1], 0);
    analogWrite(rightMotor[0], 0);
    analogWrite(rightMotor[1], rightSpeed);
  }
  
  else if (leftSpeed <= 0 && rightSpeed >= 0)
  {
    
    leftSpeed = - leftSpeed;
    analogWrite(leftMotor[0], 0);
    analogWrite(leftMotor[1], leftSpeed);   /* turn anti clockwise */
    analogWrite(rightMotor[0], rightSpeed);
    analogWrite(rightMotor[1], 0);
  } 
  
}

int matchPattern(String one, String two)
{
  if (one == two) return 1;
  else return 0;
}


void getPattern()
{
  //int i;
  for (int i = 0; i < 8 ; i++)
  {
   if (analogRead(sensor[i]) < THRESHOLD){
   // Serial.println(analogRead(sensor[i]));
   
    pattern[i] = '1';
    
   } else {
    // Serial.println(analogRead(sensor[i]));
    pattern[i] = '0';
    
   }
  }
  
  pattern[8] = '\0';
  //patterns[8] = '\0';
  
  
  //Serial.println(patterns);
  //return pattern[8];
 // currentPattern = pattern;
 
  bluetooth.println(pattern);
    
 }


void setup()
{
                       
  Serial.begin(9600);
  bluetooth.begin(9600);

                             
                                 
         
 //forwardPattern.toCharArray(forwardPatternArray, 9);
  //leftPattern.toCharArray(leftPatternArray, 9);
  //rightPattern.toCharArray(rightPatternArray, 9);
  
  for (int i = 0; i < 2 ; i++)
  {
    pinMode(leftMotor[i], OUTPUT);
    pinMode(rightMotor[i], OUTPUT);
  }
  
  for (int i =0; i < 8; i++)
  {
    pinMode(sensor[i], INPUT);
  }
}


 
void loop()
{
  //setMotors(200, 200);
  getPattern();
  //delay(1000);
  
  if (matchPattern(pattern, forwardPattern) == 1 || matchPattern(pattern, forward00111110) == 1 ||  matchPattern(pattern, forward01111100))
  {
   setMotors(200, 200); 
  }
  
  
  
  else if (matchPattern(pattern, leftPattern) == 1) {
     setMotors(120, 90);   // 01111000
  }
  
  else if (matchPattern(pattern, rightPattern) == 1)
  {
    
    setMotors(90, 120);  // 00011110
  }
  
  else if (matchPattern(pattern, slightLeft01111000) == 1 || matchPattern(pattern, slightLeft11111000) == 1 )
  {
   setMotors (120, 70); 
  }
  
  else if (matchPattern(pattern, slightRight00011110) == 1)
  {
    setMotors(90, 120); 
  }
  
  else if (matchPattern(pattern, hardRight00011111) == 1 || matchPattern(pattern, hardRight00001111) == 1 )
  
  {
    getPattern();
    while (matchPattern(pattern, forwardPattern) != 1){
     getPattern();
     setMotors(0, 150);
    }
   // setMotors(70, 120);
  }
  
   else if (matchPattern(pattern, hardLeft11100000) == 1 || matchPattern(pattern, hardLeft11110000) == 1 || matchPattern(pattern, slightTurn11111100) == 1)
   {
      setMotors(120, 70);
   }
  
  else setMotors(0, 0);
  //if (matchPattern(pattern, forwardPattern) == 1) {Serial.println("Bingo"); setMotors(155,152);}
  
  //else {Serial.println("Fucked"); setMotors(155, -155);}
  
  
  

}

