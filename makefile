vpath %.cpp src
vpath %.h include
CC := g++

CPPFLAGS = -I include
objects := pvector.o graphics.o agent.o flowField.o main.o \
           point.o path.o color.o steeringBehavior.o random.o \
		   obstacle.o scenario.o mouseFollower.o prison.o \
		   windy.o wander.o pursuit.o flee.o evade.o flock.o \
           pathFollower.o 
		   
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
