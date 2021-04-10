vpath %.cc src
vpath %.h include
CC := g++

CPPFLAGS = -I include
objects := main.o
LIBS = -lglut -lGLU -lGL

all: exec

exec: $(objects)
	$(CC) $^ -o $@ $(LIBS)

%.o: %.c
	$(CC) $(CPPFLAGS) -c $<

.PHONY: clean help
clean:
	rm exec $(objects)

help:
	@echo "make"
	@echo "make clean"
