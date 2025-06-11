#ifndef THINGPROPERTIES_H
#define THINGPROPERTIES_H

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
#include <ESP8266WiFi.h>

const char SSID[] = "moto";  // Replace with your Wi-Fi SSID
const char PASS[] = "----------";  // Replace with your Wi-Fi Password
const char DEVICE_LOGIN_NAME[]  = "ab39e076-4170-4e42-82b2-506a2d9f0cfc"; 
const char DEVICE_KEY[]  = "5bkNlhTdaaBIh@j5UG8UnpInM";  // Replace with your IoT Cloud Device Key

void onGpsChange();
void onEmergencyChange();

CloudLocation gps;
bool emergency;

void initProperties() {
  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(gps, READWRITE, ON_CHANGE, onGpsChange);
  ArduinoCloud.addProperty(emergency, READWRITE, ON_CHANGE, onEmergencyChange);
}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);

#endif
