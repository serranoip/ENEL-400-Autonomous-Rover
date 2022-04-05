#include <NewPing.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

#include "motor.h"
#define TRIGGER_PIN_LEFT 12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_LEFT    39
#define TRIGGER_PIN_RIGHT   4  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_RIGHT    36  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE     80 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

const char *ssid = "esp32";
WiFiServer server(80);

NewPing Rsensor(TRIGGER_PIN_RIGHT, ECHO_PIN_RIGHT, MAX_DISTANCE);
NewPing Lsensor(TRIGGER_PIN_LEFT,  ECHO_PIN_LEFT,  MAX_DISTANCE);

int distR;
int distL;
int lastscan;

bool driving = false;

void setup() {
  Serial.begin(115200);
  motorSetup();

  pinMode(17, OUTPUT); //solenoid pin
  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  WiFi.softAP(ssid);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();
  Serial.println("Server started");
  
  lastscan = millis();
}

void drive() {
  delay(50);
  lastscan = millis();
  distL = Lsensor.ping_cm(); 
  distL = distL?distL:100;
  
  Serial.print("distL: ");
  Serial.print(distL);
  Serial.print(",  dtime: ");
  Serial.println(millis()-lastscan);
  
  delay(50);
  lastscan = millis();
  distR = Rsensor.ping_cm();
  distR = distR?distR:100;
  
  Serial.print("distR: ");
  Serial.print(distR);
  Serial.print(",  dtime: ");
  Serial.println(millis()-lastscan);

  Serial.println();
  lastscan = millis();

  int speed = distR>distL?distL+40:distR+40;
  
  if (distR < 35 || distL < 35){
    int diff = (distR>40?40:distR) - (distL>40?40:distL);
    move(speed,true,(float)diff/40);
    Serial.printf("speed: %d, diff: %f, olddiff: %f\n", speed, (float)diff/40, (float)(diff/40));
  }
  else {
    move(speed);
    Serial.printf("speed: %d, diff: %f\n", speed, 0.0);
  }
}
void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("<p style=\"font-size:60px;\">");
            client.print("Click <a href=\"/D\">here</a> to turn Navigate.<br>");
            client.print("Click <a href=\"/S\">here</a> to turn Stop.<br><br>");
            client.print("Click <a href=\"/H\">here</a> to turn Unlock.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn Lock.<br>");
            client.print("</p>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(17, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(17, LOW);                // GET /L turns the LED off
        }
        if (currentLine.endsWith("GET /D")) {
          driving = true;             // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /S")) {
          driving = false;
          mbrake();
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
  
  if (driving){
    drive();
  }
}
