#define THERSHOLD  700
#define leftCenterSensor   59
#define leftNearSensor     60
#define leftFarSensor      62
#define rightCenterSensor  58
#define rightNearSensor    57
#define rightFarSensor     55
//#define extraLeft          61
//#define extraRight         56

int leftCenterReading;
int leftNearReading;
int leftFarReading;
int rightCenterReading;
int rightNearReading;
int rightFarReading;

int leftNudge;
int replaystage;
int rightNudge;

#define leapTime 130

#define leftMotor1  3
#define leftMotor2  4

#define rightMotor1 5
#define rightMotor2 6

#define led 13

char path[30] = {};
int pathLength;
int readLength;

void setup(){
  
  pinMode(leftCenterSensor, INPUT);
  pinMode(leftNearSensor, INPUT);
  pinMode(leftFarSensor, INPUT);
  pinMode(rightCenterSensor, INPUT);
  pinMode(rightNearSensor, INPUT);
  pinMode(rightFarSensor, INPUT);
    
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(led, OUTPUT);
  //Serial.begin(115THERSHOLD);
  analogWrite(led, HIGH);
  delay(1000);
}


void loop(){
  
 readSensors();                                                                                     
 // straight();
 if((leftFarReading<THERSHOLD || rightFarReading<THERSHOLD)&&
  (leftCenterReading>THERSHOLD && rightCenterReading>THERSHOLD))
  {
    straight();                                                                                      
  }
  else{                                                                                              
    leftHandWall();                                                                                   
  }

}

void setMotors(int leftSpeed, int rightSpeed)
{
  if (leftSpeed >= 0 && rightSpeed >= 0)
  {
    analogWrite(leftMotor1, leftSpeed);   /*   Forward  */
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, rightSpeed);
    analogWrite(rightMotor2, 0);
  }

  else if (leftSpeed < 0 && rightSpeed < 0)
  {
    leftSpeed = -leftSpeed;
    rightSpeed = -rightSpeed;

    analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, leftSpeed);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, rightSpeed);    /* Backward */
  }

  else if (leftSpeed == 0 && rightSpeed >= 0)
  {
    analogWrite(leftMotor1, 0);                     /*Left */
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, rightSpeed);
    analogWrite(rightMotor2, 0);
  }

  else if (leftSpeed >= 0 && rightSpeed == 0)

  {
    analogWrite(leftMotor1, leftSpeed);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);  /*right */
    analogWrite(rightMotor2, 0);
  }

  else if (leftSpeed >= 0 && rightSpeed <= 0)
  {
    rightSpeed = - rightSpeed;
    analogWrite(leftMotor1, leftSpeed);  /* turn clockwise */
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, rightSpeed);
  }

  else if (leftSpeed <= 0 && rightSpeed >= 0)
  {

    leftSpeed = - leftSpeed;
    analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, leftSpeed);   /* turn anti clockwise */
    analogWrite(rightMotor1, rightSpeed);
    analogWrite(rightMotor2, 0);
  }

}
void readSensors(){
  
  leftCenterReading  = analogRead(leftCenterSensor);
  leftNearReading    = analogRead(leftNearSensor);
  leftFarReading     = analogRead(leftFarSensor);
  rightCenterReading = analogRead(rightCenterSensor);
  rightNearReading   = analogRead(rightNearSensor);
  rightFarReading    = analogRead(rightFarSensor);  

// serial printing be0 for debugging purposes

// Serial.print("leftCenterReading: ");
// Serial.println(leftCenterReading);
// Serial.print("leftNearReading: ");
// Serial.println(leftNearReading);
// Serial.print("leftFarReading: ");
// Serial.println(leftFarReading);
  
// Serial.print("rightCenterReading: ");
// Serial.println(rightCenterReading);
// Serial.print("rightNearReading: ");
// Serial.println(rightNearReading);
// Serial.print("rightFarReading: ");
// Serial.println(rightFarReading);
// delay(THERSHOLD);
  

}


