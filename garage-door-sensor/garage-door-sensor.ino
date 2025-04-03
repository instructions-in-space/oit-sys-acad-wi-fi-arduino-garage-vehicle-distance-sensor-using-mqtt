#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "wi-fi_config.h"

#define REED_SWITCH_PIN D1

WiFiClient espClient;
PubSubClient client(espClient);

//Serial.println("Before setup");

void setup() {
    Serial.begin(115200);
    pinMode(REED_SWITCH_PIN, INPUT_PULLUP);
    Serial.println();
    Serial.println("Serial begin");
    
    WiFi.begin(SSID, PASSWORD);
    Serial.println("Wi-Fi begin");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    Serial.println("\nConnected! IP Address: " + WiFi.localIP().toString());
    Serial.println("Right before MQTT_Broker line");
    client.setServer(MQTT_BROKER, 1883);
    Serial.println("Right after MQTT_Broker line");
    connectMQTT();  // This is the problem; it's not getting past this.  
    Serial.println("Right after connectMQTT line");
    Serial.println("End of setup");
}

void loop() {
    Serial.println("Beginning of loop");
    if (!client.connected()) {
        connectMQTT();
    }
    client.loop();

    bool doorClosed = digitalRead(REED_SWITCH_PIN) == LOW; // LOW means closed
    client.publish("garage/door", doorClosed ? "closed" : "open");

    delay(1000); // Publish every second
    Serial.println("Publish");
}

void connectMQTT() {
    Serial.println("Beginning of connectMQTT function");
    while (!client.connected()) {
        if (client.connect("Garage_Door_Sensor")) {
            // Connected
            Serial.println("Connected");
        } else {
            delay(5000);
        }
    }
}


