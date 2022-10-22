// Load Wi-Fi library
#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid = "ALIRNOFBERKAH"; // SSID dari wifi anda
const char* password = "aldyft260200"; // SSID dari wifi anda

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output5State = "off";
String output4State = "off";
// Assign output variables to GPIO pins
const int output5 = 5;
const int output4 = 4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output5, LOW);
  digitalWrite(output4, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available();  // Listen for incoming clients
  if (client) {                            // If a new client connects,
    Serial.println("New Client.");         // print a message out in the serial port
    String currentLine = "";
    while (client.connected()) {  // loop while the client's connected
      if (client.available()) {   // if there's bytes to read
        char c = client.read();   // read a byte, then
        Serial.write(c);          // print it out the serial monitor
        header += c;
        if (c == '\n') {  // if the byte is a newline character
                          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            //and content - type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            client.print("Click <a href=\"/H\">here<a/> to turn the LED on pin 5 on.<br>");
            client.print("Click <a href=\"/L\">here<a/> to turn the LED on pin 5 off.<br>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }

        if (currentLine.endsWith("GET /H")) {
          digitalWrite(2, HIGH);
        }

        if (currentLine.endsWith("GET /L")) {
          digitalWrite(2, LOW);
        }
      }
    }
    client.stop();
    Serial.println("Client Disconnected");
  }
}