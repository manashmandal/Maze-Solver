#define THRESHOLD 500

int times = 0;
int Speed = 0;
int Delay = 0;
int dir = 0;


//int sensor[] = {55, 56, 57, 58, 59, 60, 61};
int sensor[] = {62, 61, 60, 59, 58, 57, 56, 55};



char pattern[9];

void setup()
{
  Serial.begin(9600);
  Serial.println("Ready for debugging");
  for (int i = 0; i <8; i++){
    pinMode(sensor[i], INPUT);
  }
  
  Serial.println("Ready for fucking!");
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
  
  if (times != 0)
  // For debugging purpose
  Serial.print("Times: " + String(times) + "\n"
              + "Speed: " + String(Speed) + "\n"
              + "Delay: " + String (Delay) + "\n"
              + "Dir: " + String(dir));
              
  times = 0;
}
