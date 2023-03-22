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

// Creates an instance of motor objects
AccelStepper myStepper0(motorInterfaceType, stepPin, dirPin);
AccelStepper myStepper1(motorInterfaceType, stepPin1, dirPin1);

//setup global variables
int maxVelocity = 500;
int velocity = 250;
int acceleration = 100;
int inf = 9999;


void setup() {

  pinMode(limitX, INPUT);
  pinMode(limitY, INPUT);

  //myStepper0.moveTo(inf);
  myStepper0.setMaxSpeed(maxVelocity);
  myStepper0.setSpeed(velocity);
  myStepper0.setAcceleration(acceleration);

  //myStepper1.moveTo(inf);
  myStepper1.setMaxSpeed(maxVelocity);
  myStepper1.setSpeed(velocity);
  myStepper1.setAcceleration(acceleration);

}

void loop() {
  calibrate();
}



void calibrate() {


  //run motors until limitY is reached
  while (digitalRead(limitY) == LOW && digitalRead(limitX) == LOW) {
    //set motors move location
    myStepper0.moveTo(inf);
    myStepper1.moveTo(-inf);

    //set motors to move upwards up direction
    myStepper0.setSpeed(velocity);
    myStepper1.setSpeed(-velocity);


    myStepper0.runSpeed();
    myStepper1.runSpeed();
  }

  //run motors until limitX is reached
  while (digitalRead(limitX) == LOW && digitalRead(limitY) == HIGH) {
    //set motors move location
    myStepper0.moveTo(inf);
    myStepper1.moveTo(inf);

    //set motors to move upwards up direction
    myStepper0.setSpeed(velocity);
    myStepper1.setSpeed(velocity);

    myStepper0.runSpeed();
    myStepper1.runSpeed();
  }
}


