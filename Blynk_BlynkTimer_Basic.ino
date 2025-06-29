#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6GcQTz0fp"
#define BLYNK_TEMPLATE_NAME "Latihan IoT"
#define BLYNK_AUTH_TOKEN "2sdJnAqS5vkMCrX9Vgn0--1ymAXBKK4A"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
BlynkTimer timer;

char ssid[] = "UTHM_IoT";
char pass[] = "123456abcd";

uint8_t leds[]={15,2,4,16,17,5,18,19};

BLYNK_CONNECTED()
{ Blynk.virtualWrite(V0,LOW);
  Blynk.virtualWrite(V1,LOW);
}
BLYNK_WRITE(V0)
{ int led = param.asInt();
  digitalWrite(leds[0],!led);
}
BLYNK_WRITE(V1)
{ int pwm = param.asInt();
  pwm = 255 - (pwm*255/100);
  analogWrite(leds[1],pwm);
}
bool statusLED=0;
void kelip()
{ digitalWrite(leds[2],statusLED);
  statusLED=!statusLED;
}

void setup()
{ for(uint8_t i=0;i<8;i++)
  { pinMode(leds[i],OUTPUT);
    digitalWrite(leds[i],HIGH);
  }

  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(200,kelip);
}

void loop()
{ Blynk.run();
  timer.run();
}
