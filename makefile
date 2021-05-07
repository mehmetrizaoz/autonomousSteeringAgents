vpath %.cpp src
vpath %.h include
CC := g++

CPPFLAGS = -I include
objects := pvector.o graphics.o agent.o flowField.o main.o \
           point.o path.o color.o steeringBehavior.o random.o
LIBS = -lglut -lGLU -lGL

all: agents

agents: $(objects)
	$(CC) $^ -o $@ $(LIBS)

%.o: %.c
	$(CC) $(CPPFLAGS) -c $<

.PHONY: clean help
clean:
	rm agents $(objects)

help:
	@echo "make"
	@echo "make clean"
