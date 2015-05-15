SOURCES=main.c menu.c getch.c menu_principal.c saisie.c gestionnaire.c diffuseur.c
OBJECTS =$(SOURCES:.c=.o)
CFLAGS= -std=c99 -std=gnu99 -Wall -g  -pthread
EXECUTABLE=main

$(EXECUTABLE): $(OBJECTS)
	gcc -o $(EXECUTABLE) $(OBJECTS)

%.o : %.c
	gcc -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) 

cleanall:
	rm -f $(EXECUTABLE) $(OBJECTS) 
