#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "wi-fi_config.h"

#define REED_PIN D5  // GPIO14

const char* mqtt_server = "192.168.180.36";
const char* topic = "garage/door";

WiFiClient espClient;
PubSubClient client(espClient);

int lastState = -1;

void setup_wifi() {
  delay(10);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("garage-door-sensor")) {
      // Connected
    } else {
      delay(5000);
    }
  }
}

void setup() {
  pinMode(REED_PIN, INPUT_PULLUP);  // Internal pull-up enabled
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int state = digitalRead(REED_PIN);

  if (state != lastState) {
    lastState = state;
    if (state == HIGH) {
      client.publish(topic, "open");
    } else {
      client.publish(topic, "closed");
    }
  }

  delay(100); // Debounce and avoid spamming
}
