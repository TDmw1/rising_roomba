//pin setup for HC super sonic thingy sensor

struct HCsensor {
  const int trig;
  const int echo;
};

HCsensor roombaSensor = {8, 9};
HCsensor leftWall = {10, 11};
HCsensor rightWall = {12, 13};

//motor pins
const int motorpin1 = 4;
const int motorpin2 = 5;
const int speedmotor = 3;

float rd, lwd, rwd;

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
  pinMode(roombaSensor.trig, OUTPUT);
  pinMode(roombaSensor.echo, INPUT);
  pinMode(leftWall.trig, OUTPUT);
  pinMode(leftWall.echo, INPUT);
  pinMode(rightWall.trig, OUTPUT);
  pinMode(rightWall.echo, INPUT);

  //L298N
  pinMode(motorpin1, OUTPUT);
  pinMode(motorpin2, OUTPUT);

  pinMode(speedmotor, OUTPUT); //speed controller
}

bool motor = false;
const float trackThreshold = 2.0 //filler number for threshold distance

void loop() {
  
  rd = getDistance(roombaSensor.echo, roombaSensor.trig);
  lwd = getDistance(leftWall.echo, leftWall.trig);
  rwd = getDistance(rightWall.echo, rightWall.trig);
  if ((rd < 5.0)&&(lwd<trackThreshold)&&(rwd<trackThreshold)){ //added threshold check
    delay(2000); //makes sure the roomba can get in without it starting to move
    if (!motor){
      motor = true;
      startMotor();
      analogWrite(speedmotor, 200);
    } 
  }
  else{ //stop the motor since checks failed
    motor = false;
    stopMotor();
  }

  // IN PROGRESS
  /*if(distance1 < 20.0){ //checks if lift gonna hit wall 
    motor = false;
    stopMotor();
    } */
}
