all:
	mkdir -p build
	mkdir -p build/lib
	mkdir -p build/lib/release
	mkdir -p build/objects
	g++ src/linkedlist.c -c
	g++ src/lib.cpp -c
	ar rs libhashset.a lib.o linkedlist.o
	mv libhashset.a build/lib/release
	ar rs libhashset.so lib.o linkedlist.o
	mv libhashset.so build/lib/release
	g++ -g test/test.cpp -c
	g++ -g -o main test.o build/lib/release/libhashset.a
	mkdir -p build/bin
	mv main build/bin
	mv *.o build/objects

static:
	mkdir -p build
	mkdir -p build/lib
	mkdir -p build/lib/release
	mkdir -p build/objects
	g++ src/linkedlist.c -c
	g++ src/lib.cpp -c
	ar rs libhashset.a lib.o linkedlist.o
	mv libhashset.a build/lib/release
	mv *.o build/objects

shared:
	mkdir -p build
	mkdir -p build/lib
	mkdir -p build/lib/release
	mkdir -p build/objects
	g++ src/linkedlist.c -c
	g++ src/lib.cpp -c
	ar rs libhashset.so lib.o linkedlist.o
	mv libhashset.so build/lib/release
	mv *.o build/objects

debug:
	mkdir -p build
	mkdir -p build/lib
	mkdir -p build/lib/release
	mkdir -p build/objects
	g++ -g src/linkedlist.c -c
	g++ -g src/lib.cpp -c
	ar rs libhashset.a lib.o linkedlist.o
	mv libhashset.a build/lib/release
	ar rs libhashset.so lib.o linkedlist.o
	mv libhashset.so build/lib/release
	mv *.o build/objects

clean:
	rm -rf build

install:
	g++ src/linkedlist.c -c
	g++ src/lib.cpp -c
	ar rs libhashset.so lib.o linkedlist.o
	mv libhashset.so /usr/lib

tests:
	g++ -g test/test.cpp -c
	g++ -g -o main test.o build/lib/release/libhashset.a
	mv *.o build/objects
	mkdir -p build/bin
	mv main build/bin