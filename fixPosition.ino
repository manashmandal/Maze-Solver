String preferredPos_1 = "00111000"; // Keep this up
String preferredPos_2 = "00011100"; // Or Keep this up
String preferredPos_3 = "00111100"; // Or this up

/* All leaning left and fix right or clockwise to fix*/

String pos_00011110 = "00011110"; // Leaning left, fix right
String pos_00001111 = "00001111"; // More Leaning left, fix right
String pos_00011111 = "00011111"; // More slight leaning left, fix right
String pos_00000111 = "00000111"; // Most leaning left, fix right


/* All leaning right and fix left or anticlockwise to fix */

String pos_01111000 = "01111000"; // Leaning right, fix left
String pos_11110000 = "11110000"; // More Leaning right, fix left
String pos_11111000 = "11111000"; // More slight leaning right, fix left
String pos_11100000 = "11100000"; // Most leaning right, fix left


// Sensor and motor initialization
int sensor[] = {62, 61, 60, 59, 58, 57, 56, 55};
int leftMotor[] = {3, 4};
int rightMotor[] = {5, 6};

// storing patterns 
char pattern[9];

/* Driving motors */

void setMotors(int leftSpeed, int rightSpeed)
{
  getPattern();
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

// Getting pattern
void getPattern()
{
  for (int i = 0; i < 8; i++){
    if (analogRead(sensor[i]) < THRESHOLD){
      pattern[i] = '0';
    } else {
      pattern[i] = '1';
    }
  }
  pattern[8] = '\0';
  Serial.println(pattern);
}


// Check Pattern or match pattern
int matchPattern(String one, String two)
{
  if (one == two) return 1;
  else return 0;
}

// Position fixer
void fixPosition()
{
  getPattern();
  while (pattern != preferredPos_1 || pattern != prefferedPos_2 || pattern != prefferedPos_3)
  {  
   switch(pattern){
     case pos_00011110:
     case pos_00001111:
     case pos_00011111:
     case pos_00000111:
       setMotors(255, -255);
       delay(50);
       setMotors(0,0);
     
     case pos_01111000:
     case pos_11110000:
     case pos_11111000:
     case pos_11100000:
       setMotors(-255, 255);
       delay(50);
       setMotors(0,0);  

    }  
}
  
void setup()
{
  Serial.begin(9600);
  Serial.println("Ready for debugging");
  for (int i = 0; i <8; i++){
    pinMode(sensor[i], INPUT);
  }
  getPattern();
  
}


void loop()
{
  getPattern();
  fixPosition();
}
