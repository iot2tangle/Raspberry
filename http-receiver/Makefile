CC=gcc
CFLAGS= -lwiringPi -lcurl -lm -I. -DRASPI -DSHELLPRINT -DHTTP -DEXAMPLE
DEPS = core/raspi3-4/basics.h core/raspi3-4/peripherals/gpio/gpio.h core/raspi3-4/peripherals/gpio/i2c.h core/raspi3-4/peripherals/gpio/spi.h core/raspi3-4/protocols/http/http.h core/raspi3-4/output/relay/relay.h core/json/decoder-i2t-json.h /core/json/struct-json.h /core/json/jsmn/jsmn.h


OBJ = core/raspi3-4/basics.o core/raspi3-4/peripherals/gpio/gpio.o core/raspi3-4/peripherals/i2c/i2c.o core/raspi3-4/peripherals/spi/spi.o core/raspi3-4/protocols/http/http.o core/raspi3-4/output/relay/relay.o core/json/decoder-i2t-json.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Raspi-HTTP-Receiver: $(OBJ)
	@echo "\nCompiling..."
	$(CC) -o $@ $^ $(CFLAGS) 
	@echo "\nCompiled Finished, now you can run your code with: '$ ./Raspi-HTTP-Receiver'\n"
	@$ find . -name "*.o" -type f -delete

help:
	@echo "\n'make' to compile"
	@echo "'make clean' to delete .o files\n"

.PHONY: clean
clean:
	@$ find . -name "*.o" -type f -delete
