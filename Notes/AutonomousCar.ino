void setup() {
  // put your setup code here, to run once:
// LIBRARIES

// Variables

  // Influence (Negative if Reversed Throttle or Turning Port/Left)
  #define steerInfFrontPort .5
  #define steerInfFrontStarboard -.65 // This makes it so it will favor left over right when something is right infront instead of full stopping. Need something else for detecting when the car hasn't moved.
  #define steerInfPort .25 //Left
  #define steerInfStarboard -.25 //Right
  #define steerInfRear 0
  #define throttleInfFront -.375
  #define throttleInfPort -.125 //Left
  #define throttleInfStarboard -.125 //Right
  #define throttleInfRear .25

  //Lidar Measurement Range (this should all change based on units/what we want. These are just sample values)
  #define distFrontMax 5
  #define distFrontMin 0
  #define distPortMax 5 
  #define distPortMin 1
  #define distStarboardMax 5
  #define distStarboardMin 1
  #define distRearMax 10
  #define distRearMin 0

  //Normal Speed for car.
  #define throttleInitial 640 //so 1/4 throttle while testing (512 is mid and 0 + 1/4 of 512), can definetly turn this up later. This thing is going to drive like a bullet.

// Integers
int steeringAngleCalc
int throttlePositionCalc
int steeringAngle
int throttlePosition
int frontPort
int frontStarboard
int port
int starbord
int rear
int frontPortClean
int frontStarboardClean
int portClean
int starboardClean
int rearClean

}

void loop() {
  // put your main code here, to run repeatedly:

// Code to get data from lidar
───────────────────────────────────────
───▐▀▄───────▄▀▌───▄▄▄▄▄▄▄─────────────
───▌▒▒▀▄▄▄▄▄▀▒▒▐▄▀▀▒██▒██▒▀▀▄──────────
──▐▒▒▒▒▀▒▀▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▀▄────────
──▌▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▒▒▒▒▒▒▒▒▒▒▒▒▀▄──────
▀█▒▒▒█▌▒▒█▒▒▐█▒▒▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌─────
▀▌▒▒▒▒▒▒▀▒▀▒▒▒▒▒▒▀▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▐───▄▄
▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌▄█▒█
▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒█▀─
▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▀───
▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌────
─▌▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▐─────
─▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌─────
──▌▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▐──────
──▐▄▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▌──────
────▀▄▄▀▀▀▀▀▄▄▀▀▀▀▀▀▀▄▄▀▀▀▀▀▄▄▀────────

//Code to divide it into usable chunks

//Code to clean data to remove high and low values



//Main Equations

steeringAngleCalc = (steerInfFrontPort*frontPortClean)+(steerInfFrontStarbord*frontStarboardClean)+(steerInfPort*portClean)+(steerInfStarbord*starboardClean)+(steerInfRear*rearClean)
// steeringAngle is = 0 at 512. gotta set it so -1 from the equation would equal 0 and then +1 would be 5V or 1024.
steeringAngle =
//OutputThis^^
throttlePositionCalc = (throttleInfFront*frontPortClean)+(throttleInfFront*frontStarboardClean)+(throttleInfPort*portClean)+(throttleInfStarboard*starboardClean)+(throttleInfRear*rearClean)
// Throttle will be from -1to1, again -1 as 0 and +1 as 1024. When started car should be at 512. (gotta write code to enable and disable driving...)
throttlePosition = throttleInitial + 
//OutputThis^^
}
