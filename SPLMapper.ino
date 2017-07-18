/*
 * SPLMapper v.1
 * Pete Marchetto, University of Minnesota, 07/18/2017
 * marchetto@umn.edu
 * 
 * This is code to log the SPL (or other analog inputs) and the date and time from a GPS module.
 * The GPS TX is hooked up on pin 12 (SSRX), while the analog input is on the ADC pin of a ESP8266 Thing.
 * This uses the TinyGPS++ and Cayenne libraries. This sketch is intended to be used on a SparkFun 8266 Thing.
 * Serial data may be logged by attaching an OpenLog, cutting the RST trace on the bottom of the Thing, and
 * soldering the jumper to allow power to the serial header on the Thing.
 */

#include <CayenneMQTTESP8266.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// WiFi network info.
char ssid[] = "galileo";
char wifiPassword[] = "yesyesyes";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "32f260b0-6bd9-11e7-80f0-a334be42512c";
char password[] = "2a117292506c0cc61fae2f8a0c418158c2addfc1";
char clientID[] = "3b207e70-6bd9-11e7-8378-e1a615c9f526";


SoftwareSerial GPS(12,13);
TinyGPSPlus gps;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  GPS.begin(9600);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop() {
  // put your main code here, to run repeatedly:
  printDateTime(gps.date, gps.time);
  Serial.print(",");
  printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
  printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
  Serial.print(",");
  printFloat(gps.altitude.meters(), gps.altitude.isValid(), 7, 2);
  Serial.print(",");
  int SPL=analogRead(0);
  Serial.println(SPL);
  Cayenne.virtualWrite(0, gps.date.year());
  Cayenne.virtualWrite(1, gps.date.month());
  Cayenne.virtualWrite(2, gps.date.day());
  Cayenne.virtualWrite(3, gps.time.hour());
  Cayenne.virtualWrite(4, gps.time.minute());
  Cayenne.virtualWrite(5, gps.time.second());
  Cayenne.virtualWrite(6, gps.location.lat());
  Cayenne.virtualWrite(7, gps.location.lng());
  Cayenne.virtualWrite(8, gps.altitude.meters());
  Cayenne.virtualWrite(9, SPL);
}

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (GPS.available())
      gps.encode(GPS.read());
  } while (millis() - start < ms);
}

static void printFloat(float val, bool valid, int len, int prec)
{
  if (!valid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
  smartDelay(0);
}

static void printInt(unsigned long val, bool valid, int len)
{
  char sz[32] = "*****************";
  if (valid)
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  Serial.print(sz);
  smartDelay(0);
}

static void printDateTime(TinyGPSDate &d, TinyGPSTime &t)
{
  if (!d.isValid())
  {
    Serial.print(F("********** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
    Serial.print(sz);
  }
  
  if (!t.isValid())
  {
    Serial.print(F("******** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
    Serial.print(sz);
  }

  printInt(d.age(), d.isValid(), 5);
  smartDelay(0);
}

static void printStr(const char *str, int len)
{
  int slen = strlen(str);
  for (int i=0; i<len; ++i)
    Serial.print(i<slen ? str[i] : ' ');
  smartDelay(0);
}
