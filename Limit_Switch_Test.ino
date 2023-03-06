#include <AccelStepper.h>
#include <MultiStepper.h>


// Define pin connections
const int dirPin = 2;
const int stepPin = 3;
const int dirPin1 = 4;
const int stepPin1 = 5;

const int limitX = 6;
const int limitY = 7;

// Define motor interface type
#define motorInterfaceType 1

// Creates an instance
AccelStepper myStepper(motorInterfaceType, stepPin, dirPin);
AccelStepper myStepper1(motorInterfaceType, stepPin1, dirPin1);

int moveAmount = 50;

void setup() {
  //setup serial monitor for testing
  Serial.begin(9600);


  myStepper.setMaxSpeed(500);
  myStepper.setAcceleration(250);
  myStepper.setSpeed(500);


  myStepper1.setMaxSpeed(500);
  myStepper1.setAcceleration(250);
  myStepper1.setSpeed(500);

  pinMode(limitX, INPUT);
  pinMode(limitY, INPUT);
  

}

void loop() {
  calibrate();
}


//Move right 
void dirRight(){
  myStepper.move(moveAmount);
  myStepper1.move(moveAmount);
}

//Move up
void dirUp(){
  myStepper.move(-moveAmount);
  myStepper1.move(moveAmount);
}

//Move Down
void dirDown(){
  myStepper.move(moveAmount);
  myStepper1.move(-moveAmount);
}

//Move Left
void dirLeft(){
  myStepper.move(-moveAmount);
  myStepper1.move(-moveAmount);
}

//complete movement
void completeMovement(){
  while (myStepper.distanceToGo() != 0 && myStepper1.distanceToGo() != 0){
      myStepper.run();
      myStepper1.run();
  }
}




void calibrate(){
  if(digitalRead(limitY) == LOW && digitalRead(limitX) == LOW){
  //move up until we hit limitY
  calibrateY();
  }

  if(digitalRead(limitY) == HIGH && digitalRead(limitX) == LOW){
  //move Right until we hit limitX
  calibrateX();
  }
  
}



void calibrateY(){
  while(digitalRead(limitY) == LOW){
    dirUp();
    completeMovement();
  }
  return;
}

void calibrateX(){
  while(digitalRead(limitX) == LOW){
    dirRight();
    completeMovement();
  }
  return;
}
