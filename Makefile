CC=gcc
CFLAGS= -c -Wall -g
LDFLAGS= -l sqlite3
SOURCES= tasker.c taskmanager.c taskerdb.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=tasker

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm $(OBJECTS) $(EXECUTABLE)
