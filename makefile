CC = gcc
CFLAGS = -Iinclude

SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c,obj/%.o,$(SRCS))

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

app : $(OBJS) main.o
	$(CC) $(CFLAGS) $^ -o app

.PHONY: clean m

clean:
	rm -f $(OBJS) app 

m: main.c
	$(CC) $(CFLAGS) -c $< -o main.o