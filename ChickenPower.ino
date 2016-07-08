#include "DS3231.h"

// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);
int tempC;
int tempF;
int outlet1=2;
int outlet2=3;

void setup()
{
  // Setup Serial connection
  Serial.begin(115200);
  pinMode(outlet1, OUTPUT);  
  pinMode(outlet2, OUTPUT);  
  
  // Initialize the rtc object
  rtc.begin();
}

void loop()
{

  tempC = rtc.getTemp();
  tempF = (tempC * 1.8) + 32.0; // Convert C to F
  Serial.print("TempF=");
  Serial.print(tempF);
  Serial.print(", ");
  String t = rtc.getTimeStr();
  Serial.print("time=");
  Serial.print(t);
  String h = t.substring(0,2);
  long long_h = h.toInt();
  
  if(tempF<=32){
    digitalWrite(outlet1,LOW);
    Serial.print(", Heater=On,");
  }
  if(tempF>=33){
    digitalWrite(outlet1,HIGH);
    Serial.print(", Heater=Off");
  }
  if(long_h>7 && long_h<20){
    digitalWrite(outlet2,LOW);
    Serial.print(", Light=On");
  }
  else{
    digitalWrite(outlet2,HIGH);
    Serial.print(", Light=Off");
  }
  Serial.print('\n');
  
  // Wait one second before repeating :)
  delay (1000);
}
