TARGET = temperatura

CC = gcc
CFLAGS = -Wall -Wextra -I./include

OBJ = main.o temperatura.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

main.o: main.c include/temperatura.h
	$(CC) $(CFLAGS) -c main.c -o main.o

temperatura.o: temperatura.c include/temperatura.h
	$(CC) $(CFLAGS) -c temperatura.c -o temperatura.o

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean