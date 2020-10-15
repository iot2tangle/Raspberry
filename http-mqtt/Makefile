default:
	@echo "\n' make target '"
	@echo "\nPlease put one of the following target:"
	@echo "-> Raspi-HTTP"
	@echo "-> Raspi-MQTT"
	@echo "-> Raspi-BLU"
	@echo ""

Raspi-HTTP:
	@echo "\nCompiling..."
	gcc -std=c11 -D_DEFAULT_SOURCE -o Raspi-HTTP raspi3-4/basics.c raspi3-4/mpu6050/mpu6050.c raspi3-4/bh1750/bh1750.c raspi3-4/tIntern/tIntern.c raspi3-4/http-socket/http-socket.c raspi3-4/gpio/gpio.c raspi3-4/bme280/bme280.c raspi3-4/acoustic/acoustic.c main.c -lwiringPi -lcurl -lm -DRASPI -DHTTP
	@echo "\nCompiled Finished, now you can run your code with: '$ ./Raspi-HTTP'\n"
Raspi-MQTT:
	@echo "\nCompiling..."
	gcc -std=c11 -D_DEFAULT_SOURCE -o Raspi-MQTT raspi3-4/basics.c raspi3-4/mpu6050/mpu6050.c raspi3-4/bh1750/bh1750.c raspi3-4/tIntern/tIntern.c raspi3-4/mqtt-socket/mqtt-socket.c raspi3-4/gpio/gpio.c raspi3-4/bme280/bme280.c raspi3-4/acoustic/acoustic.c main.c -lwiringPi -lpaho-mqtt3c -lm -DRASPI -DMQTT
	@echo "\nCompiled Finished, now you can run your code with: '$ ./Raspi-MQTT'\n"
Raspi-BLU:
	@ echo "Not yet :)"

.PHONY: clean
clean:
	@$ rm Raspi*
