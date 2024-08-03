all:run

BIN_DIR=bin
EXEC_NAME=SpaceInvaders
EXEC=$(BIN_DIR)/$(EXEC_NAME)

SRC_DIR=src
LANG=cpp
SRC=$(wildcard $(SRC_DIR)/*.$(LANG))

CC=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++23 -g
LDFLAGS=-lraylib

bin_dir:
	mkdir -p $(BIN_DIR)

build:bin_dir $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC) $(LDFLAGS)

run:build
	$(EXEC)
