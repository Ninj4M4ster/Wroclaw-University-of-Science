#define IN4 2  // lewe przod
#define IN3 3  // lewe tyl
#define IN2 4  // prawe tyl
#define IN1 5  // prawe przod

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
  digitalWrite(IN4, HIGH);
  digitalWrite(IN1, HIGH);
}
