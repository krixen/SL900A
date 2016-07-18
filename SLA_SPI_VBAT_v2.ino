
#include <SPI.h>

void setup() 
{
  Serial.begin(9600);
  SPI.begin();
  pinMode(53, OUTPUT);  //SEN pin
  digitalWrite(53, LOW);
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE1));
  //1MHZ SPI, SPI mode1 (sample on falling edge)
}

void loop() 
{ 
float battery_voltage;
float temp;  
battery_voltage = vbat();
temp = temperature();
}

float vbat() //function that returns battery voltage
{
  int receivedVal = 0;
  int trash = 0;
    
  digitalWrite(53, HIGH);                    //SEN (/cs) high to start coms
  delay(150);                                //critical delay
  trash = SPI.transfer(0b11000010);          //command mode: get voltage
  delay(10);                                 //critical delay
  receivedVal = SPI.transfer16(0x0000);      //receive data, 16 pulses
  digitalWrite(53, LOW);                     //SEN (/cs) low after coms complete
  float vbattery = receivedVal*.00165+1.69;  //battery conversion
  Serial.print("The Battery Voltage is: ");
  Serial.println(vbattery);
  delay(1000);
  return vbattery;
}

float temperature() //functions that returns temperature
{
  int receivedVal = 0;
  int trash = 0;
  
  digitalWrite(53, HIGH);
  delay(150);
  trash = SPI.transfer(0b11000001);           //comand mode: get temperature
  delay(10);
  receivedVal = SPI.transfer16(0x0000);
  digitalWrite(53, LOW);
  Serial.print("The Temperature is: \t");
  float temp = receivedVal*.18-89.3;          //temperature conversion
  Serial.println(temp);
  delay(1000);
  return temp; 
}
