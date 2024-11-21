#Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

#target binary
TARGET = tetris

#Directories 
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

#Source files and object files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

#Include directories
INCLUDES = -Iinclude -Isrc

#Libraries
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

#Default rule
all: $(BIN_DIR)/$(TARGET)

#Rule to build the target
$(BIN_DIR)/$(TARGET):$(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)
	@echo "Build succeessful!"

#Rule to build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

#Clean build artifcats
clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Cleaned up build files!"

#Run the game
run: all
	./$(BIN_DIR)/$(TARGET)

.PHONY: all clean run