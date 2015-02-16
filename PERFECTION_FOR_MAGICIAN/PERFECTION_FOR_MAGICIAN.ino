/*
  Author: Manash
  CFMC = Change for Magician Chassis


*/


#define THRESHOLD 650

int times;
int x = 2;
int y1 = 90;
int y2 = 0;
int Speed = 150;
// Init all bot components


int sensor[] = {62, 61, 60, 59, 58, 57, 56, 55};


//int sensor[] = {62, 61, 60, 59, 58, 57, 56, 55};

// Added left sensor
int extraLeft = 63;
int extraRight = 54;

char leftReading[] = "0";
char rightReading[] = "0";

// Unusual patterns encountered
char unusual_11000000[] = "11000000";
char unusual_00000011[] = "00000011";
char unusual_01110000[] = "01110000";
char unusual_10000000[] = "10000000";
char unusual_00000001[] = "00000001";


char unusual_single_left[] = "1";
char unusual_single_right[] = "1";







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
  if (analogRead(extraLeft) < THRESHOLD){
    leftReading[0] = '0';
  }  else {
     leftReading[0] = '1'; 
 }
 
 if (analogRead(extraRight) < THRESHOLD){
   rightReading[0] = '0';
 } else {
   rightReading[0] = '1';
 }
   
  Serial.print(leftReading);
  Serial.print(pattern);
  Serial.print(rightReading);
  Serial.println();
  
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

const char pos_01111111[] = "01111111";


const char pos_00000011[] = "00000011"; // reference from unusual
const char pos_00001110[] = "00001110"; // reference from unusual
const char pos_00000001[] = "00000001"; // reference from unusual


const char pos_00111111[] = "00111111"; // Added new pattern



const char pos_11111111[] = "11111111";


// All left Patterns in one string
const char* leftPatterns[] = {pos_00011110, pos_00001111, pos_00011111, pos_00000111, pos_00001100, pos_00000011, pos_00001110, pos_00000001};


///char pos_01111000[] = "01111000"; // Leaning right, fix left

const char pos_01111000[] = "01111000"; // More Leaning right, fix left

const char pos_11111000[] = "11111000"; // More slight leaning right, fix left
//const char pos_01111000[] = "01111000"; // Reference unusual
const char pos_11110000[] = "11110000";
const char pos_11100000[] = "11100000"; // Most leaning right, fix left
const char pos_00110000[] = "00110000"; // fix right
const char pos_01110000[] = "01110000"; // Reference from unusual_01110000
const char pos_10000000[] = "10000000"; // Reference from unusual_10000000
const char pos_11111110[] = "11111110";

const char pos_11000000[] = "11000000"; // Reference from unusual_11000000



/// added extra pattern for left

const char pos_11111100[] = "11111100";

// All right patterns in one string




const char* rightPatterns[] = {pos_01111000, pos_11111000, pos_11110000, pos_11100000, pos_00110000, pos_11000000, pos_01110000, pos_10000000};
//const char* requiredPos[] = {preferredPos_1, preferredPos_2, preferredPos_3, preferredPos_4};
//const char* leftPatterns[] = {pos_00011110, pos_00001111, pos_00011111, pos_00000111, pos_00001100};


/*
void fixit()
{
  //getPatterns();
  if (strcmp(pattern, leftPatterns[0]) == 0) {setMotors(y1, -y2); delay(x);}
  if (strcmp(pattern, leftPatterns[1]) == 0) {setMotors(y1, -y2); delay(x);}
  if (strcmp(pattern, leftPatterns[2]) == 0) {setMotors(y1, -y2); delay(x);}
  if (strcmp(pattern, leftPatterns[3]) == 0) {setMotors(y1, -y2); delay(x);}
  if (strcmp(pattern, leftPatterns[4]) == 0) {setMotors(y1, -y2); delay(x);}
  if (strcmp(pattern, leftPatterns[5]) == 0) {setMotors(y1, -y2); delay(x);}
  if (strcmp(pattern, leftPatterns[6]) == 0) {setMotors(y1, -y2); delay(x);}
  if (strcmp(pattern, leftPatterns[7]) == 0) {setMotors(y1, -y2); delay(x);}
  
  if (strcmp(pattern, rightPatterns[0]) == 0) {setMotors(-y2, y1); delay(x);}
  if (strcmp(pattern, rightPatterns[1]) == 0) {setMotors(-y2, y1); delay(x);}
  if (strcmp(pattern, rightPatterns[2]) == 0) {setMotors(-y2, y1); delay(x);}
  if (strcmp(pattern, rightPatterns[3]) == 0) {setMotors(-y2, y1); delay(x);}
  if (strcmp(pattern, rightPatterns[4]) == 0) {setMotors(-y2, y1); delay(x);}
  if (strcmp(pattern, rightPatterns[5]) == 0) {setMotors(-y2, y1); delay(x);}
  if (strcmp(pattern, rightPatterns[6]) == 0) {setMotors(-y2, y1); delay(x);}
  if (strcmp(pattern, rightPatterns[7]) == 0) {setMotors(-y2, y1); delay(x);}
  
  if(strcmp(leftReading, "1") == 0 && strcmp(pattern, stopPattern) == 0){
          setMotors(0, Speed);
          delay(50);
          setMotors(0,0); 
          delay(2);
        }
        
   if(strcmp(rightReading, "1") == 0 && strcmp(pattern, stopPattern) == 0){
     
     setMotors(Speed, 0);
          delay(50);
          setMotors(0,0); 
          delay(2);
     
   }
        
  
  
}*/


