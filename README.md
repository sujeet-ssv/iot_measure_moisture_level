# iot_measure_moisture_level
## PlantSpeak
Now don't miss to water your plants, the IoT solution mentioned here will alert/remind you on your mobile via notification.

I will guide through how you can construct IoT solution which can monitor moisture and temperature of your terrace garden seamlessly using Solar Power. This project is powered via solar energy and once it’s up and running barely you have look after it. Well I have this running in my terrace garden from last 3 months without any hitch so far! Refer to the pictures in [ImageGallery](https://github.com/sujeet-ssv/iot_measure_moisture_level/tree/master/ImageGallery).

## ESP8266 and ThingSpeak IoT Platform
Esp8266 wifi controller connects to your home router and send data to ThingSpeak IoT cloud platform.  You can create your own account on [ThingSpeak.com](https://thingspeak.com/). ThingSpeak is available as a free service for non-commercial small projects (<3 million messages/year or ~8,200 messages/day) (can write max 1 msg every 15 seconds). After registering create a channel and key in fields which will hold sensor data transmitted by your Esp8266 chip. Once you are done with the creation of channel you will get Read and Write API keys which are referenced in Arduino code and on Mobile –[IoT ThingSpeak Monitor Widget application](https://play.google.com/store/apps/details?id=ua.livi.thingspeakmonitor&hl=en_US) Download the mobile app from Google PlayStore. Refer below section to know more about how you can configure the ThingSpeak Monitor Widget on mobile.
 

## Hardware
You need below components:
1. Wemos D1 Mini Wifi Internet Development Board Based Esp8266 
2. Capacitive soil moisture sensor v1.2
3. Waterproof DS18B20 Digital Temperature Sensor Probe
4. Solar Panel >5W , 6v
5. General PCB small one
6. 4.7K resistor 
7. Battery bank 2000 mAh
(Search above components on Google and find out the nearest trusted seller according to your country. You will find all these components on Amazon as well.)


## Design Considerations
- Use good quality casing preferably waterproof to mount the Esp8266 module and other components. Take extra care if you are planning to keep it directly exposed to sunlight. 
- Solar Panel  (Power Calculations)
```
|    Wemos D1 mini R2            |    Esp8266 in Station mode     |    Esp8266  in DeepSleep    |
|--------------------------------|--------------------------------|-----------------------------|
|    Current Consumption         |           150 mA avg           |            250 µA           |
|    Runs Every                  |           300 Seconds          |                             |
|    Wakeup time                 |           ~ 7 seconds          |                             |
|    Number of Runs /Day         |               288              |                             |
|    Total Hour(s) per day       |              0.56              |            23.44            |
|    Total Consumption in mAH    |             84 mAH             |           5.86 mAH          |
|    Per Day power demand        |         90 mAH per day         |                             |
|    Per Week power demand       |             630 mAH            |                             |
```

-	Generally 2000mAh power bank chargers are based on TP4056, use solar panel with power rating at least  Vout =6 volts , Isc = 500 mA , 3W. This is considering monsoon season where the  ambient light will be low. 
-	Do not keep debug trace Serial  I/O turned on in Esp8266 chip for maximum power saving


## Connection Setup
![Connection Diagram][conn]

## Configuration with ThingSpeak Monitor Widget
## Arduino IDE & Libraries Used
- Arduino IDE 1.8.2 , Recommended to use latest
- Make sure you have the ESP8266 installed (http://arduino.esp8266.com/stable/package_esp8266com_index.json).
- Libraries used
-- OneWire
-- DallasTemperature

[conn]: https://github.com/sujeet-ssv/iot_measure_moisture_level/raw/master/ImageGallery/Connection.JPG



Everything is off but the Real Time Clock (RTC),
When in deep sleep, ESP8266 disables almost all of its functions and reboots after specified period of time. 

The Wemos D1 mini is said to consume around 77 microAmps in Deep Sleep. The on-board USB-Serial interface is said to consume about 50 microAmps, making a total of 127 microAmps for the whole system.

