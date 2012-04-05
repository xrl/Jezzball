all : jezzball

jezzball: main.c main.o draw.o jball.o jwall.o constants.o
	gcc main.o draw.o jball.o jwall.o constants.o -o jezzball
	
main.o : main.c constants.h
	gcc -c main.c
	
draw.o : draw.c draw.h constants.h
	gcc -c draw.c
	
jball.o : jball.c jball.h constants.h
	gcc -c jball.c
	
jwall.o : jwall.c jwall.h constants.h
	gcc -c jwall.c
	
constants.o : constants.h constants.c
	gcc -c constants.c
	
clean:
	rm -rf *.o jezzball