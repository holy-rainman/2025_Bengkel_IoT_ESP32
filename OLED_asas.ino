#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH    128
#define SCREEN_HEIGHT   64
#define OLED_RESET      -1 
#define SCREEN_ADDRESS  0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() 
{ Serial.begin(9600);
  
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.display();
  delay(2000);

  display.setTextSize(1);             
  display.setTextColor(SSD1306_WHITE);
  
  display.clearDisplay();
  display.setCursor(0,5);   display.println(F("Hello, World!"));
  display.setCursor(0,16);  display.println(F("Abd Rahim"));
  display.display();
}

void loop() 
{
}
