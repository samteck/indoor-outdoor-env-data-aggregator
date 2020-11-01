# indoor-outdoor-env-data-aggregator
This project will aggregate various environmental values from indoor and outdoor of the house using various sensors and store those values on Cloud. Afterwards we can expose this data via various API's and can draw inferences.

We will be following 2 layered IOT architecture for this project in which our Edge device will be communicating directly to Cloud.

## Edge Side 
We will be having a couple of sensors interfaced with an MCU to get the data and send it to cloud via MQTT.

## Cloud Side 
On the cloud side we will set up an MQTT broker to receive the telemetry from Edge device and store it into any timeseries database. Then we can expose some API's so that the data can be accessed over web.

### Hardwaare to be used

#### MPU
1. Raspberry Pi (for first POC)
2. ESP32

#### Sensors
1. DHT11 [temp and humidity] (for first POC)
2. MQ135 [Air Quality] (for first POC)
3. DHT22 
4. SM-UART-04L

### Tech to be used

#### Cloud Gateway/Connectivity
1. MQTT (for first POC)
2. Azure IOT Hub
3. COAP

#### Backend and API's
1. Node-Red (for first POC)
2. Node.js

##### Database
1. InfluxDB
2. Mongo DB

#### On Edge
1. Node-Red on Raspberry Pi (for First POC)
2. Python on Raspberry Pi
3. C on ESP32 using esp-idf