bool fixit()
{
  ///getPatterns();
  bool fixed = false;
  if (strcmp(pattern, leftPatterns[0]) == 0) {setMotors(y1, -y2); delay(x); fixed = true;}
  if (strcmp(pattern, leftPatterns[1]) == 0) {setMotors(y1, -y2); delay(x); fixed = true;}
  if (strcmp(pattern, leftPatterns[2]) == 0) {setMotors(y1, -y2); delay(x); fixed = true;}
  if (strcmp(pattern, leftPatterns[3]) == 0) {setMotors(y1, -y2); delay(x); fixed = true;}
  if (strcmp(pattern, leftPatterns[4]) == 0) {setMotors(y1, -y2); delay(x); fixed = true;}
  if (strcmp(pattern, leftPatterns[5]) == 0) {setMotors(y1, -y2); delay(x); fixed = true;}
  if (strcmp(pattern, leftPatterns[6]) == 0) {setMotors(y1, -y2); delay(x); fixed = true;}
  if (strcmp(pattern, leftPatterns[7]) == 0) {setMotors(y1, -y2); delay(x); fixed = true;}
  
  if (strcmp(pattern, rightPatterns[0]) == 0) {setMotors(-y2, y1); delay(x); fixed = true;}
  if (strcmp(pattern, rightPatterns[1]) == 0) {setMotors(-y2, y1); delay(x); fixed = true;}
  if (strcmp(pattern, rightPatterns[2]) == 0) {setMotors(-y2, y1); delay(x); fixed = true;}
  if (strcmp(pattern, rightPatterns[3]) == 0) {setMotors(-y2, y1); delay(x); fixed = true;}
  if (strcmp(pattern, rightPatterns[4]) == 0) {setMotors(-y2, y1); delay(x); fixed = true;}
  if (strcmp(pattern, rightPatterns[5]) == 0) {setMotors(-y2, y1); delay(x); fixed = true;}
  if (strcmp(pattern, rightPatterns[6]) == 0) {setMotors(-y2, y1); delay(x); fixed = true;}
  if (strcmp(pattern, rightPatterns[7]) == 0) {setMotors(-y2, y1); delay(x); fixed = true;}
  
  if(strcmp(leftReading, "1") == 0 && strcmp(pattern, stopPattern) == 0){
          setMotors(0, Speed);
          delay(50);
          setMotors(0,0); 
          delay(2);
          fixed = true;
        }
        
   if(strcmp(rightReading, "1") == 0 && strcmp(pattern, stopPattern) == 0){
     
     setMotors(Speed, 0);
          delay(50);
          setMotors(0,0); 
          delay(2);
          fixed = true;
     
   }
        
  return fixed;
  
}





void uTurn()
{
  if ((leftReading[0] == '0' && rightReading[0] == '0') && ( pattern[2]=='1' || pattern[3] == '1' || pattern[4] == '1' || pattern[5] == '1' || pattern[6] == '1')){
     if (strcmp(pattern, requiredPos[0]) == 0 || strcmp(pattern, requiredPos[1]) == 0 || strcmp(pattern, requiredPos[2]) == 0 ||  strcmp(pattern, requiredPos[3]) == 0 ) {setMotors(Speed, Speed); delay(25);}
     else fixit(); 
  }
  
  else {
   setMotors(-100, 100);
   delay(1); 
  }
}
 
  
  
 



void setup() {
  
  Serial.begin(9600);
  // put your setup code here, to run once:
  Serial.println("Fucked");
  
  
  // Added pinModes!!!
  
  for (int i = 0; i <8; i++){
    pinMode(sensor[i], INPUT);
  }
  pinMode(extraLeft, INPUT);
  pinMode(extraRight, INPUT); // Added
  
  for (int i = 0; i < 2; i++){
    pinMode(leftMotor[i], OUTPUT);
    pinMode(rightMotor[i], OUTPUT);
  }
 //Serial.println (strcmp(patterns, leftPatterns[0]));
  
  setMotors(0,0);
  delay(5000);
}

