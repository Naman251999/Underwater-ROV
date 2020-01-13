#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define m11 D1   
#define m12 D2
#define m21 D3    
#define m22 D4
OneWire a(14);
DallasTemperature sensora(&a);
char auth[] = "YEbDf38s6t5tSsgv2UWk5-gJtptCKMpG";
char ssid[] = "Shivaji";
char password[] = "9589413267";
void forward()
{
   digitalWrite(m11, LOW);
   digitalWrite(m12, HIGH);
   digitalWrite(m21, LOW);
   digitalWrite(m22, HIGH); 
}
void backward()
{
   digitalWrite(m11, HIGH);
   digitalWrite(m12, LOW);
   digitalWrite(m21, HIGH);
   digitalWrite(m22, LOW);
}
void right()
{
   digitalWrite(m11, LOW);
   digitalWrite(m12, HIGH);
   digitalWrite(m21, HIGH);
   digitalWrite(m22, LOW);
}
void left()
{
   digitalWrite(m11, HIGH);
   digitalWrite(m12, LOW);
   digitalWrite(m21, LOW);
   digitalWrite(m22, HIGH );
} 
void Stop()
{
   digitalWrite(m11, LOW);
   digitalWrite(m12, LOW);
   digitalWrite(m21, LOW);
   digitalWrite(m22, LOW);
   digitalWrite(D5, LOW);
   digitalWrite(D6, LOW);
}
void setup()
{
  pinMode(D1,OUTPUT);  //M11
  pinMode(D0,OUTPUT);  //TEMP IN
  pinMode(D2,OUTPUT); //M12
  pinMode(D3,OUTPUT); //M21
  pinMode(D4,OUTPUT); //M22
  pinMode(D5,INPUT);
  pinMode(D6,OUTPUT); 
  pinMode(D7,OUTPUT); 
  pinMode(D8,OUTPUT); 
  digitalWrite(D1,LOW);
  digitalWrite(D2,LOW);
  digitalWrite(D3,LOW);
  digitalWrite(D4,LOW);
  digitalWrite(D5,LOW);
  digitalWrite(D6,LOW);
  digitalWrite(D7,LOW);
  digitalWrite(D8,LOW);
  sensora.begin();
  Blynk.begin(auth, ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
  }
  delay(2000);
}
BLYNK_WRITE(V1)
{
  if(param.asInt()==1)
   forward();
  else
     Stop();
}
BLYNK_WRITE(V3)
{
  if(param.asInt()==1)
   left();
     else
     Stop();
}
BLYNK_WRITE(V4)
{
  if(param.asInt()==1)
   right();
     else
     Stop();
}
BLYNK_WRITE(V2)
{
  if(param.asInt()==1)
   backward();
     else
     Stop();
}
void loop()
{
   Blynk.run();
   sensora.requestTemperatures();
   Blynk.virtualWrite(V0,sensora.getTempCByIndex(0));   
}
