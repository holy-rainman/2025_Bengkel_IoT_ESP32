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
#include "DHTesp.h" 
#include <Ticker.h>
DHTesp dht;

void tempTask(void *pvParameters);
bool getTemperature();
void triggerGetTemp();

TaskHandle_t tempTaskHandle = NULL;
Ticker tempTicker;
bool tasksEnabled = false;
int dhtPin = 33;

//============================== Blynk
char ssid[] = "UTHM_IoT";
char pass[] = "123456abcd";

uint8_t leds[]={15,2,4,16,17,5,18,19};

void writeOLED(uint8_t x, uint8_t y,String text)
{ display.setCursor(x,y);             
  display.println(text);
  display.display();
}
//============================== DHT11 functions
bool initTemp() 
{ byte resultValue = 0;
 	dht.setup(dhtPin, DHTesp::DHT11);
	Serial.println("DHT initiated");

 	xTaskCreatePinnedToCore
  (	tempTask,                       /* Function to implement the task */
    "tempTask ",                    /* Name of the task */
    4000,                           /* Stack size in words */
    NULL,                           /* Task input parameter */
    5,                              /* Priority of the task */
    &tempTaskHandle,                /* Task handle. */
    1                               /* Core where the task should run */
  );
  if (tempTaskHandle == NULL) 
  { Serial.println("Failed to start task for temperature update");
    return false;
  } 
  else 
    tempTicker.attach(20, triggerGetTemp);
  return true;
}
void triggerGetTemp() 
{ if (tempTaskHandle != NULL) 
    xTaskResumeFromISR(tempTaskHandle);
}
void tempTask(void *pvParameters) 
{ Serial.println("tempTask loop started");
	while (1) 
  { if (tasksEnabled) 
      getTemperature();
		vTaskSuspend(NULL);
	}
}

float suhu, kelembapan;
char dht11Data[100], dht11DataOLED[100], dht11DataT[100], dht11DataH[100];
bool getTemperature() 
{ TempAndHumidity newValues = dht.getTempAndHumidity();
  suhu = newValues.temperature;
  kelembapan = newValues.humidity;

  Blynk.virtualWrite(V3,suhu);
  Blynk.virtualWrite(V4,kelembapan);

  sprintf(dht11DataT,"T:%.2f C",suhu);
  sprintf(dht11DataH,"H:%.2f %%",kelembapan);

  display.clearDisplay();
  writeOLED(40,0,"DHT11");
  writeOLED(10,25,dht11DataT); 
  writeOLED(10,42,dht11DataH); 

  sprintf(dht11Data,"Suhu: %.2f, Kelembapan: %.2f",suhu,kelembapan);
  Serial.println(dht11Data);
	return true;
}

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
void getDHT()
{ if(!tasksEnabled) 
  { delay(100);
    tasksEnabled = true;
    if(tempTaskHandle != NULL) 
			vTaskResume(tempTaskHandle);
  }
  yield();
}

void setup()
{ display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.display();
  delay(2000);

  display.setTextSize(2);             
  display.setTextColor(SSD1306_WHITE);
  display.clearDisplay();

  initTemp();
  tasksEnabled = true;

  writeOLED(40,0,"DHT11");
  writeOLED(20,30,"Init....");

  
  for(uint8_t i=0;i<8;i++)
  { pinMode(leds[i],OUTPUT);
    digitalWrite(leds[i],HIGH);
  }

  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(200,kelip);
  timer.setInterval(10,getADC);
  timer.setInterval(1000,getDHT);
}

void loop()
{ Blynk.run();
  timer.run();
}

// char ssid[] = "UTHM_IoT";
// char pass[] = "123456abcd";
