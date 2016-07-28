##
## Makefile for my_ftp in /u/all/sarazi_t/cu/rendu/c/my_ftp
##
## Made by tugdual sarazin
## Login   <sarazi_t@epitech.net>
##
## Started on  Fri Nov  7 23:29:34 2008 tugdual sarazin

##

CC		=	gcc

INC		=	-I.
CFLAGS		=	-I. -W -Wall -ansi -pedantic
##CFLAGS		+=	$(INC) $(OPT)
RM		=	rm -f

NAME_SERV	=	server
SRC_SERV	=	server.c		\
			serv_client.c		\
			serv_listc.c		\
			serv_connexion.c	\
			serv_func.c		\
			mylib.c
OBJ_SERV	=	$(SRC_SERV:.c=.o)
TMP_SERV	=	$(SRC_SERV:.c=.c~)

$(NAME_SERV)	: $(OBJ_SERV)
		$(CC) -o $(NAME_SERV) $(OBJ_SERV)

all	: $(NAME_SERV)

clean	:
	$(RM) $(OBJ_SERV)

fclean	: clean
	$(RM) $(TMP_SERV)
	$(RM) $(NAME_SERV)

re	: fclean all

.PHONY : all clean fclean re