#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int buzz = 13;
void setup(void)
{
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");
  sensors.begin();
  pinMode(buzz, OUTPUT);
  digitalWrite(buzz, HIGH);
}
void loop(void)
{ 
  sensors.requestTemperatures(); // Send the command to get temperatures
  float tempC = sensors.getTempCByIndex(0);
  if(tempC != DEVICE_DISCONNECTED_C) 
  {
    //Serial.print("Temperature for the device 1 (index 0) is: ");
    Serial.println(tempC);
    if (tempC >=32){
      digitalWrite(buzz, LOW);
    }
    else{
      digitalWrite(buzz, HIGH);
    }
  } 
  else
  {
    Serial.println("Error: Could not read temperature data");
  }
}