# Raspberry PI3/4

**Raspberry Pi** is one of the most widely used development computer cards in the world, especially for system development. The versatility, performance and availability of this board made it become one of the main targets of *IOT2TANGLE*.

In this repository you will find explanations and step by step for the development of a system that every certain time interval (which you will set) will collect data from 5 sensors (including internal sensor), this data package will be sent to a special gateway designed by *IOT2TANGLE* that you will have on the local network, or even on the *Raspberry Pi* itself! This gateway will be in charge of adding these packages to **Tangle Network of IOTA**, through *Streams*.

## I2T Sensors Stack

*IOT2TANGLE* provides with code to integrate the *Raspberry Pi* and a give set of generic sensors (I2T sensor's stack). These are just suggested sensors and you can always add some other peripherals required by your project, however the sensors listed here are fully compatible and will be automatically detected when you connect them.

**It is not necessary to have all the sensors listed here**, the code is able to detect which sensors were connected. In the case of not connecting any sensor, the only real data that will be displayed on the Tangle will be the **Internal Temperature** of Raspberri Pi.

This is the list of Sensors/Modules that you can connect and it will be recognized immediately:
- ***BME280*** (Bosch) - Temperature, Humidity and Pressure sensor.
- ***MPU6050*** (InvenSense-TDK) - Acelerometer and Gyroscope 6-axis.
- ***BH1750*** (ROHM) - Ambient Light Sensor.
- ***Generic Adjustable Sound Sensor with digital output*** (like *KY038 Module*)
- Also, you can connect a ***Green LED*** that blink when the data is sent to the Tangle, and a ***Red LED*** that will Blink in a certain way when it detects certain errors (totally optional).

## Available connectivity
- **[HTTP-sender](https://github.com/iot2tangle/Raspberry/tree/main/http-sender)** (Raspberry will send the sensors data through HTTP to **[I2T HTTP Gateway](https://github.com/iot2tangle/Streams-http-gateway)** or **[Keepy](https://github.com/iot2tangle/Keepy)**
- **[MQTT-sender](https://github.com/iot2tangle/Raspberry/tree/main/mqtt-sender)** (Raspberry will send the sensors data through MQTT to **[I2T MQTT Gateway](https://github.com/iot2tangle/Streams-mqtt-gateway)**)
- **[HTTP-receiver](https://github.com/iot2tangle/Raspberry/tree/main/http-receiver)** -- Raspberry will receive the sensors data through HTTP from **[Keepy](https://github.com/iot2tangle/Keepy)** and performs actions based on the data received (for now it is optimized only to work with Keepy).

