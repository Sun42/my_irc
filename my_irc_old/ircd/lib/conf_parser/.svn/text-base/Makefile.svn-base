
NAME	=	parse_conf_$(OSTYPE)_$(MACHTYPE)

SRC	= \
		init_parse.c			\
		parse_conf.c			\
		clean_str.c			\
		get_var_name.c			\
		misc_def_funcs.c		\
		get_def_funcs.c

OBJ	=	$(SRC:.c=.o)

CC	=	gcc

IPATH	=	-I. -I../../include

CFLAGS	=	-O2 $(IPATH) -Wall -W -Werror -ansi -pedantic -D$(OSTYPE)

TESTSRC	=	test.c

INCPATH =	../../include/

LIBPATH =	../

INCNAME =	conf_parser.h

TESTSRC	=	test.c

all     :       $(NAME)

$(NAME) :       $(OBJ)
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
		$(CC) -o test $(TESTSRC) $(IPATH) -L. -l$(NAME) -L../ -lhash_$(OSTYPE)_$(MACHTYPE) -l read_file_$(OSTYPE)_$(MACHTYPE)
