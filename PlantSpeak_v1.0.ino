#include <string.h>
#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <OneWire.h>
#include <DallasTemperature.h>


#define STARTUP_DELAY_MS      1000
#define LED_BUILTIN 12

// SSID to connect to

float Temperature;
int Hardreset;
const int DrySoilValue = 500; /*insert the capacitive probe inside dry soild and take this reading*/
const int WaterValue = 350;  /*insert the capacitive probe inside water and take this reading */
int intervals = (DrySoilValue - WaterValue)/3;
int soilMoistureValue = 0; // Reset the value to zero
String soilcondion="NA";  //// Reset the value to "NA"

// Data wire (DS18b20) is plugged into port D2 on the ESP8266
#define ONE_WIRE_BUS D2

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);


uint8_t sensor1[8] = { 0x28, 0xC7, 0x6C, 0x79, 0x97, 0x04, 0x03, 0x84  }; /* You need to find out the unique 64-bit address of your DS18b20 , every chip has unique id.
                                                                             Refer this article on how you can find out this 64 bit
                                                                             address https://lastminuteengineers.com/multiple-ds18b20-arduino-tutorial/ */
  void wifi_home_v1() {
            //  Force the ESP into client-only mode
            WiFi.mode(WIFI_STA); 
            WiFi.begin("ssid", "password");     /***********Enter the SSID and Password of your Wifi network.***************/
            while (WiFi.status() != WL_CONNECTED) {
              delay(500);
              //Serial.print("..");
            }
            //Serial.print("Connected to wifi!");
      }
  
  void setup()
  {
    pinMode(LED_BUILTIN, OUTPUT);
    //Serial.begin(115200);  
    /* if you face any issue for troubleshooting purpose can uncomment or Serial.println statement which will help you in debugging 
       otherwise keep them disabled to save on power reqiurements when you run on Solar Entergy */
    
    delay(50);    
    sensors.begin();              
  
    //Serial.println("Setting up WiFi");
    ////Serial.println("Initializing....");
      wifi_home_v1();                     /*Trying to boot ESP in Station mode with hardcoded credentials. */
      if (WiFi.status() != WL_CONNECTED)
    {
      WiFiManager wifiManager;
      wifiManager.setTimeout(120); /* ESP8266 running in Access Point mode with 120 seconds timeout
                                      Connect to  Configure_IoT SSID, Following that you can go to the default IP address 192.168.4.1 to open a web page that allows you to configure your SSID and password;
                                      Once a new SSID and password is set, the ESP reboots and tries to connect; */
  
         if(!wifiManager.autoConnect("Configure_IoT")) {
            //Serial.println("failed to connect and hit timeout");
            delay(500);
            /*reset and try again, or maybe put it to deep sleep, I am going for retrying */
            ESP.reset();
            delay(500);
            } 
    }
    /*if you get here you have connected to the WiFi */
    //Serial.println("connected...yeey :)");
     Hardreset=1; 
}

  void loop(){

        thingspeak();
        //Serial.println("sleeping time"); 
        ESP.deepSleep(290e6); /*  Sleep time of 290 seconds need to be converted to microseconds */
    }

  void blink() {

      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
      digitalWrite(LED_BUILTIN, HIGH);
       delay(500);
      digitalWrite(LED_BUILTIN, LOW);
       delay(500);
      digitalWrite(LED_BUILTIN, HIGH);
    //return;
    }

  void thingspeak() {

    const int httpPort = 80;
    WiFiClient client;
  
    sensors.requestTemperatures();
    //sensors.setResolution(sensor1, 10);`
    Temperature = sensors.getTempC(sensor1);  /* Gets the values of the temperature  */
    //Serial.print("temperature : ");
    //Serial.println(Temperature);

          soilMoistureValue = analogRead(A0);  /*put Sensor insert into soil  */
          //Serial.print("soilMoistureValue : ");
          //Serial.println(soilMoistureValue);

          if(soilMoistureValue > WaterValue && soilMoistureValue < (WaterValue + intervals))
          {
          //Serial.println("Very Wet");
          soilcondion="Very Wet";
          }
          else if(soilMoistureValue > (WaterValue + intervals) && soilMoistureValue < (DrySoilValue - intervals))
          {
          //Serial.println("Wet");
          soilcondion=" Wet";
          }
          else if(soilMoistureValue < DrySoilValue && soilMoistureValue > (DrySoilValue - intervals))
          {
          //Serial.println("Dry");
          soilcondion="Dry";
          }
          else {
          //Serial.println("Needs Calibration");
          soilcondion="Needs Calibration";
          }

    if ( isnan(Temperature))
        {
          //Serial.println("Failed to read from DS18B20 sensor!");
         if (!client.connect("api.thingspeak.com", httpPort)) {
          //Serial.println("Connection failed");
           blink();
           blink();
          return;
        }
  else
        {
          //Serial.println("connected to api.thingspeak.com!");
        }
          /* Do not go for Temperature Conversion to String as it is NaN and attempting to convert this will lead to skewing accuracy of other parameter as well */ 
          char str_soil_moisture[10];
          char str_percentage_soil_moisture[8];
          dtostrf(soilMoistureValue, 8, 2, str_soil_moisture);
          float percentage= (DrySoilValue - soilMoistureValue)/1.5;
          dtostrf(percentage, 4, 2, str_percentage_soil_moisture);
          char buffer[200];   
          sprintf(buffer, "GET /update?api_key=AAAABBBBCCCCDDDD&field1=%s&field2=%s&field3=%s&field4=%s\n",Temperature,soilcondion.c_str(),str_soil_moisture,str_percentage_soil_moisture);
          /* Make sure you change the above Write Api key , you will get this key from thingspeak channel id */
          
          client.print(buffer);
          
          while (client.available()) {
              String line = client.readStringUntil('\r');
            }
          client.stop();
          //Serial.println(buffer);
          //Serial.println("closing connection");
          blink();
            
            return;
          }

  //Serial.print("Temperature: ");
  //Serial.print(Temperature);
  //Serial.println(" Celsius");
   
  if (!client.connect("api.thingspeak.com", httpPort)) {
      //Serial.println("connection failed");
       blink();
       blink();
      return;
      }
  else
      {
          //Serial.println("connected to api.thingspeak.com!");
      }
      char buffer[200];                            
      char str_temp[6];
      char str_soil_moisture[8];
      char str_percentage_soil_moisture[8];
      /* 4 is mininum width, 2 is precision; float value is copied onto str_temp*/
      
      float percentage= (DrySoilValue - soilMoistureValue)/1.5;    /* DrySoilValue-WaterValue / Interval =1.5  */
      
      dtostrf(Temperature, 4, 2, str_temp);
      dtostrf(soilMoistureValue, 6, 2, str_soil_moisture);
      dtostrf(percentage, 4, 2, str_percentage_soil_moisture);
      //Serial.print("Temperature str_temp: ");  
      ////Serial.println(str_temp);  
      sprintf(buffer, "GET /update?api_key=AAAABBBBCCCCDDDD&field1=%s&field2=%s&field3=%s&field4=%s\n",str_temp,soilcondion.c_str(),str_soil_moisture,str_percentage_soil_moisture);
       /* Make sure you change the above Write Api key , you will get this key from thingspeak channel id */
    
      client.print(buffer);
      
      while (client.available()) {
          String line = client.readStringUntil('\r');
          //Serial.print(line);
        }
      client.stop();
      //Serial.println(buffer);
      //Serial.println("closing connection");
      blink();
      Hardreset=0;
     // delay(20000);
 }




