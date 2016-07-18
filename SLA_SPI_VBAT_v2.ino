
#include <SPI.h>

void setup() {
  Serial.begin(9600);
  SPI.begin();
  pinMode(53, OUTPUT);
  digitalWrite(53, LOW);
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE1));

}

void loop() {
  
  int receivedVal = 0;
  int trash = 0;
  
  digitalWrite(53, HIGH);
  delay(150);
  trash = SPI.transfer(0b11000010);
  delay(10);
  receivedVal = SPI.transfer16(0x0000);
  digitalWrite(53, LOW);
  Serial.println(receivedVal);
  delay(1000);
  


}
