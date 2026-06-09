#include <LiquidCrystal.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// I2C lcd adres: 0x27, 16 kollomen, 2 rijen.
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int button1 = 3; // Knop voor hets starten en voor laps.
const int button2 = 2; // Knop voor pauze.

// Tijd variabelen in milliseconden.
unsigned long startTime = 0;
unsigned long pauseTime = 0;
unsigned long lapTime = 0;

// Status variabelen om te bekijken of die is gerunned of gepauzeerd.
bool running = false;
bool paused = false;

int button1Status = LOW; // Standaard stand van knop 1.
unsigned long button1Pressed = 0; // Het tijdstip waarop de knop 1 is ingedrukt.
bool button1LongPressed = false; // Checkt of de knop lang is ingedrukt.

int button2Status = LOW; // Standaard stand van knop 2.

void setup(){
  
  // De knoppen instellen.
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  
  // Dit is het bericht die je te zien krijgt wanneer je de stopwatch opstart.
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Stopwatch Klaar");
  delay(1500);
  lcd.clear();
}

void loop() {
  
  // Leest huidige toestand vna de knoppen.
  int currentButtonStatus1 = digitalRead(button1);
  int currentButtonStatus2 = digitalRead(button2);
  
  // Checkt of beide knoppen tegelijk zijn ingedrukt.
  if (currentButtonStatus1 == HIGH && currentButtonStatus2 == HIGH) {
    resetStopwatch();
    delay(500); // Zodat er niet meerdere resets achter elkaar wordt uigevoerd.
    return;
  }
  
  // Dit is wat de knop 1 moet doen, dus start of start de lap.
  if (currentButtonStatus1 == HIGH && button1Status == LOW) {
    button1Pressed = millis();
    button1LongPressed = false;
  }
  
  // Checkt of knop 1 langer dan 2 seconden is ingedrukt, hiermee sla je een lap op.
  if (currentButtonStatus1 == HIGH && !button1LongPressed) {
    if (millis() - button1Pressed >= 2000) {
      if (running) {
        lapTime = getElapsedTime();
        button1LongPressed = true;
      }
    }
  }
  
  // Checkt of knop 1 niet meer is ingedrukt, dus hervat de stopwatch.
  if (currentButtonStatus1 == LOW && button1Status == HIGH && !button1LongPressed) {
    if (!running && !paused) {

      // Stopwatch voor het eerst starten
      startTime = millis();
      running = true;
      paused = false;
    } else if (paused) {

      // Start stopwatch weer nadat die was gepauzeerd.
      startTime = millis();
      running = true;
      paused = false;
    }
  }
  
  // Checkt of knop 2 net is ingedrukt zodat die pauzeert.
  if (currentButtonStatus2 == HIGH && button2Status == LOW) {
    if (running) {
      pauseTime = getElapsedTime(); // Slaat het verstreken tijd op.
      running = false;
      paused = true;
    }
  }
  
  // Berekent verstreken tijd en laat het weergeven op de stopwatch.
  unsigned long elapsedTime = getElapsedTime();
  updateDisplayScreen(elapsedTime, lapTime);
  
  // SLaat de status van de knoppen op voor de volgende keer.
  button1Status = currentButtonStatus1;
  button2Status = currentButtonStatus2;
}

// Hierbij krijg je de verstreken tijd terug in milliseconden.
unsigned long getElapsedTime() {
  if (running) {
    return (millis() - startTime) + pauseTime; // Huidige tijd min starttjd, plus verstreken tijd van pauze als die er is.
  } else {
    return pauseTime; // Gepauzeert of gestopt, geef dus opgeslagen tijd terug.
  }
}

// Toont de huidige tijd en de laptijd op het schermpje.
void updateDisplayScreen(unsigned long elapsedTime, unsigned long lap) {
  int minutes, seconds, hundredths;
  
  // Huidige verstreken tijd.
  formatTime(elapsedTime, minutes, seconds, hundredths);
  lcd.setCursor(0, 0);
  lcd.print("Tijd: ");
  
  if (minutes < 10) lcd.print("0");
  lcd.print(minutes);
  lcd.print(":");
  
  if (seconds < 10) lcd.print("0");
  lcd.print(seconds);
  lcd.print(".");
  
  if (hundredths < 10) lcd.print("0");
  lcd.print(hundredths);
  lcd.print("   ");
  
  // Wordt alleen getoond wanneer er een lap is.
  lcd.setCursor(0, 1);
  if (lap > 0) {
    formatTime(lap, minutes, seconds, hundredths);
    lcd.print("Lap:  ");
    
    if (minutes < 10) lcd.print("0");
    lcd.print(minutes);
    lcd.print(":");
    
    if (seconds < 10) lcd.print("0");
    lcd.print(seconds);
    lcd.print(".");
    
    if (hundredths < 10) lcd.print("0");
    lcd.print(hundredths);
  } else {
    lcd.print("Lap: --:--.--");
  }
}

// Zet millisecondes om naar seconds, minuten en honderdsten.
void formatTime(unsigned long ms, int &minutes, int &seconds, int &hundredths) {
  hundredths = (ms / 10) % 100;
  seconds = (ms / 1000) % 60;
  minutes = (ms / 60000);
}

// Reset alles terug naar de beginstand.
void resetStopwatch() {
  running = false;
  paused = false;
  
  startTime = 0;
  pauseTime = 0;
  lapTime = 0;
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Reset");
  delay(800);
  lcd.clear();
  updateDisplayScreen(0, 0);
}