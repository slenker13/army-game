CXX		  := g++
CXX_FLAGS := -Wall

BUILD	:= build
SRC		:= src
INCLUDE	:= include
ENGINE	:= external/expedition-engine
LDFLAGS	:= -Lexternal

LIBRARIES	:= -lSDL2 -lSDL2_image -lexpedition
EXECUTABLE	:= army-game


all: $(BUILD)/$(EXECUTABLE)

run: clean all
	clear
	./$(BUILD)/$(EXECUTABLE)

$(BUILD)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -I$(ENGINE) $(LDFLAGS) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BUILD)/*
