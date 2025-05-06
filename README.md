# ampdyno
Software for an audio amplifier testing dyno.

This is for a design using an Arduino, to measure an audio amplifiers total output power in RMS. This is used in the car audio, and pro audio industry, to validate that the amplifier is outputting the power it is supposed to.
The dyno uses a large load bank of resistors, to provide both an 8 ohm load, and a 4 ohm load. Power handling is determined by the capacity of the load bank. 
In my design, i used 100w resistors, wired in both series and paralell to achieve the 4 and 8 ohm loads, and also to increase the overall capacity.
The Arduino provides the measuring by monitoring the current flowing into the resistor bank, and knowing which load bank it is on, to calculate the I/R=P. The voltage is also calculated, but currently not displayed.

Parts:
320mmx268mmx120mm Metal enclosure 
12v 30a Relay 
12v Switch
220mmx220mm Aluminum heatsink
30a ACS712 Current Sensor
Arduino R3 Board
12v 5A Power Supply
16 - 4ohm 100w resistors
i2C 2004 LED module

Wiring Schematic will be included
