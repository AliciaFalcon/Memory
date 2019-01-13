but : memory

OFILES = menu.o \
		 interface.o \
		 main.o	

CC = gcc
CFLAGS = -Wall -ansi -pedantic

#Dépendances :

interface.o : interface.h

menu.o : menu.h interface.h

main.o : menu.h interface.h

#Dependances commandes :	

memory : $(OFILES)
	$(CC) $(CFLAGS) -o memory $(OFILES) -lgraph

#Exécution

run:
	./memory	

#Nettoyage :

clean :
	-rm -f $(OFILES) memory

#Buts :

.PHONY : but clean