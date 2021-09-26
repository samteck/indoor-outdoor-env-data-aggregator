# indoor-outdoor-env-data-aggregator

In many cities of the world, the indoor and outdoor environment varies to a great extent because of natural or man-made causes like; California wildfires, pollution in cities like New Delhi & Beijing, cities near to an active volcano.\
The main goal of this project is to aggregate various environmental values from the indoor and outdoor of the house/facility using various sensors for a certain time and store them in the Cloud for Visualization and further processing.

## The Problem it will Solve

Most of the time in a city we have AQI and Temp sensors just for a specific location, but here we will have local monitoring of the environment using an indoor and outdoor set of sensors (DHT11 for temp and humidity and MQ135 for AQI). We can calculate how much difference is between the gathered sensor values to get an estimation of outside weather conditions.\
The user can be notified if the weather outside is better or worse as compared to other days.\
Plus the data gathered is exclusive to your location and can be used in cities or rural remote areas.\
Plus we can store the telemetry in the cloud for further analysis.

## Future Vision

We will be aggregating the sensor data for over a year and will run various algorithms to infer how much difference is there between the indoor and outdoor air. The data will also be exposed via APIs for 3rd party apps to consume.

My vision for the project is to aggregate reliable data and run various ML algorithms to predict the environmental conditions inside the house as compared to outside and whether it is safe to go outside the home.

---

## Architecture
The project was carried out in 2 phases as described in the diagram below

<img src="https://github.com/samteck/indoor-outdoor-env-data-aggregator/blob/main/architectural-diagrams/ioeda-revisions.png" >

We followed 2 layered IOT architecture for this project in which our Edge device will be communicating directly to Cloud.

<p align="center">
<img src="https://github.com/samteck/indoor-outdoor-env-data-aggregator/blob/main/architectural-diagrams/ioeda-logical-arch.png" width="500">
</p>

Important Features

- Individual set of sensor system for Indoor and Outdoor

- Edge Computing : Calculate Heat Index at Edge

- Cloud Computing : Calculate Vapour Pressure and Dew Point

- Fetch City level data at cloud and store in Influx Database

- Sensor value read time can be adjusted

## Edge Side 

We have two sensor systems (outdoor/indoor) interfaced with an MCU (ESP32) to get the data and send it to the cloud via MQTT.

<p align="center">
<img src="https://github.com/samteck/indoor-outdoor-env-data-aggregator/blob/main/Images/edge-system.jpeg" width="500">
</p>

<p align="center">
<img src="https://github.com/samteck/indoor-outdoor-env-data-aggregator/blob/main/Images/sensor-system-final.jpeg" width="300">
</p>

## Cloud Side 

On the cloud side, we will set up an MQTT broker to receive the telemetry from the Edge device and store it into any time-series database. Then we can expose some API's so that the data can be accessed over the web.

We will also host a data visualization app using Grafana which will help us to view local and historical data.

<img src="https://github.com/samteck/indoor-outdoor-env-data-aggregator/blob/main/Images/grafana-visualization.png">

---

## Hardware used

#### MPU

1. ESP32

#### Sensors

1. DHT11 [temp and humidity]
2. MQ135 [Air Quality]

## Tech to be used (deployed on Cloud VM)

#### Cloud Gateway/Connectivity

1. MQTT

#### Backend and API's

1. Node-Red

#### Database

1. InfluxDB

#### Visualization

1. Grafana
2. Node-Red Dashboard

### Initial Prototyped Branch: https://github.com/samteck/indoor-outdoor-env-data-aggregator/tree/sensor-ardunio-RPi-UI
### Video of the setup : https://www.youtube.com/watch?v=35UjRXJEqd4

Note: The AQI values from MQ135 do not correspond to the PPM values.