Home Automation of power plugs
===

Control power outlets with a web interface or via an app.

## Features
This setup allows to control power outlets via the Internet. Making use of various protocols and web technologies you can toggle several power outlets with a device connected to the Internet. It's also possible to set a timer on them when each outlet should turn off.
An app makes the expirience smoother for Android users. The app can be found [here](https://github.com/louisvansanden/PowerStrip9000App).

## The setup
#### Components
The following components are used to make a network of Things that communicate with eachother.
- Raspberry Pi 4
- ESP8266
- relay circuit board for ESP

#### Software 
These components interact with the following software and protocols
- Raspbian on the RPi
  - Apache2 server
    - HTML page
    - PHP - *for connecting to database and using the RPi terminal for MQTT posts*
    - JavaScript with AJAX requests to PHP files on server
    - CSS
  - MySQL database
  - PHP
  - Python
  - MQTT broker
  - MQTT client
- Arduino code with following libraries:
  - ESP8266WiFi   - *for connecting to a WiFi network*
  - WiFiClientSecure   - *for making HTTP requests*
  - PubSubClient   - *for MQTT publishing and subscribing*
  - NTPClient *and* WiFiUdp   - *for retrieving the current time*
- Android Studio App
  - Makes HTTP requests to PHP files on server
  
## Interaction between components
The heart of the network is the Raspberry Pi: it runs the Apache server and the MQTT broker. The ESP modules act as slaves commanded by the RPi: they listen to the assigned MQTT topic and toggle the relays according to the recieved commands. The relays can complete the circuit on 220V so the power outlet turns on.

#### Apache Server
The (Apache) server provides the HTML, JS, CSS and PHP files to users on the same network, with port-forwarding to everyone. This enables a website to control the outlets directly with the HTML pages, or enables HTTP requests to the PHP files to use in e.g. an app. PHP files can alter the SQL database and they can execute a terminal command on the RPi to publish as a client an MQTT message.
In the site it is also possible to change the name of an outlet.

#### MySQL Database
The database stores the variables for every outlet:
- ID
- type (in this case always a plug/outlet)
- state (on/off)
- MQTT topic
- MQTT message prefix
- custom name

The database gets updated via PHP connections when:
- the state of an outlet changes
- the custom name gets changed

## ToDo
- [X] ESP8266: send HTTP request to server to toggle the state when using timer.
- [ ] Add token identification for php-database queries
- [ ] Prettify the webpage with CSS
- [X] Implement a way to retrieve all the devices in JSON format.
- [ ] Implement a way to add devices from the app.
