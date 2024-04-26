CC = gcc
CFLAGS = -Iinclude

SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c,obj/%.o,$(SRCS))

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	$(CC) $(CFLAGS) -c main.c -o main.o

app : $(OBJS) main.o
	$(CC) $(CFLAGS) $^ -o app

.PHONY: clean m

clean:
	rm -f $(OBJS) main.o app 