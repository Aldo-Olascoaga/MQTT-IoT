#include "DHT.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
//#include <ArduinoJson.h>
#include <PubSubClient.h>


//========= MQTT CONFIG =========
const char* mqtt_server = "54.173.105.103"; //IP of instance AWS
const int mqtt_port = 1883;
const char* mqtt_user = "";
const char* mqtt_pwd = "";


// ============ GLOBAL =============
WiFiClient ESP_client;
PubSubClient (ESP_client);

//DHT dht(2, DHT11);  // DHT read from digital pin 4
#define DHTTYPE DHT11 // DHT 11
int DHTPin = 2; // Pin D4 en el MCU
DHT dht(DHTPin, DHTTYPE);

WiFiServer server(80);

int d4 = 14;  //Fotorresistencia  




void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
