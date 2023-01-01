void setup() {
 // put your setup code here, to run once:
 //563412
}
void loop() {
 //1
 pinMode(2, OUTPUT);
 digitalWrite(2, HIGH);
 pinMode(3, OUTPUT);
 digitalWrite(3, LOW);
 pinMode(4, INPUT);
 delay(1000);
  //2
 pinMode(3, OUTPUT);
 digitalWrite(3, HIGH);
 pinMode(2, OUTPUT);
 digitalWrite(2, LOW);
 pinMode(4, INPUT);
 delay(1000);
 //3
 pinMode(3, OUTPUT);
 digitalWrite(3, HIGH);
 pinMode(4, OUTPUT);
 digitalWrite(4, LOW);
 pinMode(2, INPUT);
 delay(1000);
 //4
 pinMode(4, OUTPUT);
 digitalWrite(4, HIGH);
 pinMode(3, OUTPUT);
 digitalWrite(3, LOW);
 pinMode(2, INPUT);
 delay(1000);
 //5
 pinMode(2, OUTPUT);
 digitalWrite(2, HIGH);
 pinMode(4, OUTPUT);
 digitalWrite(4, LOW);
 pinMode(3, INPUT);
 delay(1000);
 //6
 pinMode(4, OUTPUT);
 digitalWrite(4, HIGH);
 pinMode(2, OUTPUT);
 digitalWrite(2, LOW);
 pinMode(3, INPUT);
 delay(1000);
 //5
 pinMode(2, OUTPUT);
 digitalWrite(2, HIGH);
 pinMode(4, OUTPUT);
 digitalWrite(4, LOW);
 pinMode(3, INPUT);
 delay(1000);
 //4
 pinMode(4, OUTPUT);
 digitalWrite(4, HIGH);
 pinMode(3, OUTPUT);
 digitalWrite(3, LOW);
 pinMode(2, INPUT);
 delay(1000);
 //3
 pinMode(3, OUTPUT);
 digitalWrite(3, HIGH);
 pinMode(4, OUTPUT);
 digitalWrite(4, LOW);
 pinMode(2, INPUT);
 delay(1000);
 //2
 pinMode(3, OUTPUT);
 digitalWrite(3, HIGH);
 pinMode(2, OUTPUT);
 digitalWrite(2, LOW);
 pinMode(4, INPUT);
 delay(1000);
}
