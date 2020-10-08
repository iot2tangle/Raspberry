# Raspberry PI3/4

**Raspberry Pi** is one of the most widely used development computer cards in the world, especially for system development. The versatility, performance and availability of this board made it become one of the main targets of *IOT2TANGLE*.

In this repository you will find explanations and step by step for the development of a system that every certain time interval (which you will set) will collect data from 5 sensors (including internal sensor), this data package will be sent to a special gateway designed by *IOT2TANGLE* that you will have on the local network, or even on the *Raspberry Pi* itself! This gateway will be in charge of adding these packages to **Tangle Network of IOTA**, through *Streams*.

Here is the link to the IOT2TANGLE Gateway repository: <https://github.com/iot2tangle/Streams-wifi-gateway>

Here, we will concentrate only on configuring the side that collects data from the sensors and sends this data to the gateway.
We started with the Raspberry Pi, but our next close goals are to achieve this in *ESP32*, *ESP8266*, *STM32*, and many other devices that you can easily find on the market.

## I2T Sensors Stack

*IOT2TANGLE* provides with code to integrate the *Raspberry Pi* and a give set of generic sensors (I2T sensor's stack). These are just suggested sensors and you can always add some other peripherals required by your project, however the sensors listed here are fully compatible and will be automatically detected when you connect them.

**It is not necessary to have all the sensors listed here**, the code is able to detect which sensors were connected. In the case of not connecting any sensor, the only real data that will be displayed on the Tangle will be the **Internal Temperature** of Raspberri Pi.

This is the list of Sensors/Modules that you can connect and it will be recognized immediately:
- ***BME280*** (Bosch) - Temperature, Humidity and Pressure sensor.
- ***MPU6050*** (InvenSense-TDK) - Acelerometer and Gyroscope 6-axis.
- ***BH1750*** (ROHM) - Ambient Light Sensor.
- ***Generic Adjustable Sound Sensor with digital output*** (like *KY038 Module*)
- Also, you can connect a ***Green LED*** that blink when the data is sent to the Tangle, and a ***Red LED*** that will Blink in a certain way when it detects certain errors (totally optional).

## Software Implementation
This software is written entirely in **C language**. External libraries are used, such as *cURL* (HTML socket handling) and *wiringpi* (optimized library for Raspberry hardware handling), among others already integrated in Raspberry Pi OS.

In *Shell* of Raspberry Pi:

#### 1) Install dependencies:
```
sudo apt-get install wiringpi libcurl4-openssl-dev
```
#### 2) Enable I2C in your Raspberry Pi if you never did. It is done only once:
```
sudo raspi-config
```
Use the down arrow to select 5: *'Interfacing Options'*, again use the arrow and select 5: *'I2C'*, then *Enable*.

#### 3) Copy or clone the repository to the local file system of your Raspberry.
```
git clone https://github.com/iot2tangle/Raspberry
cd Raspberry/
```
#### 4) Edit the file config.h, and complete with the configuration you need.
You must edit the "config.h" file found in the repository root and customize it as you prefer:
- ***ID Name of the device*** You can put the name you want, but remember to also set it in the *gateway configuration* so that it can recognize it.
- ***Endpoint Address:*** Here you can put the *IP address* of the local network computer that is running the I2T gateway, or *'localhost'* in case of running the gateway on the same Raspberry. Remember to always put ***'/sensor_data'*** after the host address, because the gateway listens on that endpoint. Example: "192.168.1.120/sensor_data".
- ***Port:*** Endpoint port.
- ***Interval:*** Interval in seconds between data collect.
- ***Enable and Disable Sensor data*** If you do not want to collect information from a particular device, you can disable it.
#### 5) Compile the code with:
```
make Raspi-HTTP
```
#### 6) Run:
```
./Raspi-I2T
```
That's it!! If the endpoint is configured correctly, you will be sending data to the Tangle via Streams :)

## Hardware Implementation
The following is the configuration of pins and connections of the sensors designed for this repository. You can change the pins if you want, but in that case the code must be modified, so that the software recognizes them.
- ***BME280:*** Connected via **I2C bus**: **GPIO8/SDA** and **GPIO9/SCL** --- Be careful with the voltage supply of this sensor, the BM280 was designed for 3.3V, if your module does not have a voltage regulator (some modules do not have it) the sensor can be damaged if you supply 5V.
- ***MPU6050:*** Connected via **I2C bus**: **GPIO8/SDA** and **GPIO9/SCL**
- ***BH1750*** Connected via **I2C bus**: **GPIO8/SDA** and **GPIO9/SCL**
- ***Generic Adjustable Sound Sensor with digital output:*** Digital Signal of the sensor connected directly to **GPIO24**, and **GPIO23 must be directly connected to GND**, in this way the system knows that this sensor was enabled.
- ***Green LED in GPIO17*** and a ***Red LED in GPIO2***, recommended to use each one with a resistance between 150 to 820 Ω to ground.

*Raspberry Pi board* gives very good power so you will have no problem supplying voltage to the sensors from the board itself.

**Recommended I2C Configuration:**
![I2C](https://www.analog.com/-/media/analog/en/landing-pages/technical-articles/i2c-primer-what-is-i2c-part-1-/36684.png)
In our case Raspberry Pi is the Master Device, while the rest of the I2C sensors are the Slaves.

You probably need a breadboard to make connections and debug more comfortably.


*If you have any questions, concerns, detected an error or want to suggest an improvement in this repository, please feel free to contact any member of I2T or open an Issue.*
