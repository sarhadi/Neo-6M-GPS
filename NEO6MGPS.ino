/*   

  Getting data from GPS module
 
 This is a program that can used with Neo-6M-GPS module & Arduino Uno Board
 Neo-6M-GPS module uses the latest technology to give the best possible position information
 with 4 connections: RX, TX, VCC and GND

 Created 30 July. 2018
 by Ehsan Sarhadi

/*********************
 * VCC to 5V
 * GND to GND
 * 4 to GPS Module RX
 * 3 to GPS Module TX
 * Default Baud Rate: 9600 bps
 *********************/

#include <SoftwareSerial.h>
#include <TinyGPS.h>

SoftwareSerial mySerial(4, 3); // RX, TX
TinyGPS gps;

void gpsdump(TinyGPS &gps);
void printFloat(double f, int digits = 2);

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  delay(1000);
  Serial.println("uBlox Neo 6M");
  Serial.println("by Ehsan Sarhadi");
  Serial.println();
}

void loop() // run over and over
{
  bool newdata = false;
  unsigned long start = millis();
  // Every 10 seconds we print an update
  while (millis() - start < 10000) 
  {
    if (mySerial.available()) 
    
    {
      char c = mySerial.read();
      //Serial.print(c);  // uncomment to see raw GPS data
      if (gps.encode(c)) 
      {
        newdata = true;
        //break;  // uncomment to print new data immediately!
      }
    }
  }
  
  if (newdata) 
  {
    Serial.println("GPS Data:");
    Serial.println("-------------");
    gpsdump(gps);
    Serial.println("-------------");
    Serial.println();
  }
  
}

void gpsdump(TinyGPS &gps)
{
  long lat, lon;
  float flat, flon;
  unsigned long age, date, time, chars;
  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned short sentences, failed;

   gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
  Serial.print("Date: "); Serial.print(static_cast<int>(month)); Serial.print("/"); 
    Serial.print(static_cast<int>(day)); Serial.print("/"); Serial.print(year);
  Serial.print(", Time (UTC): "); Serial.print(static_cast<int>(hour));  Serial.print(":"); //Serial.print("UTC +04:30 Tehran");
    Serial.print(static_cast<int>(minute)); Serial.print(":"); Serial.print(static_cast<int>(second));
    Serial.print("."); Serial.print(static_cast<int>(hundredths)); Serial.print(" (UTC +04:30 Tehran)"); Serial.println();
  Serial.print(" Fix age: ");  Serial.print(age); Serial.println("ms."); Serial.println();
  
  // On Arduino, GPS characters may be lost during lengthy Serial.print()

  gps.f_get_position(&flat, &flon, &age);
  Serial.print("Latitude (North): "); printFloat(flat, 10); Serial.println();
  Serial.print("Longitude (East): "); printFloat(flon, 10); Serial.println();
  Serial.print(" Fix age: "); Serial.print(age); Serial.println("ms."); Serial.println();

  Serial.print("Altitude: "); printFloat(gps.f_altitude()); Serial.print(" (m) "); Serial.println();
  Serial.print("Speed: ");  printFloat(gps.f_speed_mps()); Serial.print(" (mps), "); printFloat(gps.f_speed_kmph()); Serial.print(" (kmph) "); Serial.println();
 
  gps.stats(&chars, &sentences, &failed); Serial.println();
  Serial.print("Stats: characters: "); Serial.print(chars); Serial.print(", sentences: ");
    Serial.print(sentences); Serial.print(", failed checksum: "); Serial.println(failed);
}

void printFloat(double number, int digits)
{
  // Handle negative numbers
  if (number < 0.0) 
  {
     Serial.print('-');
     number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;
  
  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  Serial.print(int_part);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0)
    Serial.print("."); 

  // Extract digits from the remainder one at a time
  while (digits-- > 0) 
  {
    remainder *= 10.0;
    int toPrint = int(remainder);
    Serial.print(toPrint);
    remainder -= toPrint;
  }
}
