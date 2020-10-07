# Raspberry PI3/4

The Raspberry Pi is a series of small single-board computers developed in the United Kingdom by the Raspberry Pi Foundation. Early on, the Raspberry Pi project leaned towards the promotion of teaching basic computer science in schools and in developing countries

## I2T Sensors Stack

IOT2Tangle provides with code to integrate the Raspberry Pi and a give set of generic sensors (I2T sensor's stack). These are just suggested sensors and you can always add some other peripherals required by your project.

**It is not necessary to have all the sensors listed here**, the code is able to detect which sensors were connected. In the case of not connecting any sensor, the only real data that will be displayed on the Tangle will be the **Internal Temperature** of Raspberri Pi.

This is the list of Sensors/Modules that you can connect and it will be recognized immediately:

- ***BME280*** (Bosch) - Temperature, Humidity and Pressure sensor. -> Connected by I2C via: GPIO8/SDA and GPIO9/SCL --- Be careful with the supply of this sensor, the BM280 is powered with 3.3V, if your module does not have a voltage regulator (some modules do not have it) the sensor can be damaged if you supply 5V.
- ***MPU6050*** (InvenSense-TDK) - Acelerometer and Gyroscope 6-axis. -> Connected by I2C via: GPIO8/SDA and GPIO9/SCL.
- ***BH1750*** (ROHM) - Ambient Light Sensor. -> Connected by I2C via: GPIO8/SDA and GPIO9/SCL.
- ***Generic Adjustable Sound Sensor with digital output*** (like *KY038 Module*) - -> Digital Signal on GPIOX, +5V in GPIOX (to enable data collection).
- Also, you can connect a ***Green LED*** in GPIOX that blink when the data is sent to the Tangle, and a ***Red LED*** in GPIOX that will Blink in a certain way when it detects certain errors (totally optional)

## Available connectivity
- **[HTTP](https://github.com/iot2tangle/Raspberry/tree/main/http)** (WiFi will post a request with the data to a given server)


