SOURCES=main.c menu.c getch.c menu_principal.c saisie.c gestionnaire.c diffuseur.c lecteur.c
OBJECTS =$(SOURCES:.c=.o)
CFLAGS= -Wall -g  -pthread
EXECUTABLE=main

$(EXECUTABLE): $(OBJECTS)
	gcc $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS)

%.o : %.c
	gcc -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) 

cleanall:
	rm -f $(EXECUTABLE) $(OBJECTS) 
