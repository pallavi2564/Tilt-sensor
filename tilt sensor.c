#include <MPU6050_light.h>  //Include library for MPU communication
#include <LiquidCrystal_I2C.h>  //Library for LCD Display
#include <Wire.h>
MPU6050 mpu(Wire);//Create object mpu
#define I2C_ADDR    0x27
#define LCD_COLUMNS 16
#define LCD_LINES   2

LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);

unsigned long timer = 0;    

void setup() {

  Serial.begin(9600);    //Start serial communication

  lcd.init();     //Start LCD Display
  lcd.backlight();  
  lcd.setCursor(0,0);  
  lcd.print("Hi");

  Wire.begin();    
  mpu.begin();    
  Serial.print(F("MPU6050 status: "));
  Serial.println(F("Calculating offsets, do not move MPU6050"));  
  delay(1000);
  mpu.calcGyroOffsets();     //Calibrate gyroscope
  Serial.println("Done!\n");
}
  
void loop() {
  mpu.update();    //Get values from MPU
 
  if ((millis() - timer) > 100) { // print data every 100ms
    timer = millis();
   
    lcd.clear();
    lcd.print("Lz");
    lcd.print(", Lx, ");
    lcd.print("Ly");
    int x = mpu.getAngleX();
    int z = mpu.getAngleZ();
    if(z>360){
      z = z%360;
    }
    if(x>360){
      x = x%360;
    }
    int y = mpu.getAngleY();
    if(y>360){
      y = y%360;
    }
    lcd.setCursor(0,1);
    lcd.print(int(z));
    lcd.setCursor(4,1);
    lcd.print(int(x));
    lcd.setCursor(8,1);
    lcd.print(int(y));
         //Print Z angle value on LCD
    delay(10);
  }
}
