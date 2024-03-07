
#define LED 13

volatile char serialInput;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever

void loop() {
  int letters[26][4] = {
    {0, 1, 0, 0}, {1, 0, 0, 0}, {1,0,1,0}, {1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 1, 0},
    {1, 1, 0, 0},  {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 1, 1, 1}, {1, 0, 1, 0}, {0, 1, 0, 0},
    {1, 1, 0, 0}, {1, 0, 0, 0}, {1, 1, 1, 0}, {0, 1, 1, 0}, {1, 1, 0, 1}, {0, 1, 0, 0}, 
    {0, 0, 0, 0}, {1, 0, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}, {0, 1, 1, 0}, {1, 0, 0, 1},
    {1, 0, 1, 1}, {1, 1, 0, 0}
  };

  int letter_sizes[26] = {
    2, 4, 4, 3, 1, 4, 3, 4, 2, 4, 3, 4, 2, 2, 3, 4, 4, 3, 3, 1, 3, 4, 3, 4, 4, 4
  };
  int letter_indexes[] = {18, 14, 18};
  // while(Serial.available()) {
  //   serialInput = Serial.read();
  //   int letter = serialInput - 'a'
  // }
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < letter_sizes[letter_indexes[i]]; j++) {
      if(letters[letter_indexes[i]][j] == 0)
        blinkShort();
      else
        blinkLong();
    }
    delay(1500);
  }
}

void blinkLong() {
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
  delay(300);
}

void blinkShort() {
  digitalWrite(LED, HIGH);
  delay(300);
  digitalWrite(LED, LOW);
  delay(300);
}
