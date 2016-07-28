
all	:
		(cd src && make)

clean	:
		rm -f *~ \#*\# val_report.* *.core
		(cd src && make clean)

fclean	:
		rm -f *~ \#*\# val_report.* *.core
		(cd src && make fclean)

re	:
		rm -f *~ \#*\# val_report.* *.core
		(cd src && make re)

fclib	:
		cd lib && make fclean

relib	:
		cd lib && make re

allclean:	fclean fclib

rere	:	relib re

clcl	:	fclean
		cd lib && make fclean
		rm -f $(NAME)

chmod	:
		find . -type d -exec chmod 700 {} \;
		find . -type f -exec chmod 600 {} \;
