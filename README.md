# indoor-outdoor-env-data-aggregator

The main goal of this project is to aggregate various environmental values from the indoor and outdoor of the house using various sensors for a certain time and store them in the cloud. In North India, pollution rapidly increases during certain months of the year and has a major impact on the lives of the people.
We will be aggregating the sensor data for over a year and will run various inferences to find out how much difference is there between the indoor and outdoor air. The data will also be exposed via APIs for 3rd parties to consume.

My vision for the project is to aggregate reliable data and run various ML algorithms to predict the environmental conditions inside the house as compared to outside and whether it is safe to go outside the home.

### Current Working Branch: https://github.com/samteck/indoor-outdoor-env-data-aggregator/tree/sensor-ardunio-RPi-UI

We will be following 2 layered IOT architecture for this project in which our Edge device will be communicating directly to Cloud.

<img src="https://github.com/samteck/indoor-outdoor-env-data-aggregator/blob/main/architectural-diagrams/ioeda-logical-arch.png" width="800">

## Edge Side 
We will be having a couple of sensors interfaced with an MCU to get the data and send it to the cloud via MQTT.

## Cloud Side 
On the cloud side, we will set up an MQTT broker to receive the telemetry from the Edge device and store it into any time-series database. Then we can expose some API's so that the data can be accessed over the web.

### Hardware to be used

#### MPU
1. Raspberry Pi (for first POC)
2. ESP32
3. Arduino

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

#### Database
1. InfluxDB
2. Mongo DB

#### Visualization
1. Node-Red Dashboard
2. Grafana

#### On Edge
1. Node-Red on Raspberry Pi (for First POC)
2. Python on Raspberry Pi
3. C on ESP32 using esp-idf

Note: The AQI values from MQ135 do not correspond to the PPM values.
