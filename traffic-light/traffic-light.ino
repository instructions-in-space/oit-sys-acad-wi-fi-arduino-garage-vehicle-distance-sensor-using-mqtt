#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "wi-fi_config.h"

// Pin definitions
const int RED_LED = D1;
const int YELLOW_LED = D2;
const int GREEN_LED = D3;

// MQTT Broker
const char* mqtt_server = "192.168.180.36";

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long previousMillis = 0;
const long flashInterval = 500; // Flash interval for red LED
bool flashState = false;
bool flashingRed = false;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(SSID);

  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("WiFi connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  // Debug messages (uncomment to use)
  //Serial.print("Message arrived [");
  //Serial.print(topic);
  //Serial.print("] ");
  //Serial.println(message);

  // Stop flashing
  flashingRed = false;
  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, LOW);

  if (message == "flashing_red") {
    flashingRed = true;
  } else if (message == "solid_red") {
    digitalWrite(RED_LED, HIGH);
  } else if (message == "yellow") {
    digitalWrite(YELLOW_LED, HIGH);
  } else if (message == "green") {
    digitalWrite(GREEN_LED, HIGH);
  } else if (message == "closed") {
    // All LEDs are already off
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("WemosD1Client")) {
      Serial.println("connected");
      client.subscribe("garage/led");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" trying again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Handle flashing red LED
  if (flashingRed) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= flashInterval) {
      previousMillis = currentMillis;
      flashState = !flashState;
      digitalWrite(RED_LED, flashState ? HIGH : LOW);
    }
  }
}
