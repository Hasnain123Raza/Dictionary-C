all: driver

driver:
	mkdir -p bin
	gcc -o bin/driver -Iincludes `find src -name "*.c"`

clean:
	rm -rf bin