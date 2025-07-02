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

//============================== Variables
uint8_t LEDs[]={15,2,4,16,17,5,18,19};

void writeOLED(uint8_t x, uint8_t y,String text)
{ display.setCursor(x,y);             
  display.println(text);
  display.display();
}
uint16_t smoothingAnalogValue(uint8_t pin, uint8_t samples = 10) 
{ uint32_t sum = 0;
  for(uint8_t i = 0; i < samples; i++) 
  { sum += analogRead(pin);
    delay(2); 
  }
  return sum / samples;
}

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
	}
	delay(3000);	
}

//=============================================
void setup() 
{ Serial.begin(9600);
  
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.display();
  delay(2000);

  display.setTextSize(2);             
  display.setTextColor(SSD1306_WHITE);
  display.clearDisplay();

  writeOLED(40,0,"DHT11");
  writeOLED(25,30,"Init..."); 
  delay(2000);
  
  pinMode(led1,OUTPUT); pinMode(led5,OUTPUT);
  pinMode(led2,OUTPUT); pinMode(led6,OUTPUT);
  pinMode(led3,OUTPUT); pinMode(led7,OUTPUT);
  pinMode(led4,OUTPUT); pinMode(led8,OUTPUT);
  pinMode(buzz,OUTPUT);

  pinMode(rly1,OUTPUT); pinMode(rly2,OUTPUT);
  pinMode(pb1,INPUT_PULLUP);
  pinMode(pb2,INPUT_PULLDOWN);
  pinMode(irs,INPUT);
}

char tx2buf[100];
uint8_t cnt=0;
void loop() 
{ uint16_t an = smoothingAnalogValue(var);
  float volt = (float)an/4095*3.3;
  uint16_t anMAP=map(an,0,4095,0,8);
  uint16_t LDR = smoothingAnalogValue(ldr);

  sprintf(tx2buf,"ADC:%d, Volt:%.2f, LDR:%d",an,volt,LDR);
  Serial.println(tx2buf);

  for(uint8_t i=0; i<8; i++)
    digitalWrite(LEDs[i], i<anMAP? HIGH:LOW);

  getDHT11();  
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
