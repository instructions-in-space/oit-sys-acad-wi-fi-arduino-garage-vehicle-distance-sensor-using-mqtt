#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "wi-fi_config.h"
#include <NewPing.h>

#define TRIGGER_PIN D1
#define ECHO_PIN D2
#define MAX_DISTANCE 50 // Maximum distance in cm

WiFiClient espClient;
PubSubClient client(espClient);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
    Serial.begin(115200);
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    Serial.println("\nConnected! IP Address: " + WiFi.localIP().toString());
    client.setServer(MQTT_BROKER, 1883);
    client.connect("Distance_Sensor");
    //connectMQTT();
    Serial.println("After connectMQTT and before the custom message");
    client.publish("garage/distance", "cUsToM mEsSaGe");
}

void loop() {
    Serial.println("Top of the loop");  // I added this.
    if (!client.connected()) {
        Serial.println("Not connected.");
        //connectMQTT();
    }
    client.loop();
    int distance = sonar.ping_cm();
    //if (distance == 0) distance = MAX_DISTANCE; // If no response, assume max
    client.publish("garage/distance", String(distance).c_str());
    client.publish("garage/distance", "cUsToM mEsSaGe");

    Serial.println(distance);  // I added this.
    Serial.println("This is working!");  // I added this.

    delay(1000); // Publish every second
}

void connectMQTT() {
    Serial.println("Inside the connectMQTT function");
    while (!client.connected()) {
        Serial.println("Inside the not connected while loop");
        Serial.print("MQTT Broker:  ");
        Serial.println(MQTT_BROKER);
        client.publish("garage/distance", "cUsToM mEsSaGe");
          if (client.connect("Distance_Sensor")) {
            // Connected
          client.publish("garage/distance", "cUsToM mEsSaGe");
        } else {
            delay(5000);
        }
    }
}


