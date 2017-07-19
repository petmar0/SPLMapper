# SPLMapper
A GPS-enabled, wifi-connected mapper of sound levels.

## Parts
- SparkFun ESP8266 Thing
- SparkFun Sound Detector
- SparkFun OpenLog
- GPS Module
- µSD Card
- M-F and F-F Jumpers
- USB Power Pack
- USB A to microB Cable
- Enclosure
- 0.1" Header Pins
- 0.1" Header Sockets
- 0.1" Header Jumper
- Solder
- Breadboard or Perfboard

## Tools
- Soldering Iron
- Wire Cutters
- 3.3 V FTDI Programming Cable
- Microphone Calibrator

## Hardware Procedure
1. Solder pins onto the ESP8266 Thing and Sound Detector boards
2. Solder sockets onto OpenLog board
3. Cut the trace between RST and GND on the back of the Thing
4. Solder a two-pin header into the RST and GND vias on the Thing
5. Connect the ADC pin on the Thing to the Envelope pin on the Sound Detector
6. Connect the white (signal) wire from the GPS to pin 12 on the Thing
7. Connect the USB power pack to the microB port on the Thing with the USB cable
8. Connect the power and ground pins on both the GPS and Sound Detector to the 3.3 V and GND pins, respectively, on the Thing, in parallel
9. Program the Thing (see [Software Procedure](#software-procedure), below)
10. Solder across the VCC jumper on the bottom of the Thing
11. Place all components in the enclosure

## Software Procedure
1. Go to https://cayenne.mydevices.com/
2. Set up an account and follow the instructions for installing the ESP8266 MQTT library and Arduino IDE
3. Add a new ESP8266 Thing to your account and replace the SSID, wifi password, user, MQTT password, and client ID in the SPLMapper.ino code
4. Load code from SPLMapper.ino onto the Thing
5. Configure the ten channels now on your Cayenne dashboard to match those in the SPLMapper code
