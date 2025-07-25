#include <WiFi.h>
#include <PubSubClient.h>
WiFiClient espClient;
PubSubClient client(espClient);

#define LEDpin1 15
#define LEDpin2  2
#define LEDpin3  4
#define LEDpin4 16
#define LEDpin5 17
#define LEDpin6  5
#define LEDpin7 18
#define LEDpin8 19

#define pb1     digitalRead(27)
#define pb2     digitalRead(26)

uint8_t leds[]={15,2,4,16,17,5,18,19};

const char* ssid       = "YOUR_SSID";
const char* password   = "YOUR_PASSWORD";
const char* mqtt_server= "broker.emqx.io";

//=========================================== WiFi & MQTT SETUP BEGIN ===========================================
char tx2buf[100];

void setup_wifi()
{ delay(10);
  sprintf(tx2buf,"Connecting to %s",ssid);
  Serial.println(tx2buf);

  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED)
  { delay(500);
    Serial.print(".");
  }
  sprintf(tx2buf,"WiFi connected.\nIP address: %s\n\n",WiFi.localIP().toString().c_str());
  Serial.println(tx2buf);
}

void callback(char* topic, byte* payload, unsigned int length)
{ String msg="";
  for(int i=0;i<length;i++) msg+=(char)payload[i];
  msg.trim();                                        // buang CR/LF jika ada

  sprintf(tx2buf,"Message arrived [%s]: %s",topic,msg.c_str());
  Serial.println(tx2buf);

  if(msg.startsWith("led") && msg.length()>=6 && msg.charAt(4)=='_')
  { int ledNum = msg.charAt(3)-'0';                 // '1'..'8'
    int state  = msg.charAt(5)-'0';                 // '0' atau '1'

    if(ledNum>=1 && ledNum<=8)
      digitalWrite(leds[ledNum-1], state ? HIGH : LOW);
  }

  if(msg=="all_on")  { for(uint8_t i=0;i<8;i++) digitalWrite(leds[i],HIGH); }
  if(msg=="all_off") { for(uint8_t i=0;i<8;i++) digitalWrite(leds[i],LOW); }
}

void reconnect()
{ while(!client.connected())
  { Serial.println("Attempting MQTT connection...");
    if(client.connect("ESPClient"))
    { Serial.println("Connected");
      client.subscribe("aim/LedControl");
    }
    else
    { sprintf(tx2buf,"Failed, rc=%d  try again in 5 seconds",client.state());
      Serial.println(tx2buf);
      delay(5000);
    }
  }
}
//============================================ WiFi & MQTT SETUP END ============================================

void setup()
{ Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server,1883);
  client.setCallback(callback);

  for(uint8_t i=0;i<8;i++)
  { pinMode(leds[i],OUTPUT);
    digitalWrite(leds[i],LOW);                      // LED padam semasa mula
  }
  pinMode(27,INPUT_PULLUP);
  pinMode(26,INPUT_PULLDOWN);
}

void loop()
{ if(!client.connected())
    reconnect();
  client.loop();

  if(pb1==0)  
  { client.publish("aim/Button1Status","Button 1 pressed");
    while(pb1==0);
    delay(200);
  }
  if(pb2==1)  
  { client.publish("aim/Button2Status","Button 2 pressed");
    while(pb2==1);
    delay(200);
  }
  if(pb1==1)  client.publish("aim/Button1Status","Button 1 idle");
  if(pb2==0)  client.publish("aim/Button2Status","Button 2 idle");
}
