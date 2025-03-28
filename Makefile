# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Werror -Wextra -pedantic -g -fsanitize=address -fno-omit-frame-pointer
# Google Test flags
GTEST_FLAGS = -lgtest -lgtest_main -pthread
# Target executable
TARGET = unit_test
# Source files
SRCS = $(wildcard *.cc)
HEADERS = $(wildcard *.h)
# Object files
OBJS = $(SRCS:.cc=.o)
# Default target
all: $(TARGET)
# Linking the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_FLAGS)
# Compiling source files
%.o: %.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@
# Clean target
clean:
	rm -f $(TARGET) $(OBJS) 
.PHONY: all clean