#include <Servo.h>
#include <RPLidar.h>

// IO Control
byte lidar_motor = 18; // Lidar Motor speed

// Servos
byte servoPin = 24;
int minServo = 1000;
int maxServo = 2000;
int servoCurrent = 1500;

// ESC Declarations
byte ESCPin = 23;
int carStopped = 1600;
int minForward = 1615;
int maxForward = 2000;
int minBackward = 1500;
int maxBackward = 1000;
bool inReverse = false;

// Misc
byte LEDPin = 41;
byte potentiometerPin = 22;

// Input
RPLidar lidar;

// Output
Servo ESC;
Servo servo;

// Give this function -1000 to 1000 to set ESC speed. 0 = stop. Handles reversing, will stop for 1500ms between forward and backward.
void setESC(int ESCSpeed) {
  if(ESCSpeed >= -1000 && ESCSpeed <= 1000) {
    int newSpeed;
    if(ESCSpeed >= 0) {
      newSpeed = map(ESCSpeed, 0, 1000, carStopped, maxForward);
    } else {
      newSpeed = map(ESCSpeed, -1, -1000, minBackward, maxBackward);
    }
    
    if(newSpeed >= carStopped) {
      if(inReverse) {
        inReverse = false;
        ESC.writeMicroseconds(carStopped);
        delay(1500);
      }
      ESC.writeMicroseconds(newSpeed);
    } else {
      if(!inReverse) {
        // Reverse sequence
        inReverse = true;
        ESC.writeMicroseconds(carStopped);
        delay(1500);
        ESC.writeMicroseconds(maxBackward);
        delay(100);
        ESC.writeMicroseconds(carStopped);
        delay(100);
      }
      ESC.writeMicroseconds(newSpeed);
      Serial.printf("%d\n", newSpeed);
      Serial.println(inReverse);
    }
  }
}

// servoNum = -1000 for max left, 1000 for max right.
void steer(int servoNum) {
  if(servoNum >= -1000 && servoNum <= 1000) {
    int newServoUS = map(servoNum, -1000, 1000, minServo, maxServo);
    servoCurrent = newServoUS;
    servo.writeMicroseconds(newServoUS);
  }
}

void setup() {  
  pinMode(LEDPin, OUTPUT);
  digitalWrite(LEDPin, HIGH);
  
  pinMode(lidar_motor, OUTPUT);
  lidar.begin(Serial1); // set up lidar
  
  ESC.attach(ESCPin);
  ESC.writeMicroseconds(carStopped);
  delay(2000); // delay to allow the ESC to recognize the stopped signal.

  servo.attach(servoPin);
  servo.writeMicroseconds(servoCurrent);
  delay(1000);
  
  digitalWrite(LEDPin, LOW);  
}

void loop() {
if (IS_OK(lidar.waitPoint())) {
    float distance = lidar.getCurrentPoint().distance; //distance value in mm unit
    int angle    = (int) lidar.getCurrentPoint().angle; //anglue value in degree
    bool  startBit = lidar.getCurrentPoint().startBit; //whether this point is belong to a new scan
    byte  quality  = lidar.getCurrentPoint().quality; //quality of the current measurement
    float distances[12];

    // TODO: refine bucketing system
    int bucket = map(angle, 0, 360, 0, 11);
    distances[bucket] = distance;

    setESC(0); //keep motor stopped for debugging

    // Only go if 50cm available.
//    if(angle >= 0 && angle <= 1) { 
//      if(distance >= 500.0) {
//        setESC(50);                                                                                                                 
//      } else {
//        setESC(0);
//      }
//    }

    if(distances[1] <= 300 && distances[11] <= 300) {
      steer(0);
    } else if(distances[1] <= 300) {
      steer(servoCurrent - 1);
    } else if(distances[11]) {
      steer(servoCurrent + 1);
    }

    for(int i = 0; i < 12; i++) {
      Serial.printf("%d: %f\n", i, distances[i]);
    }
    
    
    
  } else {
    analogWrite(lidar_motor, 0); //stop the rplidar motor
    
    // try to detect RPLIDAR... 
    rplidar_response_device_info_t info;
    if (IS_OK(lidar.getDeviceInfo(info, 100))) {
       // detected...
       lidar.startScan();
       
       // start motor rotating at max allowed speed
       analogWrite(lidar_motor, 255);
       delay(1000);
    }
  }    
    
//    ESC.writeMicroseconds(1615);

//    int maxSpeed = 1800;
//    for(int i = 1600; i < maxSpeed; i++) {
//      digitalWrite(LEDPin, LOW);
//      ESC.writeMicroseconds(i);
//      Serial.printf("%d\n", i);
//      if(i % 50 == 0) {
//        digitalWrite(LEDPin, HIGH);
//        delay(1000);
//      }
//      delay(50);
//    }
//    for(int i = maxSpeed; i > 1500; i--) {
//      ESC.writeMicroseconds(i);
//    }
}
