CALGS=-Wall -g

all:
	mkdir -p ./bin
	gcc -Wall -pedantic ex.c -g -o ./bin/ex
val:
	valgrind ./bin/ex

clean:
	rm -rf ./bin/*

run:
	./bin/ex
