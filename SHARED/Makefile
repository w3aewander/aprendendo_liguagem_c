
CC = gcc
CFLAGS = -Wall -Wextra -fPIC -Iinclude

LIB = lib/libminha_lib.so
PROGRAMA = programa

.PHONY: all run clean

all: $(PROGRAMA)

$(LIB): src/minha_lib.c include/minha_lib.h
	mkdir -p lib
	$(CC) $(CFLAGS) -shared -o $@ $<

$(PROGRAMA): src/main.c $(LIB)
	$(CC) $(CFLAGS) -o $@ $< \
	-L./lib -lminha_lib \
	-Wl,-rpath,'$$ORIGIN/lib'

run: $(PROGRAMA)
	./$(PROGRAMA)

clean:
	rm -f $(PROGRAMA) $(LIB)

