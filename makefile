vpath %.cpp src
vpath %.h include
CC := g++

CPPFLAGS = -I include
objects := pvector.o agent.o flowField.o main.o graphics.o point.o
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
