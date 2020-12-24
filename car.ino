#include <Servo.h>
#include <RPLidar.h>

byte servoPin = 23; // signal pin for the ESC.
byte potentiometerPin = 22; // analog input pin for the potentiometer.
byte lidar_motor = 18; //analog output for lidar motor speed

Servo servo;
RPLidar lidar;

// Takes speed values 0-1000 and sets motor speed accordingly to ESC. 
void setCarSpeed(int newSpeed) {
  if(newSpeed >= 0 && newSpeed <= 1000) {
    servo.writeMicroseconds(newSpeed + 1000);
  } else {
    servo.writeMicroseconds(1000);
  }
}

void setup() {
  Serial.begin(9600); //serial for debugging
  
  lidar.begin(Serial1); // set up lidar
  pinMode(lidar_motor, OUTPUT);
  
  servo.attach(servoPin);
  servo.writeMicroseconds(1500); // send "stop" signal to ESC. Also necessary to arm the ESC.
  
  delay(2000); // delay to allow the ESC to recognize the stopped signal.
}

void loop() {
if (IS_OK(lidar.waitPoint())) {
    float distance = lidar.getCurrentPoint().distance; //distance value in mm unit
    float angle    = lidar.getCurrentPoint().angle; //anglue value in degree
    bool  startBit = lidar.getCurrentPoint().startBit; //whether this point is belong to a new scan
    byte  quality  = lidar.getCurrentPoint().quality; //quality of the current measurement
    if(angle >= 0 && angle <= 10) { 
      Serial.printf("Angle: %f\n", angle);
      Serial.printf("Distance: %f mm\n\n", distance);
      delay(500); 
    }

    int potVal = analogRead(potentiometerPin); // read input from potentiometer.
    int pwmVal = map(potVal,0, 1023, 0, 1000); // maps potentiometer values to PWM value.
    setCarSpeed(pwmVal);
    
    
    
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
}
