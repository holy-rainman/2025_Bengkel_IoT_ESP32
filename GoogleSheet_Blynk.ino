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

//============================== Google Sheet
#include <Arduino.h>
#include <WiFi.h>
#include "time.h"
#include <ESP_Google_Sheet_Client.h>
#include <GS_SDHelper.h>

// Google Project ID
#define PROJECT_ID "YOUT_PROJECT_ID"

// Service Account's client email
#define CLIENT_EMAIL "YOUR_CLIENT_EMAIL"

// Service Account's private key
const char PRIVATE_KEY[] PROGMEM = "-----BEGIN PRIVATE KEY----...YOUR_PRIVATE_KEY__...--\n";

// The ID of the spreadsheet where you'll publish the data
const char spreadsheetId[] = "YOUR_SPREADSHEET_ID";

// Timer variables
unsigned long lastTime = 0;  
unsigned long timerDelay = 3000;

// Token Callback function
void tokenStatusCallback(TokenInfo info);
const char* ntpServer = "pool.ntp.org";
unsigned long epochTime; 
unsigned long getTime() 
{ time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) 
  {
    return(0);
  }
  time(&now);
  return now;
}

//============================== Variables
uint8_t LEDs[]={15,2,4,16,17,5,18,19};
uint8_t leds[]={15,2,4,16,17,5,18,19};

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
void sendGoogleSheet()
{ bool ready = GSheet.ready();

  if (ready && millis() - lastTime > timerDelay)
  { lastTime = millis();

    FirebaseJson response;

    Serial.println("\nAppend spreadsheet values...");
    Serial.println("----------------------------");

    FirebaseJson valueRange;

    // New DHT11 sensor readings
    getDHT11();
    // Get timestamp
    epochTime = getTime();

    valueRange.add("majorDimension", "COLUMNS");
    valueRange.set("values/[0]/[0]", epochTime);
    valueRange.set("values/[1]/[0]", temperature);
    valueRange.set("values/[2]/[0]", humidity);
    // valueRange.set("values/[3]/[0]", pres);

    bool success = GSheet.values.append(&response /* returned response */, spreadsheetId /* spreadsheet Id to append */, "Sheet1!A1" /* range to append */, &valueRange /* data range to append */);
    if (success)
    { response.toString(Serial, true);
      valueRange.clear();
    }
    else
      Serial.println(GSheet.errorReason());
    
    Serial.println();
    Serial.println(ESP.getFreeHeap());
  }
}
void tokenStatusCallback(TokenInfo info)
{ if (info.status == token_status_error)
  { GSheet.printf("Token info: type = %s, status = %s\n", GSheet.getTokenType(info).c_str(), GSheet.getTokenStatus(info).c_str());
    GSheet.printf("Token error: %s\n", GSheet.getTokenError(info).c_str());
  }
  else
    GSheet.printf("Token info: type = %s, status = %s\n", GSheet.getTokenType(info).c_str(), GSheet.getTokenStatus(info).c_str());
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
  timer.setInterval(10,sendGoogleSheet);

  //============================== Google Sheet
  configTime(0, 0, ntpServer);
  GSheet.printf("ESP Google Sheet Client v%s\n\n", ESP_GOOGLE_SHEET_CLIENT_VERSION);
  GSheet.setTokenCallback(tokenStatusCallback);
  GSheet.setPrerefreshSeconds(10 * 60);
  GSheet.begin(CLIENT_EMAIL, PROJECT_ID, PRIVATE_KEY);
}

void loop()
{ Blynk.run();
  timer.run();
}
