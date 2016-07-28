##
## Makefile for my_ftp in /u/all/sarazi_t/cu/rendu/c/my_ftp
##
## Made by tugdual sarazin
## Login   <sarazi_t@epitech.net>
##
## Started on  Fri Nov  7 23:29:34 2008 tugdual sarazin
## Last update Tue Mar 10 18:45:34 2009 tugdual sarazin
##

CC		=	gcc

CFLAGS		+=	-I. -W -Wall -ansi -pedantic
RM		=	rm -f

NAME_SERV	=	server
SRC_SERV	=	server.c		\
			serv_client.c		\
			serv_listc.c		\
			serv_connexion.c
OBJ_SERV	=	$(SRC_SERV:.c=.o)
TMP_SERV	=	$(SRC_SERV:.c=.c~)

NAME_CLIENT	=	client
SRC_CLIENT	=	client.c
OBJ_CLIENT	=	$(SRC_CLIENT:.c=.o)
TMP_CLIENT	=	$(SRC_CLIENT:.c=.c~)


##$(NAME_SERV)	: $(OBJ_SERV)
##		$(CC) -o $(NAME_SERV) $(OBJ_SERV)

$(NAME_CLIENT)	: $(OBJ_CLIENT)
		$(CC) -o $(NAME_CLIENT) $(OBJ_CLIENT)


all	: $(NAME_CLIENT)

clean	:
	$(RM) $(OBJ_SERV)
	$(RM) $(OBJ_CLIENT)

fclean	: clean
	$(RM) $(TMP_SERV)
	$(RM) $(TMP_CLIENT)
	$(RM) $(NAME_SERV)
	$(RM) $(TMP_CLIENT)

re	: fclean all

.PHONY : all clean fclean re