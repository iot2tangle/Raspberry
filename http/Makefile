CC=gcc
CFLAGS= -lwiringPi -lcurl -lm -I. -DRASPI -DHTTP
DEPS = raspi3-4/basics.h raspi3-4/mpu6050/mpu6050.h raspi3-4/bh1750/bh1750.h raspi3-4/tIntern/tIntern.h raspi3-4/http-socket/http-socket.h raspi3-4/gpio/gpio.h raspi3-4/bme280/bme280.h raspi3-4/acoustic/acoustic.h
OBJ = raspi3-4/basics.o raspi3-4/mpu6050/mpu6050.o raspi3-4/bh1750/bh1750.o raspi3-4/tIntern/tIntern.o raspi3-4/http-socket/http-socket.o raspi3-4/gpio/gpio.o raspi3-4/bme280/bme280.o raspi3-4/acoustic/acoustic.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

help:
	@echo "\n' make target '"
	@echo "\nPlease put one of the following target:"
	@echo "-> Raspi-HTTP"
	@echo "-> Raspi-MQTT"
	@echo "-> Raspi-BLU"
	@echo "-> ESP8266-HTTP"
	@echo ""

Raspi-HTTP: $(OBJ)
	@echo "\nCompiling..."
	$(CC) -o $@ $^ $(CFLAGS) 
	@echo "\nCompiled Finished, now you can run your code with: '$ ./Raspi-HTTP'\n"

Raspi-MQTT:
	@ echo "Not yet :)"

Raspi-BLU:
	@ echo "Not yet :)"


.PHONY: clean
clean:
	@$ find . -name "*.o" -type f -delete
