#include <srpc.h>
#include <log.h>
#include <eh.h>
#include <proto.h>
#include <ESP8266WiFi.h>
#define SUPLADEVICE_CPP
#include <SuplaDevice.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>


WiFiClient client;


#include "myconfig.h"
//#else
//const char* ssid     = "ssid";    // WiFi SSID
//const char* password = "password";  // Wifi Password
//#endif

Adafruit_BME280 bme;

int ledPower = 5;
int ELEVATION = 135;
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;



void get_temperature_and_humidity(int channelNumber, double *temp, double *humidity) {

    delayMicroseconds(samplingTime);
    *temp = bme.readTemperature();
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");
    
    *humidity = bme.readHumidity();
    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");
    if ( isnan(*temp) || isnan(*humidity) ) {
      *temp = -275;
      *humidity = -1;
    }
//    delayMicroseconds(deltaTime);
 //   delayMicroseconds(sleepTime);    
      
}


void setup() {
pinMode(5, OUTPUT);
  Serial.begin(115200);
  WiFi.softAPdisconnect(true); // wyłączenie rozgłaszania sieci ESP

  bool status = bme.begin(0x76);
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  
 
char GUID[SUPLA_GUID_SIZE] = {0x59,0xA7,0x87,0xC4,0x21,0x41,0x50,0x15,0x05,0xC4,0x17,0x15,0xB9,0x2F,0xD2,0x83};  // ﻿with GUID that you can retrieve from https://www.supla.org/arduino/get-guid
uint8_t mac[6] = {0x84, 0xF3, 0xEB, 0x93,0x39, 0xC4};

//  SuplaDevice.addRelay(12, false);                 
//  SuplaDevice.addRelay(13, false);              
//  SuplaDevice.addRelay(14, false);
//  SuplaDevice.addRelay(15, false);
  SuplaDevice.addDHT22();

  
//   CHANNEL7,8 - Opening sensor (Normal Open)
    SuplaDevice.addSensorNO(12, true);   // A0 - ﻿Pin number where the sensor is connected
    SuplaDevice.addSensorNO(14, true);  // Call SuplaDevice.addSensorNO(A0, true) with an extra "true" parameter
                                  // to enable the internal pull-up resistor


  SuplaDevice.begin(GUID,          // Global Unique Identifier 
                    mac,           // Ethernet MAC address
                    "svr9.supla.org",     // SUPLA server address
                    2909,                 // Location ID 
                    "03e1");              // Location Password
    
}

void loop() {
  
  if (WiFi.status() != WL_CONNECTED)
  {
    WiFi_up();
  }
  
  SuplaDevice.iterate();
  SuplaDevice.setTemperatureHumidityCallback(get_temperature_and_humidity);
}


    int supla_arduino_tcp_read(void *buf, int count) {
        _supla_int_t size = client.available();
       
        if ( size > 0 ) {
            if ( size > count ) size = count;
            return client.read((uint8_t *)buf, size);
        };
    
        return -1;
    };
    
    int supla_arduino_tcp_write(void *buf, int count) {
        return client.write((const uint8_t *)buf, count);
    };
    
    bool supla_arduino_svr_connect(const char *server, int port) {
          return client.connect(server, 2015);
    }
    
    bool supla_arduino_svr_connected(void) {
          return client.connected();
    }
    
    void supla_arduino_svr_disconnect(void) {
         client.stop();
    }
    
    void supla_arduino_eth_setup(uint8_t mac[6], IPAddress *ip) {

       WiFi_up();
    }

SuplaDeviceCallbacks supla_arduino_get_callbacks(void) {
          SuplaDeviceCallbacks cb;
          
          cb.tcp_read = &supla_arduino_tcp_read;
          cb.tcp_write = &supla_arduino_tcp_write;
          cb.eth_setup = &supla_arduino_eth_setup;
          cb.svr_connected = &supla_arduino_svr_connected;
          cb.svr_connect = &supla_arduino_svr_connect;
          cb.svr_disconnect = &supla_arduino_svr_disconnect;
          cb.get_temperature = NULL;
          cb.get_temperature_and_humidity = get_temperature_and_humidity;
          cb.get_rgbw_value = NULL;
          cb.set_rgbw_value = NULL;
          
          return cb;
}

void WiFi_up()
{
  Serial.print("Proba podlaczenia do sieci ");
  Serial.println(ssid);

  WiFi.begin(ssid, password); // Próba podłączenia do sieci

  for (int x = 60; x > 0; x--) // Powtarzaj pętlę maksymanie maksymalnie 30 sekund (ponieważ przy każdym elsie jest 0,5 sekundy zwłoki)
  {
    if (WiFi.status() == WL_CONNECTED) // Jezeli WiFi jest podłączone
    {
      break;                           // to zatrzymaj pętlę
    }
    else                                 // w przeciwnym wypadku
    {
      Serial.print(".");               // wystaw na serial .
      delay(500);                      // i czekaj 0,5 sekundy
    }

  }

  if (WiFi.status() == WL_CONNECTED) // Jeżeli połączenie z siecią zostało nawiązane, wyślij na serial jego parametry
  {
    Serial.println("");
    Serial.println("Polaczenie nawiazane");
    Serial.println("Adres IP: ");
    Serial.print(WiFi.localIP());
    Serial.print(" / ");
    Serial.println(WiFi.subnetMask());
    Serial.print("Brama: ");
    Serial.println(WiFi.gatewayIP());
    long rssi = WiFi.RSSI();
    Serial.print("Sila sygnalu (RSSI): ");
    Serial.print(rssi);
    Serial.println(" dBm");
  }
  else    // w przeciwnym wypadku poinformuj przez serial o nieudanej próbie
  {
    Serial.println("");
    Serial.println("Polaczenia nie udalo sie nawiazac");
  }
}
