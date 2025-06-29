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

void setup() 
{ pinMode(led1,OUTPUT); pinMode(led5,OUTPUT);
  pinMode(led2,OUTPUT); pinMode(led6,OUTPUT);
  pinMode(led3,OUTPUT); pinMode(led7,OUTPUT);
  pinMode(led4,OUTPUT); pinMode(led8,OUTPUT);
  pinMode(buzz,OUTPUT);

  pinMode(rly1,OUTPUT); pinMode(rly2,OUTPUT);
  pinMode(pb1,INPUT_PULLUP);
  pinMode(pb2,INPUT_PULLDOWN);
  Serial.begin(9600);
}
char tx2buf[100];
uint8_t cnt=0;
void loop() 
{ if(PB2==1)
  { LED4(1); delay(500);

    while(PB2==1)
    { LED5(1);
      LED4(0);
    }

    LED6(1);  LED5(0);  delay(500);
    LED6(0);
  }
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
