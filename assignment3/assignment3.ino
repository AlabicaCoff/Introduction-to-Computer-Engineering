const int a = 9;
const int b = 8;
const int c = 2;
const int d = 3;
const int e = 4;
const int f = 10;
const int g = 11;

const int button1 = 12;
const int button2 = 13;

int randnum;

int guess = 0;

int number[9][7] = {
  {1, 0, 0, 1, 1, 1, 1} //1
  , {0, 0, 1, 0, 0, 1, 0} //2
  , {0, 0, 0, 0, 1, 1, 0} //3
  , {1, 0, 0, 1, 1, 0, 0} //4
  , {0, 1, 0, 0, 1, 0, 0} //5
  , {0, 1, 0, 0, 0, 0, 0} //6
  , {0, 0, 0, 1, 1, 1, 1} //7
  , {0, 0, 0, 0, 0, 0, 0} //8
  , {0, 0, 0, 0, 1, 0, 0} //9
};

int result[3][7] = {
  {0, 0, 0, 0, 0, 0, 1} //Correct
  , {0, 1, 0, 0, 0, 0, 1} //Greater
  , {1, 1, 1, 0, 0, 0, 1} //Lower
};

void setup()
{
  Serial.begin(9600);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT);

  randomSeed(analogRead(0));
  randnum = random(1, 10);

  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void displayNum(int n);
void displayResult(int n);
void SwitchA();
void SwitchB();

void loop()
{
  //Start Loop
  SwitchA();
  SwitchB();
}

void displayNum(int n)
{
  digitalWrite(a, number[n - 1][0]);
  digitalWrite(b, number[n - 1][1]);
  digitalWrite(c, number[n - 1][2]);
  digitalWrite(d, number[n - 1][3]);
  digitalWrite(e, number[n - 1][4]);
  digitalWrite(f, number[n - 1][5]);
  digitalWrite(g, number[n - 1][6]);
}

void displayResult(int n)
{
  digitalWrite(a, result[n][0]);
  digitalWrite(b, result[n][1]);
  digitalWrite(c, result[n][2]);
  digitalWrite(d, result[n][3]);
  digitalWrite(e, result[n][4]);
  digitalWrite(f, result[n][5]);
  digitalWrite(g, result[n][6]);
}

void SwitchA()
{
  if (digitalRead(button1) == LOW)
  {
    while (digitalRead(button1) == LOW)
      delay(1);
    if (guess == 9)
      guess = 1;
    else
      guess++;
  }

  if (guess != 0)
  {
    displayNum(guess);
  }
}

void SwitchB()
{
  if (digitalRead(button2) == HIGH)
  {
    while (digitalRead(button2) == HIGH)
      delay(1);
    if (guess == randnum)
    {
      displayResult(0);
      delay(500);
      randnum = random(1, 10);
      guess = 1;
    }
    else if (guess > randnum)
    {
      displayResult(1);
      delay(500);
    }
    else if (guess < randnum)
    {
      displayResult(2);
      delay(500);
    }
  }
}
