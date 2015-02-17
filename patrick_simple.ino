// ------------------ Variables and constants ----------------
int led = 13;



char path[30] = {};
int pathLength;
int readLength;




// ============ Leaptime
#define leaptime 150   // Change leaptime
// ===========  threshold
#define threshold 500 // Change threshold value


// -----------------    Sensor definition  -------------
const int leftFarSensor = 61;
const int leftNearSensor = 60;
const int leftCenterSensor = 59;
const int rightCenterSensor = 58;
const int rightNearSensor = 57;
const int rightFarSensor = 56;

// ------------- Sensor reading vars =--------------
int leftFar, leftNear, leftCenter, rightCenter, rightNear, rightFar;

int leftNudge, replayStage, rightNudge;




// ---------- Others ----------

int delayVar1 = 30;     // Change it, default was 30
int delayVar2 = 150;    // change it, default was 150
int delayVar3 = 100;    // Change it, default was 100


// ------------------ Motor Definition ------------------

const int leftMotor[] = {3, 4};
const int rightMotor[] = {5, 6};

// ------------------- Speed --------------------------

const int speed = 130;




//------------------------------ Methods ---------------------

// Read sensor
void readSensors()
{
	leftFar = analogRead(leftFarSensor);
	leftNear = analogRead(leftNearSensor);
	leftCenter = analogRead(leftCenterSensor);
	rightCenter = analogRead(rightCenterSensor);
	rightNear = analogRead(rightNearSensor);
	rightFar = analogRead(rightFarSensor);
}

// Drive Motor
void setMotor(int l, int r)
{
	if (l >=0 && r >= 0){
		analogWrite(leftMotor[0], l);
		digitalWrite(leftMotor[1], LOW);  // Forward, left, right
		analogWrite(rightMotor[0], r);
		digitalWrite(rightMotor[1], LOW);
	}

	else if (l < 0 && r < 0)
	{
		l = -l;
		r = -r;
			// Backward
		digitalWrite(leftMotor[0], LOW);
		analogWrite(leftMotor[1], l);
		digitalWrite(rightMotor[0], LOW);
		analogWrite(rightMotor[1], r);
	}

	else if (l >= 0 && r < 0)
	{
		// Clockwise
		analogWrite(leftMotor[0], l);
		digitalWrite(leftMotor[1], LOW);
		digitalWrite(rightMotor[0], LOW);
		analogWrite(rightMotor[1], r);
	}
	// Anti-Clockwise
	else if (l < 0 && r >= 0)
	{
		digitalWrite(leftMotor[0], LOW);
		analogWrite(leftMotor[1], l);
		analogWrite(rightMotor[0], r);
		digitalWrite(rightMotor[1], LOW);
	}
}

// ------------------------------ Left Hand Wall Rule ----------------------------------

void leftHandWall()
{
	if (leftFar > threshold && rightFar > threshold)
	{
		setMotor(speed, speed);
		delay(leaptime);
		readSensors();
		
		if (leftFar > threshold || rightFar > threshold)
		{
			done();
		}
		
		if (leftFar < threshold && rightFar < threshold)
		{
			turnLeft();
		}
	}
	
	if (leftFar > threshold)
	{
		setMotor(speed, speed);
		delay(leaptime);
		readSensors();
		
		if (leftFar < threshold && rightFar < threshold)
		{
			turnLeft();
		} 
		
		else {
			done();
		}
	}
	
	if (rightFar > threshold)
	{
		setMotor(speed, speed);
		delay(delayVar1);
		readSensors();
		
		if (leftFar > threshold)
		{
			delay(leaptime - delayVar1);
			readSensors();
		
		if (rightFar > threshold && leftFar > threshold)
		{
			done();
		}
		
		else {
			turnLeft();
			return;
		}
	}
	
	delay(leaptime - delayVar1);
	readSensors();
	
	if (leftFar < threshold && leftCenter < threshold && rightCenter < threshold && rightFar < threshold)
	{
		turnRight();
		return;
	}
	
	
	readSensors();
	
	if (leftFar < threshold && leftCenter < threshold && rightCenter < threshold && leftNear < threshold && rightNear < threshold && rightFar < threshold)
	{
		turnAround();
	}
}



// -------------------- DONE ---------------------

void done()
{
	setMotor(0,0);
	
	
	while(analogRead(leftFarSensor) > threshold)
	{
		digitalWrite(led, LOW);
		delay(150);
		digitalWrite(led, HIGH);
		delay(150);
	}
	delay(500);
	
}


//----------------- Turn Left --------------

void turnLeft()
{
	while (analogRead(rightCenterSensor) > threshold || analogRead(leftCenterSensor) > threshold){
	setMotor(-speed, speed);
	delay(2);
	setMotor(0,0);
	delay(1);
	}

	while(analogRead(rightCenterSensor) < threshold)
	{
		setMotor(-speed, speed);
		delay(2);
		setMotor(0,0);
		delay(1);
	}
	
	
	
}


// ------------------------ Turn Right -----------------

void turnRight()
{
	while (analogRead(rightCenterSensor) > threshold){
		setMotor(speed, -speed);
		delay(2);
		setMotor(0,0);
		delay(1);
	}
	
	while(analogRead(rightCenterSensor) < threshold)
	{
		setMotor(speed, speed);
		delay(2);
		setMotor(0,0);
		delay(1);
	}
	
	while(analogRead(leftCenterSensor) < threshold)
	{
		setMotor(speed, -speed);
		delay(2);
		setMotor(0,0);
		delay(1);
	}
	
	
		
}
	
	
	// -------------- Straight -----------------
	
void straight()
	{
		if (analogRead(leftCenterSensor) < threshold)
		{
			setMotor(speed, speed);
			delay(1);
			setMotor(speed, 0);
			delay(5);
			return;
		}
		
		if (analogRead(rightCenterSensor) < threshold)
		{
			setMotor(speed, speed);
			delay(1);
			setMotor(0, speed);
			delay(5);
			return;
		}
		
		setMotor(speed, speed);
		delay(4);
		setMotor(0,0);
		delay(1);
	}

	
// ----------- Turn Around ------
	
	
	void turnAround()
	{
		setMotor(speed, speed);
		delay(delayVar2);
		while (analogRead(leftCenterSensor) < threshold){
			setMotor(-speed, speed);
			delay(2);
			setMotor(0,0);
			delay(1);
		}
		
	
	}


// -------------------------------------------------




void setup()
{
  Serial.begin(9600);
	pinMode(leftFarSensor, INPUT);
	pinMode(leftNearSensor, INPUT);
	pinMode(leftCenterSensor, INPUT);
	pinMode(rightCenterSensor, INPUT);
	pinMode(rightNearSensor, INPUT);
	pinMode(rightFarSensor, INPUT);
	
	for (int i = 0 ; i < 2 ; i++){
		pinMode(leftMotor[i], OUTPUT);
		pinMode(rightMotor[i], OUTPUT);
	}
  
}


void loop()
{
  readSensors();                                                                                     
 
 if(leftFar < threshold && rightFar < threshold && 
   (leftCenter > threshold || rightCenter > threshold) ){ 
    straight();                                                                                      
  }
  else{                                                                                              
    leftHandWall();                                                                                   
  }
  
}
