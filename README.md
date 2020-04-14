# supla_termometr

File myconfig.h contains ssid and password for WiFi.

const char* ssid = "your_wifi_ssid";
const char* password = "your_wifi_password";

File suplaconfig.h contains supla server and locations parameters.

char GUID[SUPLA_GUID_SIZE] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    // ﻿with GUID that you can retrieve from https://www.supla.org/arduino/get-guid
uint8_t mac[6] = {0x00,0x00,0x00,0x00,0x00,0x00};
char serverStr[] = "svr0.supla.org";
int locationId = 0000;
char locationPass[] = "0a00";
