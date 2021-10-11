all: main

main:
	mkdir -p bin
	gcc -o bin/main -Iincludes -Iincludes/DataStructures -Iincludes/Utilities `find src -name "*.c"` -lcurl -ltidy

clean:
	rm -rf bin