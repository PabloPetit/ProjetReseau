SOURCES=main.c diffuseur.c messages.c server_tcp.c menu.c menu_principal.c getch.c saisie.c gestionnaire.c

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
