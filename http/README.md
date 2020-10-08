# Raspberry PI3/4 with I2T Sensors Stack

The Raspberry Pi is a series of small single-board computers developed in the United Kingdom by the Raspberry Pi Foundation. Early on, the Raspberry Pi project leaned towards the promotion of teaching basic computer science in schools and in developing countries

## Setting up your Raspberry with the I2T Sensors Stack

The following installation is done on **"Raspberry Pi OS"** (formerly Raspbian) and works for *Raspberry Pi 3* and *Raspberry Pi 4*.

This is the list of Sensors/Modules that you can connect and it will be recognized immediately.
- ***BME280*** (Bosch) - Temperature, Humidity and Pressure sensor. -> Connected by I2C via: GPIO8/SDA and GPIO9/SCL --- Be careful with the supply of this sensor, the BM280 is powered with 3.3V, if your module does not have a voltage regulator (some modules do not have it) the sensor can be damaged if you supply 5V.
- ***MPU6050*** (InvenSense-TDK) - Acelerometer and Gyroscope 6-axis. -> Connected by I2C via: GPIO8/SDA and GPIO9/SCL.
- ***BH1750*** (ROHM) - Ambient Light Sensor. -> Connected by I2C via: GPIO8/SDA and GPIO9/SCL.
- ***Generic Adjustable Sound Sensor with digital output*** (like *KY038 Module*) - -> Digital Signal on GPIOX, +5V in GPIOX (to enable data collection).
- Also, you can connect a ***Green LED*** in GPIOX that blink when the data is sent to the Tangle, and a ***Red LED*** in GPIOX that will Blink in a certain way when it detects certain errors (totally optional)

### Connecting the sensors

The following diagram explains how each sensor of our stack must be connected to the Raspberry pins

![I2T Sensors Stack on Raspberry](https://iot2tangle.io/assets/screenshots/Hardware_connections_Raspi-01.png)

It is not necessary to have all the sensors listed here, the code is able to detect which sensors were connected. In the case of not connecting any sensor, the only real data that will be displayed on the Tangle will be the Internal Temperature of Raspberri Pi.


## Setting up the Sensors Software

This software is written entirely in C language. External libraries are used, such as cURL (HTML socket handling) and wiringpi (optimized library for Raspberry hardware handling), among others already integrated in Raspberry Pi OS.


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

Optionally, you can see the I2C devices connected in your Raspi with: 
```
i2cdetect -y 1
```
#### 3) Copy the repository to the local file system of your Raspberry.

```
git clone https://github.com/iot2tangle/Raspberry.git
```
#### 4) Edit the file config.h

Navigate to the **Raspberry/http** directory and edit the **config.h** file to define the values for your configuration to match your WiFi data, the endpoint that will have the IOTA Streams Gateway running and the Device Id. The Device Id you define here must be exactly what you set on the Gateway configuration file. 

Keep in mind that any changes on the config file will require to recompile the code.

```
const char* id_name = "Raspi-HTTP";

/* Network */
const char* endpoint = "192.168.1.113/sensor_data";    /* Endpoint must not include 'http://xxx' */
int port = 8080;

bool isWifi = false; /* This is 'true' for microcontrollers like ESP32 or STM32. In RaspberryPi it will be 'false', because the network connection is made outside the program by the Raspberry OS */
const char* ssid_WiFi = "SSID-WIFI";
const char* pass_WiFi = "pass_WiFi";
```


#### 5) Compile the code with:
```
make Raspi-I2T-HTTP
```
#### 6) Run:
```
./Raspi-I2T
```

If the Streams Gateway endpoint is configured correctly (we will explain this next), you will be sending data to the Tangle via Streams. The following capture shows a Raspberry with a BME280 connected (note how the sensor is detected automatically)


![Raspberry with BME280 sending data to the Tangle](https://iot2tangle.io/assets/screenshots/PiStackSend.png)

	
# Setting up the Streams Gateway

## Preparation

Install Rust if you don't have it already. More info about Rust here https://www.rust-lang.org/tools/install

`curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh`

Make sure you also have the build dependencies installed, if not run:  

`sudo apt install build-essential`  
`sudo apt install pkg-config`  
`sudo apt install libssl-dev`  
`sudo apt update`  

## Installing the Streams Gateway

Get the Streams WiFi Gateway repository

`git clone https://github.com/iot2tangle/Streams-wifi-gateway`

Navigate to the **Streams-wifi-gateway** directory and edit the **config.json** file to define your device name (it must match what you set on the Sense Hat config).
There you can also change ports and the IOTA Full Node used.  

  
```
{
    "device_name": "PI3SH", 
    "port": 8080, 
    "node": "https://nodes.iota.cafe:443", 
    "mwm": 14,    
    "local_pow": false     
}
```

## Start the Streams Server

### Sending messages to the Tangle

Run the Streams Gateway:  

`cargo run --release`  

This will compile and start the Streams Gateway. Note that the compilation process may take from 3 to 30 minutes (Pi3 took us around 30 mins, Pi4 8 mins and VPS or desktop machines will generally compile under the 5 mins) depending on the device you are using as host.

You will only go through the compilation once and any restart done later will take a few seconds to have the Gateway working.

![Streams Gateway receiving SenseHat data](https://iot2tangle.io/assets/screenshots/PiSenseHatSend.png)
*The Gateway starts by giving us the channel id that will allow subscribers to access the channel data.*

### Reading messages from the Tangle

In a separate console start a subscriber using the Channel Id printed by the Gateway (see example above):  

`cargo run --release --example subscriber <your_channel_root> `  

![Streams Gateway receiving SenseHat data](https://iot2tangle.io/assets/screenshots/PiSenseHatGet.png)

### Testing without sensors

To send data to the server you can use Postman, or like in this case cURL, make sure the port is the same as in the config.json file:  

`  
curl --location --request POST '127.0.0.1:8080/sensor_data'   
--header 'Content-Type: application/json'   
--data-raw '{
    "iot2tangle": [
        {
            "sensor": "Gyroscope",
            "data": [
                {
                    "x": "4514"
                },
                {
                    "y": "244"
                },
                {
                    "z": "-1830"
                }
            ]
        },
        {
            "sensor": "Acoustic",
            "data": [
                {
                    "mp": "1"
                }
            ]
        }
    ],  
    "device": "PI3SH",  
    "timestamp": "1558511111"  
}'  
`   

IMPORTANT: The device will be authenticated through the "device" field in the request (in this case PI3SH), this has to match what was set as device_name in the config.json on the Gateway (see Configuration section above)!  
  
After a few seconds you should now see the data beeing recieved by the Subscriber!