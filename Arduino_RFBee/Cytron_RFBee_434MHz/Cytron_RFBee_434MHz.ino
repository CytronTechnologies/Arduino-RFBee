//Cytron RFBee 434MHz

const int buttonPin = 2;
const int ledPin = 13;

int serialData = 0;
int buttonState = 0;

void setup()
{
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(4800);
}

void loop()
{
  while(Serial.available())
  {
    serialData = Serial.read();
    if(serialData == '1')
    {
      digitalWrite(ledPin, HIGH);
    }
    else if(serialData =='0')
    {
      digitalWrite(ledPin, LOW);
    }
  }
  buttonState = digitalRead(buttonPin);
  if(buttonState == HIGH)
  {
    Serial.write('1');
    Serial.println("");
  }
  else if(buttonState == LOW)
  {
    Serial.write('0');
    Serial.println("");
  }
}
