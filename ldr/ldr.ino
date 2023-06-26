#define LDRpin A0
int LDRValue = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(2, OUTPUT);
}

void loop()
{
  digitalWrite(2,LOW);

  LDRValue = analogRead(LDRpin);
  if(LDRValue < 100){
    digitalWrite(2,HIGH);
  }else{
    digitalWrite(2,LOW);
  }
}