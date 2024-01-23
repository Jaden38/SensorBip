#include <Arduino.h>
#include <functions.h>
#include <WiFi.h>

//Setup des pins GPIO
#define buzzerPin 12
#define sensorTrig 32
#define sensorEcho 33
#define LedPin 26

#define SSID "iPhone de Adrien"
#define PWD "Pi!Pi!Corn123"

WiFiServer server(80);

const char* ssid = SSID;
const char* password = PWD;

String header;

boolean BipSensor = false;
boolean light = false;

//Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds
const long timeoutTime = 2000;

//String hostname = "Wemos mini D1 TEST";


unsigned int LoopDelay = 400;

void initWiFi(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500); 
    }
    Serial.println(WiFi.localIP());
}

void setup()
{
  Serial.begin(115200);

  // Setup des Pins 
  pinMode(buzzerPin, OUTPUT);
  pinMode(sensorTrig, OUTPUT);
  pinMode(sensorEcho, INPUT);
  pinMode(LedPin, OUTPUT);

  initWiFi();
  Serial.print("RSSI : ");
  Serial.println(WiFi.RSSI());
  server.begin();
}


void loop()
{
  WiFiClient client = server.available();

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
            
            // turns the GPIOs conditions on and off
            if (header.indexOf("GET /BipSensor/on") >= 0) {
              Serial.println("GPIO BipSensor on");
              BipSensor = true;
            } else if (header.indexOf("GET /BipSensor/off") >= 0) {
              Serial.println("GPIO BipSensor off");
              BipSensor = false;
            } else if (header.indexOf("GET /light/on") >= 0) {
              Serial.println("GPIO light on");
              light = true;
            } else if (header.indexOf("GET /light/off") >= 0) {
              Serial.println("GPIO light off");
              light = false;
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
            client.println(".button2 {background-color: #555555;}");
            client.println(".home-button { position: absolute; top: 10px; left: 10px; }"); // Position the SVG at the top-left corner
            client.println("</style></head>");
            
            // Web Page Heading


            client.println("<a class=\"home-button\" href=\"/\">");
            client.println("  <svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 576 512\" width=\"50\" height=\"50\">");
            client.println("    <!-- Your SVG path here -->");
            client.println("    <path fill=\"#63E6BE\" d=\"M280.4 148.3L96 300.1V464a16 16 0 0 0 16 16l112.1-.3a16 16 0 0 0 15.9-16V368a16 16 0 0 1 16-16h64a16 16 0 0 1 16 16v95.6a16 16 0 0 0 16 16.1L464 480a16 16 0 0 0 16-16V300L295.7 148.3a12.2 12.2 0 0 0 -15.3 0zM571.6 251.5L488 182.6V44.1a12 12 0 0 0 -12-12h-56a12 12 0 0 0 -12 12v72.6L318.5 43a48 48 0 0 0 -61 0L4.3 251.5a12 12 0 0 0 -1.6 16.9l25.5 31A12 12 0 0 0 45.2 301l235.2-193.7a12.2 12.2 0 0 1 15.3 0L530.9 301a12 12 0 0 0 16.9-1.6l25.5-31a12 12 0 0 0 -1.7-16.9z\"/>");
            client.println("  </svg>");
            client.println("</a>"); 
            client.println("<body><h1>BipSensor Web Server</h1>");

//Fonction pour mettre un timer sur la page => Beaucoup trop lourd en terme d'HTTP et donc sans interet.

            // client.println("<div id=\"timer\">5</div>");

            // client.println("<script type=\"text/javascript\">");
            // client.println("let temps = 5;");
            // client.println("const timerElement = document.getElementById(\"timer\")");
            
            // client.println("function timerCount(){");
            // client.println("var interval = setInterval(function(){");
            // client.println("document.getElementById(\"timer\").innerHTML = temps");
            // client.println("temps--");
            // client.println("if(temps < 0){");
            // client.println("clearInterval(interval);");
            // client.println("document.getElementById(\"timer\").innerHTML = \"please reconnect\"}");                    
            // client.println("}, 1000);}");
            // client.println("timerCount();");
                
            // client.println("</script>");
      
            // Display current state, and ON/OFF buttons for GPIO bipsensor 
             
            client.println("<p>GPIO XX - BipSensor </p>");
            // If the BipSensor is off, it displays the ON button       
            if (BipSensor== false) {
              client.println("<p><a href=\"/BipSensor/on\"><button class=\"button\">Turn ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/BipSensor/off\"><button class=\"button button2\">Turn OFF</button></a></p>");
              // Display current state, and ON/OFF buttons for GPIO light  
              client.println("<p>GPIO XX - Light </p>");
              // If the light is off, it displays the ON button       
              if (light==false) {
                client.println("<p><a href=\"/light/on\"><button class=\"button\">Turn ON</button></a></p>");
              } else {
                client.println("<p><a href=\"/light/off\"><button class=\"button button2\">Turn OFF</button></a></p>");
              }
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

    //Faire en sorte que la loop continu tant que BipSensor = On
  if (BipSensor){
    
    int distance = getDistance(sensorTrig, sensorEcho);
    int lastTime = 0;

    int beepDelay = map(distance,0, 60, 10,LoopDelay);
    int freq = map(distance, 60, 0, 500,700);

  
  // Serial.println("beepDelay: ");
  // Serial.println(beepDelay);

    beepFromDistance(distance, buzzerPin, 100, beepDelay, lastTime, LoopDelay, freq, light, LedPin);

    //Faire en sorte que la loop inclus la led seulement le light = On
    if (light){

    }

  }

  //Voir pour que si condition d'arret => Page html à mettre au propre ? Donc si BipSensorloop =! de bipSensor, renvoyé l'utilisateur sur une page propre ? 
  //Envoyé uen notif qui fait revenir à la page initial ?

}

