#include <AccelStepper.h>
#define HALFSTEP 8

// Motor pins:
#define motorPin1 D5 // IN1
#define motorPin2 D6 // IN2
#define motorPin3 D7 // IN3
#define motorPin4 D8 // IN4

// Pin sequence for using AccelStepper with 28BYJ-48
AccelStepper stepper1( HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4 );

void setup() {

  stepper1.setMaxSpeed( 1000.0 );
  stepper1.setAcceleration( 100.0 );
  stepper1.setSpeed( 200 );
  stepper1.moveTo( 20000 );
  
}

void loop() {

  // Change direction when the stepper reaches the target position
  if (stepper1.distanceToGo() == 0) {
    stepper1.moveTo(-stepper1.currentPosition());
  }
  stepper1.run();

}
