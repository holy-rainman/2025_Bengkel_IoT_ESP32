#define BLYNK_TEMPLATE_ID       "TMPL6aerwZCkK"
#define BLYNK_TEMPLATE_NAME     "Kawalan Tangki Air Automatik"
#define BLYNK_FIRMWARE_VERSION  "0.1.0"
#define BLYNK_PRINT Serial
#define APP_DEBUG
#define USE_ESP32_DEV_MODULE
#include <WiFi.h>
#include "BlynkEdgent.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH    128
#define SCREEN_HEIGHT   64
#define OLED_RESET      -1 
#define SCREEN_ADDRESS  0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define led1(x) digitalWrite(15,x? HIGH:LOW)
#define led2(x) digitalWrite(2,x? HIGH:LOW)
#define led3(x) digitalWrite(4,x? HIGH:LOW)
#define led4(x) digitalWrite(16,x? HIGH:LOW)
#define led5(x) digitalWrite(17,x? HIGH:LOW)
#define led6(x) digitalWrite(5,x? HIGH:LOW)
#define led7(x) digitalWrite(18,x? HIGH:LOW)
#define led8(x) digitalWrite(19,x? HIGH:LOW)

#define rly1(x) digitalWrite(13,x? LOW:HIGH)

#define pb1     digitalRead(27) //AL (input_pullup)
#define pb2     digitalRead(26) //AH (input_pulldown)

#define buzz  23

uint8_t leds[]={15,2,4,16,17,5,18,19};
uint8_t bypass=0;

BlynkTimer timer;
WidgetLED led(V1);

BLYNK_CONNECTED()
{ led2(1);
  beep(2,50);
  led.off();
  Blynk.virtualWrite(V2,0);
}
BLYNK_DISCONNECTED()
{ led2(0);
  beep(10,10);
}
void getPB()
{ if(pb1==0)  
  { beep(1,50);
    rly1(1);
    led3(1);
    led.on();
    Blynk.virtualWrite(V2,1);

    while(pb1==0);
    delay(200);
  }

  if(pb2==1)  
  { beep(1,50);
    rly1(0);
    led3(0);
    led.off();
    Blynk.virtualWrite(V2,0);

    while(pb2==1);
    delay(200);
  }
}
void writeOLED(uint8_t x, uint8_t y,String text)
{ display.setCursor(x,y);             
  display.println(text);
  display.display();
}
char text[100], text1[100], text2[100];
float adc, distance;
void getADC()
{ adc = analogRead(34);
  distance = adc/819;
  Blynk.virtualWrite(V0,distance);

  sprintf(text,"Height: %.2f",distance);
  Serial.println(text);

  if(distance<0.5 || bypass==1) { rly1(1); led.on();  Blynk.virtualWrite(V2,1); }
  if(distance>4.5)              { rly1(0); led.off(); Blynk.virtualWrite(V2,0); bypass=0; }
}
void beep(uint8_t bil, uint16_t tempoh)
{ for(uint8_t i=0;i<bil;i++)
  { tone(buzz,1000);  delay(tempoh);
    noTone(buzz);     delay(tempoh);
  }
}
void displayOLED()
{ display.setTextSize(2);             
  display.clearDisplay();
  
  sprintf(text1,"Jarak");
  sprintf(text2,"%.2fm",distance);
  writeOLED(38,18,text1);
  writeOLED(38,40,text2);
}
BLYNK_WRITE(V2)
{ int pb = param.asInt();
  beep(3,20);
  bypass=pb; 
}

void setup()
{ Serial.begin(9600);
  BlynkEdgent.begin();

  for(uint8_t i=0;i<8;i++)  pinMode(leds[i],OUTPUT);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  led1(1);

  pinMode(27,INPUT_PULLUP);
  pinMode(26,INPUT_PULLDOWN);
  pinMode(buzz,OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.display();
  delay(2000);

  timer.setInterval(10,getPB);
  timer.setInterval(10,getADC);
  timer.setInterval(1000,displayOLED);
  beep(1,50);

  display.setTextSize(1);             
  display.setTextColor(SSD1306_WHITE);  
  display.clearDisplay();
  writeOLED(10,25,"Kawalan Tangki Air");
  writeOLED(0,45,"By: Abd Rahim Kasiman");
  delay(2000);
}

void loop() 
{ BlynkEdgent.run();
  timer.run();
}

//Auth Token: uQ67-lF3o33PrMn-GJmCrQ6Q8IJlyYAa

