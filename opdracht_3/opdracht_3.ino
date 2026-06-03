int count = 0; // HOudt bij hoe vaak op de knop is gedrukt. 
int buttonStatus = LOW;

void setup() {
  
  // Stelt alle pinwaarden in.
  pinMode(8, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(12, INPUT);
  
  // Laadt de eerste LED lampje uit zijn en de andere aan.
  digitalWrite(8, LOW);
  digitalWrite(10, HIGH);
}

void loop() {
  
  int currentButtonStatus = digitalRead(12); // Haalt de huidige status op van de knop.
  
  // Checkt of er op de knop is gedrukt.
  if (currentButtonStatus == HIGH && buttonStatus == LOW) {
    count ++; // Telt de waarde op 
    
    // Roept de functie aan en geeft een delay mee voor de contactdender.
    switchButton();
    delay(50);
  }
  
  buttonStatus = currentButtonStatus; // Slaat de huidige status weer op.
}

void switchButton() {
  
  // Als de count even is blijft LED lampje 1 uit en de lampje 2 aan.
  if (count % 2 == 0) {
    digitalWrite(8, LOW);
    digitalWrite(10, HIGH);
  } else {

    // Als de count oneven is gaat LED lampje 2 uit en lampje 1 aan.
    digitalWrite(8, HIGH);
    digitalWrite(10, LOW);
  }

}