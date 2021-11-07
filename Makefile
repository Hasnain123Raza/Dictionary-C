all: main

main:
	mkdir -p bin
	gcc -o bin/main -Iincludes/CLI -Iincludes/Core -Iincludes/Core/DataStructures -Iincludes/Core/Utilities `find src -name "*.c"` -lcurl -ltidy

clean:
	rm -rf bin