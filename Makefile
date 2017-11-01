all: keylogger

keylogger: keylogger.o
	gcc -o keylogger keylogger.o

keylogger.o: keylogger.c
	gcc -c keylogger.c

.PHONY: clean

clean:
	rm -rf *.o keylogger
