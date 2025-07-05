#include <WiFi.h>
#include <PubSubClient.h>
WiFiClient espClient;
PubSubClient client(espClient);

#define LEDpin1      15                        

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

  pinMode(LEDpin1, OUTPUT);  
  digitalWrite(LEDpin1,LOW);  
}
void loop()
{ if(!client.connected()) 
    reconnect(); 
  client.loop();
}
