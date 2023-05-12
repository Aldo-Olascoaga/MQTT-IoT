void setup() {
  Serial.begin(115200);
  sensors_setup();
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  
  if (!client.connected()) {
    reconnect();
  }

  if (client.connected()){
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    String data = "Humedad: " + String(h) + "% ";
    data = data + "Temperatura: " + String(t) + "°C ";
    
    Serial.println(data);
    data.toCharArray(msg, 100);

    client.publish(root_topic_publish, msg);
  }
  client.loop();
}




//========= Conexion WIFI =========
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
