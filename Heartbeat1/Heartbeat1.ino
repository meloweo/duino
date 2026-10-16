#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

byte petit[8] = {
  0b00000, 0b00000, 0b11011, 0b11111,
  0b01110, 0b00100, 0b00000, 0b00000
};

byte grand[8] = {
  0b00000, 0b01010, 0b11111, 0b11111,
  0b11111, 0b01110, 0b00100, 0b00000
};

void  setup() {
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, petit);
  lcd.createChar(1, grand);
}

void  loop() {
  for (int pos = 0; pos < 16; pos++) {
    if (pos > 0) {
      lcd.setCursor(pos - 1, 0);
      lcd.print(" ");
    }
    lcd.setCursor(pos, 0);
    lcd.write(byte(pos % 2));
    delay(300);
  }
  for (int pos = 15; pos >= 0; pos--) {
    if(pos < 15) {
      lcd.setCursor(pos + 1, 0);
      lcd.print(" ");
    }
    lcd.setCursor(pos, 0);
    lcd.write(byte(pos % 2));
    delay(300);
    }
  }