#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>


#define I2C_ADDR    0x27 // <<----- Add your address here.  Find it from I2C Scanner
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7
LiquidCrystal_I2C	lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

#define ADC_ref 3.3
#define zero_x 1.65
#define zero_y 1.65
#define zero_z 1.65
#define sensitivity_x 0.33
#define sensitivity_y 0.33
#define sensitivity_z 0.33

unsigned int value_x;
unsigned int value_y;
unsigned int value_z;

float xv;
float yv;
float zv;

float angle_x;
float angle_y;
float angle_z;
float disp_angle_x;

String dir;

uint8_t degree[8]  = {140,146,146,140,128,128,128,128};



void setup()
{
  lcd.begin (16,2); 
  analogReference(EXTERNAL);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.createChar(0, degree);
  lcd.home (); 
  lcd.print("Angle Meter");  
}

void loop()
{
  value_x = analogRead(0);
  value_y = analogRead(1);
  value_z = analogRead(2);
  
  xv=(value_x/1024.0*ADC_ref-zero_x)/sensitivity_x;
  yv=(value_y/1024.0*ADC_ref-zero_y)/sensitivity_y;
  zv=(value_z/1024.0*ADC_ref-zero_z)/sensitivity_z;
  
  angle_x =360-(atan2(-yv,-zv)*57.2957795+180);
  angle_y =atan2(-xv,-zv)*57.2957795+180;
  angle_z =atan2(-yv,-xv)*57.2957795+180;

  if (angle_x < 269 && angle_x > 91) {
    lcd.setCursor (0,1);        
    lcd.print("                ");
    lcd.setCursor (0,1);   
    lcd.print("Tilt:Range Error");
  }
  else {
    if (angle_x > 269) {
      disp_angle_x = 360-angle_x;
      dir = "Up";
    }
    if (angle_x < 91) {
      disp_angle_x = angle_x;
      dir = "Down";
    }
    lcd.setCursor (0,1);        
    lcd.print("                ");
    lcd.setCursor (0,1);   
    lcd.print("Tilt:");lcd.print(disp_angle_x);lcd.write(byte(0));lcd.print(dir);
  }
  
  delay(500);

}
