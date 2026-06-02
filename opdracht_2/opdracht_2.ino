const int allUsedPins[] = {13, 12, 11, 10, 9, 8, 7, 6}; // Alle gebruikte pinnen.

void setup(){
  
  // Alle pins worden ingesteld op output. 
  for (int i = 0; i < 8; i++) {
  	pinMode(i, OUTPUT);
  }
  
}

void loop(){
  
  // Hier gaat het licht van de LED lampjes van links naar rechts.
  for (int i = 0; i < 8; i++) {
    switchLed(allUsedPins[i]);
  }
  
  // Hier gaat het licht van de LED lampjes van recht naar links.
  for (int i = 6; i >= 0; i--) {
    switchLed(allUsedPins[i]);
  }
  
}

// Functie voor het LED lampje aan of uit te kunnen zetten.
void switchLed(int position) {
  
  digitalWrite(position, HIGH);
  delay(100);
  digitalWrite(position, LOW);
  
}