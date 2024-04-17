int sensorPin = A0; // choose the input pin (for GAS sensor)
int flamePin = 2;
int buzzer = 13;    // choose the pin for the Buzzer
int G_led = 8;      // choose the pin for the Green LED
int R_led = 9;      // choose the pin for the Red LED

int read_value;
int flameValue;
int set = 20; // Set threshold value for gas detection
const int flameThreshold = HIGH;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(R_led, OUTPUT);
  pinMode(G_led, OUTPUT);
}

void loop() {
  read_value = analogRead(sensorPin);
  flameValue = digitalRead(flamePin);
  digitalWrite(G_led, HIGH);  // Turn on green LED

  if (read_value >= set) {
        digitalWrite(G_led, LOW);  // Turn off green LED
    digitalWrite(buzzer, HIGH); // Turn on buzzer
    digitalWrite(R_led, HIGH);  // Turn on red LED
    delay(500);                  // Delay for 500 milliseconds
    digitalWrite(R_led, LOW);   // Turn off red LED
    delay(600);                  // Delay for 500 milliseconds
    digitalWrite(buzzer, LOW);  // Turn off buzzer
    Serial.println("Gas Detected");
    Serial.print("Gas Value: "); // Send gas value
    Serial.println(read_value);  // Send gas value over serial port
    delay(1000);  // Wait before sending another message
  } 
  else if(flameValue == flameThreshold){
    digitalWrite(G_led, LOW); 
    digitalWrite(buzzer, HIGH); // Turn on buzzer
    digitalWrite(R_led, HIGH); // Turn on red LED
    delay(500); 
    digitalWrite(R_led, LOW);   // Turn off red LED
    delay(600);                  // Delay for 500 milliseconds  
    digitalWrite(buzzer, LOW);  // Turn off buzzer
    Serial.println("Flame Detected");
    delay(1000);
    
    delay(500);                    // Delay for 500 milliseconds
    
    digitalWrite(R_led, LOW);  // Turn off red LED
    digitalWrite(buzzer, LOW);  // Turn off buzzer
    
    delay(600);                    // Delay for 500 milliseconds
  }
  else {
    digitalWrite(R_led, LOW);   // Turn off red LED
  }

  delay(100); // Add a short delay before next reading
}
