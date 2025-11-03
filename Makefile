CXX ?= g++
CXXFLAGS ?= -O2 -pipe -std=gnu++17
LDFLAGS ?=

SRC := main.cpp
HDR := game.h
BIN := code

all: $(BIN)

$(BIN): $(SRC) $(HDR)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(BIN) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(BIN) *.o
