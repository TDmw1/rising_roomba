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

enum TrackDirection { LEFT, RIGHT, NONE };
TrackDirection currentDirection = NONE;
bool atEndOfTrack = false;
unsigned long endDetectionTime = 0;
const unsigned long reverseDelay = 1000; // 1 second delay before reversing

float getDistance(int echo, int trig) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  float temp = pulseIn(echo, HIGH);
  return (temp * 0.0343) / 2; // cm per micro second conversion
}

void startMotor(TrackDirection dir) {
  if (dir == RIGHT) {
    digitalWrite(motorpin1, HIGH);
    digitalWrite(motorpin2, LOW);
    currentDirection = RIGHT;
  } else if (dir == LEFT) {
    digitalWrite(motorpin1, LOW);
    digitalWrite(motorpin2, HIGH);
    currentDirection = LEFT;
  }
  analogWrite(speedmotor, 125);
}

void stopMotor() {
  digitalWrite(motorpin1, LOW);
  digitalWrite(motorpin2, LOW);
  currentDirection = NONE;
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

const float trackThreshold = 10; // distance in cm to detect end of track
const float roombaThreshold = 5; // distance in cm to detect roomba

void loop() {
  delay(100); // Reduced delay for more responsive behavior
  
  lwd = getDistance(roombaSensor.echo, roombaSensor.trig); // object in lifting platform checker
  rwd = getDistance(leftWall.echo, leftWall.trig); // left track end detector
  rd = getDistance(rightWall.echo, rightWall.trig); // right track end detector

  Serial.print("roomba: "); 
  Serial.println(rd);
  Serial.print("left: "); 
  Serial.println(lwd);
  Serial.print("right: "); 
  Serial.println(rwd);

  // Check if we're at either end of the track
  bool atLeftEnd = (rwd < trackThreshold);
  bool atRightEnd = (rd < trackThreshold);
  
  // If we're at an end and not already marked as at end
  if ((atLeftEnd || atRightEnd) && !atEndOfTrack) {
    atEndOfTrack = true;
    endDetectionTime = millis();
    stopMotor();
  }
  
  // If we were at an end but now neither end is detected
  if (atEndOfTrack && !atLeftEnd && !atRightEnd) {
    atEndOfTrack = false;
  }
  
  // If we've been at the end long enough and it's time to reverse
  if (atEndOfTrack && (millis() - endDetectionTime > reverseDelay)) {
    if (atLeftEnd) {
      startMotor(RIGHT); // Reverse direction to go right
    } else if (atRightEnd) {
      startMotor(LEFT); // Reverse direction to go left
    }
    atEndOfTrack = false; // Reset the end detection
  }
  
  // Normal operation - start motor if not at end and roomba is detected
  if (!atEndOfTrack && lwd < roombaThreshold) {
    // Determine which direction to go based on last direction or default
    if (currentDirection == NONE) {
      // Default to right if no previous direction
      startMotor(RIGHT);
    } else {
      // Continue in current direction
      startMotor(currentDirection);
    }
  } else if (!atEndOfTrack && lwd >= roombaThreshold) {
    // No roomba detected and not at end - stop motor
    stopMotor();
  }
}
