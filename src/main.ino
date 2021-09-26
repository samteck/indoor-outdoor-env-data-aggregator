/*
   indoor-outdoor-env-data-aggregator
   Author: Samarth Gupta
   Started Date: 02/03/21
   Version: 3.0 (ESP32)
   Additions : Using ESP32, Wifi and MQTT libraries, Additional Status LED
*/

/////////////////////////////////////////////////////////////////////////


// Including the libraries
#include "DHT.h"
#include <WiFi.h>
#include <PubSubClient.h>

// Declaring model of DHT sensor
#define DHTTYPE    DHT11

// DHT indoor/otdoor Digital pins
#define DHT_INDOOR_PIN 5
#define DHT_OUTDOOR_PIN 4

// MQ indoor/outdoor Analog Pins
#define MQ_INDOOR_PIN 32
#define MQ_OUTDOOR_PIN 35

// Object creation for DHT sensors
DHT indoor_DHT_Sensor(DHT_INDOOR_PIN, DHTTYPE);
DHT outdoor_DHT_Sensor(DHT_OUTDOOR_PIN, DHTTYPE);

// Variables to hold sensor values
float indoor_Temp;
float indoor_Humidity;
int indoor_Aqi;
float outdoor_Temp;
float outdoor_Humidity;
int outdoor_Aqi;

// Wifi Credentials
const char* ssid = "*****";
const char* password = "*****";

// Mosquitto server Credentials
const char* mqtt_server = "152.*.*.*";
#define mqtt_port 1883
#define MQTT_USER "****"
#define MQTT_PASSWORD "******"
#define MQTT_SERIAL_RECEIVER_CH "sam"
#define MQTT_FIRST_PUBLISH "ioeda/device1/activation"
#define MQTT_PUBLISH_TOPIC "ioeda/device1/values"

// Status Pin on Edge Module
#define status_Led 27

long lastMsg = 0;

// Creating client objects for Wifi and MQTT
WiFiClient wifiClient;
PubSubClient client(wifiClient);

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected to broker
  if (WiFi.status() == WL_CONNECTED) {
    while (!client.connected()) {
      Serial.print("Attempting MQTT connection...");
      // Create a random client ID
      String clientId = "IOEDA-";
      clientId += String(random(0xffff), HEX);
      // Attempt to connect
      if (client.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD)) {
        Serial.println("connected");
        // Once connected, publish an announcement...
        client.publish("ioeda/device1/activation", "edge module activated : device 1");
        digitalWrite(status_Led, HIGH);
      } else {
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds");
        digitalWrite(status_Led, LOW);
        // Wait 5 seconds before retrying
        delay(5000);
      }
    }
  }
  else {
    setup_wifi();
    Serial.print("Wifi Re-Connected");
  }
}

void setup()
{
  Serial.begin(115200);  //serial port data write speed

  // Initialize GPIO's
  indoor_DHT_Sensor.begin();
  outdoor_DHT_Sensor.begin();
  pinMode(status_Led, OUTPUT);

  // Setup Wifi and MQTT
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  reconnect(); // first connection to MQTT broker
}

void loop()
{
  if (!client.connected()) //check MQTT connection is alive
    reconnect();
  client.loop(); //keep MQTT connection alive and check for subscribed messages (not used here)

  long now = millis();
  if (now - lastMsg > 596000) { // logic to implement 10 min delay (MQTT connection gets disconnected if used delay for more than keep alive duration)
    lastMsg = now;
    // Reading the actual sensor value (DHT values from DHT objects and MQ values directly from Analog pins)
    indoor_Temp = indoor_DHT_Sensor.readTemperature();
    indoor_Humidity = indoor_DHT_Sensor.readHumidity();
    indoor_Aqi = (analogRead(MQ_INDOOR_PIN));
    delay(2000); //delay after DHT read
    outdoor_Temp = outdoor_DHT_Sensor.readTemperature();
    outdoor_Humidity = outdoor_DHT_Sensor.readHumidity();
    outdoor_Aqi = (analogRead(MQ_OUTDOOR_PIN));
    delay(2000); //delay after DHT read

    // Check if any reads failed and exit early (to try again)
    if (isnan(indoor_Temp) || isnan(indoor_Humidity) || isnan(outdoor_Temp) || isnan(outdoor_Humidity)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      delay(1000);
      return;
    }

    // Heat Index Calculation (Real Feel Temperature)
    float indoor_HI = indoor_DHT_Sensor.computeHeatIndex(indoor_Temp, indoor_Humidity, false);
    float outdoor_HI = outdoor_DHT_Sensor.computeHeatIndex(outdoor_Temp, outdoor_Humidity, false);

    // Creating a JSON string to send
    String json = String(F("{\"indoor_Temp\":\"")) + String(indoor_Temp) + String(F("\",\"indoor_Humidity\":\"")) + String(indoor_Humidity) + String(F("\",\"indoor_Aqi\":\"")) + String(indoor_Aqi) + String(F("\",\"indoor_HI\":\"")) + String(indoor_HI) + String(F("\",\"outdoor_Temp\":\"")) + String(outdoor_Temp) + String(F("\",\"outdoor_Humidity\":\"")) + String(outdoor_Humidity) + String(F("\",\"outdoor_Aqi\":\"")) + String(outdoor_Aqi) + String(F("\",\"outdoor_HI\":\"")) + String(outdoor_HI) + String(F("\"}"));

    // For debugging
    //  Serial.print(indoor_Temp);
    //  Serial.print(",\t");
    //  Serial.print(indoor_Humidity);
    //  Serial.print(",\t");
    //  Serial.print(indoor_Aqi, DEC);
    //  Serial.print(",\t");
    //  Serial.print(indoor_HI);
    //  Serial.print(",\t");
    //  Serial.print(outdoor_Temp);
    //  Serial.print(",\t");
    //  Serial.print(outdoor_Humidity);
    //  Serial.print(",\t");
    //  Serial.print(outdoor_Aqi, DEC);
    //  Serial.print(",\t");
    //  Serial.print(outdoor_Hi);
    //  Serial.print(",\t");

    // Send value to the serial Port
    Serial.println(json);

    // Converting String to Char array for publish function
    int n = json.length();
    char char_array[n + 1];
    strcpy(char_array, json.c_str());

    // Public JSON sensor string to MQTT broker
    client.publish(MQTT_PUBLISH_TOPIC, char_array);
  }
  //delay(600000);
}