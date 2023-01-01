#include <Arduino_FreeRTOS.h>
#include "queue.h"

#define RED     6
#define YELLOW  7
#define GREEN   8

#define SW1 2
#define SW2 3
#define SW3 4

unsigned long REDtime = 0;
unsigned long YELLOWtime = 0;
unsigned long GREENtime = 0;
unsigned long REDdelay = 0;
unsigned long debounceTime_RED = 50;
unsigned long debounceTime_YELLOW = 50;

int onRED = LOW;
int onYELLOW = LOW;
int onGREEN = LOW;
int REDcount = LOW;
int GREENcount = LOW;

QueueHandle_t BlinkQueue;

void setup()
{
  Serial.begin(9600);
  BlinkQueue =  xQueueCreate(5, sizeof(int32_t));

  xTaskCreate(vSenderTask, "RED_SENDER TASK", 100, SW1, 1, NULL);
  xTaskCreate(vSenderTask, "YELLOW_SENDER TASK", 100, SW2, 1, NULL);
  xTaskCreate(vSenderTask, "GREEN_SENDER TASK", 100, SW3, 1, NULL);

  xTaskCreate(vReceiverTask, "RED_RECEIVER TASK", 100, RED, 1, NULL);
  xTaskCreate(vReceiverTask, "YELLOW_RECEIVER TASK", 100, YELLOW, 1, NULL);
  xTaskCreate(vReceiverTask, "GREEN_RECEIVER TASK", 100, GREEN, 1, NULL);
}

void vSenderTask(void *pvParameters)
{
  BaseType_t qStatus;
  int32_t valueToSend = 0;
  int SW = (int32_t)pvParameters;
  pinMode(SW, INPUT);
  while (1)
  {
    if (digitalRead(SW))
    {
      valueToSend = SW;
      Serial.println(valueToSend);
      qStatus = xQueueSend(BlinkQueue, &valueToSend, 0);
      vTaskDelay(1);
    }
  }
}


void vReceiverTask(void *pvParameters)
{
  int32_t valueReceived;
  int32_t LED = (int32_t) pvParameters;
  BaseType_t qStatus;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  while (1)
  {
    qStatus = xQueueReceive(BlinkQueue, &valueReceived, xTicksToWait);
    if (qStatus == pdPASS)
    {
      if (valueReceived == SW1 && LED == RED)
      {
        onRED = HIGH;
        REDdelay += 3000;
        REDcount++;
        REDtime = millis();
        digitalWrite(RED, HIGH);
        Serial.println(REDdelay / 1000);
      }
      if (valueReceived == SW2 && LED == YELLOW && millis() - debounceTime_YELLOW >= 500)
      {
        debounceTime_YELLOW = millis();
        onYELLOW++;
        onYELLOW %= 2;
      }
      if (valueReceived ==  SW3  && LED == GREEN && !onGREEN)
      {
        onGREEN = HIGH;
        GREENcount = 0;
      }
    }
    if (millis() - REDtime >= REDdelay && onRED)
    {
      onRED = LOW;
      REDdelay = 0;
      digitalWrite(RED, LOW);
    }

    if (onYELLOW)
    {
      if (millis() -  YELLOWtime >= 500)
      {
        digitalWrite(YELLOW, !digitalRead(YELLOW));
        YELLOWtime = millis();
      }
    }
    else
    {
      digitalWrite(YELLOW, LOW);
    }
    if (onGREEN)
    {
      if (millis() - GREENtime >= 500)
      {
        digitalWrite(GREEN, !digitalRead(GREEN));
        GREENcount++;
        GREENtime = millis();
      }
      if (GREENcount >= 6)
      {
        digitalWrite(GREEN, LOW);
        onGREEN = LOW;
        GREENcount = 0;
      }
    }
    vTaskDelay(10);
  }
}

void loop() { }
