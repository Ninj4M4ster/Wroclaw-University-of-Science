#define IN4 2  // prawe ty;
#define IN3 3  // prawe przod
#define IN2 4  // lewe przod
#define IN1 5  // lewe tyl
#define ENA 10   // prawe zasilanie
#define ENB 9  // lewe zasilanie

void setup() {
  // put your setup code here, to run once:
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // digitalWrite(IN4, HIGH);
  // analogWrite(ENA, 20);
  // digitalWrite(IN4, HIGH);
  analogWrite(ENB, 70);
  digitalWrite(IN3, HIGH);
}
