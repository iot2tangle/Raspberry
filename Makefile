default:
	@echo "\n' make target '"
	@echo "\nPlease put one of the following target:"
	@echo "-> Raspi3-4-HTTP"
	@echo "-> Raspi3-4-BLU"
	@echo "-> ESP8266-HTTP"
	@echo ""
Raspi3-4-HTTP:
	@echo "\nCompiling..."
	gcc -g -Wextra -pedantic -std=c11 -D_DEFAULT_SOURCE -D_BSD_SOURCE -o Raspi-I2T raspi3-4/basics.c raspi3-4/mpu6050/mpu6050.c raspi3-4/bh1750/bh1750.c raspi3-4/tIntern/tIntern.c raspi3-4/http-socket/http-socket.c raspi3-4/gpio/gpio.c raspi3-4/bme280/bme280.c raspi3-4/acoustic-sens/acoustic-sens.c main.c -lwiringPi -lcurl -lm
	@echo "\nCompiled Finished, now you can run your code with: '$ ./Raspi-I2T'\n"	
Raspi3-4-BLU:
	@ echo "Not yet :)"
			
ESP8266-HTTP:
	@ echo "Not yet :)"


