test: test.cpp
	clang++ -pthread -std=c++1y test.cpp -o ./test.o
	./test.o

clean:
	rm -rf ./test.o