/**
   @example HTTPGET.ino
   @brief The HTTPGET demo of library WeeESP8266.
   @author Wu Pengfei<pengfei.wu@itead.cc>
   @date 2015.03

   @par Copyright:
   Copyright (c) 2015 ITEAD Intelligent Systems Co., Ltd. \n\n
   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of
   the License, or (at your option) any later version. \n\n
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
*/

#include "ESP8266.h"
#include <SoftwareSerial.h>
SoftwareSerial mySerial(11, 10); /* RX:D3, TX:D2 */

#define SSID        "dar1g"
#define PASSWORD    "0922600161"
#define HOST_NAME   "106.187.54.242"
const char* host = "106.187.54.242";

#define HOST_PORT   (80)

ESP8266 wifi(mySerial);

void setup(void)
{
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  Serial.print("setup begin\r\n");

  Serial.print("FW Version:");
  Serial.println(wifi.getVersion().c_str());

  if (wifi.setOprToStationSoftAP()) {
    Serial.print("to station + softap ok\r\n");
  } else {
    Serial.print("to station + softap err\r\n");
  }

  if (wifi.joinAP(SSID, PASSWORD)) {
    Serial.print("Join AP success\r\n");

    Serial.print("IP:");
    Serial.println( wifi.getLocalIP().c_str());
  } else {
    Serial.print("Join AP failure\r\n");
  }

  if (wifi.disableMUX()) {
    Serial.print("single ok\r\n");
  } else {
    Serial.print("single err\r\n");
  }

  Serial.print("setup end\r\n");
}
int num = 0;
void loop(void)
{
  uint8_t buffer[1024] = {0};

  if (wifi.createTCP(HOST_NAME, HOST_PORT)) {
    Serial.print("create tcp ok\r\n");
  } else {
    Serial.print("create tcp err\r\n");
  }
  String val = String( millis());
  Serial.println(val);
  num++;
  String mhello = "";
  if (num % 2 == 0)
    mhello = "GET /upload/dar1203.php?command=1 HTTP/1.1\r\nHost: 106.187.54.242\r\nConnection: close\r\n\r\n";
  else
    mhello = "GET /upload/dar1203.php?command=2 HTTP/1.1\r\nHost: 106.187.54.242\r\nConnection: close\r\n\r\n";

  Serial.println(mhello);
  //  char *hello = "GET /upload/dar1203.php?command=" + val + " HTTP/1.1\r\nHost: 106.187.54.242\r\nConnection: close\r\n\r\n";

  char *hello = mhello.c_str();

  wifi.send((const uint8_t*)hello, strlen(hello));

  uint32_t len = wifi.recv(buffer, sizeof(buffer), 10000);
  if (len > 0) {
    Serial.print("Received:[");
    for (uint32_t i = 0; i < len; i++) {
      Serial.print((char)buffer[i]);
    }
    Serial.print("]\r\n");
  }

  if (wifi.releaseTCP()) {
    Serial.print("release tcp ok\r\n");
  } else {
    Serial.print("release tcp err\r\n");
  }
  delay(5000);


}