void leftHandWall(){
  

  if( leftFarReading>THERSHOLD && rightFarReading>THERSHOLD){
    analogWrite(leftMotor1, 130);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 130);
    analogWrite(rightMotor2, 0);
    delay(leapTime);
    readSensors();
    
    if(leftFarReading>THERSHOLD || rightFarReading>THERSHOLD){
      done();
    }
    if(leftFarReading<THERSHOLD && rightFarReading<THERSHOLD){ 
      turnLeft();
    }
    
  }
  
  if(leftFarReading>THERSHOLD){ // if you can turn left then turn left
    analogWrite(leftMotor1, 130);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 130);
    analogWrite(rightMotor2, 0);
    delay(leapTime);
    readSensors();
      
      if(leftFarReading<THERSHOLD && rightFarReading<THERSHOLD){
        turnLeft();
      }
      else{
        done();
      }
  }
   
  if(rightFarReading>THERSHOLD){
    analogWrite(leftMotor1, 130);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 130);
    analogWrite(rightMotor2, 0);
    delay(30);
    readSensors();
    
    if(leftFarReading>THERSHOLD){
      delay(leapTime-30);
      readSensors();
      
      if(rightFarReading>THERSHOLD && leftFarReading>THERSHOLD){
        done();
      }
      else{
        turnLeft();
        return;
      }
    }
    delay(leapTime-30);
    readSensors();
    if(leftFarReading<THERSHOLD && leftCenterReading<THERSHOLD &&
      rightCenterReading<THERSHOLD && rightFarReading<THERSHOLD){
      turnRight();
      return;
    }
    //path[pathLength]='S';
   // Serial.println("s");
    //pathLength++;
    //Serial.print("Path length: ");
    //Serial.println(pathLength);
    if(path[pathLength-2]=='B'){
    //Serial.println("shortening path");
    //shortPath();
     }
    straight();
  }
  readSensors();
  if(leftFarReading<THERSHOLD && leftCenterReading<THERSHOLD && rightCenterReading<THERSHOLD 
    && rightFarReading<THERSHOLD && leftNearReading<THERSHOLD && rightNearReading<THERSHOLD){
    turnAround();
  }

}
void done(){
  analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
  //replaystage=1;
  //path[pathLength]='D';
  //pathLength++;
 while(analogRead(leftFarSensor)>THERSHOLD){
   analogWrite(led, 0);
   delay(130);
   analogWrite(led, HIGH);
   delay(130);
 }
 delay(500);
  //replay();
}

void turnLeft(){
  
    
 
  while(analogRead(rightCenterSensor)>THERSHOLD||analogRead(leftCenterSensor)>THERSHOLD){
     analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 130);
    analogWrite(rightMotor1, 130);
    analogWrite(rightMotor2, 0);
    delay(2);
     analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    delay(1);
  }
    
  while(analogRead(rightCenterSensor)<THERSHOLD){
    analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 130);
    analogWrite(rightMotor1, 130);
    analogWrite(rightMotor2, 0);
    delay(2);
    analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    delay(1);
  }
 
 /* if(replaystage==0){
    path[pathLength]='L';
    //Serial.println("l");
    pathLength++;
    //Serial.print("Path length: ");
    //Serial.println(pathLength);
      if(path[pathLength-2]=='B'){
        //Serial.println("shortening path");
        //shortPath();
      }
  }*/
}

void turnRight(){

    
  while(analogRead(rightCenterSensor)>THERSHOLD){
     analogWrite(leftMotor1, 130);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 130);
    delay(2);
     analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    delay(1);
  }
   while(analogRead(rightCenterSensor)<THERSHOLD){
     analogWrite(leftMotor1, 130);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 130);
    delay(2);
     analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    delay(1);
  }
   while(analogRead(leftCenterSensor)<THERSHOLD){
     analogWrite(leftMotor1, 130);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 130);
    delay(2);
    analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    delay(1);
  }
  
  /*if(replaystage==0){
  path[pathLength]='R';
  Serial.println("r");
  pathLength++;
  Serial.print("Path length: ");
  Serial.println(pathLength);
    if(path[pathLength-2]=='B'){
      Serial.println("shortening path");
      //shortPath();
    }
  }*/
 
}

