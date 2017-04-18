BIN = bin
INC = include
LIB = lib
OBJ = obj
SRC = src

CXX = g++
CPPFLAGS = -Wall -g -c -std=c++11 -I$(INC)

all : $(BIN)/main

$(BIN)/main : $(OBJ)/main.o $(LIB)/libgame.a
	$(CXX) -o $@ $^

$(OBJ)/main.o : $(SRC)/main.cpp $(INC)/game.h
	$(CXX) $(CPPFLAGS) -o $@ $<

# Bibliotecas

$(LIB)/libgame.a : $(OBJ)/game.o
	ar -rvs $@ $^

$(OBJ)/game.o : $(SRC)/game.cpp $(INC)/game.h
	$(CXX) $(CPPFLAGS) -o $@ $<

