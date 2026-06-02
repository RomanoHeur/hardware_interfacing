void setup() {

  // Pinmodes instellen volgens opdracht (10, 13)
  pinMode(10, OUTPUT);
  pinMode(13, OUTPUT);

}

void loop() {

  // Alleen LED op pin 10 gaat aan voor 1,5 sec en LED op pin 13 blijft uit.
  digitalWrite(10, HIGH);
  delay(1500);
  digitalWrite(10, LOW);

  // Alleen LED op pin 13 gaat aan voor 1,5 sec en LED op pin 10 blijft uit.
  digitalWrite(13, HIGH);
  delay(1500);
  digitalWrite(13, LOW);

}
