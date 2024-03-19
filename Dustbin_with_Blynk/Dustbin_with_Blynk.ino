#define BLYNK_TEMPLATE_ID "TMPLWvYWd8wi"
#define BLYNK_DEVICE_NAME "Smart Dustbin 1"
#define BLYNK_AUTH_TOKEN "9Qntnrv5xJYa9fB2Y-G_TFfhZ6GDx4Hw"


#define TRIGGER1 D2
#define ECHO1    D1
#define TRIGGER2 D5
#define ECHO2    D6
#define BLYNK_PRINT Serial


#include <Servo.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

Servo myservo;

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "Mi Engineer ";
char pass[] = "11112222";





BLYNK_WRITE(V0)
{
  int value = param.asInt();
  if (value ==1){
  myservo.write(180);

  delay(7000);
  myservo.write(10);
  delay(800);

}
}

void setup()
{

  Serial.begin(115200);
  myservo.attach(D3,500,2400);
  myservo.write(10);
  pinMode(TRIGGER1, OUTPUT);
  pinMode(ECHO1, INPUT);
  pinMode(TRIGGER2, OUTPUT);
  pinMode(ECHO2, INPUT);
 

  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  
}

void loop()
{

  Blynk.run();
  long duration;
  long distance;
  long duration2;
  long distance2;
  int i; 

  digitalWrite(TRIGGER1, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER1, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGER1, LOW);
  duration = pulseIn(ECHO1, HIGH);
  
  distance = duration * 0.034 / 2;
  delay(100);

if (distance <=60){
  myservo.write(180);

  delay(6000);
  myservo.write(10);
  delay(800);

}

else {
    
 digitalWrite(TRIGGER2, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER2, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGER2, LOW);
  duration2 = pulseIn(ECHO2, HIGH);
  distance2 =110- (duration2 * 0.034 / 2);
  
  Blynk.virtualWrite(V2,distance2 );
  delay(1000);
  if (distance2 <=30){
    
    //i+=1;
   

  
    Blynk.logEvent("alert");
    Blynk.email("muhamadzubair2000@gmail.com","Alert","Dustbin is full");
    Serial.println(distance2);
        if (distance2 <=30 && i==5){
      i=0;
      
  }
}
  }
 

}
}