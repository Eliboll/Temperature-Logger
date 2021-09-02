#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "Adafruit_Si7021.h"
Adafruit_Si7021 sensor = Adafruit_Si7021();
const char* ssid     = "PLACEHOLDER";
const char* password = "PLACEHOLDER";

void setup() {
  sensor.begin();
  
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED ) {delay(500);} // Forces the board to wait until the wifi is connected
}

void loop() {
 
  if (WiFi.status() == WL_CONNECTED) { //Checks WiFi connection status
 
    HTTPClient http;  //Declares an object of class HTTPClient
    float temp = (sensor.readTemperature() * 1.8) +32; //Converts celcius to farenheit
    http.begin("192.168.1.203:5000/?temp=" + String(temp));  //Address of linux box with DHCP reservation
    int httpCode = http.GET();                                  //Sends the request
 
    if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();   //Get the request response payload
      //Serial.println(payload);
 
    }
 
    http.end();   //Close connection
 
  }
 
  delay(3000);    //Send a request every 30 seconds
}
