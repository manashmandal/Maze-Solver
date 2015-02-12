#define THRESHOLD 500

int times = 0;
int Speed = 0;
int Delay = 0;
int dir = 0;


//int sensor[] = {55, 56, 57, 58, 59, 60, 61};
int sensor[] = {62, 61, 60, 59, 58, 57, 56, 55};
int leftMotor[] = {3, 4};
int rightMotor[] = {5, 6};


char pattern[9];

void setup()
{
  Serial.begin(9600);
  Serial.println("Ready for debugging");
  for (int i = 0; i <8; i++){
    pinMode(sensor[i], INPUT);
  }
}



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


void getSensorReadings()
{
  for (int i = 0; i < 7 ; i++){
    Serial.print("Sensor [" + String(i) + "] = ");
    Serial.println(analogRead(sensor[i]));
    delay(250);
  }
  delay(1000);
}


void loop()
{
  
  while (Serial.available() > 0){
   times = Serial.parseInt();
   Speed = Serial.parseInt();
   Delay = Serial.parseInt();
   dir = Serial.parseInt();
  }
  

  
  if (times != 0 ){
    while (times > 0){
      if (dir == 0){
        setMotors(0, -Speed);
        delay(Delay);
        setMotors(0, 0); 
      }
      
      else {
       setMotors( -Speed, 0);
       delay(Delay);
       setMotors(0,0);
      }
     times--; 
     Serial.print("The pattern: ");
     getPattern();
    }
    
    times = 0;
 }
  
  
  
   /* // For debugging purpose
    Serial.print("Times: " + String(times) + "\n"
                + "Speed: " + String(Speed) + "\n"
                + "Delay: " + String (Delay) + "\n"
                + "Dir: " + String(dir));
              */
  
}