void loop() {
  // Delay back time for 5cm in 150 ms
  // Added anti clock wise turns [guessed turn time: estd: 450ms @ this speed]
  // put your main code here, to run repeatedly:
  // Added U turn guessed time estd: 600ms for StopPattern
  
  delay(1);
  getPatterns();
  if (strcmp(pattern, requiredPos[0]) == 0 || strcmp(pattern, requiredPos[1]) == 0 || strcmp(pattern, requiredPos[2]) == 0 ||  strcmp(pattern, requiredPos[3]) == 0 ) {setMotors(Speed, Speed); delay(25);}
  
  // Cross-section
 else if (
            (strcmp(pattern, pos_11111111) == 0  && leftReading[0] == '1') || 
            (strcmp(pattern, pos_11111111) == 0  && rightReading[0] == '1') || 
            (strcmp(pattern, pos_11111111) == 0  && leftReading[0] == '1') || 
            (strcmp(pattern, pos_11111111) == 0)  /*|| 
            (strcmp(pattern, "00011110") && rightReading[0] == '1')
            //|| 
            //(strcmp(pattern, pos_11111110) && leftReading[0] == '1') || 
            //(strcmp(pattern, pos_01111111) && rightReading[0] == '1')*/
         )
         
        
  {
 // getPatterns();
//  setMotors(0,0); delay(50); setMotors(-Speed, -Speed); delay(120); setMotors(0,0); delay(10); setMotors(0, Speed); delay(530); setMotors(0,0); delay(10);}
  
   
    if (!fixit()){
        setMotors(0,0); delay(300); /* setMotors(Speed, Speed); delay(80); */ setMotors(0,0); delay(10); setMotors(0, Speed); delay(450); setMotors(0,0); delay(10);
    }
    
    else {
     
       Serial.println("Turning left");
             setMotors(0,0);
            
             delay(10);
            /* setMotors(-Speed, -Speed);      // CMFC
                                                // Editing
             delay(130);*/
             setMotors(0,0);
             
             delay(500);
             setMotors(0, Speed);
             delay(350);                 // CMFC
             setMotors(0,0);
             delay(10);
      
      
    }
}
  
    
  
  
  else if (strcmp(pattern, stopPattern) == 0) 
      { 
           /* Serial.println("U Turn detected");
            setMotors(0,0); 
            delay(500); 
            setMotors(-Speed, -Speed);           // U turn 
            delay(160); 
            setMotors(-Speed, Speed); 
            delay(530); 
            setMotors(0,0); 
            delay(1000);
            */
            
            uTurn();
            
         /*   //getPattern(); /* Debugging here for marginal errors
            //if (strcmp(pattern, stopPattern) == 0 || strcmp(leftReading, "1")
            getPatterns();
            if (strcmp(pattern, stopPattern) == 0){
              while (strcmp(pattern, stopPattern) != 0){
                setMotors(0, 100);
                delay(20);
                setMotors(0,0);
                delay(10);
              } 
              
            }
            // End of debugging    */      
        }
  
  
  // Added left turn, for right turn just invert this!
  else if (
               (strcmp(pattern, pos_11111100) == 0 && strcmp(leftReading, "1") == 0) ||
               (strcmp(pattern, pos_11111000) == 0 && strcmp(leftReading, "1") == 0) ||
               (strcmp(pattern, pos_11110000) == 0 && strcmp(leftReading, "1") == 0) ||
               (strcmp(pattern, pos_11100000) == 0 && strcmp(leftReading, "1") == 0) //||
               
              // (strcmp(pattern, pos_11000000) == 0 && strcmp(leftReading, "1") == 0) //||
               //(strcmp(pattern, 
               //|| 
              /* (strcmp(pattern, pos_11111111) == 0 && strcmp(leftReading, "1") == 0) ||
               (strcmp(pattern, pos_11111110) == 0 && strcmp(leftReading, "1") == 0)   */    
          )
          
           {
             Serial.println("Turning left");
             setMotors(0,0);
             delay(10);
            /* setMotors(-Speed, -Speed);
             delay(130);*/
             setMotors(0,0);
             delay(500);
             setMotors(0, Speed);
             delay(500);
             setMotors(0,0);
             delay(10);
             
           }

   // Added right turn
    else if (
               (strcmp(pattern, pos_00111111) == 0 && strcmp(rightReading, "1") == 0) ||
               (strcmp(pattern, pos_00011111) == 0 && strcmp(rightReading, "1") == 0) ||
               (strcmp(pattern, pos_00001111) == 0 && strcmp(rightReading, "1") == 0) ||
               (strcmp(pattern, pos_00000111) == 0 && strcmp(rightReading, "1") == 0) //||
              // (strcmp(pattern, pos_00000011) == 0 && strcmp(rightReading, "1") == 0) 
               
           
           )
           {
             Serial.println("Turning right");
             setMotors(0,0);
             delay(10);
           /*  setMotors(-Speed, -Speed);
             delay(130);*/
             setMotors(0,0);
             delay(500);
             setMotors(Speed, 0);
             delay(500);
             setMotors(0,0);
             delay(10);
             
             
             /* Added more flexibility */
             getPatterns();
             if (strcmp(pattern, "00000000") == 0 || strcmp(rightReading, "1") == 0) {
               
              
              setMotors(200, -200);
             delay(100);                          // CFMC
             
             }
             
           }
           
        
           
      else  fixit();
  
  

  
}

