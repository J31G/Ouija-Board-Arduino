#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server;

// LED PINS:
uint8_t yellowLED = D2;
uint8_t blueLED = D1;

// WiFi Connections details:
char* ssid = "YE Staff";
char* password = "3nt3rpr!5E";

void setup() {

  // Set LED's to Outputs
  pinMode ( yellowLED, OUTPUT );
  pinMode ( blueLED, OUTPUT );

  // Start Serial Console
  Serial.begin ( 115200 );

  // WiFi setup
  WiFi.begin ( ssid, password );

  Serial.println ( "" );
  Serial.print ( "Trying to connect to WiFi..." );
  while ( WiFi.status () != WL_CONNECTED ) {

    Serial.print ( "." );
    delay ( 500 );
      
  }

  // Connection successful:
  Serial.println ( "" );
  Serial.print ( "Connection successful! IP Address: " );
  Serial.println ( WiFi.localIP () );
  
  // Web Server ( Root ):
  server.on ( "/", [] () { 
    server.send ( 200, "text.html", "<h1>Connection successful</h1>" ); 
  } );
  // Web Server ( Toogle Pages)
  server.on ( "/toggleYellow", toggleYellowLED );
  server.on ( "/toggleBlue", toggleBlueLED );

  // Web Server begin
  server.begin ();
  
}


void loop() {

  // Check for users
  server.handleClient ();

}

void toggleYellowLED () {
  
  digitalWrite ( yellowLED, !digitalRead ( yellowLED ) );
  server.send ( 204, "" );
  
}

void toggleBlueLED () {
  
  digitalWrite ( blueLED, !digitalRead ( blueLED ) );
  server.send ( 204, "" );
  
}
