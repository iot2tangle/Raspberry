# Raspberry2Tangle
Intro....

## Installation and usage

The following installation is done on **"Raspberry Pi OS"** (formerly Raspbian) and works for *Raspberry Pi 3* and *Raspberry Pi 4*.

**It is not necessary to have all the sensors listed here**, the code is able to detect which sensors were connected. In the case of not connecting any sensor, the only real data that will be displayed on the Tangle will be the **Internal Temperature** of Raspberri Pi.

This is the list of Sensors/Modules that you can connect and it will be recognized immediately.
- ***BME280*** (Bosch) - Temperature, Humidity and Pressure sensor. -> Connected by I2C via: GPIO8/SDA and GPIO9/SCL --- Be careful with the supply of this sensor, the BM280 is powered with 3.3V, if your module does not have a voltage regulator (some modules do not have it) the sensor can be damaged if you supply 5V.
- ***MPU6050*** (InvenSense-TDK) - Acelerometer and Gyroscope 6-axis. -> Connected by I2C via: GPIO8/SDA and GPIO9/SCL.
- ***BH1750*** (ROHM) - Ambient Light Sensor. -> Connected by I2C via: GPIO8/SDA and GPIO9/SCL.
- ***Generic Adjustable Sound Sensor with digital output*** (like *KY038 Module*) - -> Digital Signal on GPIOX, +5V in GPIOX (to enable data collection).
- Also, you can connect a ***Green LED*** in GPIOX that blink when the data is sent to the Tangle, and a ***Red LED*** in GPIOX that will Blink in a certain way when it detects certain errors (totally optional)

### C Software Configuration:
In the *Shell* of Raspberry Pi:

#### 1) Install dependencies:
```
sudo apt-get install libi2c-dev i2c-tools wiringpi libcurl4-openssl-dev
```
#### 2) Enable I2C in your Raspberry Pi if you never did. It is done only once:
```
sudo raspi-config
```
Use the down arrow to select 5: *'Interfacing Options'*, again use the arrow and select 5: *'I2C'*, then *Enable*.

#### 3) Reboot the Raspberry.

Optionally, you can see the I2C devices connected in your Raspi with: 
```
i2cdetect -y 1
```
#### 4) Copy the repository to the local file system of your Raspberry.
```
git clone https://github.com/iot2tangle/raspberry2tangle
cd raspberry-c/
```
#### 5) Edit the file config.h, and complete with the configuration you need.
 ---- Edit later ----

#### 6) Compile the code with:
```
make Raspi3-4-HTTP
```
#### 7) Run:
```
./Raspi-I2T
```

If the endpoint is configured correctly, you will be sending data to the Tangle via Streams :)
	
### Rust Software Configuration:
