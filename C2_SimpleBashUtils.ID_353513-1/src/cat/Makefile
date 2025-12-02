CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

SRC = s21_cat.c flag_v.c flags_left.c parse_flags.c process_files.c raise_flag.c 
BIN = s21_cat
TEST_DIR = src/testTXT

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(BIN)

clean:
	rm -f $(BIN)

re: clean all

test:
	bash test_cat.sh