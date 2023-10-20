import machine
import time

# Define los pines GPIO para los segmentos y los displays
# Ajusta estos pines según tu conexión física.
segment_pins = [machine.Pin(12), machine.Pin(11), machine.Pin(19), machine.Pin(20), machine.Pin(21), machine.Pin(10), machine.Pin(22)]
display_pins = [machine.Pin(16), machine.Pin(17), machine.Pin(18), machine.Pin(15), machine.Pin(14), machine.Pin(13)]

# Tabla de segmentos para mostrar números (a, b, c, d, e, f, g)
digit_segments = [
    [0, 0, 0, 0, 0, 0, 1],  # 0
    [1, 0, 0, 1, 1, 1, 1],  # 1
    [0, 0, 1, 0, 0, 1, 0],  # 2
    [0, 0, 0, 0, 1, 1, 0],  # 3
    [1, 0, 0, 1, 1, 0, 0],  # 4
    [0, 1, 0, 0, 1, 0, 0],  # 5
    [0, 1, 0, 0, 0, 0, 0],  # 6
    [0, 0, 0, 1, 1, 1, 1],  # 7
    [0, 0, 0, 0, 0, 0, 0],  # 8
    [0, 0, 0, 0, 1, 0, 0]   # 9
]

def rising_edge_callback(pin):
    global risingEdgeCount
    risingEdgeCount += 1
    
inputPin = machine.Pin(1, mode=machine.Pin.IN, pull=machine.Pin.PULL_UP) # Pin donde se recibe la señal

inputPin.irq(trigger=machine.Pin.IRQ_RISING, handler=rising_edge_callback)

startTime = time.ticks_ms()
startTimeDisp = time.ticks_ms()

risingEdgeCount = 0
inputState = inputPin.value()
displayOn = -1
frequencyVector = [0, 0, 0, 0, 0, 0]

# Configura los pines GPIO como salidas
for segment_pin in segment_pins:
    segment_pin.init(machine.Pin.OUT)
for display_pin in display_pins:
    display_pin.init(machine.Pin.OUT)

def turn_on_digit_pin(digit_pin):
  #Loop through digitPins, turn on only one at a time
  for i in range(6):
    if (i == digit_pin):
      display_pins[i].value(1)
    else:
      display_pins[i].value(0)

def display_number(pattern):
    for i in range(7):
      segment_pins[i].value(pattern[i])

def update_frequency_vector(frequency):
  # Actualiza el vector de frecuencia con los dígitos de 'frequency'
  for i in range(5, -1, -1):
    frequencyVector[i] = frequency % 10 
    frequency = frequency // 10

    
# Bucle principal para multiplexar los displays
while True:
  
    if (time.ticks_ms() - startTimeDisp >= 1):
        
        display_pins[displayOn].value(0)
        displayOn +=  1
        displayOn = displayOn % 6
        display_number(digit_segments[frequencyVector[displayOn]])
        display_pins[displayOn].value(1)
      
        startTimeDisp = time.ticks_ms()
  

    if (time.ticks_ms() - startTime >= 1000):
        
        update_frequency_vector(risingEdgeCount)
        
        risingEdgeCount = 0
        startTime = time.ticks_ms()
  
  
    
  

