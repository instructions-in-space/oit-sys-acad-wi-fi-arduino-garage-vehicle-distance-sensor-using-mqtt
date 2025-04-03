// LED Controller
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "wi-fi_config.h"

#define RED_LED D1
#define YELLOW_LED D2
#define GREEN_LED D3

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
    pinMode(RED_LED, OUTPUT);
    pinMode(YELLOW_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    Serial.begin(115200);
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        digitalWrite(RED_LED, !digitalRead(RED_LED));
        delay(500);
    }
    Serial.println("\nConnected! IP Address: " + WiFi.localIP().toString());
    client.setServer(MQTT_BROKER, 1883);
    client.connect("LED_Controller");
    //client.setCallback(callback);
    //Serial.println("Right before connectMQTT line");
    //connectMQTT();
    //Serial.println("Right after connectMQTT line");
}

void loop() {
    if (!client.connected()) {
        Serial.println("Not connected.");
        //connectMQTT();
    }
    client.loop();
    // client.publish("garage/distance", "mEssagE"); // Basic sanity check.
    client.subscribe("garage/led");
    // --------------------------------------------------------------
    unsigned int length;
    byte* payload;
    char* topic;
    String message = "";
    for (int i = 0; i < length; i++) {
        message += (char)payload[i];
    }
    if (String(topic) == "garage/door" && message == "closed") {
        digitalWrite(RED_LED, LOW);
        digitalWrite(YELLOW_LED, LOW);
        digitalWrite(GREEN_LED, LOW);
    }


    // --------------------------------------------------------------
    delay(500);  // Publish every half second.

}

//void connectMQTT() {
//    Serial.println("Beginning of connectMQTT function");
//    while (!client.connected()) {
//        if (client.connect("LED_Controller")) {
//            client.subscribe("garage/distance");
//            client.subscribe("garage/door");
//        } else {
//            delay(5000);
//        }
//    }
//}

//void callback(char* topic, byte* payload, unsigned int length) {
//    String message = "";
//    for (int i = 0; i < length; i++) {
//        message += (char)payload[i];
//    }
//    if (String(topic) == "garage/door" && message == "closed") {
//        digitalWrite(RED_LED, LOW);
//        digitalWrite(YELLOW_LED, LOW);
//        digitalWrite(GREEN_LED, LOW);
//    }
//    if (String(topic) == "garage/distance") {
//        int distance = message.toInt();
//        controlLEDs(distance);
//    }
//}

//void controlLEDs(int distance) {
//    digitalWrite(RED_LED, LOW);
//    digitalWrite(YELLOW_LED, LOW);
//    digitalWrite(GREEN_LED, LOW);
//    if (distance > 24) {
//        digitalWrite(GREEN_LED, HIGH);
//    } else if (distance > 12) {
//        digitalWrite(YELLOW_LED, HIGH);
//    } else if (distance > 5) {
//        digitalWrite(RED_LED, HIGH);
//    } else {
//        while (true) {
//            digitalWrite(RED_LED, !digitalRead(RED_LED));
//            delay(500);
//        }
//    }
//}


