target= main.o header.o header_inc.o comment_rem.o macro_rep1.o
CC= cc 
exe: $(target)
	$(CC) $(target) -o mypreprocessor
main.o: main.c
	$(CC) -c $^
header.o: header.c
	$(CC) -c $^
header_inc.o: header_inc.c
	$(CC) -c $^
comment_rem.o: comment_rem.c
	$(CC) -c $^
macro_rep1.o: macro_rep1.c
	$(CC) -c $^
clear:
	@echo "cleaning up..."
	@rm -vr *.o
 
