# PlantSpeak
Now don't miss to water your plants, the IoT solution will alert/remind via mobile notification.

This article intended to guide through the design  steps to build Solar Powered IoT solution which can monitor percentage (%) moisture present in soil and temperature of the surrounding seamlessly. This project is powered via solar energy and once it’s up and running barely you have look after it. Well I have this running in my terrace garden from last 3 months without any hitch so far! Refer to the pictures in [ImageGallery](https://github.com/sujeet-ssv/iot_measure_moisture_level/tree/master/ImageGallery). In this project Capacitive soil moisture sensor used to sense water/moisture level inside the soil at an interval of every 5 minutes along with outdoor temperature using DS18b20 chip. 

Capacitive soil sensors are made of corrosion-resistant material and have long service life when compared to resistive sensors. This needs to be kept inserted into the soil around your plants. DS18b20 sensor has  1-Wire interface-and can measure temperatures from -55°C to +125°C with accuracy of ±0.5°C. Each DS8B20 has a unique 64-bit serial address burned in factory, [refer Addressfinder to know this unique address](https://github.com/sujeet-ssv/iot_measure_moisture_level/tree/master/AddressFinder). The sensor data scheduled to be collected every 5 minutes and sent over to ThingSpeak IoT cloud platform using Esp8266 wifi controller. You can monitor the moisture and temperature level remotely from your mobile device.

## ESP8266 and ThingSpeak IoT Platform
Esp8266 wifi controller connects to your home router and send data to ThingSpeak IoT cloud platform.  You can create your own account on [ThingSpeak.com](https://thingspeak.com/). ThingSpeak is available as a free service for non-commercial small projects (<3 million messages/year or ~8,200 messages/day) (can write max 1 msg every 15 seconds). After registering create a channel and key in fields which will hold sensor data transmitted by your Esp8266 chip. For more information on fields refer 'Configuration with ThingSpeak Monitor Widget' section and/or [Arduino code](https://github.com/sujeet-ssv/iot_measure_moisture_level/raw/master/PlantSpeak_v1.0.ino). Once you are done with the creation of channel you will get Read and Write API keys which are referenced in Arduino code and on Mobile –[IoT ThingSpeak Monitor Widget application](https://play.google.com/store/apps/details?id=ua.livi.thingspeakmonitor&hl=en_US) Download the mobile app from Google PlayStore. Refer below section to know more about how you can configure the ThingSpeak Monitor Widget on mobile.

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
1. Use good quality casing preferably waterproof to mount the Esp8266 module and other components. Take extra care if you are planning to keep it directly exposed to sunlight. 
2. 5 min sampling interval for sensing data. Esp8266 is programmed to run in deep sleep mode for 97% of the time saving a lot power. In deepsleep everything is off except Real Time Clock (RTC),ESP8266 disables almost all of its functions and reboots after specified period of time.
3. Solar Panel  (Power Calculations)
```

|    Wemos D1 mini R2            |    Esp8266 in Station mode     |    Esp8266  in DeepSleep    |
|--------------------------------|--------------------------------|-----------------------------|
|    Current Consumption         |           150 mA avg           |            250 µA           |
|    Runs Every                  |           300 Seconds          |                             |
|    Wakeup time                 |           ~ 7 seconds          |                             |
|    Number of Runs /Day         |               288              |                             |
|    Total Hour(s) per day       |              0.56              |            23.44            |
|    Total Consumption in mAH    |             84 mAH             |           5.86 mAH          |
|    Per Day power demand        |             90 mAH per day     |                             |
|    Per Week power demand       |             630 mAH            |                             |
```
4. Generally 2000mAh power bank chargers are based on TP4056 module, use solar panel with power rating at least  Vout=6 volts,I=500 mA, 3W. This is considering monsoon season where the ambient light will be low. 
5. Do not keep debug trace Serial  I/O turned on in Esp8266 chip for maximum power saving.
6. For accurate results make sure you insert the Capacitive Soil sensor inside <b>well-draining soil</b>. You can use Coco Peat Soil mix which is good in draining water and also not sticky. If its not possible to change the entire soil make a small dig depth :4-6 inches and 2 inches wide. Fill in Coco Peat directly init and you are good to Go. [Refer to this image for some ideas](https://github.com/sujeet-ssv/iot_measure_moisture_level/raw/master/ImageGallery/cocopeat-filler.jpg)
7. Calibrate the Capacitive Soil Sensor and make appropriate changes in Arduino(PlantSpeak_v1.0.ino) sketch. ``` (DrySoilValue = 500; /*insert the capacitive probe inside dry soild and take this reading */ and WaterValue = 350;  /*insert the capacitive probe inside water and take this reading */ ) ```

## Connection Setup
![Connection Diagram][conn]

## Prototype
![Prototype][proto]<br/>
This is how the end prototype looks like, you can plan to make use of even smaller enclosure case perferably IP65 rated.

## Assembly
![Assembly][assembly]<br/>
Make use of Glue gun to seal the Cable openings etc wherever appropriate. 

## Placement with Sensors, Solar, and Controller
![Placement][placement] ![][solar]<br/>
Typical setup , Solar panel fitted East direction facing where it gets 4-5 hrs sunlight.

## Configuration with ThingSpeak Monitor Widget
![Configure IoT ThingSpeak Monitor Widget on mobile][mobile-configure]<br/>
Configuration settings need to be done in Mobile application 'ThingSpeak Monitor Widget'

## ThingSpeak Monitor Widget
![ThingSpeak Monitor Widget on mobile][widget]![][widget2]<br/>
This is how the widget display near real time information on your mobile device.

## Trend Analytics Temp vs Moisture level
![Trend Analytics][trend]<br/>
In Summer you can observe the perfect curve for Moisture signal decresing linerly as the sun rises and back to > 80% once you water the plant.

## Arduino IDE & Libraries Used
- Arduino IDE 1.8.2 , Recommended to use latest
- Make sure you have the ESP8266 installed (http://arduino.esp8266.com/stable/package_esp8266com_index.json).
- Libraries used
   - OneWire
   - DallasTemperature
   
## Terrace Garden
![Garden Ideas][garden]

[conn]: https://github.com/sujeet-ssv/iot_measure_moisture_level/raw/master/ImageGallery/Connection.JPG
[cocopeat]:https://github.com/sujeet-ssv/iot_measure_moisture_level/raw/master/ImageGallery/cocopeat-filler.jpg
[mobile-configure]: https://github.com/sujeet-ssv/iot_measure_moisture_level/raw/master/ImageGallery/configure.jpg
[widget]: https://github.com/sujeet-ssv/iot_measure_moisture_level/raw/master/ImageGallery/mobile-notification.jpg
[widget2]: https://github.com/sujeet-ssv/iot_measure_moisture_level/raw/master/ImageGallery/widget2.jpg
[trend]: https://github.com/sujeet-ssv/iot_measure_moisture_level/raw/master/ImageGallery/trend_analytics.jpg
[proto]: https://github.com/sujeet-ssv/iot_measure_moisture_level/raw/master/ImageGallery/prototype.jpg
[placement]: https://github.com/sujeet-ssv/iot_measure_moisture_level/raw/master/ImageGallery/assembly-all.jpg
[assembly]: https://github.com/sujeet-ssv/iot_measure_moisture_level/raw/master/ImageGallery/assembly.jpg
[garden]: https://github.com/sujeet-ssv/iot_measure_moisture_level/raw/master/ImageGallery/Garden.jpg
[solar]: https://github.com/sujeet-ssv/iot_measure_moisture_level/raw/master/ImageGallery/solar.jpg

