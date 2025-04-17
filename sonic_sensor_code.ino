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
  Serial.begin(9600);
  
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
const float trackThreshold = 20; //filler number for threshold distance
const float roombaThreshold = 5; //filler number for threshold distance

void loop() {

  


  delay(2000);
  
  lwd = getDistance(roombaSensor.echo, roombaSensor.trig); //object in lifting platform checker
  rwd = getDistance(leftWall.echo, leftWall.trig); //left track end detector
  rd = getDistance(rightWall.echo, rightWall.trig); //right track end detector

  //Serial.print("roomba: "); 
  //Serial.println(rd);
  
  Serial.print("left: "); 
  Serial.println(lwd);

  Serial.print("right: "); 
  Serial.println(rwd);
  


 

  
  if (((true)||(true)) && (lwd<10)&&(rwd<10)){ //switch true for roomba calc after
    delay(10); //give a 2 second delay
    if (!motor){ //start the motor or keep it running
      motor = true;
      startMotor();
      analogWrite(speedmotor, 200);
    } 
  }
  else{ //stop the motor since checks failed
    motor = false;
    stopMotor();
  }

 
}
