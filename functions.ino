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