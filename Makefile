test: test.cpp
	$(CXX) -std=c++1y -lpthread test.cpp -o ./test.o
	./test.o

clean:
	rm -rf ./test.o