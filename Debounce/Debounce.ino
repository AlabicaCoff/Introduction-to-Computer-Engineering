const int buttonPin[4] = {2, 4, 6, 8};
const int ledPin[4] = {10, 11, 12, 13};

int reading[4];
int buttonState[4];
int lastButtonState[4] = {LOW, LOW, LOW, LOW};
unsigned long lastDebounceTime[4] = {0, 0, 0, 0};
unsigned long debounceDelay = 50;

int pressed = 0;
int savestate = 0;
int Aval[3] = {0, 0, 0};
int Bval[3] = {0, 0, 0};
int t_value[3] = {0, 0, 0};

void debounce(int i) {
  reading[i] = digitalRead(buttonPin[i]);
  if (reading[i] != lastButtonState[i]) {
    lastDebounceTime[i] = millis();
  }
  if ((millis() - lastDebounceTime[i]) > debounceDelay) {
    if (reading[i] != buttonState[i]) {
      buttonState[i] = reading[i];
      if (savestate == 0 && i != 3) {
        if (buttonState[i] == HIGH) {
          Aval[i] = 1;
        }
      }
      else if (savestate == 1 && i != 3) {
        if (buttonState[i] == HIGH) {
          Bval[i] = 1;
        }
      }
      if (buttonState[3] == HIGH && i == 3) {
        pressed = 1;
      }
    }
  }
}

void ledControl(int n) {
  if (t_value[n] >= 8) {
    digitalWrite(ledPin[3], HIGH);
    t_value[n] = t_value[n] - 8;
  }
  if (t_value[n] >= 4) {
    digitalWrite(ledPin[2], HIGH);
    t_value[n] = t_value[n] - 4;
  }
  if (t_value[n] >= 2) {
    digitalWrite(ledPin[1], HIGH);
    t_value[n] = t_value[n] - 2;
  }
  if (t_value[n] >= 1) {
    digitalWrite(ledPin[0], HIGH);
    t_value[n] = t_value[n] - 1;
  }
}

void resetVal() {
  for (int i = 0; i < 4; i++){
    Aval[i] = 0;
    Bval[i] = 0;
  }
}

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 4; i++) {
    pinMode(buttonPin[i], INPUT_PULLUP);
    pinMode(ledPin[i], OUTPUT);
    digitalWrite(ledPin[i], LOW);
  }
}

void loop() {
  if (pressed == 1 && savestate == 0) {
    t_value[0] = (Aval[2] * 4) + (Aval[1] * 2) + (Aval[0] * 1);
    savestate = 1;
    pressed = 0;
    Serial.print("Aval : ");
    Serial.println(t_value[0]);
    for (int i = 0; i < 4; i++) {
      digitalWrite(ledPin[i], LOW);
    }
  }
  if (pressed == 1 && savestate == 1) {
    t_value[1] = (Bval[2] * 4) + (Bval[1] * 2) + (Bval[0] * 1);
    savestate = 2;
    pressed = 0;
    Serial.print("Bval : ");
    Serial.println(t_value[1]);
    for (int i = 0; i < 4; i++) {
      digitalWrite(ledPin[i], LOW);
    }
  }
  if (pressed == 1 && savestate == 2) {
    pressed = 0;
    savestate = 0;
    Serial.print("outval : ");
    Serial.println(t_value[2]);
    resetVal();
    for (int i = 0; i < 4; i++) {
      digitalWrite(ledPin[i], LOW);
    }
  }

  if (savestate == 1) {
    t_value[2] += t_value[0];
    ledControl(0);
  }
  if (savestate == 2) {
    t_value[2] += t_value[1];
    ledControl(1);
  }
  if (savestate == 0) {
    ledControl(2);
  }

  for (int i = 0; i < 4; i++) {
    debounce(i);
    lastButtonState[i] = reading[i];
  }
}
