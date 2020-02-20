CXX		  := g++
CXX_FLAGS := -Wall -std=c++11

BUILD		:= build
SRC			:= src
INCLUDE		:= include
EXTERNAL	:= external
LDFLAGS		:= -L$(EXTERNAL)

LIBRARIES	:= -lSDL2 -lSDL2_image -lexpedition
EXECUTABLE	:= army-game


all: $(BUILD)/$(EXECUTABLE)

run: clean all
	clear
	./$(BUILD)/$(EXECUTABLE)

$(BUILD)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -I$(EXTERNAL) $(LDFLAGS) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BUILD)/*
