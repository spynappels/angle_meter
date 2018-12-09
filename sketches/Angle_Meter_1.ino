#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <MMA7660.h>

#define I2C_ADDR    0x27 // <<----- Add your address here.  Find it from I2C Scanner
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

float angley = 0.00;
LiquidCrystal_I2C	lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

void setup()
{
  lcd.begin (16,2); //  <<----- My LCD was 16x2
  accel.init();
  
// Switch on the backlight
lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
lcd.setBacklight(HIGH);
lcd.home (); // go home

  lcd.print("Angle Meter");  
}

void loop()
{
  accel.getValues();
  if (accel.y > 21)  {
    lcd.setCursor (0,1);        
    lcd.print("                ");
    lcd.setCursor (0,1); 
    lcd.print("Tilt Range Error");
  }
  if (accel.y < 22) {
    if (accel.y == 0) angley = 00.00;
    if (accel.y == 1) angley = 02.69;
    if (accel.y == 2) angley = 05.38;
    if (accel.y == 3) angley = 08.08;
    if (accel.y == 4) angley = 10.81;
    if (accel.y == 5) angley = 13.55;
    if (accel.y == 6) angley = 16.33;
    if (accel.y == 7) angley = 19.16;
    if (accel.y == 8) angley = 22.02;
    if (accel.y == 9) angley = 24.95;
    if (accel.y == 10) angley = 27.95;
    if (accel.y == 11) angley = 31.04;
    if (accel.y == 12) angley = 34.23;
    if (accel.y == 13) angley = 37.54;
    if (accel.y == 14) angley = 41.01;
    if (accel.y == 15) angley = 44.68;
    if (accel.y == 16) angley = 48.59;
    if (accel.y == 17) angley = 52.83;
    if (accel.y == 18) angley = 57.54;
    if (accel.y == 19) angley = 62.95;
    if (accel.y == 20) angley = 69.64;
    if (accel.y == 21) angley = 79.86;
    lcd.setCursor (0,1);        
    lcd.print("                ");
    lcd.setCursor (0,1);   
    lcd.print("Tilt:");lcd.print(angley);lcd.print(" down");
  } 
  delay(500);

}
