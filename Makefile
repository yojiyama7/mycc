CC      := cc
CFLAGS  := -std=c11 -Wall -Wextra -Werror -Wimplicit-fallthrough -g -static
LDFLAGS := 
NAME := mycc
SRCS := main.c \
        parse.c \
        codegen.c
OBJS := $(addprefix objs/, $(SRCS:.c=.o))

.PHONY: all
all: $(NAME)

.PHONY: run
run: $(NAME)
	./$(NAME)

.PHONY: clean
clean:
	rm -f $(NAME) *.o objs/* *.out *~ tmp*

.PHONY: re
re:
	$(MAKE) clean
	$(MAKE) all

.PHONY: test
test: $(NAME)
	./test.sh

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

$(OBJS): mycc.h

objs/%.o: %.c
	mkdir -p objs
	$(CC) $(CFLAGS) -o $@ -c $<