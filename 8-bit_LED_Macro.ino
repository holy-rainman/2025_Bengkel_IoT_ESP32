#define led1 15
#define led2 2
#define led3 4
#define led4 16
#define led5 17
#define led6 5
#define led7 18
#define led8 19

#define LED1(x) digitalWrite(led1, x? HIGH:LOW)
#define LED2(x) digitalWrite(led2, x? HIGH:LOW)
#define LED3(x) digitalWrite(led3, x? HIGH:LOW)
#define LED4(x) digitalWrite(led4, x? HIGH:LOW)
#define LED5(x) digitalWrite(led5, x? HIGH:LOW)
#define LED6(x) digitalWrite(led6, x? HIGH:LOW)
#define LED7(x) digitalWrite(led7, x? HIGH:LOW)
#define LED8(x) digitalWrite(led8, x? HIGH:LOW)

void setup() 
{ pinMode(led1,OUTPUT); pinMode(led5,OUTPUT);
  pinMode(led2,OUTPUT); pinMode(led6,OUTPUT);
  pinMode(led3,OUTPUT); pinMode(led7,OUTPUT);
  pinMode(led4,OUTPUT); pinMode(led8,OUTPUT);
}
void loop() 
{ kelip();
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
