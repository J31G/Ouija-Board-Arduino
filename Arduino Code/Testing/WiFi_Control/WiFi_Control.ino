#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <AccelStepper.h>

// LED Pin's
#define blueLED D1
#define yellowLED D2

// Motor Pins:
#define motorPin1 D5 // IN1
#define motorPin2 D6 // IN2
#define motorPin3 D7 // IN3
#define motorPin4 D8 // IN4
#define HALFSTEP 8
bool enableMotor = false;

// // WiFi Details
char* ssid = "YE Staff";
char* pass = "3nt3rpr!5E";

// For Web server
ESP8266WebServer Server;

// Pin sequence for using AccelStepper with 28BYJ-48
AccelStepper stepper1( HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4 );

void setup() {

  // Set pins to output and turn off
  pinMode ( blueLED, OUTPUT );
  pinMode ( yellowLED, OUTPUT );
  digitalWrite ( blueLED, LOW );
  digitalWrite ( yellowLED, LOW );

  // Stepper setup
  stepper1.setMaxSpeed( 1000.0 );
  stepper1.setAcceleration( 100.0 );
  stepper1.setSpeed( 200 );
  stepper1.moveTo( 20000 );
  

  // Start console
  Serial.begin ( 115200 );

  // Start WiFi
  WiFi.begin ( ssid, pass );

  // Print to console trying to connect
  while ( WiFi.status () != WL_CONNECTED ) {

    Serial.print ( "." );
    delay ( 500 );

  }

  // The IP of the hardware
  Serial.println ( "" );
  Serial.print ( "IP Address: " );
  Serial.print ( WiFi.localIP () );

  // Simple Site, so you know we are online
  Server.on ( "/", [] () {
    Server.send ( 200, "text/plain", "You are connected!" );
  } );

  // FOR LED's
  Server.on ( "/blueOn", blueOn );
  Server.on ( "/blueOff", blueOff );
  Server.on ( "/yellowOn", yellowOn );
  Server.on ( "/yellowOff", yellowOff );

  // FOR MOTOR
  Server.on ( "/stepOn", stepOn );
  Server.on ( "/stepOff", stepOff );

  Server.begin();

}

void loop() {

  Server.handleClient();

  if (enableMotor == true) {

    stepper1.run();
    
  }
}

void blueOn () {

  digitalWrite ( blueLED, HIGH );
  Server.send ( 204, "" );
  Serial.println ( "" );
  Serial.print ( "Blue LED = On" );

}
void blueOff () {

  digitalWrite ( blueLED, LOW );
  Server.send ( 204, "" );
  Serial.println ( "" );
  Serial.print ( "Blue LED = Off" );

}
void yellowOn () {

  digitalWrite ( yellowLED, HIGH );
  Server.send ( 204, "" );
  Serial.println ( "" );
  Serial.print ( "Yellow LED = On" );

}
void yellowOff () {

  digitalWrite ( yellowLED, LOW );
  Server.send ( 204, "" );
  Serial.println ( "" );
  Serial.print ( "Yellow LED = Off" );

}
void stepOn () {

  enableMotor = true;
  Server.send ( 204, "" );
  Serial.println ( "" );
  Serial.print ( "Motor = On" );

}
void stepOff () {

  enableMotor = false;
  Server.send ( 204, "" );
  Serial.println ( "" );
  Serial.print ( "Motor = Off" );

}
