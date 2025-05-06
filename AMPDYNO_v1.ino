
/*

 * Wattmeter for Solar PV using Arduino

 * Dated: 27-7-2018

 * Website: www.circuitdigest.com

 * 

 * Power LCD and circuitry from the +5V pin of Arduino whcih is powered via 7805

 * LCD RS -> pin 2

 * LCD EN -> pin 3

 * LCD D4 -> pin 8

 * LCD D5 -> pin 9

 * LCD D6 -> pin 10

 * LCD D7 -> pin 11

 * Potetnital divider to measure voltage -> A3

 * Op-Amp output to measure current -> A4

 */



#include <LiquidCrystal.h>  //Default Arduino LCD Librarey is included 


int Read_Voltage  = A3;

int Read_Current  = A4;

const int rs = 3, en = 4, d4 = 8, d5 = 9, d6 = 10, d7 = 11; //Mention the pin number for LCD connection

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);


void setup() {

  lcd.begin(16, 2); //Initialise 16*2 LCD

  lcd.print("MATT'S AMP DYNO"); //Intro Message line 1

  lcd.setCursor(0, 1);

  lcd.print("      V1  "); //Intro Message line 2

  delay(2000);

  lcd.clear();



}


void loop() {

 

 float Voltage_Value = analogRead(Read_Voltage);

 float Current_Value = analogRead(Read_Current);


 Voltage_Value = Voltage_Value * (5.0/1023.0) * 6.46;

 Current_Value = Current_Value * (5.0/1023.0) * 0.239;


 lcd.setCursor(0, 0);

 lcd.print("V="); lcd.print(Voltage_Value); 

 lcd.print("  "); 

 lcd.print("I=");lcd.print(Current_Value); 


 float Power_Value = Voltage_Value * Current_Value;


 lcd.setCursor(0, 1);

 lcd.print("Power="); lcd.print(Power_Value); 
 

delay(200);


    

}




