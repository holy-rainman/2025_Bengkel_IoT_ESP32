#define BLYNK_TEMPLATE_ID       "TMPL6GcQTz0fp"
#define BLYNK_TEMPLATE_NAME     "Latihan IoT"
#define BLYNK_FIRMWARE_VERSION  "0.1.0"
#define BLYNK_PRINT Serial
#define APP_DEBUG
#define USE_ESP32_DEV_MODULE
#include <WiFi.h>
#include "BlynkEdgent.h"

BlynkTimer timer;

uint8_t status=0;
void kelip()
{ digitalWrite(15,status);
  status=!status;
}

void setup()
{ Serial.begin(9600);
  BlynkEdgent.begin();

  pinMode(15,OUTPUT);
  timer.setInterval(1000,kelip);
}

void loop() 
{ BlynkEdgent.run();
  timer.run();
}

