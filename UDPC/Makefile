SOURCES=main.c diffuseur.c messages.c server_tcp.c menu.c menu_principal.c getch.c
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
