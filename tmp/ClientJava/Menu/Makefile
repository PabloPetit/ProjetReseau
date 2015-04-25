SOURCES=main.c menu.c
OBJECTS =$(SOURCES:.c=.o)
CFLAGS= -std=c99 -std=gnu99 -Wall -g -lncurses
EXECUTABLE=main

$(EXECUTABLE): $(OBJECTS)
	gcc -o $(EXECUTABLE) $(OBJECTS)

%.o : %.c
	gcc -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) 

cleanall:
	rm -f $(EXECUTABLE) $(OBJECTS) 