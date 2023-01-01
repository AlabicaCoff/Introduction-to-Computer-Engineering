#define ST_BUTTON 2
#define LED_ST_R 3
#define LED_ST_Y 4
#define LED_ST_G 5

#define WS_BUTTON 6
#define LED_WS_R 7
#define LED_WS_Y 8
#define LED_WS_G 9

#define CS_BUTTON 10
#define LED_CS_R 11
#define LED_CS_G 12

#define goS      0
#define waitS    1
#define waitS2C  2
#define goW      3
#define waitW    4
#define waitW2C  5
#define goC      6
#define waitCS1  7
#define goCS1    8
#define waitCS2  9
#define goCS2    10
#define waitCS3  11
#define goCS3    12
#define waitCW1  13
#define goCW1    14
#define waitCW2  15
#define goCW2    16
#define waitCW3  17
#define goCW3    18

int LED_PIN[8] = {LED_ST_G, LED_ST_Y, LED_ST_R, LED_WS_G, LED_WS_Y, LED_WS_R, LED_CS_G, LED_CS_R};

struct FiniteState
{
  unsigned long ST_Out;
  unsigned long Time;
  unsigned long Next[8];
};

void setup()
{
  pinMode(CS_BUTTON, INPUT_PULLUP);
  pinMode(WS_BUTTON, INPUT_PULLUP);
  pinMode(ST_BUTTON, INPUT_PULLUP);
  for (size_t i = 0; i < 8; i++)
  {
    pinMode(LED_PIN[i], OUTPUT);
  }
}

FiniteState FSM[] = {
  {B10100001, 200, {goS, goS, waitS, waitS, waitS2C, waitS2C, waitS2C, waitS}},
  {B10100010, 500, {goW, goW, goW, goW, goW, goW, goW, goW}},
  {B10100010, 500, {goC, goC, goC, goC, goC, goC, goC, goC}},
  {B10001100, 2000, {goW, waitW, goW, waitW, waitW2C, waitW2C, waitW2C, waitW2C}},
  {B10010100, 500, {goS, goS, goS, goS, goS, goS, goS, goS}},
  {B10010100, 500, {goC, goC, goC, goC, goC, goC, goC, goC}},
  {B01100100, 2000, {goC, waitCS1, waitCW1, waitCS1, goC, waitCS1, waitCW1, waitCS1}},
  {B00100100, 500, {goCS1, goCS1, goCS1, goCS1, goCS1, goCS1, goCS1, goCS1}},
  {B01100100,  500, {waitCS2, waitCS2, waitCS2, waitCS2, waitCS2, waitCS2, waitCS2, waitCS2}},
  {B00100100, 500, {goCS2, goCS2, goCS2, goCS2, goCS2, goCS2, goCS2, goCS2}},
  {B01100100,  500, {waitCS3, waitCS3, waitCS3, waitCS3, waitCS3, waitCS3, waitCS3, waitCS3}},
  {B00100100, 500, {goCS3, goCS3, goCS3, goCS3, goCS3, goCS3, goCS3, goCS3}},
  {B01100100,  500, {goS, goS, goS, goS, goS, goS, goS, goS}},
  {B00100100, 500, {goCW2, goCW2, goCW2, goCW2, goCW2, goCW2, goCW2, goCW2}},
  {B01100100,  500, {waitCW2, waitCW2, waitCW2, waitCW2, waitCW2, waitCW2, waitCW2, waitCW2}},
  {B00100100, 500, {goCW1, goCW1, goCW1, goCW1, goCW1, goCW1, goCW1, goCW1}},
  {B01100100,  500, {waitCW3, waitCW3, waitCW3, waitCW3, waitCW3, waitCW3, waitCW3, waitCW3}},
  {B00100100, 500, {goCW3, goCW3, goCW3, goCW3, goCW3, goCW3, goCW3, goCW3}},
  {B01100100,  500, {goW, goW, goW, goW, goW, goW, goW, goW}},
};

int S;
int Input, Input1, Input2, Input3;

void loop()
{
  for (size_t i = 0; i < 8; i++)
  {
    digitalWrite(LED_PIN[i], bitRead(FSM[S].ST_Out, i));
  }

  delay(FSM[S].Time);

  Input1 = !digitalRead(CS_BUTTON);
  Input2 = !digitalRead(WS_BUTTON);
  Input3 = !digitalRead(ST_BUTTON);
  Input = Input1 * 4 + Input2 * 2 + Input3;

  S = FSM[S].Next[Input];
}
