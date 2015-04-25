SOURCES=main.c menu.c getch.c menu_principal.c saisie.c
OBJECTS =$(SOURCES:.c=.o)
CFLAGS= -std=c99 -std=gnu99 -Wall -g -pedantic
EXECUTABLE=main

$(EXECUTABLE): $(OBJECTS)
	gcc -o $(EXECUTABLE) $(OBJECTS)

%.o : %.c
	gcc -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) 

cleanall:
	rm -f $(EXECUTABLE) $(OBJECTS) 