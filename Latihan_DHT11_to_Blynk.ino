#define led1 15
#define led2 2
#define led3 4
#define led4 16
#define led5 17
#define led6 5
#define led7 18
#define led8 19
#define buzz 23
#define rly1 13
#define rly2 14
#define pb1  27
#define pb2  26
#define irs  25
#define var  34
#define ldr  35

#define LED1(x) digitalWrite(led1, x? HIGH:LOW)
#define LED2(x) digitalWrite(led2, x? HIGH:LOW)
#define LED3(x) digitalWrite(led3, x? HIGH:LOW)
#define LED4(x) digitalWrite(led4, x? HIGH:LOW)
#define LED5(x) digitalWrite(led5, x? HIGH:LOW)
#define LED6(x) digitalWrite(led6, x? HIGH:LOW)
#define LED7(x) digitalWrite(led7, x? HIGH:LOW)
#define LED8(x) digitalWrite(led8, x? HIGH:LOW)

#define RLY1(x) digitalWrite(rly1, x? LOW:HIGH)
#define RLY2(x) digitalWrite(rly2, x? LOW:HIGH)

#define PB1 digitalRead(pb1)
#define PB2 digitalRead(pb2)
#define IRS digitalRead(irs)

//============================== BLYNK
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6GcQTz0fp"
#define BLYNK_TEMPLATE_NAME "Latihan IoT"
#define BLYNK_AUTH_TOKEN "2sdJnAqS5vkMCrX9Vgn0--1ymAXBKK4A"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
BlynkTimer timer;

#define var  34

//============================== OLED
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH    128
#define SCREEN_HEIGHT   64
#define OLED_RESET      -1 
#define SCREEN_ADDRESS  0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//============================== DHT11
#include <dhtESP32-rmt.h>
float temperature = 0.0;
float humidity = 0.0;

//============================== Blynk
char ssid[] = "UTHM_IoT";
char pass[] = "123456abcd";

uint8_t leds[]={15,2,4,16,17,5,18,19};

//============================== Variables
uint8_t LEDs[]={15,2,4,16,17,5,18,19};

//============================== DHT11 functions
char dht11DataOLED[100], dht11DataT[100], dht11DataH[100];;
void getDHT11()
{ uint8_t error=read_dht(temperature, humidity, 33, DHT11);
	if(error)
		Serial.println(error);
	else
	{ Serial.print("Suhu: ");
		Serial.print(temperature);
		Serial.print(", Kelembapan:");
		Serial.println(humidity);

    sprintf(dht11DataT,"T:%.2f C",temperature);
    sprintf(dht11DataH,"H:%.2f %%",humidity);
  
    display.clearDisplay();
    writeOLED(40,0,"DHT11");
    writeOLED(10,25,dht11DataT); 
    writeOLED(10,42,dht11DataH); 

    Blynk.virtualWrite(V3,temperature);
    Blynk.virtualWrite(V4,humidity);
	}
}
void writeOLED(uint8_t x, uint8_t y,String text)
{ display.setCursor(x,y);             
  display.println(text);
  display.display();
}

BLYNK_CONNECTED()
{ Blynk.virtualWrite(V0,LOW);
  Blynk.virtualWrite(V1,LOW);
}
BLYNK_WRITE(V0)
{ int led = param.asInt();
  digitalWrite(leds[0],led);
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
void getADC()
{ uint32_t sum=0, avg=0;
  uint8_t adc=0;
  for(uint8_t i=0; i<10; i++) 
  { sum += analogRead(var);
    delay(2); 
  }
  avg=sum/10;
  adc=map(avg,0,4095,1,10);
  Blynk.virtualWrite(V2,adc);
}

void setup()
{ display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.display();
  delay(2000);

  display.setTextSize(2);             
  display.setTextColor(SSD1306_WHITE);
  display.clearDisplay();

  writeOLED(40,0,"DHT11");
  writeOLED(25,30,"Init..."); 
  delay(2000);
  
  for(uint8_t i=0;i<8;i++)
  { pinMode(leds[i],OUTPUT);
    digitalWrite(leds[i],LOW);
  }

  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(200,kelip);
  timer.setInterval(10,getADC);
  timer.setInterval(3000,getDHT11);
}

void loop()
{ Blynk.run();
  timer.run();
}
