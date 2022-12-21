SRCS = client.c server.c
OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = minitalk

all: $(NAME)

$(NAME): libft client server

client: client.o libft
	$(CC) $(CFLAGS) -o client client.o -Llibft -lft
	
server: server.o libft
	$(CC) $(CFLAGS) -o server server.o -Llibft -lft

libft:
	make -C libft

clean:
	make -C libft clean
	rm -f $(OBJS)

fclean: clean
	make -C libft fclean
	rm -f client server

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus libft.a client server
