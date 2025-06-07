/*
 * Basic Amplifier Dyno 
 * Date: 10-22-2024
 * Version: 1.2
 * Designed by M Greathouse
 * Current Sensor Input -> A2
 * Temperature Sensor Input -> D6
 * Reset button input - D8
 * 4-8ohm Load Bank Switch Input - D12
 */

#include <LiquidCrystal.h>      //Default Arduino LCD Library is included 
#include <LiquidCrystal_I2C.h>  // Library to use I2C displays
#include <DHT.h>                // Define library for temp sensor

// Set the DHT11 parameters
#define DHT22PIN 6            // USE PIN 7 Digital for the DHT11 temp sensor
#define DHTTYPE DHT22           // DHT 22 for actual use
DHT dht(DHT22PIN, DHTTYPE);

// Set the I2C Display parameters
#define I2C_ADDR    0x27
#define LCD_COLUMNS 20
#define LCD_LINES   4

LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);

// Define Input Pins. 
const int ResetPin = 8;          // This is the reset button pin. Using 10k resistor to gnd on the pin 8 side, then the other side of the button to 5v
const int LoadPin = 12;          // This is the digital button input for 4-8 ohm switching
const float Read_Current =A2;     // Analog Pin 2 input for the current reading

float ampRms=0;
float watt=0;
float resistance=0;

int resetValue1 = LOW;      // Defines the base reset value. Once the pin goes high, that will trigger the reset
float Max_Value;            // Define the Peak value outside of the loop so the state can be reset

void setup() 
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();                // Turn on the backlight
  lcd.setCursor(2, 1);
    lcd.print(" MATTS AMP DYNO"); // Intro Message line 1
  lcd.setCursor(2, 2);
    lcd.print("      V1.2  ");    // Intro Message line 2

  delay(3000);                    // Set the intro message display length
  lcd.clear();                    // Clear the display before moving to the data reading

  pinMode(ResetPin, INPUT);      // Set the reset button to an input
  pinMode(LoadPin, INPUT);       // Set the reset button to an input

  dht.begin();                   // Initialize the DHT Sensor
}

void loop() 
{

 // Assign variables for the analog input readings so they can be manipulated
  float Current_Value = analogRead(Read_Current);
  float Temp_Value = dht.readTemperature();
  Serial.println(Temp_Value);
// Set a static amperage and voltage values since they will need to be calculated
  float Amperage_Value = 0;
  float Voltage_Value = 0;
  float Watt_Value = 0;

// Calculate a basic current value - NEEDS IMPROVEMENT
// 0.066v(66mV) is rise in output voltage when 1A current flows at input.
// This value might change depending on the situation, adjust as necessiary per sensor

Amperage_Value = ((Current_Value - 511) * (5 / 1023)) / 0.10 - 0.066;

// Calculate the Farenheit temperature based off the 0-1023 input
float fahrenheit = ((Temp_Value * 9) + 3) / 5 + 32;

// Handle the button press for 4 or 8 ohm operation
if (digitalRead(LoadPin) == HIGH)
{
  resistance = 4;
}
else if (digitalRead(LoadPin) == LOW)
{
  resistance = 8;
}

// Calculate the wattage based on the amperage squared * resistance
// While we are at it, might as well calculate the voltage also

Watt_Value = (Amperage_Value * Amperage_Value) * resistance;
Voltage_Value = Amperage_Value * resistance;

// DISPLAY
// First Line on the display
lcd.setCursor(0, 0);
lcd.print("R = "); lcd.print(resistance);
lcd.print("   "); 
lcd.print("I = "); lcd.print(Voltage_Value,1);

// Calculate the peak into variables for display
float Power_Value = Watt_Value;

  if(Power_Value > Max_Value)
 {Max_Value = Power_Value;}

//--------------------- Display ---------------------------
// First Line on the display
lcd.setCursor(0, 1);
  lcd.print("Temp = ");
  lcd.print(fahrenheit, 1);
  lcd.print(" F");
// Second Line on the display
lcd.setCursor(0, 2);  
 lcd.print("Wattage = "); 
 lcd.print(Watt_Value,2);
// Third Line on the display
lcd.setCursor(0, 3);
  lcd.print("Peak = "); 
  lcd.print(Max_Value,2); 

// RESET Button
int resetValue = digitalRead(ResetPin); // Read from the input pin and assign to resetValue

// Compare resetValue to the LOW variation (defined at the top)
if(resetValue != resetValue1)
  {
    if(resetValue == HIGH)
    {
      Max_Value = 0.0000; // Set the MAX value to 0 for the beginning of the next loop
    }
    // Remember the value for the next time, since the loop might be faster than how quick you push the button
    resetValue1 = resetValue;
  }

// Delay controls the refresh rate of the metering. 200 is the default value.
delay(200);

}




