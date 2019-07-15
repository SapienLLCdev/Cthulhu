void setup() {
  // put your setup code here, to run once:
  // put your setup code here, to run once:
Serial.begin(9600);
delay(1000);

for(int i = 3; i<14; i++)
{
pinMode(i, OUTPUT);
digitalWrite(i, LOW);
}
pinMode(A0, OUTPUT);
digitalWrite(A0, LOW);
pinMode(A1, OUTPUT);
digitalWrite(A1, LOW);
pinMode(A2, OUTPUT);
digitalWrite(A2, LOW);
pinMode(A3, OUTPUT);
digitalWrite(A3, LOW);
pinMode(A4, OUTPUT);
digitalWrite(A4, LOW);
pinMode(A5, OUTPUT);
digitalWrite(A5, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
  for(byte i = 2; i <14  ;i++)
  {
Serial.print(DanalogRead(i,100,100));Serial.print(",");
  //delay(5);
  }
    for(byte i = A0; i <A6  ;i++)
  {
Serial.print(DanalogRead(i,10,10));Serial.print(",");
 // delay(5);
  }
  Serial.println();
  delay(50);
}

long DanalogRead(byte pin, byte lowtime, byte hightime)
{
  pinMode(pin, INPUT_PULLUP);
    long timenow = micros();
  delayMicroseconds(hightime);
  pinMode(pin, INPUT);
  while(digitalRead(pin) == HIGH)
  {
    delayMicroseconds(1);
    if ((micros()-timenow)>10000)
    {
      break;
    }
  }
  long reading = micros()-timenow;
  pinMode(pin,OUTPUT);
  digitalWrite(pin, LOW);
  delayMicroseconds(lowtime);
  return reading;  
}
