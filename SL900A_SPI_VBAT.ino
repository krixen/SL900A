void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //used random GPIO pins instead of traditional Arduino SPI pins
  pinMode(31,OUTPUT); //CS
  pinMode(32,OUTPUT); //SPICLK
  pinMode(33,OUTPUT); // Data In
  pinMode(34,INPUT); //Data Out

  digitalWrite(31,LOW);
  digitalWrite(32,LOW);
  digitalWrite(33,LOW);
  
}

void loop() {

  int receivedVal = 0; //16-bit integer

  digitalWrite(31, HIGH);  //start with putting SEN line (or /CS) high
                           //Typically CS is low for active but not with this chip
  delayMicroseconds(150);  //This delay is necessary, need at least 150 uS

  //note: the SL900A reads data on the falling edge of the clock
  //note: I put a 1uS delay in between every pulse to make it ~1MHz clock
  //      although digitalWrite takes ~15uS to execute
  
  //I am sending here 11000010 which is command mode - get battery voltage
  
  digitalWrite(32, HIGH); //clock high
  digitalWrite(33, HIGH); //data bit first high
  delayMicroseconds(1);
  digitalWrite(32, LOW);  //clock low, first sample
  delayMicroseconds(1);
  
  digitalWrite(32, HIGH); //clock high
  delayMicroseconds(1);
  digitalWrite(32, LOW);  //clock low, second sample
  delayMicroseconds(1);
  digitalWrite(33, LOW);  //data low
  delayMicroseconds(1);
  
  digitalWrite(32, HIGH); //sample 3
  delayMicroseconds(1);
  digitalWrite(32,LOW);
  delayMicroseconds(1);

  digitalWrite(32, HIGH); //sample 4
  delayMicroseconds(1);
  digitalWrite(32,LOW);
  delayMicroseconds(1);

  digitalWrite(32, HIGH); //sample 5
  delayMicroseconds(1);
  digitalWrite(32,LOW);
  delayMicroseconds(1);

  digitalWrite(32, HIGH); //sample 6
  delayMicroseconds(1);
  digitalWrite(32,LOW);
  delayMicroseconds(1);

  digitalWrite(32, HIGH); //sample 7
  digitalWrite(33,HIGH); 
  delayMicroseconds(1);
  digitalWrite(32,LOW);
  digitalWrite(33,LOW);
  delayMicroseconds(1);

  digitalWrite(32, HIGH); //sample 8
  //digitalWrite(33, HIGH); //sample high
  delayMicroseconds(1);
  digitalWrite(32,LOW);
  delayMicroseconds(1);
  digitalWrite(33,LOW);
  delayMicroseconds(1);

  delay(10); //this delay is CRITICAL, it takes about 10mS to get
             // the data ready, however, you can also do wait for the
             // data line to go high before you start pulsing the clock
             // to read the data, which is the smarter way that I have
             // not implemented yet
  for(int i=0; i<16; i++)   //This loop reads the data, it pulses the clock
  {                         //and samples the output on the falling edge. 
    digitalWrite(32, HIGH);
    delayMicroseconds(1);
    digitalWrite(32,LOW);
    delayMicroseconds(1);
    if(digitalRead(34))
    {
      receivedVal |= 1;
    }
    receivedVal <<= 1;
    delayMicroseconds(1);
  }

  receivedVal >>= 1; //This is here because for some reason the data was shifted over
                     //one, I still have to look into this, for now this will give you
                     //the right data
                     
  float vbat = receivedVal*.00165 + 1.69; //converts 10-bit data to battery voltage in V
  digitalWrite(31, LOW);                  //SPI over, put SEN (/cs) low
  Serial.println(vbat);
  delay(1000);
  }

