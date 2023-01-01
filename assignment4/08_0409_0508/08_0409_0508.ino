#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET -1
Adafruit_SSD1306 OLED(OLED_RESET);

//Global variables
int game = 0;
const int paddle_len = 8, paddle_wid = 2, ballSize = 2;
int ballX = 64, ballY = 16, ball_speedX, ball_speedY;
int right = random(0, 2), up = random(0, 2);
int botX = 108, botY = 5;
int P_score = 0, B_score = 0;
int winner;

int speakerPin = 8;
int sound1 = 0, sound2 = 0;
int numTones = 10;
int tones[] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440};

void drawCourt() {
  OLED.drawRect(0, 0, 128, 32, WHITE);
}

void startGame() {
  OLED.clearDisplay();
  OLED.setTextColor(WHITE);
  OLED.setTextSize(1);
  OLED.setCursor(0, 0);
  OLED.println("GAME START");
  OLED.setCursor(0, 15);
  OLED.println("PONG GAME");
  OLED.display();
  delay(5000);
}

void print_PlayerWin() {
  OLED.clearDisplay();
  OLED.setTextColor(WHITE);
  OLED.setTextSize(1);
  OLED.setCursor(0, 0);
  OLED.println("GAME OVER");
  OLED.setCursor(0, 15);
  OLED.println("PLAYER WINS");
  OLED.display();
  delay(5000);
}

void print_BotWin() {
  OLED.clearDisplay();
  OLED.setTextColor(WHITE);
  OLED.setTextSize(1);
  OLED.setCursor(0, 0);
  OLED.println("GAME OVER");
  OLED.setCursor(0, 15);
  OLED.println("BOT WINS");
  OLED.display();
  delay(5000);
}

void setup() {
  Serial.begin(115200);
  pinMode(A0, INPUT);
  pinMode(speakerPin, OUTPUT);
  digitalWrite(speakerPin, HIGH);
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
  //Start game
  if (game == 0) {
    startGame();
    game = 1;
  }
  //Play game
  else if (game == 1) {
    int player = analogRead(A0) / 42; //input variable
    OLED.clearDisplay();
    drawCourt();
    OLED.drawRect(ballX, ballY, ballSize, ballSize, WHITE); //Draw ball
  //Play sound
    if (sound1) {
      tone(speakerPin, 300);
      delay(50);
      noTone(speakerPin);
      sound1 = 0;
    }
    if (sound2) {
      tone(speakerPin, 650);
      delay(400);
      noTone(speakerPin);
      sound2 = 0;
    }
  //Set ball direction
    if (right == 1) {
      ball_speedX = 2;
    }
    else {
      ball_speedX = -2;
    }
    if (up == 1) {
      ball_speedY = -2;
    }
    else {
      ball_speedY = 2;
    }
  //Update ball position
    ballX += ball_speedX;
    ballY += ball_speedY;
  //Ball hit horizontal wall
    if (ballY <= 0) {
      up = 0;
      ballY = 1;
      sound1 = 1;
    }
    else if (ballY + ballSize >= 32) {
      up = 1;
      ballY = 30;
      sound1 = 1;
    }
  //Ball hit paddle
    if (ballX + ballSize == 108 && ballY + ballSize >= botY && ballY <= botY + paddle_len) {
      right = 0;
      sound1 = 1;
    }
    if (ballX == 20 && ballY + ballSize >= player && ballX <= player + paddle_len) {
      right = 1;
      sound1 = 1;
    }
  //AI bot's paddle
    if (ballY > botY + paddle_len / 2 && random(0, 2) == 1) {
      botY += 2;  // Move down
    } else if (ballY < botY + paddle_len / 2 && random(0, 2) == 1) {
      botY += -2;  // Move up
    }
  //Ball hit vertical wall
    if (ballX <= 0) {
      B_score += 1;
      ballX = 64;
      ballY = random(20, 108);
      right = random(0, 2);
      up =  random(0, 2);
      sound2 = 1;
    }
    else if (ballX >= 127) {
      P_score += 1;
      ballX = 64;
      ballY = random(20, 108);
      right =  random(0, 2);
      up =  random(0, 2);
      sound2 = 1;
    }
  //Reset score
    if (P_score >= 10) {
      P_score = 0;
      B_score = 0;
      winner = 1;
      game = 2;
    }
    else if (B_score >= 10) {
      B_score = 0;
      P_score = 0;
      winner = 2;
      game = 2;
    }
  //draw paddle
    OLED.drawRect(20, player, paddle_wid, paddle_len, WHITE);
    OLED.drawRect(botX, botY, paddle_wid, paddle_len, WHITE);

  //Show score
    OLED.setTextColor(WHITE);
    OLED.setTextSize(0);
    OLED.setCursor(10, 2);
    OLED.println(P_score);
    OLED.setCursor(115, 2);
    OLED.println(B_score);
    OLED.display();
  }
  //Show winner
  else {
    if (winner == 1) {
      print_PlayerWin();
    }
    else {
      print_BotWin();
    }
    game = 1;
  }
}
