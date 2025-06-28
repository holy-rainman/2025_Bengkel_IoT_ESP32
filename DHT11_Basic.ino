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
char dht11Data[100];
bool getTemperature() 
{ TempAndHumidity newValues = dht.getTempAndHumidity();
  suhu = newValues.temperature;
  kelembapan = newValues.humidity;

  sprintf(dht11Data,"Suhu: %.2f, Kelembapan: %.2f",suhu,kelembapan);
  Serial.println(dht11Data);
	return true;
}

void setup()
{ Serial.begin(9600);
  Serial.println();
  Serial.println("DHT ESP32 example with tasks");
  initTemp();
  tasksEnabled = true;
}

void loop() 
{ if (!tasksEnabled) 
  { delay(2000);
    tasksEnabled = true;
    if (tempTaskHandle != NULL) 
			vTaskResume(tempTaskHandle);
  }
  yield();
}
