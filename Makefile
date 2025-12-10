CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -g
SRCS := $(wildcard src/*.cpp)
TARGET := sim

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
