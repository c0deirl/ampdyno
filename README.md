# Audio Amplifier Dyno
Software for an audio amplifier testing dyno.

This is for a design using an Arduino, to measure an audio amplifiers total output power in RMS. This is used in the car audio, and pro audio industry, to validate that the amplifier is outputting the power it is supposed to.
The dyno uses a large load bank of resistors, to provide both an 8 ohm load, and a 4 ohm load. Power handling is determined by the capacity of the load bank.  
I used 4ohm - 100w resistors, wired in both series and paralell to achieve the 4 and 8 ohm loads. When only one bank is connected, it is an 8 ohm load, but the relay allows me to paralell another 8 ohm load, creating a larger 4 ohm load. You could probably increase the size of the overall load banks, for increased power handling, and with more relays, creating other resistance values.  

The Arduino provides the measuring by monitoring the current flowing into the resistor bank(s), and knowing which load bank is connected. It uses the current value and the resistance to calculate the I²*R=P. The voltage is also calculated, but currently not displayed.  

There is also a temperature sensor included to monitor the temperature of the heatsink, to make sure that things dont get too hot if you are testing for a long period of time. This is optional, but a good idea. I do have a fan in the enclosure now, which is why the 3d printed front panel includes my logo that is hollow. I'm just using the logo as a way for air to enter or exhaust for better cooling.

Reccomended to use a 40HZ or 1000hz sine wave directly into the amplifier, right along the edge of peak to gather the best data. I added in a set of binding posts on the back to allow you to connect an osciliscope to watch the sine wave and check for distortion, and watch when the amp starts to clip.

## Parts:  
- 320mmx268mmx120mm Metal enclosure  
- 12v 30a Relay  
- 12v Switch    
- 220mmx220mm Aluminum heatsink  
- 30a ACS712 Current Sensor  
- Arduino R3 Board  
- 12v 5A Power Supply  
- 16 - 4ohm 100w resistors  
- i2C 2004 LED module  
- DHT11 Temperature sensor  


## Wiring Schematic  

![AmpDyno2](https://github.com/user-attachments/assets/29001fe6-f7c0-43c6-b74f-5daf5599edf7)

## Build  

![24-11-08 16-18-10 5836](https://github.com/user-attachments/assets/ff974486-0075-41a3-bc1e-0c9c84607b32)
![24-11-02 07-54-56 5727](https://github.com/user-attachments/assets/2f4c98c8-3f28-46d1-af98-09e95a85cc84)
![24-11-08 15-47-49 5835](https://github.com/user-attachments/assets/b4f910eb-31f0-4fbc-ba15-25acce97b041)
![24-11-08 16-28-46 5839](https://github.com/user-attachments/assets/64ecc2cb-3538-45a2-8d09-a35775052235)![24-10-29 20-23-45 5687](https://github.com/user-attachments/assets/6641ba8b-0f3c-4f56-b17c-aedb407fbec4)

