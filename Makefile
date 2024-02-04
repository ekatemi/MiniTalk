NAME = server client
SERVER = server
CLIENT = client	
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I.
SRCS = server.c client.c aux.c
OBJS = $(SRCS:.c=.o)

all : $(SERVER) $(CLIENT)

bonus : all

$(CLIENT) : client.o aux.o
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

$(SERVER) : server.o aux.o
	 $(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

%.o: %.c $(SRCS) minitalk.h Makefile
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean : 
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)


re : fclean all

.PHONY : clean fclean re all bonus