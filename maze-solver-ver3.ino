#define THRESHOLD 300

int sensor[] = {60, 59, 58, 57, 56, 55, 54};
//int sensor[] = {54, 55, 56, 57, 58, 59, 60};
int leftMotor[] = {3,4};
int rightMotor[] = {5,6};
int extra = 52;


String pattern = "0000000";
//String forwardPattern = "0011100";
//String leftPattern = "0111100";
//String rightPattern = "000111110";

String leftPattern_1111100 = "1111100";
String rightPattern_0011111 = "0011111";
//String rightPattern_
String forwardPattern_0011100 = "0011100";
String forwardPattern_0111000 = "0111000";
String forwardPattern_0001110 = "0001110";




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
  for (int i = 0; i < 7 ; i++)
  {
   if (analogRead(sensor[i]) < THRESHOLD){
   // Serial.println(analogRead(sensor[i]));
   
    pattern[i] = '0';
    
   } else {
    // Serial.println(analogRead(sensor[i]));
    pattern[i] = '1';
    
   }
  }
  
  pattern[7] = '\0';
  //patterns[8] = '\0';
  
  
  //Serial.println(patterns);
  //return pattern[8];
 // currentPattern = pattern;
 
  Serial.println(pattern);
    
 }


void setup()
{
  Serial.begin(9600);
  Serial.println("Ready");

  pinMode(extra, OUTPUT);
  digitalWrite(extra, HIGH);
  
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
  
  if (matchPattern(pattern, forwardPattern_0011100) == 1)
  {
    setMotors(200, 200);
  }
  
  else if (matchPattern(pattern, forwardPattern_0111000) == 1){
    setMotors(200, 180);
  }
  
  else if (matchPattern(pattern, forwardPattern_0001110) == 1){
     setMotors(180, 200); 
  }
  
  else {
     setMotors(0, 0);
    
  }
  //if (matchPattern(pattern, forwardPattern) == 1) {Serial.println("Bingo"); setMotors(155,152);}
  
  //else {Serial.println("Fucked"); setMotors(155, -155);}
  
  
  

}
