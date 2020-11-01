We need to make sure that our sensors are working fine and showing correct values.
For that we will make a sample node-red application in raspberry pi and save the data from sensors.

First trying with Temp Sensor.
Steps:
1. Install Node-Red on raspberry pi
- sudo apt-get update
- sudo apt-get dist-upgrade
- curl -sL https://deb.nodesource.com/setup_10.x | sudo -E bash -
- sudo apt-get install -y nodejs
- sudo npm install -g --unsafe-perm node-red

Node-Red is installed and can be accessed over : http://localhost:1880
Guide Here : https://iot.samteck.net/enablers/node-red/set-up-node-red-64bit-raspberry-pi-os/
