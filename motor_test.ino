void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11,OUTPUT);

  pinMode(46, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);

}

void loop() {
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(11, HIGH);
  
  digitalWrite(46, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(9, HIGH);

}
