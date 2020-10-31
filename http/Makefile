CC=gcc
CFLAGS= -lwiringPi -lcurl -lm -I. -DRASPI -DSHELLPRINT -DHTTP
DEPS = core/raspi3-4/basics.h core/raspi3-4/peripherals/gpio/gpio.h core/raspi3-4/peripherals/gpio/i2c.h core/raspi3-4/peripherals/gpio/spi.h core/raspi3-4/sensors/internal/internal.h core/raspi3-4/sensors/bme280/bme280.h core/raspi3-4/sensors/mpu6050/mpu6050.h core/raspi3-4/sensors/bh1750/bh1750.h core/raspi3-4/sensors/acoustic/acoustic.h core/raspi3-4/protocols/http/http.h
OBJ = core/raspi3-4/basics.o core/raspi3-4/peripherals/gpio/gpio.o core/raspi3-4/peripherals/i2c/i2c.o core/raspi3-4/peripherals/spi/spi.o core/raspi3-4/sensors/internal/internal.o core/raspi3-4/sensors/bme280/bme280.o core/raspi3-4/sensors/mpu6050/mpu6050.o core/raspi3-4/sensors/bh1750/bh1750.o core/raspi3-4/sensors/acoustic/acoustic.o core/raspi3-4/protocols/http/http.o main.o

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
