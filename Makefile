test: test.cpp
	clang++ -std=c++1y test.cpp -o ./test.o
	./test.o

clean:
	rm -rf ./test.o