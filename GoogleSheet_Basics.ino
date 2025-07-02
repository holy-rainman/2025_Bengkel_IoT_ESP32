#include <Arduino.h>
#include <WiFi.h>
#include "time.h"
#include <ESP_Google_Sheet_Client.h>
#include <GS_SDHelper.h>

#define WIFI_SSID "UTHM_IoT"
#define WIFI_PASSWORD "123456abcd"

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

// DHT11 Header
#include <dhtESP32-rmt.h>
float temperature = 0.0;
float humidity = 0.0;

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
	}
}

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

void setup()
{ Serial.begin(9600);
  Serial.println();
  Serial.println();

  configTime(0, 0, ntpServer);
  GSheet.printf("ESP Google Sheet Client v%s\n\n", ESP_GOOGLE_SHEET_CLIENT_VERSION);

  WiFi.setAutoReconnect(true);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) 
  { Serial.print(".");
    delay(1000);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  GSheet.setTokenCallback(tokenStatusCallback);
  GSheet.setPrerefreshSeconds(10 * 60);
  GSheet.begin(CLIENT_EMAIL, PROJECT_ID, PRIVATE_KEY);
}

void loop()
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
