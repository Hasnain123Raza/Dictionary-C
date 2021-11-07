all: main

main:
	mkdir -p bin
	gcc -g -o bin/main -Iincludes -Iincludes/CLI -Iincludes/Core -Iincludes/GUI -Iincludes/Core/DataStructures -Iincludes/Core/Utilities -Iincludes/GUI/Core -Iincludes/GUI/SceneElement -Iincludes/GUI/Scene -Iincludes/GUI/SceneManager `find src -name "*.c"` -lcurl -ltidy -lncurses

clean:
	rm -rf bin