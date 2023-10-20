int segmentPins[7] = {12, 11, 19, 20, 21, 10, 22};
int digitPins[6] = {16, 17, 18, 15, 14, 13};

int numbers[][10] = {
  {0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 1, 1, 1, 1},
  {0, 0, 1, 0, 0, 1, 0},
  {0, 0, 0, 0, 1, 1, 0},
  {1, 0, 0, 1, 1, 0, 0},
  {0, 1, 0, 0, 1, 0, 0},
  {0, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0}
  };



int inputPin = 1;  // Pin donde se recibe la señal
unsigned long startTime;
unsigned long startTimeDisp;
unsigned long endTime;
int risingEdgeCount = 0;
int inputState;
int displayOn = -1;
int frequencyVector[6] = {0, 0, 0, 0, 0, 0};  // Vector de 6 enteros para almacenar la frecuencia


void setup() {
  Serial.begin(9600);
  pinMode(inputPin, INPUT);
  
  //Set mode as output for 7 segments
  for(int i=0; i<7; i++)
    pinMode(segmentPins[i], OUTPUT);
  //Set mode as output for 4 digits
  for(int i=0; i<6; i++)
    pinMode(digitPins[i], OUTPUT);

  startTime = millis();
  inputState = digitalRead(inputPin);

}

void loop() {

  if(inputState!=digitalRead(inputPin)){
      if(inputState == HIGH){
          risingEdgeCount++;
      }
      inputState=digitalRead(inputPin);
  }

  
  if(millis() - startTimeDisp >= 1){
    
      digitalWrite(digitPins[displayOn++], LOW);
      displayOn = displayOn%6;
      DisplayNumber(numbers[frequencyVector[displayOn]]);
      digitalWrite(digitPins[displayOn], HIGH);
      
      startTimeDisp = millis();
  }

  if (millis() - startTime >= 1000) {
      // 1 segundo ha transcurrido, muestra el conteo y reinicia
      // Serial.print("Flancos de subida en 1 segundo: ");
      // Serial.println(risingEdgeCount);
      updateFrequencyVector(risingEdgeCount);
      // printFrequencyVector();
      risingEdgeCount = 0;
      startTime = millis();
  }
  
  int num_to_display[6] = {9, 6, 5, 2, 3, 7};
  
  
}


void DisplayAll(int num_to_display[]){
  //Loop through digitPins, turn on only one at a time
  for(int i=1; i<=6; i++)
  {
    DisplayNumber(numbers[num_to_display[i-1]]);
    TurnOnDigitPin(i-1);
    
    delay(5);
  }
}

void TurnOnDigitPin(int digitPin){
  //Loop through digitPins, turn on only one at a time
  for(int i=0; i<6; i++){
    if(i == digitPin)
      digitalWrite(digitPins[i], HIGH);
    else
      digitalWrite(digitPins[i], LOW);
  }
}


void DisplayNumber(int pattern[]){
    for(int i=0; i<7; i++)
      digitalWrite(segmentPins[i], pattern[i]);
}

void updateFrequencyVector(int frequency) {
  // Actualiza el vector de frecuencia con los dígitos de 'frequency'
  for (int i = 5; i >= 0; i--) {
    frequencyVector[i] = frequency % 10;
    frequency /= 10;
  }
}

void printFrequencyVector() {
  Serial.print("Frecuencia: ");
  for (int i = 0; i < 6; i++) {
    Serial.print(frequencyVector[i]);
  }
  Serial.println(" Hz");
}
