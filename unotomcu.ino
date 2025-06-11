#include <SoftwareSerial.h>
#include <math.h>

// Define pin connections
#define RED 7
#define GREEN 6

// Threshold distance in kilometers
const float thresholdDistance = 0.1; // 500 meters

SoftwareSerial espSerial(2, 3); // RX, TX for communication with ESP8266

// Traffic Light Coordinates (Set Your Fixed Traffic Light Location)
const float trafficLat = 12.926800;  // Example: Replace with actual traffic light latitude
const float trafficLon = 77.604200;  // Example: Replace with actual traffic light longitude

// Function Prototypes (Declare functions before use)
void processGPSData(String data);
float degToRad(float deg);
float calculateDistance(float lat1, float lon1, float lat2, float lon2);

void setup() {
    Serial.begin(9600);      // Serial Monitor
    espSerial.begin(9600);   // Communication with ESP8266

    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);

    digitalWrite(RED, HIGH);  // Default: Red ON
    digitalWrite(GREEN, LOW); // Green OFF

    Serial.println("🚦 Traffic Signal Controller Started");
}

void loop() {
    if (espSerial.available()) {
        String receivedData = espSerial.readStringUntil('\n'); // Read data until newline
        receivedData.trim(); // Remove unwanted spaces or newlines

        Serial.print("🔹 Received Raw Data: ");
        Serial.println(receivedData);

        // Process GPS Data
        processGPSData(receivedData);
    }
}

void processGPSData(String data) {
    // Expected format: "latitude,longitude,emergencyStatus"
    float latitude, longitude;
    int emergencyActive;

    int firstComma = data.indexOf(',');
    int secondComma = data.indexOf(',', firstComma + 1);

    if (firstComma != -1 && secondComma != -1) {
        latitude = data.substring(0, firstComma).toFloat();
        longitude = data.substring(firstComma + 1, secondComma).toFloat();
        emergencyActive = data.substring(secondComma + 1).toInt();

        Serial.println("✅ Parsed Data Successfully:");
        Serial.print("   Latitude: "); Serial.println(latitude, 6);
        Serial.print("   Longitude: "); Serial.println(longitude, 6);
        Serial.print("   Emergency Active: ");
        Serial.println(emergencyActive ? "YES" : "NO");

        float distance = calculateDistance(latitude, longitude, trafficLat, trafficLon);
        Serial.print("📏 Distance to Traffic Light: ");
        Serial.print(distance, 2);
        Serial.println(" km");

        if (emergencyActive && distance <= thresholdDistance) {
            Serial.println("🚦 Traffic Light: GREEN (Emergency Passing)");
            digitalWrite(RED, LOW);
            digitalWrite(GREEN, HIGH);
        } else {
            Serial.println("🚦 Traffic Light: RED (No Emergency)");
            digitalWrite(RED, HIGH);
            digitalWrite(GREEN, LOW);
        }
    } else {
        Serial.println("❌ ERROR: Invalid GPS Data Format");
    }
}

// Convert degrees to radians
float degToRad(float deg) {
    return deg * (PI / 180);
}

// Calculate distance between two GPS coordinates using Haversine formula
float calculateDistance(float lat1, float lon1, float lat2, float lon2) {
    const float R = 6371.0; // Earth radius in km
    float dLat = degToRad(lat2 - lat1);
    float dLon = degToRad(lon2 - lon1);

    float a = sin(dLat / 2) * sin(dLat / 2) +
              cos(degToRad(lat1)) * cos(degToRad(lat2)) *
              sin(dLon / 2) * sin(dLon / 2);

    float c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return R * c; // Distance in km
}