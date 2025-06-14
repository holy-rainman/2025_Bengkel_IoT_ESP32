#define led1 15
#define led2 2
#define led3 4
#define led4 16
#define led5 17
#define led6 5
#define led7 18
#define led8 19

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
{ digitalWrite(led8,LOW);  digitalWrite(led1,HIGH);  delay(50);
  digitalWrite(led1,LOW);  digitalWrite(led2,HIGH);  delay(50);
  digitalWrite(led2,LOW);  digitalWrite(led3,HIGH);  delay(50);
  digitalWrite(led3,LOW);  digitalWrite(led4,HIGH);  delay(50);
  digitalWrite(led4,LOW);  digitalWrite(led5,HIGH);  delay(50);
  digitalWrite(led5,LOW);  digitalWrite(led6,HIGH);  delay(50);
  digitalWrite(led6,LOW);  digitalWrite(led7,HIGH);  delay(50);
  digitalWrite(led7,LOW);  digitalWrite(led8,HIGH);  delay(50); 

  digitalWrite(led1,LOW);  digitalWrite(led8,HIGH);  delay(50);
  digitalWrite(led8,LOW);  digitalWrite(led7,HIGH);  delay(50);
  digitalWrite(led7,LOW);  digitalWrite(led6,HIGH);  delay(50);
  digitalWrite(led6,LOW);  digitalWrite(led5,HIGH);  delay(50);
  digitalWrite(led5,LOW);  digitalWrite(led4,HIGH);  delay(50);
  digitalWrite(led4,LOW);  digitalWrite(led3,HIGH);  delay(50);
  digitalWrite(led3,LOW);  digitalWrite(led2,HIGH);  delay(50);
  digitalWrite(led2,LOW);  digitalWrite(led1,HIGH);  delay(50); 
}
