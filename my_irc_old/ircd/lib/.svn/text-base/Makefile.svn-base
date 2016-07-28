
all:
	cd hash && make
	cd read_lib && make
	cd conf_parser && make

clean:
	cd hash && make clean
	cd read_lib && make clean
	cd conf_parser && make clean

fclean:
	cd hash && make fclean
	cd read_lib && make fclean
	cd conf_parser && make fclean
	rm -f *.a

re: fclean all
