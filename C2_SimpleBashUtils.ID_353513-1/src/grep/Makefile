CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

SRC = s21_grep.c line_matches.c output.c parse_flags.c process_files.c raise_flag.c 
BIN = s21_grep
TEST_DIR = src/testTXT

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(BIN)

clean:
	rm -f $(BIN)

re: clean all
