
NAME	=	hash_$(OSTYPE)_$(MACHTYPE)

SRC	=	hash.c			\
		hash_free.c		

OBJ	=	$(SRC:.c=.o)

CC      =       gcc

IPATH   =       -I.

LIB     =       -L.

CFLAGS  =       $(IPATH) -Wall -W -Werror -ansi -pedantic

TESTSRC	=	test.c

INCPATH =	../../include/

LIBPATH =	../

INCNAME =	libhash.h

all     :       $(NAME)

$(NAME) :       $(OBJ)
		$(CC) -c $(SRC) $(IPATH)
		ar -r lib$(NAME).a $(OBJ)
		ranlib lib$(NAME).a                
		cp lib$(NAME).a $(LIBPATH)
		cp $(INCNAME) $(INCPATH)

clean   :
		rm -f test
		rm -f *.o
		rm -f *~
		rm -f \#*\#

fclean  :       clean
		rm -f lib$(NAME).a

re      :       fclean all

test	:	$(NAME)
		$(CC) -o test $(TESTSRC) -L. -l$(NAME)
