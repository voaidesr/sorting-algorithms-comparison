CXX = g++
CXXFLAGS = -O2 -std=c++17 -Wall
TARGET = main
SRCS = main.cpp sorts.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	@$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	@rm -f $(TARGET)
