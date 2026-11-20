#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int BOUTON = 2;
const int BUZZER = 8;
bool enLair = false;            // le perso est-il en l'air ? (vrai ou faux)
unsigned long debutSaut = 0;    // à quel moment il a sauté (en ms)
int posCactus = 15;
unsigned long dernierPas = 0;
unsigned long start = 0;
int speed = 300;
int count = 0;

byte ground[8] = { 0x0E, 0x0E, 0x04, 0x1F, 0x15, 0x0E, 0x0A, 0x0A };

byte jump[8] = { 0x0E, 0x0E, 0x15, 0x1F, 0x04, 0x0E, 0x0A, 0x00 };

byte cactus[8] = { 0x00, 0x04, 0x04, 0x15, 0x17, 0x1C, 0x04, 0x04 };

/*byte rock[8] = { 0x00, 0x00, 0x00, 0x00, 0x0E, 0x1F, 0x1F, 0x1F };*/

/*byte opened[8] = {
  0b00000, 0b00000, 0b01010, 0b00000,
  0b01110, 0b01010, 0b01110, 0b00000
};*/

void  setup() {
  lcd.init();
  lcd.backlight();
  pinMode(BOUTON, INPUT_PULLUP); 
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, HIGH);
  lcd.createChar(0, ground);
  lcd.createChar(1, jump);
  lcd.createChar(2, cactus);
  /*lcd.createChar(3, rock);*/
  /*lcd.createChar(2, opened);*/

  lcd.setCursor(1, 1);
  lcd.write(byte(0));
  lcd.setCursor(15, 1);
  lcd.write(byte(2));
  start = millis();
  /*Serial.begin(9600);*/
}

void  loop() {
  /*Serial.println(digitalRead(BOUTON));*/
  if (digitalRead(BOUTON) == LOW && !enLair) {
    debutSaut = millis();   // on note l'heure du saut
    enLair = true;          // on retient qu'il est en l'air
    lcd.setCursor(1, 1);
    lcd.print(" ");
    lcd.setCursor(1, 0);
    lcd.write((byte(1)));
  }
  else if (enLair == true && millis() - debutSaut >= 700) {
    enLair = false;
    lcd.setCursor(1, 0);
    lcd.print(" ");
    lcd.setCursor(1, 1);
    lcd.write((byte(0)));
  }
  if (millis() - dernierPas >= speed) {
    dernierPas = millis();
    lcd.setCursor(posCactus, 1);
    lcd.print(" ");
    posCactus--;
    
    if (posCactus < 0){
    posCactus = 15;
    count++;

    if (count == 30) {
      speed -= 20;
      count = 0;
    }
    }
    lcd.setCursor(posCactus, 1);   // ← dessiné à CHAQUE pas
    lcd.write(byte(2));

    lcd.setCursor(12, 0);
    lcd.print((millis() - start) / 1000);
    lcd.print("s");
  }

  if (posCactus == 1 && !enLair) {
    lcd.clear();
    digitalWrite(BUZZER, LOW);
    delay(400);
    digitalWrite(BUZZER, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("GAME OVER");
    lcd.setCursor(10, 0);
    lcd.print((millis() - start) / 1000);
    lcd.print("s");
    lcd.setCursor(1, 1);
    lcd.print("Appuie 2 fois");
    
    while (digitalRead(BOUTON) == HIGH){}
    delay(50);
    while (digitalRead(BOUTON) == LOW){}
    delay(50);
    while (digitalRead(BOUTON) == HIGH){}
    delay(50);
    while (digitalRead(BOUTON) == LOW) {}
    delay(50);
    posCactus = 15;
    lcd.clear();
    setup();
  }
}