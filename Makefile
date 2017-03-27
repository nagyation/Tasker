CC=gcc
CFLAGS= -c -Wall
LDFLAGS= 
SOURCES= tasker.c listmanager.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=tasker

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm $(OBJECTS) $(EXECUTABLE)
