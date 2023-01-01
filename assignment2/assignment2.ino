int button[3] = {2, 3, 4}; //RED YELLOW GREEN
int led[3] = {6, 7, 8}; //RED YELLOW GREEN
int counter[3] = {0, 0, 0};
int reading[3];
unsigned long timer[3];
int buttonState[3] = {LOW, HIGH, HIGH}; // DOWN UP IN_UP
int lastButtonState[3] = {LOW, HIGH, HIGH}; // DOWN UP IN_UP
unsigned long lastDebounceTime[3];
unsigned long debounceDelay = 50;

void setup() {
  Serial.begin(9600);
  pinMode(led[0], OUTPUT);
  pinMode(led[1], OUTPUT);
  pinMode(led[2], OUTPUT);
  pinMode(button[0], INPUT);
  pinMode(button[1], INPUT);
  pinMode(button[2], INPUT);
}

void loop() {
  //0 1 2 RED YELLOW GREEN
  reading[0] = digitalRead(button[0]);
  reading[1] = digitalRead(button[1]);
  reading[2] = digitalRead(button[2]);

  //----------------RED CODE------------------------------
  if (reading[0] != lastButtonState[0]) {
    lastDebounceTime[0] = millis();
  }
  if (millis() - lastDebounceTime[0] > debounceDelay) {
    if (reading[0] != buttonState[0]) {
      buttonState[0] = reading[0];
      if (buttonState[0] == HIGH) {
        timer[0] = millis();
        digitalWrite(led[0], HIGH);
        ++counter[0];
      }
    }
  }
  if (buttonState[0] == HIGH && counter[0] > 1) {
    digitalWrite(led[0], LOW);
    counter[0] = 0;
  }
  if (millis() - timer[0] >= 3000 && digitalRead(led[0])) {
    digitalWrite(led[0], LOW);
    counter[0] = 0;
  }
  //----------------RED CODE------------------------------

  //----------------YELLOW CODE---------------------------
  if (reading[1] != lastButtonState[1]) {
    lastDebounceTime[1] = millis();
  }

  if (millis() - lastDebounceTime[1] > debounceDelay) {
    if (reading[1] != buttonState[1]) {
      buttonState[1] = reading[1];
      if (buttonState[1] == HIGH && digitalRead(led[0]) == LOW && digitalRead(led[2]) == LOW) {
        timer[1] = millis();
        counter[1] = millis();
        digitalWrite(led[1], HIGH);
      }
    }
  }
  if (millis() - timer[1] <= 2000 && timer[1] != 0)
  {
    if ((millis() - counter[1]) > 500)
    {
      digitalWrite(led[1], !digitalRead(led[1]));
      counter[1] = millis();
    }
  }
  else if (millis() - timer[1] > 2000 && timer[1] != 0)
  {
    digitalWrite(led[1], LOW);
    timer[1] = 0;
  }
  //----------------YELLOW CODE---------------------------

  //----------------GREEN CODE----------------------------
  if (reading[2] != lastButtonState[2]) {
    lastDebounceTime[2] = millis();
  }
  if (millis() - lastDebounceTime[2] > debounceDelay) {
    if (reading[2] != buttonState[2]) {
      buttonState[2] = reading[2];
      if (buttonState[2] == HIGH && digitalRead(led[0]) == LOW) {
        timer[2] = millis();
        digitalWrite(led[2], HIGH);
        ++counter[2];
      }
    }
  }
  if (buttonState[2] == HIGH && counter[2] > 1) {
    digitalWrite(led[2], LOW);
    counter[2] = 0;
  }
  if (millis() - timer[2] >= 3000 && digitalRead(led[2])) {
    digitalWrite(led[2], LOW);
    counter[2] = 0;
  }
  //----------------GREEN CODE----------------------------

  lastButtonState[0] = reading[0];
  lastButtonState[1] = reading[1];
  lastButtonState[2] = reading[2];
}
