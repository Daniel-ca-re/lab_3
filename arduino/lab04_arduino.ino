/**
 * @file
 * @brief Funciones relacionadas a la medida de frecuencia y visualización en los displays.
 */

 /**
 * @brief Pines de segmento para los displays de 7 segmentos.
 */
int segmentPins[7] = {12, 11, 19, 20, 21, 10, 22};

/**
 * @brief Pines de dígito para los displays de 7 segmentos.
 */
int digitPins[6] = {16, 17, 18, 15, 14, 13};


/**
 * @brief Patrones de números en segmentos.
 */
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


/**
 * @brief Pin donde se recibe la señal de entrada.
 */
int inputPin = 1;  // Pin donde se recibe la señal

/**
 * @brief Tiempo de inicio de la medición.
 */
unsigned long startTime;

/**
 * @brief Tiempo de inicio de la visualización en los displays.
 */
unsigned long startTimeDisp;


/**
 * @brief Contador de flancos de subida.
 */
int risingEdgeCount = 0;

/**
 * @brief Estado actual del pin de entrada.
 */
int inputState;

/**
 * @brief Índice del display activo (-1 significa desactivado).
 */
int displayOn = -1;

/**
 * @brief Vector de 6 enteros para almacenar la frecuencia.
 * Contiene los dígitos de la frecuencia medida.
 */
int frequencyVector[6] = {0, 0, 0, 0, 0, 0};  // Vector de 6 enteros para almacenar la frecuencia

/**
 * @brief Configuración inicial del programa.
 * Inicializa los pines y variables necesarios.
 */
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

/**
 * @brief Bucle principal del programa.
 * Realiza la medición de frecuencia y visualización en los displays.
 */
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
      updateFrequencyVector(risingEdgeCount);
      risingEdgeCount = 0;
      startTime = millis();
  }
  
}


/**
 * @brief Activa un display de 7 segmentos a la vez.
 * 
 * @param digitPin Índice del display a activar.
 */
void TurnOnDigitPin(int digitPin){
  //Loop through digitPins, turn on only one at a time
  for(int i=0; i<6; i++){
    if(i == digitPin)
      digitalWrite(digitPins[i], HIGH);
    else
      digitalWrite(digitPins[i], LOW);
  }
}

/**
 * @brief Muestra un patrón en los displays de 7 segmentos.
 * 
 * @param pattern Patrón a mostrar en los displays.
 */
void DisplayNumber(int pattern[]){
    for(int i=0; i<7; i++)
      digitalWrite(segmentPins[i], pattern[i]);
}

/**
 * @brief Actualiza el vector de frecuencia con los dígitos de la frecuencia.
 * 
 * @param frequency Frecuencia medida.
 */
void updateFrequencyVector(int frequency) {
  // Actualiza el vector de frecuencia con los dígitos de 'frequency'
  for (int i = 5; i >= 0; i--) {
    frequencyVector[i] = frequency % 10;
    frequency /= 10;
  }
}
