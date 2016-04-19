PRO=$(shell basename `realpath .`)
all:
	cd src && make

clean:
	cd src && make clean

run:
	./$(PRO) --daemon

stop:
	kill `pidof $(PRO)`
