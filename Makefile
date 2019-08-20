test: test.cpp
	$(CXX) -std=c++1y test.cpp -o ./out/test.o
	./out/test.o

clean:
	rm -rf ./out