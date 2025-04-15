CXX = g++
CXXFLAGS = -O2 -std=c++17 -Wall -Wextra
TARGET = bin/main
INCLUDE = include
SRC = src

all: $(TARGET)

$(TARGET): $(SRC)/main.cpp $(SRC)/quick_sort.cpp $(SRC)/merge_sort.cpp $(SRC)/radix_sort.cpp $(SRC)/intro_sort.cpp $(SRC)/shell_sort.cpp $(SRC)/test_utils.cpp $(SRC)/tim_sort.cpp
	@mkdir -p bin
	@$(CXX) $(CXXFLAGS) -I$(INCLUDE) $^ -o $@
bin/visualizer: $(SRC)/visualizer.cpp $(SRC)/quick_sort.cpp $(SRC)/merge_sort.cpp $(SRC)/radix_sort.cpp $(SRC)/test_utils.cpp $(SRC)/intro_sort.cpp $(SRC)/shell_sort.cpp $(SRC)/tim_sort.cpp
	@mkdir -p bin
	@$(CXX) $(CXXFLAGS) -I$(INCLUDE) $^ -o $@
clean:
	@rm -rf bin
