CC=gcc
CFLAGS= -lwiringPi -lcurl -lm -I. -DRASPI -DSHELLPRINT -DHTTP
DEPS = raspi3-4/basics.h raspi3-4/gpio/gpio.h raspi3-4/tIntern/tIntern.h raspi3-4/bme280/bme280.h raspi3-4/mpu6050/mpu6050.h raspi3-4/bh1750/bh1750.h raspi3-4/acoustic/acoustic.h raspi3-4/http-socket/http-socket.h
OBJ = raspi3-4/basics.o raspi3-4/gpio/gpio.o raspi3-4/tIntern/tIntern.o raspi3-4/bme280/bme280.o raspi3-4/mpu6050/mpu6050.o raspi3-4/bh1750/bh1750.o raspi3-4/acoustic/acoustic.o raspi3-4/http-socket/http-socket.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Raspi-HTTP: $(OBJ)
	@echo "\nCompiling..."
	$(CC) -o $@ $^ $(CFLAGS) 
	@echo "\nCompiled Finished, now you can run your code with: '$ ./Raspi-HTTP'\n"

help:
	@echo "\n'make' to compile"
	@echo "'make clean' to delete .o files\n"

.PHONY: clean
clean:
	@$ find . -name "*.o" -type f -delete
