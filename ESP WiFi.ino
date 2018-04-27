#include<stdlib.h>

#define SSID "<SSID>"
#define PASS "<password>"
#define IP "api.thingspeak.com"
//String GET = "GET /update?key=GKXXWO25MLONCAUO&field1=";

void wifipass(int, String);
const int ledpin = 6;
const int pin = A1;
int led;

void setup()
{ 
  Serial.begin(9600);
  pinMode(ledpin, OUTPUT);
  digitalWrite(ledpin, LOW); 
  Serial.println("AT");
  delay(3000);
  if(Serial.find("OK")){
    connectWiFi();
  }
}

void loop() {
int value=analogRead(pin);
led=led_funct(value); 
String GET = "GET /update?key=63T39LIM1TNJD3P2&field1=";
String GET1 = "GET /update?key=63T39LIM1TNJD3P2&field2=";
  wifipass(value,GET);
  wifipass(led,GET1);
}

void wifipass(int x, String temp)
{
 String beginning = "AT+CIPSTART=\"TCP\",\"";
 beginning  += IP;
 beginning  += "\",80";
 Serial.println(beginning );
 delay(2000);
 if(Serial.find("Error"))
    return;  
 beginning= temp;
 beginning +=x;
 beginning +="\r\n";
 Serial.print("AT+CIPSEND=");
 Serial.println(beginning.length());
 if(Serial.find(">")){
   Serial.print(beginning);
  }
 else
    Serial.println("AT+CIPCLOSE");
 delay(2000);
}
 
boolean connectWiFi(){
 Serial.println("AT+CWMODE=1");
 delay(2000);
 String hotspot="AT+CWJAP=\"";
 hotspot+=SSID;
 hotspot+="\",\"";
 hotspot+=PASS;
 hotspot+="\"";
 Serial.println(hotspot);
 delay(3000);
 if(Serial.find("OK"))
    return true;
  else
    return false;
}

int led_funct(int x){
  Serial.print("\t");
  Serial.println(x);
  if(x<70){
    digitalWrite(ledpin, HIGH);
    return 1;
  }
  else{
   digitalWrite(ledpin, LOW);
   return 0; 
  }
  delay(100);
}

