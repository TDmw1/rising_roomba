//pin setup for HC super sonic thingy sensor
const int tpSensor1 = 8, epSensor1 = 9; //first sensor
const int tpSensor2 = 10, epSensor2 = 11; //second sensor
const int tpSensor3 = 12, epSensor3 = 13; //third sensor

//motor pins
const int motorpin1 = 4;
const int motorpin2 = 5;
const int speedmotor = 3;

float distance1, distance2, distance3;

float getDistance(int echo, int trig){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  float temp = pulseIn(echo, HIGH);
  return (temp*0.0343)/2; // cm per micro second conversion
}

void startMotor(){
  digitalWrite(motorpin1, HIGH);
  digitalWrite(motorpin2, LOW);
}

void stopMotor(){
  digitalWrite(motorpin1, LOW);
  digitalWrite(motorpin2, LOW);
}

void setup() {
  //hc sensor
  pinMode(tpSensor1, OUTPUT);
  pinMode(epSensor1, INPUT);
  pinMode(tpSensor2, OUTPUT);
  pinMode(epSensor2, INPUT);
  pinMode(tpSensor3, OUTPUT);
  pinMode(epSensor3, INPUT);

  //L298N
  pinMode(motorpin1, OUTPUT);
  pinMode(motorpin2, OUTPUT);

  pinMode(speedmotor, OUTPUT); //speed controller
}

bool motor = false;

void loop() {
  
  distance1 = getDistance(epSensor1, tpSensor1);
  distance2 = getDistance(epSensor2, tpSensor2);
  distance3 = getDistance(epSensor3, tpSensor3);
  
  if (distance2 < 20.0){ //checks if roomba is in thing
    if (!motor){
      motor = true;
      startMotor();
    } 
  }
  if(distance1 < 20.0){ //checks if lift gonna hit wall
    motor = false;
    stopMotor();
    } 
}
