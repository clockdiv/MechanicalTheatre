const uint8_t pin_dir = 4;
const uint8_t pin_dir_rev = 5;
const uint8_t pin_step = 6;
const uint8_t pin_poti = A0;
uint16_t v = 0;

void makeStep() {
  v = analogRead(pin_poti) + 1;
  digitalWrite(pin_step, HIGH);
  delayMicroseconds(v);
  digitalWrite(pin_step, LOW);
  delayMicroseconds(v);
}


void setup() {
  pinMode(pin_dir, OUTPUT);
  pinMode(pin_dir_rev, OUTPUT);
  pinMode(pin_step, OUTPUT);
  digitalWrite(pin_dir, HIGH);
  digitalWrite(pin_dir_rev, LOW);

  for(int i = 0; i < 800; i++) {
    makeStep();
  }
  delay(1000);
}

void loop() {
  makeStep();
}
