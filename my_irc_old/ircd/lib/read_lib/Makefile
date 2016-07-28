
NAME	=	read_file_$(OSTYPE)_$(MACHTYPE)

SRC	=	open_file.c		\
		close_file.c		\
		get_line.c

OBJ	=	$(SRC:.c=.o)

CC      =       gcc

IPATH   =       -I.

LIB     =       -L.

CFLAGS  =       $(IPATH) -Wall -W -Werror -ansi -pedantic -ggdb -DDEBUG

TESTSRC	=	test.c

INCPATH =	../../include/

LIBPATH =	../

INCNAME =	readlib.h

all     :       $(NAME)

$(NAME) :       
		$(CC) -c $(SRC) $(IPATH)
		ar -r lib$(NAME).a $(OBJ)
		ranlib lib$(NAME).a                
		cp lib$(NAME).a $(LIBPATH)
		cp $(INCNAME) $(INCPATH)

clean   :
		rm -f *.o
		rm -f *~
		rm -f \#*\#
		rm -f test

fclean  :       clean
		rm -f lib$(NAME).a

re      :       fclean all

test	:	$(NAME)
		$(CC) -o test $(TESTSRC) -L. -l$(NAME)
