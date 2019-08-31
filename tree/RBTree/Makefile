all:insert.cc RBNodeImpl.cc RBTree.h rotate.cc test.cc test.h remove.cc
	test -d bin || mkdir bin
	g++ -g -std=c++11 -o bin/insert.o -c insert.cc
	g++ -g -std=c++11 -o bin/RBNodeImpl.o -c RBNodeImpl.cc
	g++ -g -std=c++11 -o bin/test.o -c test.cc
	g++ -g -std=c++11 -o bin/main.o -c main.cc
	g++ -g -std=c++11 -o bin/rotate.o -c rotate.cc
	g++ -g -std=c++11 -o bin/remove.o -c remove.cc
	g++ -o main bin/insert.o bin/RBNodeImpl.o bin/test.o bin/main.o bin/rotate.o bin/remove.o

clean:
	-rm -rf bin
	-rm main