CC = gcc
CFLAGS = -Wall -Wextra -IInc
LDFLAGS = -lssl -lcrypto
TARGET = file_transfer

SRC = $(wildcard Src/*.c)
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

Src/%.o: Src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f Src/*.o $(TARGET)

re: clean all