void straight(){
  if (rightFarReading < THERSHOLD &&((leftFarReading > THERSHOLD && leftNearReading > THERSHOLD)||(leftNearReading > THERSHOLD&& leftCenterReading > THERSHOLD)))
      {
      //setMotors(0,0);
     // delay(20);
      setMotors(50,80);
      delay(20);
      //setMotors(80,80);
      
    }
else if (leftFarReading < THERSHOLD && ((rightFarReading > THERSHOLD && rightNearReading > THERSHOLD)||(rightNearReading > THERSHOLD&& rightCenterReading > THERSHOLD)))
     {
     // setMotors(0,0);
     // delay(20);
      setMotors(80,50);
      delay(20);
      //setMotors(80,80);
      
    }
else if (leftFarSensor < THERSHOLD && rightFarSensor < THERSHOLD && ( leftNearSensor >THERSHOLD|| leftCenterSensor > THERSHOLD|| rightNearSensor || rightCenterSensor > THERSHOLD))
  setMotors(130, 145);
}

void turnAround(){
    /*analogWrite(leftMotor1, 130);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 130);
    analogWrite(rightMotor2, 0);
    delay(150);*/
    setMotors(-130,130);
    delay(135);
   while(analogRead(leftCenterSensor)<THERSHOLD){
     analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 130);
    analogWrite(rightMotor1, 130);
    analogWrite(rightMotor2, 0);
    delay(20);
     analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    delay(1);
  }
  //path[pathLength]='B';
  //pathLength++;
  straight();
  //Serial.println("b");
  //Serial.print("Path length: ");
  //Serial.println(pathLength);
}

/*void shortPath(){
 int shortDone=0;
  if(path[pathLength-3]=='L' && path[pathLength-1]=='R'){
    pathLength-=3;
    path[pathLength]='B';
    //Serial.println("test1");
    shortDone=1;
  }
   
  if(path[pathLength-3]=='L' && path[pathLength-1]=='S' && shortDone==0){
    pathLength-=3;
    path[pathLength]='R';
    //Serial.println("test2");
    shortDone=1;
  }
   
  if(path[pathLength-3]=='R' && path[pathLength-1]=='L' && shortDone==0){
    pathLength-=3;
    path[pathLength]='B';
    //Serial.println("test3");
    shortDone=1;
  }
  
   
  if(path[pathLength-3]=='S' && path[pathLength-1]=='L' && shortDone==0){
    pathLength-=3;
    path[pathLength]='R';
    //Serial.println("test4");
    shortDone=1;
  }
     
  if(path[pathLength-3]=='S' && path[pathLength-1]=='S' && shortDone==0){
    pathLength-=3;
    path[pathLength]='B';
    //Serial.println("test5");
    shortDone=1;
  }
    if(path[pathLength-3]=='L' && path[pathLength-1]=='L' && shortDone==0){
    pathLength-=3;
    path[pathLength]='S';
    //Serial.println("test6");
    shortDone=1;
  }
  
  path[pathLength+1]='D';
  path[pathLength+2]='D';
  pathLength++;
  //Serial.print("Path length: ");
  //Serial.println(pathLength);
  //printPath();
}*/




/*void printPath(){
  Serial.println("+++++++++++++++++");
  int x;
  while(x<=pathLength){
  Serial.println(path[x]);
  x++;
  }
  Serial.println("+++++++++++++++++");
}*/


/*void replay(){
   readSensors();
  if(leftFarReading<THERSHOLD && rightFarReading<THERSHOLD){
    straight();
  }
  else{
    if(path[readLength]=='D'){
       analogWrite(leftMotor1, 130);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 130);
    analogWrite(rightMotor2, 0);
    delay(100);
    analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
      endMotion();
    }
    if(path[readLength]=='L'){
     analogWrite(leftMotor1, 130);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 130);
    analogWrite(rightMotor2, 0);
    delay(leapTime);
      turnLeft();
    }
    if(path[readLength]=='R'){
       analogWrite(leftMotor1, 130);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 130);
    analogWrite(rightMotor2, 0);
    delay(leapTime);
    turnRight();
    }
    if(path[readLength]=='S'){
       analogWrite(leftMotor1, 130);
    analogWrite(leftMotor2, 0);
    analogWrite(rightMotor1, 130);
    analogWrite(rightMotor2, 0);
    delay(leapTime);
    straight();
    }
    
    readLength++;
  }
    
  replay();
  
}*/

void endMotion(){
    analogWrite(led, 0);
    delay(500);
    analogWrite(led, 130);
    delay(130);
      analogWrite(led, 0);
    delay(130);
    analogWrite(led, 130);
    delay(500);
  endMotion();
}
