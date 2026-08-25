CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

all: testing

testing: src/testing.cpp
	@echo "---"
	@echo "Compiling testing.cpp"

	$(CXX) $(CXXFLAGS) src/testing.cpp -o testing

	@echo "Finished compiling testing.cpp"

clean:
	rm -f ./testing

.PHONY: all clean
