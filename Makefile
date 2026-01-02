MAKEFLAGS := -rR

CC      := cc
CFLAGS  := -std=c11 -Wall -Wextra -Werror -Wimplicit-fallthrough -g -static
LDFLAGS := 
NAME := mycc
SRCS := main.c \
        parse.c \
				type.c \
        codegen.c \
				for_debug.c
OBJS := $(addprefix objs/, $(SRCS:.c=.o))

.PHONY: all
all: $(NAME)

.PHONY: run
run: $(NAME)
	./$(NAME)

.PHONY: clean
clean:
	rm -f *.o objs/* *.out *~ tmp*

.PHONY: fclean
fclean:
	$(MAKE) clean
	rm -f $(NAME)

.PHONY: re
re:
	$(MAKE) clean
	$(MAKE) all

.PHONY: test
test: $(NAME)
	./test.sh
#	@$(MAKE) --silent clean

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

$(OBJS): mycc.h

objs/%.o: %.c
	mkdir -p objs
	$(CC) $(CFLAGS) -o $@ -c $<
