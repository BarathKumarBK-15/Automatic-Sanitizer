// Pins used for relay module, LEDs and ultrasonic sensor
const int RELAY_PIN = A5;
const int LED_PIN = 8;
const int READY_PIN = 9;
int distance = 0;
int cont = 0;

// Function to measure the time taken to recieve the echo 
// after a sound is triggered
long readUSD(int trigger_pin, int echo_pin) {
  
  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigger_pin, LOW);
  
  return pulseIn(echo_pin, HIGH);
}

// Setting up the Arduino pins as Input/Output
void setup() {
  pinMode(A0, OUTPUT);
  pinMode(A1, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(READY_PIN, OUTPUT);
  digitalWrite(LED_PIN,LOW);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  // Computing the distance of the object using the time
  // taken to recieve the echo
  distance = readUSD(A0, A1)/58.2;
  Serial.println(distance);

  // If the hand is in a decent distance
  // allow the pump to run
  if(distance <= 10 && cont == 0) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(RELAY_PIN,LOW);
    digitalWrite(READY_PIN, LOW);
    cont = 1;

    // time for which the pump pumps the sanitizer
    delay(250);

    // Stopping the motor by blocking the circuit using the relay module
    digitalWrite(LED_PIN, LOW);
    digitalWrite(RELAY_PIN,HIGH);

    // allow the users to use the sanitizer only after 2s of previous use
    delay(2000);
    
    digitalWrite(READY_PIN, HIGH);
    
  } else if(distance > 10) { // Allow the users to use the system again 
                             //after moving out of the range
    cont = 0;
    
    digitalWrite(LED_PIN, LOW);
    digitalWrite(RELAY_PIN,HIGH);
    digitalWrite(READY_PIN, HIGH);
  }
}
