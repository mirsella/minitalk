SRCS = client.c server.c
OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -g3
NAME = minitalk

all: $(NAME)

$(NAME): libft client server

client: client.o libft.a
	$(CC) $(CFLAGS) -o client client.o libft/libft.a
	
server: server.o libft.a
	$(CC) $(CFLAGS) -o server server.o libft/libft.a

libft.a:
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
