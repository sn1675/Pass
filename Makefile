# ==== Compiler ====
CXX	= g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./src -I./json

# ==== Directory ====
SRC_DIR = src
BUILD_DIR = build

# ==== Files ====
SRC = main.cpp $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:%.cpp=$(BUILD_DIR)/%.o)

TARGET = $(BUILD_DIR)/main

# ==== Rules ====
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

re: clean all

.PHONY: all clean re
