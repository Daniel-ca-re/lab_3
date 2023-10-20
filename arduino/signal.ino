unsigned int freq = 5000;
int sqwPin = 13;
void setup() {
  Serial.begin(9600);
}
void loop() {

  tone(sqwPin, freq);

}
