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

int moveAmount = 500;
int currentPos = 1;

void setup() {
  // set the maximum speed, acceleration factor,
  // initial speed and the target position
  myStepper.setMaxSpeed(1000);
  myStepper.setAcceleration(250);
  myStepper.setSpeed(200);


  myStepper1.setMaxSpeed(1000);
  myStepper1.setAcceleration(250);
  myStepper1.setSpeed(200);

  pinMode(limitX, INPUT);
  pinMode(limitY, INPUT);
  

}

void loop() {
  calibrate();
}


//Move right 
void dirRight(){
  myStepper.moveTo(moveAmount);
  myStepper1.moveTo(moveAmount);
}

//Move up
void dirUp(){
  myStepper.moveTo(-moveAmount);
  myStepper1.moveTo(moveAmount);
}

//Move Down
void dirDown(){
  myStepper.moveTo(moveAmount);
  myStepper1.moveTo(-moveAmount);
}

//Move Left
void dirLeft(){
  myStepper.moveTo(-moveAmount);
  myStepper1.moveTo(-moveAmount);
}



void calibrate(){
  int calStep = 0;
  //keep moving until we hit both limit switches
  while (digitalRead(limitY) == LOW && digitalRead(limitX) == LOW){
    moveAmount = 100;
      
      //move left a lil for the first step
      if(calStep == 0){
        dirLeft();
        calStep = 1;
      }

      //now move up until we hit the limit switch
      if(calStep == 1){
        dirUp();
        //now check if limit switch is on to see if we need to switch to moving right
        if(digitalRead(limitY) == HIGH){
          dirRight();
          if(digitalRead(limitX) == HIGH){
            calStep = 3;
            }
        }
      }

 
        //now check if limit switch is on
       
      

    myStepper.run();
    myStepper1.run();

  }
}
