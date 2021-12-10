#define L1_En A0
#define L2_En A1
#define L3_En A2
#define L4_En A3
#define L5_En A4
#define L6_En A5
#define L7_En 5
#define L8_En 4
#define L9_En 9

const int LEDS [8] = {L1_En, L2_En, L3_En, L4_En, L5_En, L6_En, L7_En, L8_En};

void timer1_init() {
  cli();
  TCCR1A = 0;
  TCCR1B = 0;

  TIMSK1 |= (1 << TOIE1);
  TCCR1B |= (1 << CS11);
  TCCR1B |= (1 << CS10);

  sei();
}

void test_all_led(int *leds, size_t sizee){
  for(int i=0 ; i<sizee ; ++i){
    digitalWrite(leds[i], HIGH);
    delay(1000);
  }
}

void onOffLeds(int *pins, int sizee, int delayToOff, int delayToOn) {
  for (int i = 0; i < sizee ; ++i) {
    digitalWrite(pins[i], HIGH);
  }
  delay(delayToOff);
  for (int i = sizee ; i >= 0 ; --i) {
    digitalWrite(pins[i], LOW);
  }
  delay(delayToOn);
}

void randomMode(int minLedSize, int maxLedSize, int totalLedCount, int onToOffDelayMin = 250, 
                int onToOffDelayMax = 350, int offToOnDelayMax = 25, int offToOnDelayMin = 50) {
  int *to_sendLed;
  static int ledSize = random(minLedSize, maxLedSize+1);
  to_sendLed = (int*)malloc(ledSize * sizeof(int));
  for (int i = 0 ; i < ledSize ; ++i) {
    to_sendLed[i] = LEDS[random(totalLedCount)];
  }
  onOffLeds(to_sendLed, ledSize, random(onToOffDelayMin, onToOffDelayMax), random(offToOnDelayMax, offToOnDelayMin));
  free(to_sendLed);
}

void setup() {
  pinMode(L1_En, OUTPUT);
  pinMode(L2_En, OUTPUT);
  pinMode(L3_En, OUTPUT);
  pinMode(L4_En, OUTPUT);
  pinMode(L5_En, OUTPUT);
  pinMode(L6_En, OUTPUT);
  pinMode(L7_En, OUTPUT);
  pinMode(L8_En, OUTPUT);
  pinMode(L9_En, OUTPUT);

  timer1_init();
}

void loop() {
  randomMode(3, 8, 8);

/*
  for(int i=0 ; i<255 ; ++i){
    analogWrite(L7_En, i);
    delay(10);
  }

   for(int i=255 ; i>0 ; --i){
    analogWrite(L7_En, i);
    delay(10);
  }
  */
}

ISR(TIMER1_OVF_vect) {
  digitalWrite(L9_En, !digitalRead(L9_En));
}
