#include "thingProperties.h"

void setup() {
  Serial.begin(9600);
  Serial.println("ESP8266 Connecting to Arduino IoT Cloud...");

  Serial1.begin(9600); // Communication with Arduino Uno

  // Initialize Arduino IoT Cloud connection
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
}

void loop() {
    ArduinoCloud.update(); // Sync with IoT Cloud

    // Corrected Data Retrieval
    Location currentGPS = gps.getValue(); // `gps.getValue()` returns a Location object

    if (currentGPS.lat != 0.0 || currentGPS.lon != 0.0) {  // Avoid sending zero values
        float lat = currentGPS.lat;  // Corrected: Use `lat`
        float lon = currentGPS.lon;  // Corrected: Use `lon`

        Serial.print(lat, 6);
        Serial.print(",");
        Serial.print(lon, 6);
        Serial.print(",");
        Serial.println(emergency ? "1" : "0"); // Emergency status

        Serial1.print(lat, 6);
        Serial1.print(",");
        Serial1.print(lon, 6);
        Serial1.print(",");
        Serial1.println(emergency ? "1" : "0"); // Send correctly formatted data

        Serial.println("✅ GPS Data Sent Successfully!");
    } else {
        Serial.println("❌ GPS Data Invalid! Retrying...");
    }

    delay(4000);  // Delay of 4 seconds
}
// Ensure no duplicate functions
void onGpsChange() {
    Serial.println(" GPS Data Updated!");
}

void onEmergencyChange() {
    Serial.println("🚨 Emergency Status Changed!");
}
