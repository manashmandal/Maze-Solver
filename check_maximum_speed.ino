#define THRESHOLD 700

int sensor[] = {62, 61, 60, 59, 58, 57, 56, 55};
int leftMotor[] = {3, 4};
int rightMotor[] = {5, 6};

String pattern = "00000000";

void getPattern()
{
  //int i;
  for (int i = 0; i < 8 ; i++)
  {
    if (analogRead(sensor[i]) < THRESHOLD) {
      // Serial.println(analogRead(sensor[i]));

      pattern[i] = '0';

    } else {
      // Serial.println(analogRead(sensor[i]));
      pattern[i] = '1';

    }
  }
	 pattern[8] = '\0';
   Serial.println(pattern);

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

void setup()
{
  Serial.begin(9600);
  Serial.println("Ready");

  pinMode(extra, OUTPUT);
  //digitalWrite(extra, HIGH);

  for (int i = 0; i < 2 ; i++)
  {
    pinMode(leftMotor[i], OUTPUT);
    pinMode(rightMotor[i], OUTPUT);
  }

  for (int i = 0; i < 8; i++)
  {
    pinMode(sensor[i], INPUT);
  }
}


void loop()
{
  getPattern();
  if (pattern != "11111111") setMotors(100,100);
  else setMotors(0,0);
}



