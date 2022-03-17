

/*
  WiFiAccessPoint.ino Create a wifi hotspot, and provide a web service

  Steps:
  1. Connect to the wifi "yourAp"
  2. Visit http://192.168.4.1/H to turn on the LED; Visit http://192.168.4.1/L to turn off the LED
     OR
     Run raw TCP "GET /H" and "GET /L" on PuTTY terminal with 192.168.4.1 as IP address and 80 as port
*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include "motor.h"
// Set your wifi and password
const char *ssid = "esp32";
const char *password = "";


WiFiServer server(80);

void setup() {

  
  pinMode(LED_BUILTIN, OUTPUT);//Set pin LED to output mode
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  // Configure wifi and get IP address
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();
  Serial.println("Server started");
  msetup();
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
            client.print("Click <a href=\"/F\">here</a> to move Forward.<br>");
            client.print("Click <a href=\"/B\">here</a> to move Backward.<br>");
            client.print("Click <a href=\"/R\">here</a> to turn Left.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn Right.<br>");

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
        if (currentLine.endsWith("GET /F")) {
          dMove();             // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /B")) {
          dMove(false);                // GET /L turns the LED off
        }
        if (currentLine.endsWith("GET /R")) {
          dTurn(true);                // GET /L turns the LED off
        }
        if (currentLine.endsWith("GET /L")) {
          dTurn(false);                // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
