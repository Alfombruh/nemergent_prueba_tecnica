NAME = nemergent
CC = gcc
CFLAGS = -Werror -Wall -Wextra -I ./includes
FILES = srcs/main
SRCS = $(addsuffix .c, $(FILES))
OBJS = $(addsuffix .o, $(FILES))

%.o: %.c 
	$(CC) $(CFLAGS) -c $^ -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

sanitize:
	$(eval CFLAGS += -fsanitize=address -g3)

sani: sanitize all

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re sani sanitize