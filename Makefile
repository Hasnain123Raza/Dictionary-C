all: main

main:
	mkdir -p bin
	gcc -o bin/main -Iincludes `find src -name "*.c"`

clean:
	rm -rf bin