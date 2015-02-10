#define THRESHOLD 300

int sensor[] = {55, 56, 57, 58, 59, 60, 61};

char pattern[8];

void setup()
{
  Serial.begin(9600);
  for (int i = 0; i <7; i++){
    pinMode(sensor[i], INPUT);
  }
  
  Serial.println("Ready for fucking!");
}

void getPattern()
{
  for (int i = 0; i < 7; i++){
    if (analogRead(sensor[i]) < THRESHOLD){
      pattern[i] = '0';
    } else {
      pattern[i] = '1';
    }
  }
  pattern[7] = '\0';
  Serial.println(pattern);
}


void loop()
{
  for (int i = 0; i < 7 ; i++){
    Serial.print("Sensor [" + String(i) + "] = ");
    Serial.println(analogRead(sensor[i]));
    delay(250);
  }
  getPattern();
  delay(1000);
}
