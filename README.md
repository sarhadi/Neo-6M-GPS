# Neo-6M-GPS
Getting data from GPS module

 This is a program that can used with Neo-6M-GPS module & Arduino Uno Board
 Neo-6M-GPS module uses the latest technology to give the best possible position information
 Neo-6M-GPS module has 4 connections: RX, TX, VCC and GND

 Created 30 July. 2018
 by Ehsan Sarhadi

/*********************
 * VCC to 5V
 * GND to GND
 * 4 to GPS Module RX
 * 3 to GPS Module TX
 *********************/
 
 Some country have different time zone and some share the same time zone.
 
 Libraries:
 
 1. SoftwareSerial 
 is a library of Arduino which enables serial data communication through other digital pins of Arduino.
 
 2. TinyGPS
 is a library that converts all those NMEA messages into a readable format by stuffing the character sequences into variables.
 
 Serial monitor is available & will display the data of your gps (Tools > Serial monitor menu)
 
 If you didn't get anything, check the wiring and try it outside or near the window to get the signal.
