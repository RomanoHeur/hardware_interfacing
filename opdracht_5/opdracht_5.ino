#include <Servo.h>

const int button1 = 12;
const int button2 = 9;
const int servoPin = 8;

Servo servo; // Servo object aanmaken.

void setup() {
  Serial.begin(9600);

  // Pinmodes van de knop worden ingesteld.
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  
  // Start de servo bij 0 graden en koppelt de servo aan de juiste pin.
  servo.write(0);
  servo.attach(servoPin);
}

void loop() {
  
  int pressedButton1 = digitalRead(button1);
  int pressedButton2 = digitalRead(button2);
  
  // Berekend door aantal seconden in miliseconden / 120. 
  if (pressedButton1 == HIGH && pressedButton2 == HIGH) { // Beide knoppen ingedrukt.
    moveServo(41, 2000, 4); // Heenweg duurt ongeveer (5sec, 41ms), wacht (2sec, 2000ms) en dan (0,5sec, 4ms) terug.
  }
  
  else if (pressedButton1 == HIGH) { // Alleen knop 1 gedrukt.
    moveServo(41, 0, 41); // Heenweg duur (5sec, 41ms), terugweg duurt ook (5sec, 41ms)
  }
  
  else if (pressedButton2 == HIGH) { // Alleen knop 2 gedrukt
    moveServo(4, 0, 4); // Heenweg duurt (0,5sec, 4ms), terugweg duurt ook (0,5sec, 4ms)
  }
}

void moveServo(int servoMoveDelayForward, int servoPauseDelay, int servoMoveDelayBack) {

  // Heenweg, van 0 graden naar 120.
  for (int i = 0; i <= 120; i++) {
    servo.write(i);
    delay(servoMoveDelayForward);
  }
  
  // Voor als er een pauze is meegegeven.
  if (servoPauseDelay > 0) {
    delay(servoPauseDelay);
  }
  
  // Terugweg, van 120 graden naar 0.
  for (int i = 120; i >= 0; i--) {
    servo.write(i);
    delay(servoMoveDelayBack);
  }
  
}