#define button3 12 //green
#define button2 11 //yellow
#define button1 10 //red
#define LED3 4 // red
#define LED2 3 //yellow
#define LED1 2 //green
#define pressed LOW
#define unpressed HIGH
int delayRed = 0, delayGreen = 0, delayYellow = 0;
int countRed = 0, countGreen = 0, countYellow = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(button3, INPUT);
  pinMode(button2, INPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(LED3, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED1, OUTPUT);
}

void loop()
{
  int timer = millis();
  
  //Red 
    if (timer - delayRed > 3000 && delayRed != 0)
  {
    digitalWrite(LED3, LOW);
    delayRed = 0;
  }
  else if (digitalRead(button3) == unpressed)
  {
    digitalWrite(LED3, !digitalRead(LED3));
    delayRed = millis();
    delay(200);
   }
   
   //Green
    if (timer - delayGreen > 3000 && delayGreen != 0)
  {
    digitalWrite(LED1, LOW);
    delayGreen = 0;
  }
  else if (digitalRead(button1) == pressed && digitalRead(LED3) != unpressed)
  {
    digitalWrite(LED1, !digitalRead(LED1));
    delayGreen = millis();
    delay(200);
  }
  
  //Yellow
    if (timer - delayYellow <= 2000 && delayYellow != 0)
  {
    if ((timer - countYellow) > 500) 
    {
      digitalWrite(LED2, !digitalRead(LED2));
      countYellow = millis();
    }
  }
  else if (timer - delayYellow > 2000 && delayYellow != 0)
  {
    digitalWrite(LED2, LOW);
    delayYellow = 0;
  }
  else if (digitalRead(button2) == pressed && digitalRead(LED3) != unpressed && digitalRead(LED1) != unpressed)
  {
    digitalWrite(LED2, HIGH);
    delayYellow = millis();
    countYellow = millis();
    delay(200);
  }
}
