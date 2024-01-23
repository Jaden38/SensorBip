#include <Arduino.h>
#include <WiFi.h>


String BipSensor = "off";
String light = "off";

String header;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds
const long timeoutTime = 10000;

void checkserver(){   
  
  WiFiClient client = server.available();

  //delay(10000);
  //Serial.println(client);

  if (client){
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /BipSensor/on") >= 0) {
              Serial.println("GPIO BipSensor on");
              BipSensor = "on";
              //digitalWrite(output26, HIGH);
            } else if (header.indexOf("GET /BipSensor/off") >= 0) {
              Serial.println("GPIO BipSensor off");
              BipSensor = "off";
              //digitalWrite(output26, LOW);
            } else if (header.indexOf("GET /light/on") >= 0) {
              Serial.println("GPIO light on");
              light = "on";
              //digitalWrite(output27, HIGH);
            } else if (header.indexOf("GET /light/off") >= 0) {
              Serial.println("GPIO light off");
              light = "off";
              //digitalWrite(output27, LOW);
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>BipSensor Web Server</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 26  
            client.println("<p>GPIO XX - BipSensor </p>");
            // If the BipSensor is off, it displays the ON button       
            if (BipSensor=="off") {
              client.println("<p><a href=\"/BipSensor/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/BipSensor/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 27  
            client.println("<p>GPIO XX - Light </p>");
            // If the light is off, it displays the ON button       
            if (light=="off") {
              client.println("<p><a href=\"/light/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/light/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}