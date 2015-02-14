#define THRESHOLD 700

int x = 10;
int y1 = 70;
int y2 = 0;
// Init all bot components

int sensor[] = {62, 61, 60, 59, 58, 57, 56, 55};
int leftMotor[] = {3, 4};
int rightMotor[] = {5, 6};

char pattern[] = "00000000";


// Drive the motors

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

// Fetch patterns

void getPatterns()
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

//



const char preferredPos_1[] = "00111000"; // Keep this up
const char preferredPos_2[] = "00011100"; // Or Keep this up
const char preferredPos_3[] = "00111100"; // Or this up
const char preferredPos_4[] = "00011000";

const char* requiredPos[] = {preferredPos_1, preferredPos_2, preferredPos_3, preferredPos_4};



const char stopPattern[] = "00000000";

const char pos_00011110[] = "00011110"; // Leaning left, fix right
const char pos_00001111[] = "00001111"; // More Leaning left, fix right
const char pos_00011111[] = "00011111"; // More slight leaning left, fix right
const char pos_00000111[] = "00000111"; // Most leaning left, fix right
const char pos_00001100[] = "00001100"; // fix right

const char pos_11111111[] = "11111111";


// All left Patterns in one string
const char* leftPatterns[] = {pos_00011110, pos_00001111, pos_00011111, pos_00000111, pos_00001100};


///char pos_01111000[] = "01111000"; // Leaning right, fix left

const char pos_01111000[] = "11110000"; // More Leaning right, fix left
const char pos_11111000[] = "11111000"; // More slight leaning right, fix left
const char pos_11110000[] = "11110000";
const char pos_11100000[] = "11100000"; // Most leaning right, fix left
const char pos_00110000[] = "00110000"; // fix right

// All right patterns in one string




const char* rightPatterns[] = {pos_01111000, pos_11111000, pos_11110000, pos_11100000, pos_00110000};
//const char* requiredPos[] = {preferredPos_1, preferredPos_2, preferredPos_3, preferredPos_4};
//const char* leftPatterns[] = {pos_00011110, pos_00001111, pos_00011111, pos_00000111, pos_00001100};


void fixit()
{
  //getPatterns();
  if (strcmp(pattern, leftPatterns[0]) == 0) {setMotors(y1, -y2); delay(x);}
  if (strcmp(pattern, leftPatterns[1]) == 0) {setMotors(y1, -y2); delay(x);}
  if (strcmp(pattern, leftPatterns[2]) == 0) {setMotors(y1, -y2); delay(x);}
  if (strcmp(pattern, leftPatterns[3]) == 0) {setMotors(y1, -y2); delay(x);}
  if (strcmp(pattern, leftPatterns[4]) == 0) {setMotors(y1, -y2); delay(x);}
  if (strcmp(pattern, rightPatterns[0]) == 0) {setMotors(-y2, y1); delay(x);}
  if (strcmp(pattern, rightPatterns[1]) == 0) {setMotors(-y2, y1); delay(x);}
  if (strcmp(pattern, rightPatterns[2]) == 0) {setMotors(-y2, y1); delay(x);}
  if (strcmp(pattern, rightPatterns[3]) == 0) {setMotors(-y2, y1); delay(x);}
  if (strcmp(pattern, rightPatterns[4]) == 0) {setMotors(-y2, y1); delay(x);}
  
}



void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  Serial.println("Fucked");
 //Serial.println (strcmp(patterns, leftPatterns[0]));
  setMotors(0,0);
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:

  getPatterns();
  if (strcmp(pattern, requiredPos[0]) == 0 || strcmp(pattern, requiredPos[1]) == 0 || strcmp(pattern, requiredPos[2]) == 0 ||  strcmp(pattern, requiredPos[3]) == 0 || strcmp(pattern, pos_11111111) == 0) {setMotors(130, 130); delay(25);}
  else if (strcmp(pattern, stopPattern) == 0) {setMotors(0,0);}
  else  fixit();
}
