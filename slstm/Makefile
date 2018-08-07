CC = g++
CFLAGS = -std=c++11 -Wall -g -O0
INCLUDE = -I ./include
SRC_DIR = ./src
SRC = $(wildcard $(SRC_DIR)/*.cpp)

TARGET_DIR = ./bin

all: stm test_bin

test: stm test_bin
	$(TARGET_DIR)/stm < $(TARGET_DIR)/stmbin.o

stm: $(SRC)
	mkdir -p $(TARGET_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(TARGET_DIR)/stm $(SRC_DIR)/slstm.cpp

test_bin: $(SRC)
	mkdir -p $(TARGET_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(TARGET_DIR)/test_bin_gen $(SRC_DIR)/test_bin_gen.cpp
	$(TARGET_DIR)/test_bin_gen $(TARGET_DIR)/stmbin.o

clean:
	rm -rf $(TARGET_DIR)
