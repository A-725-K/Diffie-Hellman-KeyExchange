CC = g++
FLAGS = -lpthread -Wall -pedantic -O2
COMMON = utils.cpp math.cpp diffie_hellman.h

S = server
C = client

BIN_DIR = bin
TESTS_DIR = tests

all: server client

server: $(BIN_DIR)
	$(CC) main_$(S).cpp $(S).cpp $(S).h $(COMMON) -o $(BIN_DIR)/$(S) $(FLAGS)
client: $(BIN_DIR)
	$(CC) main_$(C).cpp $(C).cpp $(C).h $(COMMON) -o $(BIN_DIR)/$(C) $(FLAGS)

test:
	./$(TESTS_DIR)/tst.sh

$(BIN_DIR):
	mkdir $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR)
	rm -rf $(TESTS_DIR)/figure.png
