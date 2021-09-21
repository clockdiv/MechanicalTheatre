#include <EEPROM.h>

#define EEPROM_SIZE 64

uint32_t showCounterManualStart = 0;
uint32_t showCounterCoinslotStart = 0;
uint32_t showCounterTelephoneStart = 0;


/* ------------------------------------ */
void readEEPROM()
{
  if (!EEPROM.begin(EEPROM_SIZE))
  {
    Serial.println("failed to initialise EEPROM");
    return;
  }

  showCounterManualStart = EEPROM.readUInt(0);
  showCounterCoinslotStart = EEPROM.readUInt(4);
  showCounterTelephoneStart = EEPROM.readUInt(8);

  EEPROM.end();
}

/* ------------------------------------ */
void writeEEPROM()
{
  if (!EEPROM.begin(EEPROM_SIZE))
  {
    Serial.println("failed to initialise EEPROM");
    return;
  }

  EEPROM.writeInt(0, showCounterManualStart);
  EEPROM.writeUInt(4, showCounterCoinslotStart);
  EEPROM.writeUInt(8, showCounterTelephoneStart);

  EEPROM.end();
}

void setup() {
  readEEPROM();
  Serial.print("times started from manual start (or show-repeat): ");
  Serial.println(showCounterManualStart);
  Serial.print("times started from coinslot: ");
  Serial.println(showCounterCoinslotStart);
  Serial.print("times started from telephone: ");
  Serial.println(showCounterTelephoneStart);

  showCounterManualStart = 0;
  showCounterCoinslotStart = 0;
  showCounterTelephoneStart = 0;
  writeEEPROM();
  delay(1000);
}

void loop() {
  readEEPROM();
  Serial.print("times started from manual start (or show-repeat): ");
  Serial.println(showCounterManualStart);
  Serial.print("times started from coinslot: ");
  Serial.println(showCounterCoinslotStart);
  Serial.print("times started from telephone: ");
  Serial.println(showCounterTelephoneStart);
  delay(1000);

  showCounterManualStart += 10000;
  showCounterCoinslotStart += 20000;
  showCounterTelephoneStart += 30000;
  writeEEPROM();
  delay(1000);
}
