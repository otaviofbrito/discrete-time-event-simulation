CC = gcc
CFLAGS = -Wall -Iinclude
LDFLAGS = -lm
SRC = src/main.c src/metrics.c src/little.c
OBJ_DIR = object
OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

all: main

# Cria o diretório de objetos, se não existir
$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

main: $(OBJ)
	$(CC) -o main $(OBJ) $(LDFLAGS)

clean:
	rm -rf $(OBJ_DIR) main
	rm -rf ./data/*.csv
