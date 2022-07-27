#include "TM1651.h"
#define PIN_COINSENSOR_IN 2
#define PIN_TRIGGER_OUT 3
#define PIN_LED 4
#define PIN_DATA 5
#define PIN_CLK 6

volatile uint8_t impulsCount;
uint8_t impulsCountOld;
volatile unsigned long millisCounter;
unsigned long coinTimeout, currentMillis;
int totalAmount;
volatile bool ledStat = HIGH;
bool ledStatOld = ledStat;

TM1651 Display(PIN_CLK, PIN_DATA);
//float coinValues[] = {2.0, 1.0, 0.5, 0.2, 0.1};
int coinValues[] = {200, 100, 50, 20, 10};
int bars[] = {19, 20, 21, 20, 19};

enum states {IDLE, COUNTING_PULSES, FINISHED_COUNTING_PULSES, START_SHOW};
states currentState = IDLE;

void setup() {


  Serial.begin(115200);
  pinMode(PIN_COINSENSOR_IN, INPUT_PULLUP);
  pinMode(PIN_TRIGGER_OUT, OUTPUT);
  pinMode(PIN_LED, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(PIN_COINSENSOR_IN), incomingImpuls, FALLING);


  digitalWrite(PIN_TRIGGER_OUT, LOW);
  digitalWrite(PIN_LED, LOW);

  Display.displaySet(7); //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;

  //displayTotalAmount(888);
  //delay(1000);
  //displayStartAnimation();

  displayTotalAmount(0);
  impulsCount = 0;
  impulsCountOld = 0;
  digitalWrite(PIN_LED, ledStat);


  coinTimeout = millis();
  totalAmount = 0;
}


void incomingImpuls()
{
  coinTimeout = currentMillis;
  impulsCount++;
  ledStat = LOW;
}

void displayTotalAmount(int amount)
{
  if (amount <= 9)
  {
    Display.displayNum(0, 16);
    Display.displayNum(1, 16);
    Display.displayNum(2, amount % 10);
  }
  else if (amount <= 99)
  {
    Display.displayNum(0, 16);
    Display.displayNum(1, int(amount / 10));
    Display.displayNum(2, amount % 10);
  }
  else if (amount <= 999)
  {
    Display.displayInteger(amount);
  }
  else {
    displayTotalAmount(amount - 1000);
  }
}

void displayStartAnimation() {
  for (int i = 0; i < 20; i++) {
    Display.displayNum(0, bars[i % 5]);
    Display.displayNum(1, bars[(i + 1) % 5]);
    Display.displayNum(2, bars[(i + 2) % 5]);
    delay(150);
  }
  displayTotalAmount(0);
}


void loop() {
  currentMillis = millis();

  switch (currentState) {
    case IDLE:
      if (impulsCount > 0) {
        currentState = COUNTING_PULSES;
      }
      break;

    case COUNTING_PULSES: // counting the pulses from the coin-slot-machine
      Serial.println(impulsCount);
      if (currentMillis - coinTimeout > 200) {
        currentState = FINISHED_COUNTING_PULSES;
      }
      break;

    case FINISHED_COUNTING_PULSES:
      int coinValueInCent = impulsCount * 10;
      totalAmount += coinValueInCent;
      displayTotalAmount(totalAmount);

      impulsCount = 0;
      ledStat = HIGH;

      Serial.print("finished counting pulses. Total Amount: ");
      Serial.println(totalAmount);
      if (totalAmount >= 200) {
        Serial.println("Start Show");
        totalAmount = 0;
        detachInterrupt(digitalPinToInterrupt(PIN_COINSENSOR_IN));
        digitalWrite(PIN_TRIGGER_OUT, HIGH);
        delay(20);
        digitalWrite(PIN_TRIGGER_OUT, LOW);
        displayStartAnimation();
        attachInterrupt(digitalPinToInterrupt(PIN_COINSENSOR_IN), incomingImpuls, FALLING);
        delay(100);
      }
      currentState = IDLE;
      break;

  }

  if (ledStat != ledStatOld)
  {
    digitalWrite(PIN_LED, ledStat);
    ledStatOld = ledStat;
  }
  
  delay(20);
}
