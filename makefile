CXX = g++
CXXFLAGS = -O2 -std=c++17 -Wall -Wextra
TARGET = bin/main
INCLUDE = include
SRC = src

all: $(TARGET)

$(TARGET): $(SRC)/main.cpp $(SRC)/quick_sort.cpp $(SRC)/merge_sort.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) $^ -o $@

clean:
	rm -f $(TARGET)