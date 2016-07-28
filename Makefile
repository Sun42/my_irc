CC = gcc
NAME = client
SRC = client.c \
	graphics.c \
	connect.c \
	cmd.c \
	cmd2.c \
	cli_utils.c \
	do_select.c \
	buffer.c \
	ord.c
OBJ = $(SRC:.c=.o)
CFLAGS += -W -Wall -ansi -pedantic
LDFLAGS = `pkg-config --cflags --libs gtk+-2.0`
RM = rm -f


$(NAME) : 
	$(CC) -c $(SRC) $(LDFLAGS)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean $(NAME)

all : $(NAME)
