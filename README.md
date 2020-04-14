<h1 class="code-line" data-line-start=0 data-line-end=1 ><a id="supla_termometr_0"></a>supla_termometr</h1>
<p class="has-line-data" data-line-start="2" data-line-end="3">File myconfig.h contains ssid and password for WiFi.</p>
<p class="has-line-data" data-line-start="4" data-line-end="6">const char* ssid = “your_wifi_ssid”;<br>
const char* password = “your_wifi_password”;</p>
<p class="has-line-data" data-line-start="7" data-line-end="8">File suplaconfig.h contains supla server and locations parameters.</p>
<p class="has-line-data" data-line-start="9" data-line-end="15">char GUID[SUPLA_GUID_SIZE] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};<br>
// ﻿with GUID that you can retrieve from <a href="https://www.supla.org/arduino/get-guid">https://www.supla.org/arduino/get-guid</a><br>
uint8_t mac[6] = {0x00,0x00,0x00,0x00,0x00,0x00};<br>
char serverStr[] = &quot;<a href="http://svr0.supla.org">svr0.supla.org</a>&quot;;<br>
int locationId = 0000;<br>
char locationPass[] = “0a00”;</p>
