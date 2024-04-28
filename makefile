CC = gcc
CFLAGS = -Iinclude

SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c,obj/%.o,$(SRCS))

obj/%.o: src/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

app : $(OBJS)
	@$(CC) $(CFLAGS) $^ -o app

.PHONY: clean m

clean:
	@rm -f $(OBJS) main.o app 