#define THRESHOLD 700


char preferredPos_1[] = "00111000"; // Keep this up
char preferredPos_2[] = "00011100"; // Or Keep this up
char preferredPos_3[] = "00111100"; // Or this up
char preferredPos_4[] = "00011000";


char stopPattern[] = "0000000";

/* All leaning left and fix right or clockwise to fix*/

char pos_00011110[] = "00011110"; // Leaning left, fix right
char pos_00001111[] = "00001111"; // More Leaning left, fix right
char pos_00011111[] = "00011111"; // More slight leaning left, fix right
char pos_00000111[] = "00000111"; // Most leaning left, fix right
char pos_00001100[] = "00001100"; // fix right
char pos_11111111[] = "11111111";


/* All leaning right and fix left or anticlockwise to fix */

char pos_01111000[] = "01111000"; // Leaning right, fix left
char pos_11110000[] = "11110000"; // More Leaning right, fix left
char pos_11111000[] = "11111000"; // More slight leaning right, fix left
char pos_11100000[] = "11100000"; // Most leaning right, fix left
char pos_00110000[] = "00110000"; // fix right


char pattern[] = "00000000";

// Sensor and motor initialization
int sensor[] = {62, 61, 60, 59, 58, 57, 56, 55};
int leftMotor[] = {3, 4};
int rightMotor[] = {5, 6};

// storing patterns 


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
  
  Serial.println(pattern);
}


// Check Pattern or match pattern
/*int strcmp(String one, String two)
{
  if (one == two) return 1;
  else return 0;
}*/

// Position fixer
void fixPosition()
{
  getPattern();
  
  //bool x;
  //getPattern();
  while (strcmp(pattern,preferredPos_1) != 0 || strcmp(pattern,preferredPos_2) != 0 || strcmp(pattern,preferredPos_3) != 0 || strcmp(pattern, preferredPos_4) != 0)
  {  
    
    if (strcmp(pattern, pos_00011110) == 0 || strcmp(pattern, pos_00001111) == 0 || strcmp(pattern, pos_00011111) == 0 || strcmp(pattern, pos_00000111) == 0 || strcmp(pattern, pos_00001100) == 0){
      getPattern();
     Serial.println("Go to right"); 
      
    }
    /*if (strcmp(pattern, pos_00011110) == 1 || strcmp(pattern, pos_00001111) == 1 || strcmp(pattern, pos_00011111) == 1 || strcmp(pattern, pos_00000111) == 1 || strcmp(pattern, pos_00001100) == 1){
       setMotors(50, -50);
       delay(50);
       Serial.println("First condition");
    } 
    else if (strcmp(pattern, pos_01111000) == 1 || strcmp(pattern, pos_11110000) == 1 || strcmp(pattern, pos_11111000) == 1 || strcmp(pattern, pos_11100000) == 1 || strcmp(pattern, pos_00110000) == 1)
     {
       setMotors(-100, 100);
       delay(50);
       Serial.println("second condition");
     } */
     else if (strcmp(pattern, pos_01111000) == 0|| strcmp(pattern, pos_11110000) == 0|| strcmp(pattern, pos_11111000) == 0 || strcmp(pattern, pos_11100000) == 0 || strcmp(pattern, pos_00110000) == 0){
       getPattern();
       Serial.println("Go to left");
     }
     
     else {
       getPattern();
      Serial.println("Unknown pattern"); 
     }
     
   }
   setMotors(0,0);  
}
  
void setup()
{
  Serial.begin(9600);
  Serial.println("Ready for debugging");
  for (int i = 0; i <8; i++){
    pinMode(sensor[i], INPUT);
  }
  for (int i = 0; i < 2; i++){
    pinMode(leftMotor[i], OUTPUT);
    pinMode(rightMotor[i], OUTPUT);
  }
  
  getPattern();
  delay(2000);
  
}


void loop()
{
  getPattern();
  if (strcmp(pattern, stopPattern) == 0) Serial.println("Bot stopped");
  else fixPosition();
}
