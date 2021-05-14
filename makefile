vpath %.cpp src
vpath %.h include
CC := g++

CPPFLAGS = -I include
objects := pvector.o graphics.o agent.o flowField.o main.o \
           point.o path.o color.o steeringBehavior.o random.o \
		   obstacle.o scenario.o mouseFollower.o prison.o \
		   windy.o wander.o pursuit.o flee.o evade.o flock.o \
           pathFollower.o obstacleAvoidance.o
		   
LIBS = -lglut -lGLU -lGL

all: exec

exec: $(objects)
	$(CC) $^ -o $@ $(LIBS)
	mv exec build
	mv *.o build

%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $<
	

.PHONY: clean help
clean:
	rm build/exec build/*.o

help:
	@echo "make"
	@echo "make clean"
