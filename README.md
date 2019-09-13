# Crash Reporter Arduino
Arduino program to detect an accident and make a crash report.

## Hardware Setup
### Required Electronics Components
- Arduino [Uno](https://store.arduino.cc/arduino-uno-rev3) microcontroller board
- [SIM800L](https://nettigo.eu/products/sim800l-gsm-grps-module) GSM/GPRS module
- [NEO-6M](https://www.addicore.com/NEO-6M-GPS-p/231.htm) GPS Module
- [ADXL335](https://www.analog.com/en/products/adxl335.html#product-evaluationkit) 3-axis accelerometer
### Schematic
![connection](crash-detector.png)

**NB:**
- Insert a SIM card with a data subscription into the SIM800L module and power it from a 5V external source.
- Connect RX, TX, and RST of the SIM800L module to pins 7, 6, and 5 respectively of the Uno.
- Connect X_OUT, Y_OUT, and Z_OUT of the accelerometer to analog pins A3, A2, and A1 respectively of the Uno as indicated in `crash_reporter.ino`. Power the accelerometer from the 5V output of the Uno board.
- Power the GPS module from the Uno board and connect its RX and TX to pins 11 and 10 respectively of the Uno.
- Load the program in `crash_reporter.ino` onto the Uno board.
### Testing
- Set up an HTTP server which can accept POST requests.
- Specify the server's URL in the `sendJSONData()` function in `crash_reporter.ino`.
- Simulate a crash by sharply moving the accelerometer (equivalent to a sudden change in speed).
- Verify that the specified server received the POST request (crash report).
