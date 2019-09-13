#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// GPS coordinates
double gpsLatitude;
double gpsLongitude;

SoftwareSerial gpsPort(10, 11);
TinyGPSPlus gps;

void setup()
{
    Serial.begin(9600);
    gpsPort.begin(9600);
    Serial.println("GPS Started...");
    delay(5000);
}

void loop()
{
    updateGPSLocation();
}

void updateGPSLocation()
{
    while (gpsPort.available())
    {
        gps.encode(gpsPort.read());
    }
    if (gps.location.isValid())
    {
        gpsLatitude = gps.location.lat();
        gpsLongitude = gps.location.lng();
    }
    else
    {
        gpsLatitude = 0.3431551;
        gpsLongitude = 32.5914989;
    }
    Serial.println("Latitude:");
    Serial.println(gpsLatitude);
    Serial.println("Longitude:");
    Serial.println(gpsLongitude);
}
