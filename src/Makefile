#
# Makefile
# Defines compilation rules.
#
# inedito
#

# Configuration

CC        = gcc
CFLAGS    = -g -Wall
LIBS      = -lm

DIRECTORY = ../bin/
TARGET    = 19

# Rules

.PHONY    : default all clean

all       : default
default   : $(TARGET)

HEADERS   = $(wildcard *.h)
OBJECTS   = $(patsubst %.c, %.o, $(wildcard *.c))

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS : $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@
	-rm -f *.o
	-mv $(TARGET) $(DIRECTORY)

clean:
	-rm -f $(DIRECTORY)*
