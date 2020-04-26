# iot_measure_moisture_level
## PlantSpeak
Now don't miss to water your plants, the IoT solution mentioned here will alert/remind you on your mobile via notification.

I will guide through how you can costruct IoT solution which can monitor moisture and temperature of your terrace garden seemlessly using Solar Power. This project is powered via solar energy and once it’s up and running barely you have look after it. Well I have this running in my terrace garden from last 3 months without any hitch so far! Refer to the pictures in [ImageGallery](https://github.com/sujeet-ssv/iot_measure_moisture_level/tree/master/ImageGallery).

## ESP8266 and ThingSpeak IoT Platform
Esp8266 wifi controller connects to your home router and senddata to ThingSpeak IoT cloud platform.  You can create your own account on [ThingSpeak.com](https://thingspeak.com/). ThingSpeak is available as a free service for non-commercial small projects (<3 million messages/year or ~8,200 messages/day) (can send max 1 msg every 15 seconds). After registering you have to create channel and key in fields which will hold sensor data transmitted by your Esp8266 chip. Once you are done with creation of channel you will get Read and Write Api keys which are referenced in Arduino code and on Mobile –[IoT ThingSpeak Monitor Widget application](https://play.google.com/store/apps/details?id=ua.livi.thingspeakmonitor&hl=en_US) Download the mobile app from Google PlayStore.

## Hardware
You need below components :
1. Wemos D1 Mini Wifi Internet Development Board Based Esp8266 
2. Capacitive soil moisture sensor v1.2
3. Waterproof DS18B20 Digital Temperature Sensor Probe
4. Solar Panel >5W , 6v
5. General PCB small one
6. 4.7K resistor 
7. jumper wires
(Search above components on Google and find out the nearest trusted seller according to your contry. You will find all these components on Amazon as well.)


## Key Considerations
## Connection Setup
![Connection Diagram][conn]

## Configuration with ThingSpeak Monitor Widget
## Arduino IDE & Libraries Used
- Arduino IDE 1.8.2 , Reccomended to use latest
- Make sure you have the ESP8266 installed (http://arduino.esp8266.com/stable/package_esp8266com_index.json).
- Libraries used
-- OneWire
-- DallasTemperature

[conn]: https://github.com/sujeet-ssv/iot_measure_moisture_level/raw/master/ImageGallery/Connection.JPG

