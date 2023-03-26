CC = gcc
EXEC = Gestion


$(EXEC):main.o function-bd.o saisie.o
	$(CC)  main.o function-bd.o saisie.o -o $@ -I/usr/include/python3.10 `mysql_config --cflags --libs` -lpython3.10 

main.o:main.c 
	$(CC)  -o main.o -c main.c -I/usr/include/python3.10 `mysql_config --cflags --libs` -lpython3.10

function-bd.o:function-bd.c
	$(CC) -c function-bd.c `mysql_config --cflags --libs` -o function-bd.o 

saisie.o:saisie.c
	$(CC) -o saisie.o -c saisie.c

clean:
	rm -rf *.o


# variable speciales
#$@ nom cible
#$< nom premier dépendance
#$^ liste dépendance
#$? liste dépendance plus récente que la cible