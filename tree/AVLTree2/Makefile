all: AVLtree.h insert.cc main.cc rotation.cc test.h test.cc fixup.cc
	test -d bin || mkdir bin
	g++ -g -std=c++11 -o bin/insert.o -c insert.cc
	g++ -g -std=c++11 -o bin/main.o -c main.cc
	g++ -g -std=c++11 -o bin/rotation.o -c rotation.cc
	g++ -g -std=c++11 -o bin/test.o -c test.cc
	g++ -g -std=c++11 -o bin/fixup.o -c fixup.cc
	g++ -g -std=c++11 -o bin/remove.o -c remove.cc
	g++ -o main bin/rotation.o bin/insert.o bin/main.o bin/test.o bin/fixup.o bin/remove.o

clean:
	-rm -rf bin
	-rm main