// MQTT-IoT
// Herramientas computacionales: el arte de la programación (TC1001S.200)
// Camila Turner A01423579, Aldo Olascoaga A01424731, Patricio Álvarez A01423897
// 12/05/23

#include "DHT.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <PubSubClient.h>



//========== MQTT CONFIG ==========
const char *mqtt_server = "IP ADRESS"; //IP of instance in AWS
const int mqtt_port = 1883; // Port open for MQTT
const char *mqtt_user = ""; // In case of Log In
const char *mqtt_pass = ""; // In case of Log In
const char *root_topic_subscribe = "/input"; // Topic to pub -> Send Info
const char *root_topic_publish = "/output"; // Topic to sub  -> Receive Info



//========== WIFI CONFIG ==========
char* ssid = "INTERNET NET NAME";
char* password =  "INTERNET NET PASSWORD";




//========== GLOBALS ==========
WiFiClient espClient;
PubSubClient client(espClient);
char msg[100]; //length of message
long count=0;


// Configuration for the DHT11 sensor
#define DHTTYPE DHT11 // DHT 11
int DHTPin = 2; // Pin D4 in MCU
DHT dht(DHTPin, DHTTYPE);
float Temperature = 0;
float Humidity = 0;
WiFiServer server(80);



//========== FUNCTIONS ==========
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();
void setup_wifi();
void sensors_setup();

// When start
void setup() {
  Serial.begin(115200);
  sensors_setup();
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

// Every time
void loop() {
  
  if (!client.connected()) { //in case it loses connection
    reconnect();
  }

  if (client.connected()){
    float h = dht.readHumidity(); //get values for humidity
    float t = dht.readTemperature(); //get values for temperature

    String data = "Humedad: " + String(h) + "% ";
    data = data + "Temperatura: " + String(t) + "°C "; //message that will be displayed
    
    Serial.println(data);
    data.toCharArray(msg, 100);

    client.publish(root_topic_publish, msg);
    delay(1000) //comment line to get values in real time
  }

  client.loop();
}



//========= WIFI Connection =========
void setup_wifi(){
  delay(10);
  // Nos conectamos a nuestra red Wifi
  Serial.println();
  Serial.print("Conectando a ssid: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Conectado a red WiFi!");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());
}


//========= MQTT CONNECTION =========    
// In case connection fails...
void reconnect() {
  while (!client.connected()) {
    Serial.print("Intentando conexión Mqtt...");
    // We create a client
    String clientId = "WIX_Team";
    clientId += String(random(0xffff), HEX);
    // Let's try to connect...
    if (client.connect(clientId.c_str(),mqtt_user,mqtt_pass)) {
      Serial.println("Conectado!");
      // Let's suscribe
      if(client.subscribe(root_topic_subscribe)){
        Serial.println("Suscripcion ok");
      }else{
        Serial.println("Fallo Suscripción");
      }
    } else {
      Serial.print("falló :( con error -> ");
      Serial.print(client.state());
      Serial.println(" Intentamos de nuevo en 5 segundos");
      delay(5000);
    }
  }
}


//========= CALLBACK =========
// Callback function for the message
void callback(char* topic, byte* payload, unsigned int length){
  String incoming = "";
  Serial.print("Mensaje recibido desde -> ");
  Serial.print(topic);
  Serial.println("");
  for (int i = 0; i < length; i++) {
    incoming += (char)payload[i];
  }
  incoming.trim();
  Serial.println("Mensaje -> " + incoming);

}


//========= SENSORS SETUP =========

// The purpose of this function is to start the DHT11 sensor so it works smoothly
void sensors_setup(){
  dht.begin();
}
