#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// Accelerometer pins
const int xInput = A3;
const int yInput = A2;
const int zInput = A1;

// minimum and maximum raw values for each accelerometer axis
int minRawInput = 0;
int maxRawInput = 1023;

// number of samples per accelerometer axis
const int sampleSize = 10;

int previousAccel = 0;
int currentAccel;

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

int crashHasOccured()
{
    // read raw acceleration values
    int xRaw = getAxisAcceleration(xInput);
    int yRaw = getAxisAcceleration(yInput);
    int zRaw = getAxisAcceleration(zInput);

    // convert raw values to milli-g
    long xScaled = map(xRaw, minRawInput, maxRawInput, -3000, 3000);
    long yScaled = map(yRaw, minRawInput, maxRawInput, -3000, 3000);
    long zScaled = map(zRaw, minRawInput, maxRawInput, -3000, 3000);

    // re-scale to g
    float xAccel = xScaled / 1000.0;
    float yAccel = yScaled / 1000.0;
    float zAccel = zScaled / 1000.0;

    float totalAccel = sqrt(xAccel * xAccel + yAccel * yAccel + zAccel * zAccel);
    if (previousAccel == 0)
    {
        previousAccel = totalAccel;
        return 0;
    }
    Serial.println(totalAccel);
    currentAccel = totalAccel;
    int diff = currentAccel - previousAccel;
    previousAccel = currentAccel;
    if (abs(diff) > 0.7)
    {
        Serial.println("Crash detected...");
        Serial.println("Previous Acceleration:");
        Serial.println(previousAccel);
        Serial.println("Current Acceleration:");
        Serial.println(currentAccel);
        Serial.println("Acceleration Difference:");
        Serial.println(diff);
        return 1;
    }
    else
    {
        return 0;
    }
}

// take samples and return average
int getAxisAcceleration(int axisPin)
{
    long reading = 0;
    analogRead(axisPin);
    delay(1);
    for (int i = 0; i < sampleSize; i++)
    {
        reading += analogRead(axisPin);
    }
    return reading / sampleSize;
}
