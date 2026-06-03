const int allUsedPins[] = {13, 12, 11, 10, 9, 8}; // Alle gebruikte pinnen.
const int potPin = A0; // Gebruikte pin voor de draai analoge.

void setup() {

  // Stelt alle pinnen in op OUTPUT.
  for (int i = 0; i < 6; i++) {
    pinMode(allUsedPins[i], OUTPUT);
  }

  pinMode(potPin, INPUT); // Stelt de pot pin in als INPUT.
}


void loop() {
  
  int potValue = analogRead(potPin); // Leest de waarde van de analoge.
  
  // Update de lichten via de analoge.
  updateLedLights(potValue);
  delay(50);
}

// Functie die bekijkt hoeveel LEDS er aan of uit gaan.
void updateLedLights(int potValue) {
  
  int getActiveLed = map(potValue, 0, 1023, 7, 0); // Zet de analoge waarde in om aantal LEDS lampjes aan of uit moet.
  
  // Gaat door alle LEDS lampjes heen
  for (int i = 0; i < 6; i++) {
    if (i < getActiveLed) {
      digitalWrite(allUsedPins[i], HIGH); // LED lampje gaan aan.
    } else {
      digitalWrite(allUsedPins[i], LOW); // LEDS lampje gaat uit.
    }
  }
  
}