
/*
 * Basic Amplifier Dyno 
 * Date: 10-22-2024
 * Version: 1.2
 * Designed by M Greathouse 
 * Voltage Sensor Input -> A3
 * Current Sensor Input -> A2
 * Temperature Sensor Input -> D7
 * Reset button input - A1
 */

#include <LiquidCrystal.h>  //Default Arduino LCD Library is included 
#include <LiquidCrystal_I2C.h> // Library to use I2C displays
#include <dht.h> // Define library for temp sensor

#define DHT11_PIN 7 // USE PIN 7 Digital for the DHT11 temp sensor
#define DHTTYPE DHT11 // DHT 11 for actual use
dht DHT;

// Degine the I2C Display parameters
#define I2C_ADDR    0x27
#define LCD_COLUMNS 20
#define LCD_LINES   4

// I2C address 0x27, 20 column and 4 rows
LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES); 

// Define Input Pins. These are analog inputs from 0-5v
int Read_Voltage  = A3;
int Reset = A1;

// Voltage variables - NOT NEEDED

  float FinalRMSVoltage;
  float Voltage_Value;

const float acsOut =A2; // Analog Pin 2
int acsSensitivity =59;
float voltage =-1;
float vRms=0;
float ampRms=0;
float watt=0;
float resistance=0;


const int buttonPin = 8; // This is the reset button pin. Using 10k resistor to gnd on the pin 8 side, then the other side of the button to 5v
int resetValue1 = LOW; // Defines the base reset value. Once the pin goes high, that will trigger the reset
float Max_Value; // Define the Peak value outside of the loop so the state can be reset

int button1 = 12; //This is the button input for 4-8 ohm switching


void setup() {

  //lcd.begin(20, 4); //Initialise 20*4 LCD
  lcd.init();
  lcd.backlight(); // Turn on the backlight

  lcd.setCursor(2, 1);
    lcd.print(" MATTS AMP DYNO"); //Intro Message line 1

  lcd.setCursor(2, 2);
    lcd.print("      V1.0  "); //Intro Message line 2

  delay(3000); // Set the intro message display length
  lcd.clear(); // Clear the display before moving to the data reading

  pinMode(buttonPin, INPUT); // Set the reset button to an input

}


// Voltage reading section, this is not needed as we are calculating from the current and resistance
float getVpp()
{
float result;

int readValue;
int maxValue=0;
int minValue=1023;
uint32_t start_time=millis();
while((millis()-start_time < 1000))
{
    readValue =analogRead(acsOut);
    if(readValue > maxValue)
    {
       maxValue=readValue;
    }
    if(readValue < minValue)
    { 
       minValue=readValue;
    }
       
}
result=((maxValue-minValue)*5.0)/1023.0;
return result;
}



void loop() {

 // Assign variables for the analog input readings so they can be manipulated
 float Voltage_Value = analogRead(Read_Voltage);
 //float Current_Value = analogRead(Read_Current);
 //float Temp_Value = analogRead(Read_Temp);

// Set a static amperage value since it will need to be calculated
 float Amperage_Value = 0;
// Basic constraint for voltage 0-1023 corresponds to 0v-100v

// Calculate a basic current value - NEEDS IMPROVEMENT

//Amperage_Value = (Current_Value - 510) * 5 / 1024 / 0.10 - 0.54;

// Calculate the actual celcius temperature based off the 0-1023 input
float fahrenheit = ((DHT.temperature * 9) + 3) / 5 + 32;

  FinalRMSVoltage = map(Voltage_Value,400,490,0,125);


if (digitalRead(button1) == HIGH)
{
  resistance = 4;
  
}
if (digitalRead(button1) == LOW)
{
  resistance = 8;
  
}

float voltage =getVpp();
vRms =(voltage/2.0)*0.707;
ampRms =(vRms*1000)/acsSensitivity;
watt = ampRms * resistance;

// DISPLAY
// First Line on the display
lcd.setCursor(0, 0);
lcd.print("R = "); lcd.print(resistance);
lcd.print("   "); 
//lcd.print("I = "); lcd.print(Amperage_Value);
//lcd.print("I = "); lcd.print(Amperage_Value,1);
lcd.print("I = "); lcd.print(ampRms,1);
  
// Calculate the wattage and peak into variables for display
float Power_Value = watt;

  if(Power_Value > Max_Value)
 {Max_Value = Power_Value;}

// Set the pinput check PER LOOP to read the temperature sensor, The DHT values will change depending on the type of DHT sensor.
int chk = DHT.read11(DHT11_PIN);

// Second Line on the display
lcd.setCursor(0, 1);
  lcd.print("Temp = ");
  lcd.print(fahrenheit, 1);
  lcd.print(" F");


// Third Line on the display
lcd.setCursor(0, 2);  
 lcd.print("Wattage = "); 
// lcd.print(Power_Value,2); 
lcd.print(watt,2);

// Fourth Line on the display
lcd.setCursor(0, 3);
  lcd.print("Peak = "); 
  lcd.print(Max_Value,2); 

// RESET Button
int resetValue = digitalRead(buttonPin); // Read from the input pin and assign to resetValue
// Compare resetValue to the LOW variation (defined at the top)
if(resetValue != resetValue1)
  {
    if(resetValue == HIGH)
    {
      Max_Value = 0.0000; // Set the MAX value to 0 for the beginning of the next loop
      //delay (1000);
    }
    // Remember the value for the next time.
    resetValue1 = resetValue;
  }

// Delay controls the refresh rate of the metering. 200 is the default value.
delay(200);

}




