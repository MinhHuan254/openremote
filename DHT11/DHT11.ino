#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <DHT.h>  

// WiFi Configuration
const char* ssid = "Smarthome"; 
const char* password = "123456789"; 

// MQTT Broker Configuration
const char* mqtt_server = "192.168.214.183";
const unsigned int mqtt_port = 8883;
const char* mqtt_username = "master:mqtt_lgc";
const char* mqtt_password = "KOrcZOu7Ymk3dS0Z1v6MeiinYZGq19wo";
const char* mqtt_client_id = "esp32-sensor-01"; 
const char* last_will_topic = "master/esp32-sensor-01/writeattributevalue/writeAttribute/2y2ylM2ZpbvS16bmzfPvtt";
const char* last_will_message = "0";
const char* subscribe_topic = "master/esp32-sensor-01/attribute/subscribeAttribute/2y2ylM2ZpbvS16bmzfPvtt";


#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE); 


WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(mqttCallback);

  
  dht.begin();
}

void loop() {
  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop();

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

 
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  
  client.publish("master/esp32-sensor-01/writeattributevalue/temperature/2y2ylM2ZpbvS16bmzfPvtt", String(temperature).c_str());
  client.publish("master/esp32-sensor-01/writeattributevalue/humidity/2y2ylM2ZpbvS16bmzfPvtt", String(humidity).c_str());

  Serial.print("Temp: ");
  Serial.println(temperature);
  Serial.print("Hum: ");
  Serial.println(humidity);
  Serial.println("- - - - -");

  delay(1000); 
}


void mqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}


void reconnectMQTT() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(mqtt_client_id, mqtt_username, mqtt_password, last_will_topic, 1, true, last_will_message)) {
      Serial.println("connected");
      client.subscribe(subscribe_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}
