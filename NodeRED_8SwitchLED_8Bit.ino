#include <WiFi.h>
#include <PubSubClient.h>
WiFiClient espClient;
PubSubClient client(espClient);

#define LEDpin1 15                        
#define LEDpin2 2                        
#define LEDpin3 4                        
#define LEDpin4 16                        
#define LEDpin5 17                        
#define LEDpin6 5                        
#define LEDpin7 18                        
#define LEDpin8 19                        

uint8_t leds[]={15,2,4,16,17,5,18,19};

const char* ssid = "YOUR_SSID";                   
const char* password = "YOUR_PASSWORD";         
const char* mqtt_server = "broker.emqx.io";

//=========================================== WiFi & MQTT SETUP BEGIN ===========================================
char tx2buf[100];
void setup_wifi()
{ delay(10);
  sprintf(tx2buf,"Connecting to %s",ssid);
  Serial.println(tx2buf);
  WiFi.begin(ssid, password);

  while(WiFi.status()!=WL_CONNECTED) 
  { delay(500);
    Serial.print(".");
  }
  sprintf(tx2buf,"WiFi connected.\nIP address: %s\n\n",WiFi.localIP());
  Serial.println(tx2buf);
}

void callback(char* topic, byte* payload, unsigned int length) 
{ String msg="";

  for(int i=0;i<length;i++) msg+=(char)payload[i];
  sprintf(tx2buf,"Message arrived [%s]: %s\n",topic,msg.c_str());
  Serial.print(tx2buf);

  if(msg=="led1_1") digitalWrite(LEDpin1,HIGH);
  if(msg=="led1_0") digitalWrite(LEDpin1,LOW);
  if(msg=="led2_1") digitalWrite(LEDpin2,HIGH);
  if(msg=="led2_0") digitalWrite(LEDpin2,LOW);
  if(msg=="led3_1") digitalWrite(LEDpin3,HIGH);
  if(msg=="led3_0") digitalWrite(LEDpin3,LOW);
  if(msg=="led4_1") digitalWrite(LEDpin4,HIGH);
  if(msg=="led4_0") digitalWrite(LEDpin4,LOW);
  if(msg=="led5_1") digitalWrite(LEDpin5,HIGH);
  if(msg=="led5_0") digitalWrite(LEDpin5,LOW);
  if(msg=="led6_1") digitalWrite(LEDpin6,HIGH);
  if(msg=="led6_0") digitalWrite(LEDpin6,LOW);
  if(msg=="led7_1") digitalWrite(LEDpin7,HIGH);
  if(msg=="led7_0") digitalWrite(LEDpin7,LOW);
  if(msg=="led8_1") digitalWrite(LEDpin8,HIGH);
  if(msg=="led8_0") digitalWrite(LEDpin8,LOW);
}

void reconnect() 
{ while(!client.connected()) 
  { Serial.println("Attempting MQTT connection...");
    if(client.connect("ESPClient")) 
    { Serial.println("Connected");
      client.subscribe("/LedControl");
    } 
    else 
    { sprintf(tx2buf,"Failed, rc=%s  try again in 5 seconds",client.state());
      Serial.println(tx2buf);
      delay(5000);
    }
  }
}
//============================================ WiFi & MQTT SETUP END ============================================

void setup()
{ Serial.begin(115200);
  setup_wifi(); 
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  for(uint8_t i=0;i<8;i++)
  { pinMode(leds[i], OUTPUT);  
    digitalWrite(leds[i],LOW);  
  }
}
void loop()
{ if(!client.connected()) 
    reconnect(); 
  client.loop();
}
