#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//====================================================== DHT11
#include "DHTesp.h" 
#include <Ticker.h>

#ifndef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP32 ONLY!)
#error Select ESP32 board.
#endif

DHTesp dht;
void tempTask(void *pvParameters);
bool getTemperature();
void triggerGetTemp();

TaskHandle_t tempTaskHandle = NULL;
Ticker tempTicker;
ComfortState cf;
bool tasksEnabled = false;
int dhtPin = 25;

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
#define rly2 12
#define pb1  14
#define pb2  27
#define irs  26
#define var  34

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

uint8_t LEDs[]={15,2,4,16,17,5,18,19};
char tx2buf[100];

void writeOLED(uint8_t x, uint8_t y,String text)
{ display.setCursor(x,y);             
  display.println(text);
  display.display();
}
bool initTemp() 
{ byte resultValue = 0;
 	dht.setup(dhtPin, DHTesp::DHT11);
	Serial.println("DHT initiated");

 	xTaskCreatePinnedToCore(
			tempTask,                       
			"tempTask ",                    
			4000,                           
			NULL,                           
			5,                              
			&tempTaskHandle,                
			1);                             

  if (tempTaskHandle == NULL) 
  { Serial.println("Failed to start task for temperature update");
    return false;
  } 
  else 
    tempTicker.attach(2, triggerGetTemp);
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
bool getTemperature() 
{ TempAndHumidity newValues = dht.getTempAndHumidity();
	if (dht.getStatus() != 0) 
  { Serial.println("DHT11 error status: " + String(dht.getStatusString()));
		return false;
	}

  float suhu   = newValues.temperature;
  float lembap = newValues.humidity;

  display.clearDisplay();
  sprintf(tx2buf,"\rT:%.2fC, H:%.0f%%",suhu,lembap);
  writeOLED(50,0,"DHT11");
  writeOLED(20,15,tx2buf);
  Serial.println(" T:" + String(newValues.temperature) + " H:" + String(newValues.humidity)); // + " I:" + String(heatIndex) + " D:" + String(dewPoint) + " " + comfortStatus);
	return true;
}
void setup() 
{ initTemp();
  tasksEnabled = true;
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) 
  { Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);             
  display.setTextColor(SSD1306_WHITE);
  
  pinMode(led1,OUTPUT); pinMode(led5,OUTPUT);
  pinMode(led2,OUTPUT); pinMode(led6,OUTPUT);
  pinMode(led3,OUTPUT); pinMode(led7,OUTPUT);
  pinMode(led4,OUTPUT); pinMode(led8,OUTPUT);
  pinMode(buzz,OUTPUT);

  pinMode(rly1,OUTPUT); pinMode(rly2,OUTPUT);
  pinMode(pb1,INPUT_PULLUP);
  pinMode(pb2,INPUT_PULLDOWN);
  pinMode(irs,INPUT);
  Serial.begin(9600);
}
uint8_t cnt=0;
void loop() 
{ uint16_t an = analogRead(var);
  float volt = (float)an/4095*3.3;
  uint16_t anMAP=map(an,0,4095,0,8);

  for(uint8_t i=0; i<8; i++)
    digitalWrite(LEDs[i], i<anMAP? HIGH:LOW);

  if (!tasksEnabled) 
  { delay(2000);
    tasksEnabled = true;
    if (tempTaskHandle != NULL) 
    { vTaskResume(tempTaskHandle);
		}
  }
  yield();
}
void checkCnt()
{ if(cnt==1) LED1(1);
  if(cnt==2) LED2(1);
  if(cnt==3) LED3(1);
  if(cnt==4) LED4(1);
  if(cnt==5) LED5(1);
  if(cnt==6) LED6(1);
  if(cnt==7) LED7(1);
  if(cnt==8) LED8(1);
  if(cnt==9)
  { cnt=0;
    beep(2,50);
    LED1(0);LED2(0);LED3(0);LED4(0);
    LED5(0);LED6(0);LED7(0);LED8(0);
  }
  return;
}

void beep(uint8_t bil, uint16_t tempoh)
{ for(uint8_t i=0;i<bil;i++)
  { tone(buzz,1000);  delay(tempoh);
    noTone(buzz);     delay(tempoh);
  }
}

void kelip()
{ LED8(0);  LED1(1);  delay(50);
  LED1(0);  LED2(1);  delay(50);
  LED2(0);  LED3(1);  delay(50);
  LED3(0);  LED4(1);  delay(50);
  LED4(0);  LED5(1);  delay(50);
  LED5(0);  LED6(1);  delay(50);
  LED6(0);  LED7(1);  delay(50);
  LED7(0);  LED8(1);  delay(50);
  
  LED1(0);  LED8(1);  delay(50);
  LED8(0);  LED7(1);  delay(50);
  LED7(0);  LED6(1);  delay(50);
  LED6(0);  LED5(1);  delay(50);
  LED5(0);  LED4(1);  delay(50);
  LED4(0);  LED3(1);  delay(50);
  LED3(0);  LED2(1);  delay(50);
  LED2(0);  LED1(1);  delay(50);
}
