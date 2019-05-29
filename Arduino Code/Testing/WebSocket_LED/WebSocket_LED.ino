/* ------------------------------------------
 *  Title:    Simple Web Socket Test
 *  Author:   J31G
 *  Date:     29/05/2019
------------------------------------------ */
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>

// Define our Web & Socket server:
ESP8266WebServer server;
WebSocketsServer webSocket = WebSocketsServer(81);

// Define pin layout
uint8_t blueLED = D1;
uint8_t yellowLED = D2;

// WiFI Details
char* ssid = "YE Staff";
char* pass = "3nt3rpr!5E";

// Simple Web page to control things
char webpage[] PROGMEM = R"=====(
<html>
<head>
  <title>Success</title>
</head>
<body>
  <h1>You are connected!</h1>
  <p>Please use the web sockets to send commands to board.</p>
</body>
</html>
)=====";

void setup() {

  // Set LED's to output and make sure they are off
  pinMode ( blueLED, OUTPUT );
  pinMode ( yellowLED, OUTPUT );
  digitalWrite ( blueLED, OUTPUT );
  digitalWrite ( yellowLED, OUTPUT );

  // WiFi & Console setup
  WiFi.begin ( ssid, pass );
  Serial.begin ( 115200 );
  Serial.println ( "" );
  Serial.print ( "Connecting to WiFi..." );
  
  while ( WiFi.status () != WL_CONNECTED ) {

    Serial.print ( "." );
    delay ( 500 );
      
  }

  // Connected, print info
  Serial.println ( "" );
  Serial.print ( "IP Address: " );
  Serial.println ( WiFi.localIP () );

  // Web Pages
  server.on ( "/", [] () {
    server.send_P ( 200, "text/html", webpage );
  } );

  // Begin services
  server.begin ();
  webSocket.begin ();
  webSocket.onEvent ( webSocketEvent );
  
}

void loop() {

  // Server & Socket loops
  webSocket.loop ();
  server.handleClient ();

  // Check for serial info
  if ( Serial.available () > 0 ) {
    char c [] = { ( char ) Serial.read () };
    webSocket.broadcastTXT ( c, sizeof (c) );
  }
  
}

void webSocketEvent ( uint8_t num, WStype_t type, uint8_t * payload, size_t length ) {

  if ( type == WStype_TEXT ) {

    // Config page: Slider
    if ( payload [0] == '#' ) {

      uint16_t brightness = ( uint16_t ) strtol ( ( const char * ) & payload [1], NULL, 10 );
      // brightness = 1024 - brightness;
      analogWrite ( blueLED, brightness );
      Serial.print ( "Brightness = " );
      Serial.println ( brightness );
      
    } 

    // FreeText page: Random words
    else if ( payload [0] == '!' ) {

      Serial.print ( "Free Word = " );
      for ( int i = 1; i < length; i++ ) {
        Serial.print ( ( char ) payload [i] );
      }
    Serial.println ();
        
    }

    // Pre-Definded words
    else if ( payload [0] == '*' ) {

      Serial.print ( "Predefined = " );
      for ( int i = 1; i < length; i++ ) {
        Serial.print ( ( char ) payload [i] );
      }
      Serial.println ();
        
    }
    // Unknown - Print
    else {

      Serial.print ( "Unknown = " );
      for ( int i = 0; i < length; i++ ) {
        Serial.print ( ( char ) payload [i] );
      }
      Serial.println ();
      
    }
    
  }
  
}
