#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6rj7YaUWJ"
#define BLYNK_TEMPLATE_NAME "Latihan IoT"
#define BLYNK_AUTH_TOKEN "nNVfm7Ty_6iFg7ntPU-Kzoku7VZZFaEI"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "UTHM_IoT";
char pass[] = "123456abcd";

BLYNK_WRITE(V0)
{ int led = param.asInt();
  digitalWrite(15,!led);
}

void setup()
{ pinMode(15,OUTPUT);
  digitalWrite(15,HIGH);
  
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{ Blynk.run();
}

// char ssid[] = "UTHM_IoT";
// char pass[] = "123456abcd";
